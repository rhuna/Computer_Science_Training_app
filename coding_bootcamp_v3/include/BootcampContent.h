#pragma once

#include <QString>
#include <QVector>

struct Lesson
{
    QString id;
    QString title;
    QString objective;
    QString explanation;
    QVector<QString> checklist;
    QVector<QString> practicePrompts;
};

struct Exercise
{
    QString id;
    QString title;
    QString difficulty;
    QString prompt;
    QString starterCode;
    QString expectedConcepts;
};

struct QuizQuestion
{
    QString id;
    QString question;
    QVector<QString> choices;
    int correctIndex = 0;
    QString explanation;
};

struct PortfolioProject
{
    QString id;
    QString title;
    QString level;
    QString description;
    QVector<QString> requirements;
    QVector<QString> stretchGoals;
};

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

struct LanguageTrack
{
    QString id;
    QString name;
    QString professionalUse;
    QString whyLearnIt;
    QString setupCommand;
    QVector<QString> installChecks;
    QVector<QString> runCommands;
    QVector<QString> starterFiles;
    QVector<QString> firstWeekPlan;
    QVector<QString> coreTopics;
    QVector<QString> beginnerMilestones;
    QVector<QString> professionalMilestones;
    QVector<QString> portfolioProjects;
};

struct CareerPath
{
    QString id;
    QString title;
    QString summary;
    QVector<QString> requiredSkills;
    QVector<QString> recommendedLanguages;
    QVector<QString> capstones;
};

class BootcampContent
{
public:
    static QVector<Module> createDefaultModules();
    static QVector<LanguageTrack> createLanguageTracks();
    static QVector<CareerPath> createCareerPaths();
};
