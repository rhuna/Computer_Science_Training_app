#pragma once

#include "BootcampContent.h"
#include "ProgressStore.h"

#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QProgressBar>
#include <QStringList>
#include <QPushButton>
#include <QLineEdit>
#include <QProcess>
#include <QStackedWidget>
#include <QTextEdit>
#include <QVector>

// MainWindow is intentionally a normal C++ class without a Q_OBJECT macro.
// The app uses lambda-based signal/slot connections, which keeps this v2 repo
// easier to build while still using Qt's professional widget toolkit.
class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void buildLayout();
    void buildSidebar();
    void buildPages();
    void applyAppStyle();
    void refreshAllPages();

    QWidget* createDashboardPage();
    QWidget* createCurriculumPage();
    QWidget* createLessonPage();
    QWidget* createExercisePage();
    QWidget* createExerciseRunnerPage();
    QWidget* createAlgorithmVisualizerPage();
    QWidget* createProjectGeneratorPage();
    QWidget* createQuizPage();
    QWidget* createProjectsPage();
    QWidget* createLanguageTracksPage();
    QWidget* createLanguageWorkspacePage();
    QWidget* createCareerPathsPage();
    QWidget* createProgressPage();
    QWidget* createNotesPage();

    void selectModule(int index);
    void selectLesson(int index);
    void selectExercise(int index);
    void selectQuizQuestion(int index);
    void selectProject(int index);
    void selectLanguageTrack(int index);
    void selectWorkspaceTrack(int index);
    void selectCareerPath(int index);

    void prepareAlgorithmSteps();
    void showAlgorithmStep();
    void resetAlgorithmVisualizer();
    void advanceAlgorithmVisualizer();

    void refreshRunnerForLanguage(int index);
    void browseRunnerWorkingDirectory();
    void openRunnerWorkingDirectory();
    void runRunnerCommand(const QString& command);
    QString runnerFolderNameForTrack(const LanguageTrack& track) const;
    QString defaultRunnerDirectoryForTrack(const LanguageTrack& track) const;
    QString commandForTrack(const LanguageTrack& track, const QString& action) const;

    Module* currentModule();
    Lesson* currentLesson();
    Exercise* currentExercise();
    QuizQuestion* currentQuizQuestion();
    PortfolioProject* currentProject();

    QString currentItemIdForNotes() const;
    int totalTrackableItems() const;

    QVector<Module> m_modules;
    QVector<LanguageTrack> m_languageTracks;
    QVector<CareerPath> m_careerPaths;
    ProgressStore m_progress;

    QListWidget* m_sidebar = nullptr;
    QStackedWidget* m_pages = nullptr;

    QLabel* m_dashboardTitle = nullptr;
    QLabel* m_dashboardSummary = nullptr;
    QLabel* m_dashboardRoadmap = nullptr;
    QProgressBar* m_dashboardProgress = nullptr;

    QComboBox* m_moduleSelector = nullptr;
    QLabel* m_moduleSummary = nullptr;
    QListWidget* m_lessonList = nullptr;
    QListWidget* m_exerciseList = nullptr;
    QListWidget* m_quizList = nullptr;
    QListWidget* m_projectList = nullptr;

    QLabel* m_lessonTitle = nullptr;
    QTextEdit* m_lessonBody = nullptr;
    QPushButton* m_lessonCompleteButton = nullptr;

    QLabel* m_exerciseTitle = nullptr;
    QTextEdit* m_exerciseBody = nullptr;
    QTextEdit* m_codeEditor = nullptr;
    QPushButton* m_exerciseCompleteButton = nullptr;

    QComboBox* m_runnerLanguageSelector = nullptr;
    QLineEdit* m_runnerWorkingDirectory = nullptr;
    QTextEdit* m_runnerCommandPreview = nullptr;
    QTextEdit* m_runnerOutput = nullptr;
    QPushButton* m_runnerRunButton = nullptr;
    QPushButton* m_runnerBuildButton = nullptr;
    QPushButton* m_runnerTestButton = nullptr;
    QPushButton* m_runnerStopButton = nullptr;
    QProcess* m_runnerProcess = nullptr;

    QComboBox* m_algorithmSelector = nullptr;
    QLineEdit* m_algorithmInput = nullptr;
    QTextEdit* m_algorithmOutput = nullptr;
    QLabel* m_algorithmComplexity = nullptr;
    QPushButton* m_algorithmResetButton = nullptr;
    QPushButton* m_algorithmStepButton = nullptr;
    QStringList m_algorithmSteps;
    int m_algorithmStepIndex = 0;

    QLabel* m_quizTitle = nullptr;
    QTextEdit* m_quizBody = nullptr;
    QListWidget* m_quizChoices = nullptr;
    QLabel* m_quizFeedback = nullptr;
    QPushButton* m_quizCheckButton = nullptr;
    QPushButton* m_quizCompleteButton = nullptr;

    QLabel* m_projectTitle = nullptr;
    QTextEdit* m_projectBody = nullptr;
    QPushButton* m_projectCompleteButton = nullptr;

    QListWidget* m_languageList = nullptr;
    QLabel* m_languageTitle = nullptr;
    QTextEdit* m_languageBody = nullptr;

    QListWidget* m_careerList = nullptr;
    QListWidget* m_workspaceLanguageList = nullptr;
    QLabel* m_workspaceTitle = nullptr;
    QTextEdit* m_workspaceBody = nullptr;

    QLabel* m_careerTitle = nullptr;
    QTextEdit* m_careerBody = nullptr;

    QLabel* m_progressStats = nullptr;
    QListWidget* m_progressList = nullptr;

    QLabel* m_notesContext = nullptr;
    QTextEdit* m_notesEditor = nullptr;

    int m_currentModuleIndex = 0;
    int m_currentLessonIndex = 0;
    int m_currentExerciseIndex = 0;
    int m_currentQuizIndex = 0;
    int m_currentProjectIndex = 0;
    int m_currentLanguageIndex = 0;
    int m_currentWorkspaceIndex = 0;
    int m_currentCareerIndex = 0;
};
