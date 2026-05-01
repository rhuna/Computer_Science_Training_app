#pragma once

#include "BootcampContent.h"
#include "ProgressStore.h"

#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QProgressBar>
#include <QVector>

// MainWindow is the shell of the bootcamp app.
// It owns navigation, page layout, and connects the curriculum model to widgets.
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
    QWidget* createQuizPage();
    QWidget* createProjectsPage();
    QWidget* createProgressPage();
    QWidget* createNotesPage();

    void selectModule(int index);
    void selectLesson(int index);
    void selectExercise(int index);
    void selectQuizQuestion(int index);
    void selectProject(int index);

    Module* currentModule();
    Lesson* currentLesson();
    Exercise* currentExercise();
    QuizQuestion* currentQuizQuestion();
    PortfolioProject* currentProject();

    QString currentItemIdForNotes() const;
    int totalTrackableItems() const;

    QVector<Module> m_modules;
    ProgressStore m_progress;

    QListWidget* m_sidebar = nullptr;
    QStackedWidget* m_pages = nullptr;

    QLabel* m_dashboardTitle = nullptr;
    QLabel* m_dashboardSummary = nullptr;
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

    QLabel* m_quizTitle = nullptr;
    QTextEdit* m_quizBody = nullptr;
    QListWidget* m_quizChoices = nullptr;
    QLabel* m_quizFeedback = nullptr;
    QPushButton* m_quizCheckButton = nullptr;
    QPushButton* m_quizCompleteButton = nullptr;

    QLabel* m_projectTitle = nullptr;
    QTextEdit* m_projectBody = nullptr;
    QPushButton* m_projectCompleteButton = nullptr;

    QLabel* m_progressStats = nullptr;
    QListWidget* m_progressList = nullptr;

    QLabel* m_notesContext = nullptr;
    QTextEdit* m_notesEditor = nullptr;

    int m_currentModuleIndex = 0;
    int m_currentLessonIndex = 0;
    int m_currentExerciseIndex = 0;
    int m_currentQuizIndex = 0;
    int m_currentProjectIndex = 0;
};
