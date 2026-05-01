#pragma once

#include <QJsonObject>
#include <QSet>
#include <QString>

// ProgressStore persists the user's learning state in a local JSON file.
// The class is small on purpose: v1 proves the persistence flow, while v2+ can
// add richer analytics, spaced repetition, and multiple user profiles.
class ProgressStore
{
public:
    explicit ProgressStore(QString filePath);

    void load();
    void save() const;

    bool isCompleted(const QString& itemId) const;
    void setCompleted(const QString& itemId, bool completed);

    QString notesFor(const QString& itemId) const;
    void setNotesFor(const QString& itemId, const QString& notes);

    int completedCount() const;

private:
    QString m_filePath;
    QSet<QString> m_completedItems;
    QJsonObject m_notesByItem;
};
