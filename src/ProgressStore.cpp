#include "ProgressStore.h"

#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QtGlobal>
#include <utility>

namespace
{
    bool execSql(QSqlQuery& query, const QString& sql)
    {
        return query.exec(sql);
    }

    QString escapePipe(QString text)
    {
        return text.replace("|", "\\|").replace("\n", " ");
    }
}

ProgressStore::ProgressStore(QString databasePath)
    : m_databasePath(std::move(databasePath))
    , m_connectionName(QString("cs_bootcamp_progress_%1").arg(reinterpret_cast<quintptr>(this)))
{
}

ProgressStore::~ProgressStore()
{
    if (QSqlDatabase::contains(m_connectionName))
    {
        {
            QSqlDatabase db = QSqlDatabase::database(m_connectionName);
            db.close();
        }
        QSqlDatabase::removeDatabase(m_connectionName);
    }
}

void ProgressStore::load()
{
    openDatabase();
    createSchema();
    ensureDefaultProfile();
    reloadCaches();
}

void ProgressStore::save() const
{
    // SQLite writes each change as it happens. This method stays in the API so
    // older MainWindow code can keep calling save() without needing a rewrite.
}

void ProgressStore::openDatabase()
{
    QDir().mkpath(QFileInfo(m_databasePath).absolutePath());

    QSqlDatabase db = QSqlDatabase::contains(m_connectionName)
        ? QSqlDatabase::database(m_connectionName)
        : QSqlDatabase::addDatabase("QSQLITE", m_connectionName);

    db.setDatabaseName(m_databasePath);
    db.open();
}

void ProgressStore::createSchema()
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);

    execSql(query, "PRAGMA foreign_keys = ON");
    execSql(query, "CREATE TABLE IF NOT EXISTS learner_profiles ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "display_name TEXT NOT NULL UNIQUE, "
                   "target_role TEXT NOT NULL DEFAULT 'Junior Software Engineer', "
                   "created_at TEXT NOT NULL)");
    execSql(query, "CREATE TABLE IF NOT EXISTS completed_items ("
                   "profile_id INTEGER NOT NULL, "
                   "item_id TEXT NOT NULL, "
                   "completed_at TEXT NOT NULL, "
                   "PRIMARY KEY(profile_id, item_id), "
                   "FOREIGN KEY(profile_id) REFERENCES learner_profiles(id) ON DELETE CASCADE)");
    execSql(query, "CREATE TABLE IF NOT EXISTS item_notes ("
                   "profile_id INTEGER NOT NULL, "
                   "item_id TEXT NOT NULL, "
                   "notes TEXT NOT NULL, "
                   "updated_at TEXT NOT NULL, "
                   "PRIMARY KEY(profile_id, item_id), "
                   "FOREIGN KEY(profile_id) REFERENCES learner_profiles(id) ON DELETE CASCADE)");
    execSql(query, "CREATE TABLE IF NOT EXISTS study_events ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "profile_id INTEGER NOT NULL, "
                   "item_id TEXT NOT NULL, "
                   "event_type TEXT NOT NULL, "
                   "minutes INTEGER NOT NULL DEFAULT 0, "
                   "notes TEXT NOT NULL DEFAULT '', "
                   "created_at TEXT NOT NULL, "
                   "FOREIGN KEY(profile_id) REFERENCES learner_profiles(id) ON DELETE CASCADE)");
    execSql(query, "CREATE TABLE IF NOT EXISTS skill_mastery ("
                   "profile_id INTEGER NOT NULL, "
                   "skill_name TEXT NOT NULL, "
                   "mastery_percent INTEGER NOT NULL DEFAULT 0, "
                   "evidence TEXT NOT NULL DEFAULT '', "
                   "updated_at TEXT NOT NULL, "
                   "PRIMARY KEY(profile_id, skill_name), "
                   "FOREIGN KEY(profile_id) REFERENCES learner_profiles(id) ON DELETE CASCADE)");
    execSql(query, "CREATE TABLE IF NOT EXISTS code_attempts ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "profile_id INTEGER NOT NULL, "
                   "language TEXT NOT NULL, "
                   "exercise_id TEXT NOT NULL, "
                   "result TEXT NOT NULL, "
                   "created_at TEXT NOT NULL, "
                   "FOREIGN KEY(profile_id) REFERENCES learner_profiles(id) ON DELETE CASCADE)");
    execSql(query, "CREATE TABLE IF NOT EXISTS code_attempt_reviews ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "profile_id INTEGER NOT NULL, "
                   "language TEXT NOT NULL, "
                   "topic TEXT NOT NULL, "
                   "exercise_id TEXT NOT NULL, "
                   "difficulty TEXT NOT NULL, "
                   "command_text TEXT NOT NULL, "
                   "output_summary TEXT NOT NULL, "
                   "review_status TEXT NOT NULL, "
                   "review_notes TEXT NOT NULL, "
                   "created_at TEXT NOT NULL, "
                   "FOREIGN KEY(profile_id) REFERENCES learner_profiles(id) ON DELETE CASCADE)");
    execSql(query, "CREATE TABLE IF NOT EXISTS ai_provider_settings ("
                   "profile_id INTEGER NOT NULL, "
                   "provider_name TEXT NOT NULL, "
                   "endpoint TEXT NOT NULL DEFAULT '', "
                   "model_name TEXT NOT NULL DEFAULT '', "
                   "api_key_env TEXT NOT NULL DEFAULT '', "
                   "enabled INTEGER NOT NULL DEFAULT 0, "
                   "safety_notes TEXT NOT NULL DEFAULT '', "
                   "updated_at TEXT NOT NULL, "
                   "PRIMARY KEY(profile_id, provider_name), "
                   "FOREIGN KEY(profile_id) REFERENCES learner_profiles(id) ON DELETE CASCADE)");
    execSql(query, "CREATE TABLE IF NOT EXISTS ai_tutor_reviews ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "profile_id INTEGER NOT NULL, "
                   "provider_name TEXT NOT NULL, "
                   "mode TEXT NOT NULL, "
                   "language TEXT NOT NULL, "
                   "topic TEXT NOT NULL, "
                   "prompt_preview TEXT NOT NULL, "
                   "response_summary TEXT NOT NULL, "
                   "status TEXT NOT NULL, "
                   "created_at TEXT NOT NULL, "
                   "FOREIGN KEY(profile_id) REFERENCES learner_profiles(id) ON DELETE CASCADE)");

    execSql(query, "CREATE TABLE IF NOT EXISTS instructor_assignments ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "cohort_name TEXT NOT NULL, "
                   "assignment_title TEXT NOT NULL, "
                   "due_date TEXT NOT NULL, "
                   "rubric TEXT NOT NULL, "
                   "created_at TEXT NOT NULL, "
                   "UNIQUE(cohort_name, assignment_title))");
    execSql(query, "CREATE TABLE IF NOT EXISTS instructor_scores ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "cohort_name TEXT NOT NULL, "
                   "learner_name TEXT NOT NULL, "
                   "assignment_title TEXT NOT NULL, "
                   "score INTEGER NOT NULL, "
                   "feedback TEXT NOT NULL, "
                   "created_at TEXT NOT NULL)");
}

void ProgressStore::ensureDefaultProfile()
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery insert(db);
    insert.prepare("INSERT OR IGNORE INTO learner_profiles(display_name, target_role, created_at) VALUES(?, ?, ?)");
    insert.addBindValue("Default Learner");
    insert.addBindValue("Junior Software Engineer");
    insert.addBindValue(nowIso());
    insert.exec();

    QSqlQuery select(db);
    select.prepare("SELECT id FROM learner_profiles WHERE display_name = ?");
    select.addBindValue("Default Learner");
    if (select.exec() && select.next())
    {
        m_profileId = select.value(0).toInt();
    }
}

void ProgressStore::reloadCaches()
{
    m_completedItems.clear();
    m_notesByItem = QJsonObject{};

    QSqlDatabase db = QSqlDatabase::database(m_connectionName);

    QSqlQuery completed(db);
    completed.prepare("SELECT item_id FROM completed_items WHERE profile_id = ? ORDER BY item_id");
    completed.addBindValue(m_profileId);
    if (completed.exec())
    {
        while (completed.next())
        {
            m_completedItems.insert(completed.value(0).toString());
        }
    }

    QSqlQuery notes(db);
    notes.prepare("SELECT item_id, notes FROM item_notes WHERE profile_id = ? ORDER BY item_id");
    notes.addBindValue(m_profileId);
    if (notes.exec())
    {
        while (notes.next())
        {
            m_notesByItem.insert(notes.value(0).toString(), notes.value(1).toString());
        }
    }
}

bool ProgressStore::isCompleted(const QString& itemId) const
{
    return m_completedItems.contains(itemId);
}

void ProgressStore::setCompleted(const QString& itemId, bool completed)
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    if (completed)
    {
        QSqlQuery query(db);
        query.prepare("INSERT OR REPLACE INTO completed_items(profile_id, item_id, completed_at) VALUES(?, ?, ?)");
        query.addBindValue(m_profileId);
        query.addBindValue(itemId);
        query.addBindValue(nowIso());
        query.exec();
        m_completedItems.insert(itemId);
        recordStudyEvent(itemId, "completed", 20, "Marked complete inside the desktop app.");
    }
    else
    {
        QSqlQuery query(db);
        query.prepare("DELETE FROM completed_items WHERE profile_id = ? AND item_id = ?");
        query.addBindValue(m_profileId);
        query.addBindValue(itemId);
        query.exec();
        m_completedItems.remove(itemId);
        recordStudyEvent(itemId, "reopened", 0, "Marked incomplete for another review pass.");
    }
}

QString ProgressStore::notesFor(const QString& itemId) const
{
    return m_notesByItem.value(itemId).toString();
}

void ProgressStore::setNotesFor(const QString& itemId, const QString& notes)
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO item_notes(profile_id, item_id, notes, updated_at) VALUES(?, ?, ?, ?)");
    query.addBindValue(m_profileId);
    query.addBindValue(itemId);
    query.addBindValue(notes);
    query.addBindValue(nowIso());
    query.exec();
    m_notesByItem.insert(itemId, notes);
    recordStudyEvent(itemId, "notes", 5, "Saved study notes.");
}

int ProgressStore::completedCount() const
{
    return static_cast<int>(m_completedItems.size());
}

QString ProgressStore::databasePath() const
{
    return m_databasePath;
}

QString ProgressStore::activeProfileName() const
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT display_name FROM learner_profiles WHERE id = ?");
    query.addBindValue(m_profileId);
    if (query.exec() && query.next()) return query.value(0).toString();
    return "Default Learner";
}

int ProgressStore::notesCount() const
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM item_notes WHERE profile_id = ? AND length(notes) > 0");
    query.addBindValue(m_profileId);
    if (query.exec() && query.next()) return query.value(0).toInt();
    return 0;
}

int ProgressStore::studyEventCount() const
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM study_events WHERE profile_id = ?");
    query.addBindValue(m_profileId);
    if (query.exec() && query.next()) return query.value(0).toInt();
    return 0;
}

int ProgressStore::trackedSkillCount() const
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM skill_mastery WHERE profile_id = ?");
    query.addBindValue(m_profileId);
    if (query.exec() && query.next()) return query.value(0).toInt();
    return 0;
}

QStringList ProgressStore::recentStudyEvents(int limit) const
{
    QStringList rows;
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT created_at, event_type, item_id, minutes, notes FROM study_events WHERE profile_id = ? ORDER BY id DESC LIMIT ?");
    query.addBindValue(m_profileId);
    query.addBindValue(limit);
    if (query.exec())
    {
        while (query.next())
        {
            rows << QString("%1 | %2 | %3 | %4 min | %5")
                        .arg(query.value(0).toString(), query.value(1).toString(), query.value(2).toString())
                        .arg(query.value(3).toInt())
                        .arg(query.value(4).toString());
        }
    }
    return rows;
}

QStringList ProgressStore::skillMasteryRows() const
{
    QStringList rows;
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT skill_name, mastery_percent, evidence, updated_at FROM skill_mastery WHERE profile_id = ? ORDER BY skill_name");
    query.addBindValue(m_profileId);
    if (query.exec())
    {
        while (query.next())
        {
            rows << QString("%1 — %2% — %3 — updated %4")
                        .arg(query.value(0).toString())
                        .arg(query.value(1).toInt())
                        .arg(query.value(2).toString(), query.value(3).toString());
        }
    }
    return rows;
}

void ProgressStore::recordStudyEvent(const QString& itemId, const QString& eventType, int minutes, const QString& notes)
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("INSERT INTO study_events(profile_id, item_id, event_type, minutes, notes, created_at) VALUES(?, ?, ?, ?, ?, ?)");
    query.addBindValue(m_profileId);
    query.addBindValue(itemId);
    query.addBindValue(eventType);
    query.addBindValue(minutes);
    query.addBindValue(notes);
    query.addBindValue(nowIso());
    query.exec();
}

void ProgressStore::updateSkillMastery(const QString& skillName, int masteryPercent, const QString& evidence)
{
    const int bounded = qBound(0, masteryPercent, 100);
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO skill_mastery(profile_id, skill_name, mastery_percent, evidence, updated_at) VALUES(?, ?, ?, ?, ?)");
    query.addBindValue(m_profileId);
    query.addBindValue(skillName);
    query.addBindValue(bounded);
    query.addBindValue(evidence);
    query.addBindValue(nowIso());
    query.exec();
}

QString ProgressStore::exportMarkdownSummary() const
{
    QString markdown;
    markdown += "# CS Bootcamp Desktop v11 Progress Database Summary\n\n";
    markdown += "Profile: " + activeProfileName() + "\n\n";
    markdown += "Database path: `" + m_databasePath + "`\n\n";
    markdown += QString("Completed items: **%1**\n\n").arg(completedCount());
    markdown += QString("Notes saved: **%1**\n\n").arg(notesCount());
    markdown += QString("Study events recorded: **%1**\n\n").arg(studyEventCount());
    markdown += QString("Tracked skills: **%1**\n\n").arg(trackedSkillCount());

    markdown += "## Skill Mastery\n\n";
    for (const QString& row : skillMasteryRows()) markdown += "- " + row + "\n";
    if (skillMasteryRows().isEmpty()) markdown += "- No skills have been seeded yet.\n";

    markdown += "\n## Recent Study Events\n\n";
    for (const QString& row : recentStudyEvents(15)) markdown += "- " + row + "\n";
    if (recentStudyEvents(15).isEmpty()) markdown += "- No study events recorded yet.\n";
    return markdown;
}


void ProgressStore::recordCodeAttempt(const QString& language,
                                      const QString& topic,
                                      const QString& exerciseId,
                                      const QString& difficulty,
                                      const QString& commandText,
                                      const QString& outputSummary,
                                      const QString& reviewStatus,
                                      const QString& reviewNotes)
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("INSERT INTO code_attempt_reviews(profile_id, language, topic, exercise_id, difficulty, command_text, output_summary, review_status, review_notes, created_at) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(m_profileId);
    query.addBindValue(language.trimmed().isEmpty() ? "Unknown" : language.trimmed());
    query.addBindValue(topic.trimmed().isEmpty() ? "General Practice" : topic.trimmed());
    query.addBindValue(exerciseId.trimmed().isEmpty() ? "untitled-attempt" : exerciseId.trimmed());
    query.addBindValue(difficulty.trimmed().isEmpty() ? "Unrated" : difficulty.trimmed());
    query.addBindValue(commandText.trimmed());
    query.addBindValue(outputSummary.trimmed());
    query.addBindValue(reviewStatus.trimmed().isEmpty() ? "Needs Work" : reviewStatus.trimmed());
    query.addBindValue(reviewNotes.trimmed());
    query.addBindValue(nowIso());
    query.exec();
    recordStudyEvent("v16-code-attempt", "code-attempt-saved", 10, "Saved " + language + " attempt for " + exerciseId + ".");
}

int ProgressStore::codeAttemptCount() const
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM code_attempt_reviews WHERE profile_id = ?");
    query.addBindValue(m_profileId);
    if (query.exec() && query.next()) return query.value(0).toInt();
    return 0;
}

QStringList ProgressStore::codeAttemptRows(int limit) const
{
    QStringList rows;
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT created_at, language, topic, exercise_id, difficulty, review_status, output_summary FROM code_attempt_reviews WHERE profile_id = ? ORDER BY id DESC LIMIT ?");
    query.addBindValue(m_profileId);
    query.addBindValue(limit);
    if (query.exec())
    {
        while (query.next())
        {
            rows << QString("%1 | %2 | %3 | %4 | %5 | %6 | %7")
                .arg(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString(), query.value(6).toString());
        }
    }
    return rows;
}

QString ProgressStore::codeAttemptMarkdown() const
{
    QString markdown;
    markdown += "# CS Bootcamp Desktop v19 Code Attempt History\n\n";
    markdown += "Profile: " + activeProfileName() + "\n\n";
    markdown += "Database path: `" + m_databasePath + "`\n\n";
    markdown += QString("Saved attempts: **%1**\n\n").arg(codeAttemptCount());

    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT created_at, language, topic, exercise_id, difficulty, command_text, output_summary, review_status, review_notes FROM code_attempt_reviews WHERE profile_id = ? ORDER BY id DESC");
    query.addBindValue(m_profileId);

    markdown += "| Date | Language | Topic | Exercise | Difficulty | Status | Output summary | Review notes |\n";
    markdown += "|---|---|---|---|---|---|---|---|\n";
    bool hasRows = false;
    if (query.exec())
    {
        while (query.next())
        {
            hasRows = true;
            markdown += "| " + escapePipe(query.value(0).toString())
                + " | " + escapePipe(query.value(1).toString())
                + " | " + escapePipe(query.value(2).toString())
                + " | " + escapePipe(query.value(3).toString())
                + " | " + escapePipe(query.value(4).toString())
                + " | " + escapePipe(query.value(7).toString())
                + " | " + escapePipe(query.value(6).toString())
                + " | " + escapePipe(query.value(8).toString()) + " |\n";
        }
    }
    if (!hasRows) markdown += "| No attempts yet |  |  |  |  |  |  |  |\n";

    markdown += "\n## How to use this history\n\n";
    markdown += "- Review repeated errors and convert them into study goals.\n";
    markdown += "- Mark clean, tested, documented attempts as portfolio-ready.\n";
    markdown += "- Export this file before instructor reviews, resume work, or interview prep.\n";
    return markdown;
}


void ProgressStore::saveAiProviderSettings(const QString& providerName,
                                           const QString& endpoint,
                                           const QString& modelName,
                                           const QString& apiKeyEnvironmentVariable,
                                           bool enabled,
                                           const QString& safetyNotes)
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO ai_provider_settings(profile_id, provider_name, endpoint, model_name, api_key_env, enabled, safety_notes, updated_at) VALUES(?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(m_profileId);
    query.addBindValue(providerName.trimmed().isEmpty() ? "Offline Tutor" : providerName.trimmed());
    query.addBindValue(endpoint.trimmed());
    query.addBindValue(modelName.trimmed());
    query.addBindValue(apiKeyEnvironmentVariable.trimmed());
    query.addBindValue(enabled ? 1 : 0);
    query.addBindValue(safetyNotes.trimmed());
    query.addBindValue(nowIso());
    query.exec();
    recordStudyEvent("v18-ai-provider-settings", "ai-provider-settings-saved", 5, "Updated model adapter settings for " + providerName + ".");
}

QString ProgressStore::aiProviderSettingsMarkdown() const
{
    QString markdown;
    markdown += "# CS Bootcamp Desktop v19 AI Provider Settings\n\n";
    markdown += "Profile: " + activeProfileName() + "\n\n";
    markdown += "Database path: `" + m_databasePath + "`\n\n";
    markdown += "| Provider | Enabled | Endpoint | Model | API key environment variable | Safety notes | Updated |\n";
    markdown += "|---|---:|---|---|---|---|---|\n";

    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT provider_name, enabled, endpoint, model_name, api_key_env, safety_notes, updated_at FROM ai_provider_settings WHERE profile_id = ? ORDER BY provider_name");
    query.addBindValue(m_profileId);

    bool hasRows = false;
    if (query.exec())
    {
        while (query.next())
        {
            hasRows = true;
            markdown += "| " + escapePipe(query.value(0).toString())
                + " | " + QString(query.value(1).toInt() ? "yes" : "no")
                + " | " + escapePipe(query.value(2).toString())
                + " | " + escapePipe(query.value(3).toString())
                + " | " + escapePipe(query.value(4).toString())
                + " | " + escapePipe(query.value(5).toString())
                + " | " + escapePipe(query.value(6).toString()) + " |\n";
        }
    }
    if (!hasRows) markdown += "| Offline Tutor | yes | local/offline | rules-based tutor | none | No network calls required. | not saved yet |\n";

    markdown += "\n## v18 adapter rule\n\n";
    markdown += "Keep Offline Tutor as the safe default. Hosted providers should read secrets from environment variables, show prompt previews before sending, and store only summaries unless the learner intentionally exports full text.\n";
    return markdown;
}

void ProgressStore::recordAiTutorReview(const QString& providerName,
                                        const QString& mode,
                                        const QString& language,
                                        const QString& topic,
                                        const QString& promptPreview,
                                        const QString& responseSummary,
                                        const QString& status)
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("INSERT INTO ai_tutor_reviews(profile_id, provider_name, mode, language, topic, prompt_preview, response_summary, status, created_at) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(m_profileId);
    query.addBindValue(providerName.trimmed().isEmpty() ? "Offline Tutor" : providerName.trimmed());
    query.addBindValue(mode.trimmed().isEmpty() ? "General coaching" : mode.trimmed());
    query.addBindValue(language.trimmed().isEmpty() ? "General CS" : language.trimmed());
    query.addBindValue(topic.trimmed().isEmpty() ? "Current lesson" : topic.trimmed());
    query.addBindValue(promptPreview.left(4000));
    query.addBindValue(responseSummary.left(4000));
    query.addBindValue(status.trimmed().isEmpty() ? "Draft" : status.trimmed());
    query.addBindValue(nowIso());
    query.exec();
    recordStudyEvent("v18-ai-tutor-review", "ai-review-saved", 10, "Saved AI tutor review for " + topic + ".");
}

int ProgressStore::aiTutorReviewCount() const
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM ai_tutor_reviews WHERE profile_id = ?");
    query.addBindValue(m_profileId);
    if (query.exec() && query.next()) return query.value(0).toInt();
    return 0;
}

QStringList ProgressStore::aiTutorReviewRows(int limit) const
{
    QStringList rows;
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT created_at, provider_name, mode, language, topic, status, response_summary FROM ai_tutor_reviews WHERE profile_id = ? ORDER BY id DESC LIMIT ?");
    query.addBindValue(m_profileId);
    query.addBindValue(limit);
    if (query.exec())
    {
        while (query.next())
        {
            rows << QString("%1 | %2 | %3 | %4 | %5 | %6 | %7")
                .arg(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString(), query.value(6).toString());
        }
    }
    return rows;
}

QString ProgressStore::aiTutorReviewMarkdown() const
{
    QString markdown;
    markdown += "# CS Bootcamp Desktop v19 AI Tutor Review History\n\n";
    markdown += "Profile: " + activeProfileName() + "\n\n";
    markdown += "Database path: `" + m_databasePath + "`\n\n";
    markdown += QString("Saved AI tutor reviews: **%1**\n\n").arg(aiTutorReviewCount());
    markdown += "## Provider Settings\n\n";
    markdown += aiProviderSettingsMarkdown() + "\n\n";
    markdown += "## Review Rows\n\n";
    markdown += "| Date | Provider | Mode | Language | Topic | Status | Response summary |\n";
    markdown += "|---|---|---|---|---|---|---|\n";

    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("SELECT created_at, provider_name, mode, language, topic, status, response_summary FROM ai_tutor_reviews WHERE profile_id = ? ORDER BY id DESC");
    query.addBindValue(m_profileId);

    bool hasRows = false;
    if (query.exec())
    {
        while (query.next())
        {
            hasRows = true;
            markdown += "| " + escapePipe(query.value(0).toString())
                + " | " + escapePipe(query.value(1).toString())
                + " | " + escapePipe(query.value(2).toString())
                + " | " + escapePipe(query.value(3).toString())
                + " | " + escapePipe(query.value(4).toString())
                + " | " + escapePipe(query.value(5).toString())
                + " | " + escapePipe(query.value(6).toString()) + " |\n";
        }
    }
    if (!hasRows) markdown += "| No AI tutor reviews yet |  |  |  |  |  |  |\n";

    markdown += "\n## Completion rule\n\n";
    markdown += "Use AI as a tutor and reviewer, not as a replacement for building. Every AI-guided session should end with a committed code change, a test, or a written explanation in your own words.\n";
    return markdown;
}

void ProgressStore::createInstructorAssignment(const QString& cohortName, const QString& assignmentTitle, const QString& dueDate, const QString& rubric)
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO instructor_assignments(cohort_name, assignment_title, due_date, rubric, created_at) VALUES(?, ?, ?, ?, ?)");
    query.addBindValue(cohortName.trimmed().isEmpty() ? "Default Cohort" : cohortName.trimmed());
    query.addBindValue(assignmentTitle.trimmed().isEmpty() ? "Untitled Assignment" : assignmentTitle.trimmed());
    query.addBindValue(dueDate.trimmed().isEmpty() ? nowIso().left(10) : dueDate.trimmed());
    query.addBindValue(rubric);
    query.addBindValue(nowIso());
    query.exec();
    recordStudyEvent("v12-instructor-assignment", "assignment-created", 5, "Created or updated instructor assignment: " + assignmentTitle);
}

void ProgressStore::recordInstructorScore(const QString& cohortName, const QString& learnerName, const QString& assignmentTitle, int score, const QString& feedback)
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare("INSERT INTO instructor_scores(cohort_name, learner_name, assignment_title, score, feedback, created_at) VALUES(?, ?, ?, ?, ?, ?)");
    query.addBindValue(cohortName.trimmed().isEmpty() ? "Default Cohort" : cohortName.trimmed());
    query.addBindValue(learnerName.trimmed().isEmpty() ? activeProfileName() : learnerName.trimmed());
    query.addBindValue(assignmentTitle.trimmed().isEmpty() ? "Untitled Assignment" : assignmentTitle.trimmed());
    query.addBindValue(qBound(0, score, 100));
    query.addBindValue(feedback);
    query.addBindValue(nowIso());
    query.exec();
    recordStudyEvent("v12-instructor-score", "score-recorded", 5, "Recorded instructor score for " + learnerName + " on " + assignmentTitle);
}

QString ProgressStore::instructorDashboardMarkdown() const
{
    QString markdown;
    markdown += "# Instructor / Bootcamp Mode Dashboard\n\n";
    markdown += "Active learner profile: " + activeProfileName() + "\n\n";

    QSqlDatabase db = QSqlDatabase::database(m_connectionName);

    QSqlQuery assignmentCount(db);
    assignmentCount.exec("SELECT COUNT(*) FROM instructor_assignments");
    const int assignments = assignmentCount.next() ? assignmentCount.value(0).toInt() : 0;

    QSqlQuery scoreCount(db);
    scoreCount.exec("SELECT COUNT(*) FROM instructor_scores");
    const int scores = scoreCount.next() ? scoreCount.value(0).toInt() : 0;

    markdown += QString("Assignments stored: **%1**\n\n").arg(assignments);
    markdown += QString("Scores / grading notes stored: **%1**\n\n").arg(scores);

    markdown += "## Current Assignments\n\n";
    QSqlQuery assignmentsQuery(db);
    assignmentsQuery.exec("SELECT cohort_name, assignment_title, due_date, rubric FROM instructor_assignments ORDER BY id DESC LIMIT 8");
    bool hasAssignments = false;
    while (assignmentsQuery.next())
    {
        hasAssignments = true;
        markdown += "- **" + assignmentsQuery.value(1).toString() + "** | " + assignmentsQuery.value(0).toString() + " | due " + assignmentsQuery.value(2).toString() + "\n";
    }
    if (!hasAssignments) markdown += "- No assignments saved yet. Use Save Assignment to seed the cohort workflow.\n";

    markdown += "\n## Recent Scores\n\n";
    QSqlQuery scoresQuery(db);
    scoresQuery.exec("SELECT cohort_name, learner_name, assignment_title, score, feedback, created_at FROM instructor_scores ORDER BY id DESC LIMIT 8");
    bool hasScores = false;
    while (scoresQuery.next())
    {
        hasScores = true;
        markdown += QString("- **%1** scored **%2/100** on **%3** in %4. Feedback: %5\n")
            .arg(scoresQuery.value(1).toString())
            .arg(scoresQuery.value(3).toInt())
            .arg(scoresQuery.value(2).toString())
            .arg(scoresQuery.value(0).toString())
            .arg(scoresQuery.value(4).toString());
    }
    if (!hasScores) markdown += "- No grading notes saved yet. Use Record Score after reviewing a learner submission.\n";

    markdown += "\n## Instructor Workflow\n\n";
    markdown += "1. Create a weekly cohort assignment.\n";
    markdown += "2. Attach a clear rubric.\n";
    markdown += "3. Use the Project Generator and Exercise Runner for hands-on work.\n";
    markdown += "4. Record scores and feedback.\n";
    markdown += "5. Export reports for learner reviews or bootcamp records.\n";
    return markdown;
}

QString ProgressStore::exportInstructorMarkdown() const
{
    QString markdown;
    markdown += "# CS Bootcamp Desktop v12 Instructor Report\n\n";
    markdown += instructorDashboardMarkdown();
    markdown += "\n## Progress Database Snapshot\n\n";
    markdown += exportMarkdownSummary();
    return markdown;
}


QString ProgressStore::nowIso() const
{
    return QDateTime::currentDateTime().toString(Qt::ISODate);
}
