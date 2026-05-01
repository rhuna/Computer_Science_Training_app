#pragma once

#include "BootcampContent.h"
#include "ProgressStore.h"

#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QStackedWidget>
#include <QTextEdit>
#include <QVector>

// CS Bootcamp Desktop v21 intentionally keeps the main window as a normal C++
// class without Q_OBJECT. All events are connected with lambda-based signals.
// This keeps the repo easier to build while still using Qt professionally.
class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void buildLayout();
    void buildSidebar();
    void buildPages();
    void applyAppStyle();
    void refreshAllTabs();

    QWidget* createDashboardPage();
    QWidget* createLearningPathPage();
    QWidget* createPracticeLabPage();
    QWidget* createExerciseRunnerPage();
    QWidget* createQuizTrainerPage();
    QWidget* createAlgorithmVisualizerPage();
    QWidget* createLanguageWorkspacePage();
    QWidget* createContentPackPage();
    QWidget* createAiTutorPage();
    QWidget* createModelAdapterPage();
    QWidget* createProgressDatabasePage();
    QWidget* createInstructorModePage();
    QWidget* createFinalCapstonePage();
    QWidget* createAdvancedLearningPage();
    QWidget* createNotesPage();
    QWidget* createProjectGeneratorPage();

    Module* currentModule();
    Lesson* currentLesson();
    Exercise* currentExercise();
    QuizQuestion* currentQuizQuestion();
    LanguageTrack* currentLanguageTrack();

    QString currentContextId() const;
    QString lessonDetailText(const Lesson& lesson) const;
    QString exerciseDetailText(const Exercise& exercise) const;
    QString moduleSummaryText(const Module& module) const;
    QString quizSummaryText() const;
    QString expectedOutputTokenForExercise(const Exercise& exercise) const;
    QString starterFolderForExercise(const QString& languageId, const Exercise& exercise) const;
    QString commandForRunner(const QString& action) const;

    void selectModule(int index);
    void selectLesson(int index);
    void selectExercise(int index);
    void selectQuiz(int index);
    void selectLanguageTrack(int index);
    void copyExerciseToRunner();
    void runRunnerAction(const QString& action);
    void verifyRunnerOutput();
    void appendRunnerOutput(const QString& text);
    void recordRunnerAttempt(const QString& status);
    void resetAlgorithm();
    void nextAlgorithmStep();
    void prepareAlgorithmSteps();
    void exportProgressSummary();

    QVector<Module> m_modules;
    QVector<LanguageTrack> m_languageTracks;
    ProgressStore m_progress;

    QListWidget* m_sidebar = nullptr;
    QStackedWidget* m_pages = nullptr;

    QLabel* m_dashboardSummary = nullptr;
    QProgressBar* m_dashboardProgress = nullptr;
    QTextEdit* m_dashboardPlan = nullptr;

    QComboBox* m_moduleSelector = nullptr;
    QListWidget* m_lessonList = nullptr;
    QLabel* m_lessonTitle = nullptr;
    QTextEdit* m_lessonBody = nullptr;

    QListWidget* m_exerciseList = nullptr;
    QLabel* m_exerciseTitle = nullptr;
    QTextEdit* m_exerciseBody = nullptr;
    QTextEdit* m_exerciseCode = nullptr;

    QComboBox* m_runnerLanguage = nullptr;
    QLabel* m_runnerContext = nullptr;
    QTextEdit* m_runnerCommandPreview = nullptr;
    QTextEdit* m_runnerOutput = nullptr;
    QProcess* m_runnerProcess = nullptr;
    QString m_lastRunnerOutput;

    QListWidget* m_quizList = nullptr;
    QLabel* m_quizTitle = nullptr;
    QTextEdit* m_quizBody = nullptr;
    QListWidget* m_quizChoices = nullptr;
    QLabel* m_quizFeedback = nullptr;

    QComboBox* m_algorithmSelector = nullptr;
    QTextEdit* m_algorithmOutput = nullptr;
    QLabel* m_algorithmComplexity = nullptr;
    QVector<QString> m_algorithmSteps;
    int m_algorithmStepIndex = 0;

    QListWidget* m_languageList = nullptr;
    QLabel* m_languageTitle = nullptr;
    QTextEdit* m_languageBody = nullptr;

    QTextEdit* m_contentBody = nullptr;
    QTextEdit* m_aiTutorBody = nullptr;
    QTextEdit* m_modelAdapterBody = nullptr;
    QTextEdit* m_databaseBody = nullptr;
    QTextEdit* m_instructorBody = nullptr;
    QTextEdit* m_capstoneBody = nullptr;
    QTextEdit* m_advancedBody = nullptr;
    QTextEdit* m_projectGeneratorBody = nullptr;
    QLabel* m_notesContext = nullptr;
    QTextEdit* m_notesEditor = nullptr;

    int m_currentModuleIndex = 0;
    int m_currentLessonIndex = 0;
    int m_currentExerciseIndex = 0;
    int m_currentQuizIndex = 0;
    int m_currentLanguageIndex = 0;
};
