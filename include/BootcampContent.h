#pragma once

#include <QString>
#include <QVector>

// A single lesson inside a bootcamp module.
// Lessons are intentionally plain data so future versions can load them from JSON,
// SQLite, Markdown, or a remote content server without changing the UI contract.
struct Lesson
{
    QString id;
    QString title;
    QString objective;
    QString explanation;
    QVector<QString> checklist;
    QVector<QString> practicePrompts;
};

// A coding exercise that the student can attempt inside or outside the app.
// v1 stores starter code and expected ideas; later versions can compile/run code.
struct Exercise
{
    QString id;
    QString title;
    QString difficulty;
    QString prompt;
    QString starterCode;
    QString expectedConcepts;
};

// A quiz question with answer choices and a short teaching explanation.
struct QuizQuestion
{
    QString id;
    QString question;
    QVector<QString> choices;
    int correctIndex = 0;
    QString explanation;
};

// A portfolio project that pushes the user toward professional readiness.
struct PortfolioProject
{
    QString id;
    QString title;
    QString level;
    QString description;
    QVector<QString> requirements;
    QVector<QString> stretchGoals;
};

// A larger curriculum module, such as C++ Fundamentals or Data Structures.
struct Module
{
    QString id;
    QString title;
    QString level;
    QString summary;
    QVector<Lesson> lessons;
    QVector<Exercise> exercises;
    QVector<QuizQuestion> quiz;
    QVector<PortfolioProject> projects;
};

// BootcampContent owns the built-in v1 curriculum.
// Keeping this separate from MainWindow prevents the UI from becoming tangled
// with lesson data and makes later content upgrades easier.
class BootcampContent
{
public:
    static QVector<Module> createDefaultModules();
};
