#include "ProgressStore.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

ProgressStore::ProgressStore(QString filePath)
    : m_filePath(std::move(filePath))
{
}

void ProgressStore::load()
{
    QFile file(m_filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly))
    {
        return;
    }

    const QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    const QJsonObject root = document.object();

    m_completedItems.clear();
    for (const QJsonValue& value : root.value("completedItems").toArray())
    {
        m_completedItems.insert(value.toString());
    }

    m_notesByItem = root.value("notesByItem").toObject();
}

void ProgressStore::save() const
{
    QJsonArray completed;
    for (const QString& id : m_completedItems)
    {
        completed.append(id);
    }

    QJsonObject root;
    root.insert("completedItems", completed);
    root.insert("notesByItem", m_notesByItem);

    QFile file(m_filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    }
}

bool ProgressStore::isCompleted(const QString& itemId) const
{
    return m_completedItems.contains(itemId);
}

void ProgressStore::setCompleted(const QString& itemId, bool completed)
{
    if (completed)
    {
        m_completedItems.insert(itemId);
    }
    else
    {
        m_completedItems.remove(itemId);
    }
    save();
}

QString ProgressStore::notesFor(const QString& itemId) const
{
    return m_notesByItem.value(itemId).toString();
}

void ProgressStore::setNotesFor(const QString& itemId, const QString& notes)
{
    m_notesByItem.insert(itemId, notes);
    save();
}

int ProgressStore::completedCount() const
{
    return static_cast<int>(m_completedItems.size());
}
