#pragma once

#include <QJsonObject>
#include <QSet>
#include <QString>
#include <QStringList>

// ProgressStore is the local learning database for CS Bootcamp Desktop.
// v1-v10 used a small JSON file. v11 upgrades the same public API to SQLite
// while keeping the rest of the app source compatible with previous versions.
class ProgressStore
{
public:
    explicit ProgressStore(QString databasePath);
    ~ProgressStore();

    void load();
    void save() const;

    bool isCompleted(const QString& itemId) const;
    void setCompleted(const QString& itemId, bool completed);

    QString notesFor(const QString& itemId) const;
    void setNotesFor(const QString& itemId, const QString& notes);

    int completedCount() const;

    QString databasePath() const;
    QString activeProfileName() const;
    int notesCount() const;
    int studyEventCount() const;
    int trackedSkillCount() const;
    QStringList recentStudyEvents(int limit = 10) const;
    QStringList skillMasteryRows() const;

    void recordStudyEvent(const QString& itemId, const QString& eventType, int minutes, const QString& notes);
    void updateSkillMastery(const QString& skillName, int masteryPercent, const QString& evidence);
    QString exportMarkdownSummary() const;

    void recordCodeAttempt(const QString& language,
                           const QString& topic,
                           const QString& exerciseId,
                           const QString& difficulty,
                           const QString& commandText,
                           const QString& outputSummary,
                           const QString& reviewStatus,
                           const QString& reviewNotes);
    int codeAttemptCount() const;
    QStringList codeAttemptRows(int limit = 12) const;
    QString codeAttemptMarkdown() const;

    void saveAiProviderSettings(const QString& providerName,
                                const QString& endpoint,
                                const QString& modelName,
                                const QString& apiKeyEnvironmentVariable,
                                bool enabled,
                                const QString& safetyNotes);
    QString aiProviderSettingsMarkdown() const;
    void recordAiTutorReview(const QString& providerName,
                             const QString& mode,
                             const QString& language,
                             const QString& topic,
                             const QString& promptPreview,
                             const QString& responseSummary,
                             const QString& status);
    int aiTutorReviewCount() const;
    QStringList aiTutorReviewRows(int limit = 12) const;
    QString aiTutorReviewMarkdown() const;

    void createInstructorAssignment(const QString& cohortName, const QString& assignmentTitle, const QString& dueDate, const QString& rubric);
    void recordInstructorScore(const QString& cohortName, const QString& learnerName, const QString& assignmentTitle, int score, const QString& feedback);
    QString instructorDashboardMarkdown() const;
    QString exportInstructorMarkdown() const;

private:
    void openDatabase();
    void createSchema();
    void ensureDefaultProfile();
    void reloadCaches();
    QString nowIso() const;

    QString m_databasePath;
    QString m_connectionName;
    int m_profileId = 1;
    QSet<QString> m_completedItems;
    QJsonObject m_notesByItem;
};
