#include "MainWindow.h"

#include <algorithm>

#include <QApplication>
#include <QCoreApplication>
#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFrame>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QStandardPaths>
#include <QTextStream>
#include <QUrl>
#include <QVBoxLayout>
#include <QtGlobal>

namespace
{
    QLabel* header(const QString& text)
    {
        QLabel* label = new QLabel(text);
        label->setObjectName("pageHeader");
        label->setWordWrap(true);
        return label;
    }

    QLabel* smallTitle(const QString& text)
    {
        QLabel* label = new QLabel(text);
        label->setObjectName("smallTitle");
        label->setWordWrap(true);
        return label;
    }

    QTextEdit* readOnlyText(int height = 260)
    {
        QTextEdit* text = new QTextEdit;
        text->setReadOnly(true);
        text->setMinimumHeight(height);
        return text;
    }

    QString bullets(const QVector<QString>& values)
    {
        QString out;
        for (const QString& value : values)
        {
            out += "• " + value + "\n";
        }
        return out;
    }

    QString numbered(const QVector<QString>& values)
    {
        QString out;
        int n = 1;
        for (const QString& value : values)
        {
            out += QString::number(n++) + ". " + value + "\n";
        }
        return out;
    }

    QFrame* card()
    {
        QFrame* frame = new QFrame;
        frame->setObjectName("card");
        return frame;
    }
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_modules(BootcampContent::createDefaultModules())
    , m_languageTracks(BootcampContent::createLanguageTracks())
    , m_progress(QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).filePath("progress_v21.sqlite"))
{
    QDir().mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    m_progress.load();
    buildLayout();
    applyAppStyle();
    refreshAllTabs();
    setWindowTitle("CS Bootcamp Desktop v21 - Verified Exercise Packs");
    setWindowIcon(QIcon(":/assets/app_icon.png"));
    resize(1480, 900);
}

void MainWindow::buildLayout()
{
    QWidget* root = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(root);
    layout->setContentsMargins(14, 14, 14, 14);
    layout->setSpacing(14);
    buildSidebar();
    buildPages();
    layout->addWidget(m_sidebar, 0);
    layout->addWidget(m_pages, 1);
    setCentralWidget(root);
}

void MainWindow::buildSidebar()
{
    m_sidebar = new QListWidget;
    m_sidebar->setObjectName("sidebar");
    m_sidebar->setFixedWidth(290);
    m_sidebar->addItems({
        "Dashboard",
        "Learning Path",
        "Practice Lab",
        "Exercise Runner",
        "Quiz Trainer",
        "Algorithm Visualizer",
        "Language Workspace",
        "Content Pack Expansion",
        "AI Tutor Mode",
        "Model Adapter Lab",
        "Progress Database",
        "Instructor / Bootcamp Mode",
        "Final Capstone Certification",
        "Advanced Learning Extension",
        "Notes",
        "Project Generator"
    });
    m_sidebar->setCurrentRow(0);
    connect(m_sidebar, &QListWidget::currentRowChanged, this, [this](int row)
    {
        if (row >= 0 && row < m_pages->count())
        {
            m_pages->setCurrentIndex(row);
            refreshAllTabs();
        }
    });
}

void MainWindow::buildPages()
{
    m_pages = new QStackedWidget;
    m_pages->addWidget(createDashboardPage());
    m_pages->addWidget(createLearningPathPage());
    m_pages->addWidget(createPracticeLabPage());
    m_pages->addWidget(createExerciseRunnerPage());
    m_pages->addWidget(createQuizTrainerPage());
    m_pages->addWidget(createAlgorithmVisualizerPage());
    m_pages->addWidget(createLanguageWorkspacePage());
    m_pages->addWidget(createContentPackPage());
    m_pages->addWidget(createAiTutorPage());
    m_pages->addWidget(createModelAdapterPage());
    m_pages->addWidget(createProgressDatabasePage());
    m_pages->addWidget(createInstructorModePage());
    m_pages->addWidget(createFinalCapstonePage());
    m_pages->addWidget(createAdvancedLearningPage());
    m_pages->addWidget(createNotesPage());
    m_pages->addWidget(createProjectGeneratorPage());
}

void MainWindow::applyAppStyle()
{
    qApp->setStyleSheet(R"(
        QWidget { font-family: Segoe UI, Arial; font-size: 14px; color: #172033; }
        QMainWindow, QWidget { background: #f4f6fb; }
        QListWidget#sidebar { background: #111827; color: #e5e7eb; border-radius: 18px; padding: 10px; }
        QListWidget#sidebar::item { padding: 13px 12px; border-radius: 12px; margin: 3px; }
        QListWidget#sidebar::item:selected { background: #2563eb; color: white; }
        QFrame#card { background: white; border: 1px solid #d8deea; border-radius: 18px; padding: 14px; }
        QLabel#pageHeader { font-size: 26px; font-weight: 800; color: #0f172a; }
        QLabel#smallTitle { font-size: 16px; font-weight: 800; color: #1d4ed8; }
        QPushButton { background: #2563eb; color: white; border: none; border-radius: 12px; padding: 10px 14px; font-weight: 700; }
        QPushButton:hover { background: #1d4ed8; }
        QTextEdit, QListWidget, QComboBox { background: white; border: 1px solid #cbd5e1; border-radius: 12px; padding: 8px; }
        QProgressBar { border: 1px solid #cbd5e1; border-radius: 10px; height: 24px; text-align: center; background: white; }
        QProgressBar::chunk { background: #22c55e; border-radius: 10px; }
    )");
}

QWidget* MainWindow::createDashboardPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setSpacing(12);
    layout->addWidget(header("CS Bootcamp Desktop v21 - Verified Exercise Packs"));
    m_dashboardSummary = new QLabel;
    m_dashboardSummary->setWordWrap(true);
    m_dashboardProgress = new QProgressBar;
    m_dashboardPlan = readOnlyText(420);
    QFrame* top = card();
    QVBoxLayout* topLayout = new QVBoxLayout(top);
    topLayout->addWidget(m_dashboardSummary);
    topLayout->addWidget(m_dashboardProgress);
    layout->addWidget(top);
    layout->addWidget(smallTitle("How the tabs now work together"));
    layout->addWidget(m_dashboardPlan);
    layout->addStretch();
    return page;
}

QWidget* MainWindow::createLearningPathPage()
{
    QWidget* page = new QWidget;
    QHBoxLayout* root = new QHBoxLayout(page);

    QVBoxLayout* left = new QVBoxLayout;
    left->addWidget(header("Learning Path"));
    m_moduleSelector = new QComboBox;
    for (const Module& module : m_modules) m_moduleSelector->addItem(module.title);
    m_lessonList = new QListWidget;
    left->addWidget(smallTitle("Module"));
    left->addWidget(m_moduleSelector);
    left->addWidget(smallTitle("Lessons"));
    left->addWidget(m_lessonList, 1);

    QVBoxLayout* right = new QVBoxLayout;
    m_lessonTitle = smallTitle("Lesson");
    m_lessonBody = readOnlyText(560);
    QPushButton* complete = new QPushButton("Mark Current Lesson Complete");
    QPushButton* sendPractice = new QPushButton("Open Matching Practice Lab");
    right->addWidget(m_lessonTitle);
    right->addWidget(m_lessonBody, 1);
    right->addWidget(complete);
    right->addWidget(sendPractice);

    root->addLayout(left, 0);
    root->addLayout(right, 1);

    connect(m_moduleSelector, &QComboBox::currentIndexChanged, this, [this](int index) { selectModule(index); });
    connect(m_lessonList, &QListWidget::currentRowChanged, this, [this](int index) { selectLesson(index); });
    connect(complete, &QPushButton::clicked, this, [this]
    {
        if (Lesson* lesson = currentLesson())
        {
            m_progress.setCompleted(lesson->id, true);
            m_progress.recordStudyEvent(lesson->id, "lesson_completed", 25, "Completed detailed lesson walkthrough.");
            refreshAllTabs();
        }
    });
    connect(sendPractice, &QPushButton::clicked, this, [this]
    {
        m_sidebar->setCurrentRow(2);
    });
    return page;
}

QWidget* MainWindow::createPracticeLabPage()
{
    QWidget* page = new QWidget;
    QHBoxLayout* root = new QHBoxLayout(page);
    QVBoxLayout* left = new QVBoxLayout;
    left->addWidget(header("Practice Lab"));
    left->addWidget(smallTitle("Exercises connected to the selected module"));
    m_exerciseList = new QListWidget;
    left->addWidget(m_exerciseList, 1);
    QVBoxLayout* right = new QVBoxLayout;
    m_exerciseTitle = smallTitle("Exercise");
    m_exerciseBody = readOnlyText(310);
    m_exerciseCode = new QTextEdit;
    m_exerciseCode->setMinimumHeight(220);
    QPushButton* copyToRunner = new QPushButton("Send This Exercise to Runner");
    QPushButton* complete = new QPushButton("Mark Exercise Reviewed");
    right->addWidget(m_exerciseTitle);
    right->addWidget(m_exerciseBody);
    right->addWidget(smallTitle("Starter code / your attempt"));
    right->addWidget(m_exerciseCode, 1);
    right->addWidget(copyToRunner);
    right->addWidget(complete);
    root->addLayout(left, 0);
    root->addLayout(right, 1);
    connect(m_exerciseList, &QListWidget::currentRowChanged, this, [this](int index) { selectExercise(index); });
    connect(copyToRunner, &QPushButton::clicked, this, [this] { copyExerciseToRunner(); });
    connect(complete, &QPushButton::clicked, this, [this]
    {
        if (Exercise* exercise = currentExercise())
        {
            m_progress.setCompleted(exercise->id, true);
            m_progress.recordCodeAttempt(currentLanguageTrack() ? currentLanguageTrack()->name : "Unknown", currentModule() ? currentModule()->title : "Unknown", exercise->id, exercise->difficulty, "manual_review", "Learner marked exercise reviewed.", "reviewed", "Manual review from Practice Lab.");
            refreshAllTabs();
        }
    });
    return page;
}

QWidget* MainWindow::createExerciseRunnerPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Exercise Runner and Correctness Verifier"));
    m_runnerContext = new QLabel;
    m_runnerContext->setWordWrap(true);
    layout->addWidget(m_runnerContext);
    m_runnerLanguage = new QComboBox;
    for (const LanguageTrack& track : m_languageTracks) m_runnerLanguage->addItem(track.name, track.id);
    layout->addWidget(smallTitle("Language"));
    layout->addWidget(m_runnerLanguage);
    m_runnerCommandPreview = readOnlyText(100);
    layout->addWidget(smallTitle("Commands that will be used"));
    layout->addWidget(m_runnerCommandPreview);
    QHBoxLayout* buttons = new QHBoxLayout;
    QPushButton* build = new QPushButton("Build / Compile");
    QPushButton* run = new QPushButton("Run");
    QPushButton* test = new QPushButton("Test");
    QPushButton* verify = new QPushButton("Verify Correct");
    QPushButton* stop = new QPushButton("Stop");
    buttons->addWidget(build);
    buttons->addWidget(run);
    buttons->addWidget(test);
    buttons->addWidget(verify);
    buttons->addWidget(stop);
    layout->addLayout(buttons);
    m_runnerOutput = new QTextEdit;
    m_runnerOutput->setMinimumHeight(430);
    layout->addWidget(smallTitle("Console output and verification report"));
    layout->addWidget(m_runnerOutput, 1);
    m_runnerProcess = new QProcess(this);
    connect(m_runnerLanguage, &QComboBox::currentIndexChanged, this, [this](int index) { selectLanguageTrack(index); });
    connect(build, &QPushButton::clicked, this, [this] { runRunnerAction("build"); });
    connect(run, &QPushButton::clicked, this, [this] { runRunnerAction("run"); });
    connect(test, &QPushButton::clicked, this, [this] { runRunnerAction("test"); });
    connect(verify, &QPushButton::clicked, this, [this] { verifyRunnerOutput(); });
    connect(stop, &QPushButton::clicked, this, [this] { if (m_runnerProcess) m_runnerProcess->kill(); });
    connect(m_runnerProcess, &QProcess::readyReadStandardOutput, this, [this] { appendRunnerOutput(QString::fromLocal8Bit(m_runnerProcess->readAllStandardOutput())); });
    connect(m_runnerProcess, &QProcess::readyReadStandardError, this, [this] { appendRunnerOutput(QString::fromLocal8Bit(m_runnerProcess->readAllStandardError())); });
    connect(m_runnerProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this](int code, QProcess::ExitStatus)
    {
        appendRunnerOutput(QString("\n[process finished with exit code %1]\n").arg(code));
        recordRunnerAttempt(code == 0 ? "ran" : "failed_to_run");
    });
    return page;
}

QWidget* MainWindow::createQuizTrainerPage()
{
    QWidget* page = new QWidget;
    QHBoxLayout* root = new QHBoxLayout(page);
    QVBoxLayout* left = new QVBoxLayout;
    left->addWidget(header("Quiz Trainer"));
    m_quizList = new QListWidget;
    left->addWidget(m_quizList, 1);
    QVBoxLayout* right = new QVBoxLayout;
    m_quizTitle = smallTitle("Question");
    m_quizBody = readOnlyText(170);
    m_quizChoices = new QListWidget;
    m_quizFeedback = new QLabel;
    m_quizFeedback->setWordWrap(true);
    QPushButton* check = new QPushButton("Check Answer");
    QPushButton* complete = new QPushButton("Mark Question Mastered");
    right->addWidget(m_quizTitle);
    right->addWidget(m_quizBody);
    right->addWidget(m_quizChoices, 1);
    right->addWidget(check);
    right->addWidget(complete);
    right->addWidget(m_quizFeedback);
    root->addLayout(left, 0);
    root->addLayout(right, 1);
    connect(m_quizList, &QListWidget::currentRowChanged, this, [this](int index) { selectQuiz(index); });
    connect(check, &QPushButton::clicked, this, [this]
    {
        QuizQuestion* q = currentQuizQuestion();
        if (!q || !m_quizChoices) return;
        const bool correct = m_quizChoices->currentRow() == q->correctIndex;
        m_quizFeedback->setText((correct ? "Correct. " : "Not quite. ") + q->explanation);
        m_progress.recordStudyEvent(q->id, correct ? "quiz_correct" : "quiz_missed", 5, q->question);
    });
    connect(complete, &QPushButton::clicked, this, [this]
    {
        if (QuizQuestion* q = currentQuizQuestion())
        {
            m_progress.setCompleted(q->id, true);
            m_progress.updateSkillMastery(currentModule() ? currentModule()->title : "Quiz", 70, "Quiz question mastered: " + q->question);
            refreshAllTabs();
        }
    });
    return page;
}

QWidget* MainWindow::createAlgorithmVisualizerPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Algorithm Visualizer"));
    m_algorithmSelector = new QComboBox;
    m_algorithmSelector->addItems({"Binary Search", "Bubble Sort", "Hash Table Lookup", "BFS Traversal", "DFS Traversal", "Stack Operations", "Queue Operations"});
    m_algorithmComplexity = smallTitle("Complexity");
    m_algorithmOutput = readOnlyText(480);
    QHBoxLayout* buttons = new QHBoxLayout;
    QPushButton* reset = new QPushButton("Reset");
    QPushButton* next = new QPushButton("Next Step");
    buttons->addWidget(reset);
    buttons->addWidget(next);
    layout->addWidget(m_algorithmSelector);
    layout->addWidget(m_algorithmComplexity);
    layout->addLayout(buttons);
    layout->addWidget(m_algorithmOutput, 1);
    connect(m_algorithmSelector, &QComboBox::currentIndexChanged, this, [this] { resetAlgorithm(); });
    connect(reset, &QPushButton::clicked, this, [this] { resetAlgorithm(); });
    connect(next, &QPushButton::clicked, this, [this] { nextAlgorithmStep(); });
    return page;
}

QWidget* MainWindow::createLanguageWorkspacePage()
{
    QWidget* page = new QWidget;
    QHBoxLayout* root = new QHBoxLayout(page);
    QVBoxLayout* left = new QVBoxLayout;
    left->addWidget(header("Language Workspace"));
    m_languageList = new QListWidget;
    for (const LanguageTrack& track : m_languageTracks) m_languageList->addItem(track.name);
    left->addWidget(m_languageList, 1);
    QVBoxLayout* right = new QVBoxLayout;
    m_languageTitle = smallTitle("Language");
    m_languageBody = readOnlyText(560);
    QPushButton* openRunner = new QPushButton("Use This Language in Exercise Runner");
    right->addWidget(m_languageTitle);
    right->addWidget(m_languageBody, 1);
    right->addWidget(openRunner);
    root->addLayout(left, 0);
    root->addLayout(right, 1);
    connect(m_languageList, &QListWidget::currentRowChanged, this, [this](int index) { selectLanguageTrack(index); });
    connect(openRunner, &QPushButton::clicked, this, [this] { m_sidebar->setCurrentRow(3); });
    return page;
}

QWidget* MainWindow::createContentPackPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Professional Content Pack Expansion"));
    m_contentBody = readOnlyText(620);
    layout->addWidget(m_contentBody, 1);
    return page;
}

QWidget* MainWindow::createAiTutorPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("AI Tutor Mode"));
    m_aiTutorBody = readOnlyText(620);
    layout->addWidget(m_aiTutorBody, 1);
    return page;
}

QWidget* MainWindow::createModelAdapterPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Model Adapter Lab"));
    m_modelAdapterBody = readOnlyText(620);
    layout->addWidget(m_modelAdapterBody, 1);
    return page;
}

QWidget* MainWindow::createProgressDatabasePage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Progress Database"));
    m_databaseBody = readOnlyText(560);
    QPushButton* exportButton = new QPushButton("Export Progress Summary");
    layout->addWidget(m_databaseBody, 1);
    layout->addWidget(exportButton);
    connect(exportButton, &QPushButton::clicked, this, [this] { exportProgressSummary(); });
    return page;
}

QWidget* MainWindow::createInstructorModePage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Instructor / Bootcamp Mode"));
    m_instructorBody = readOnlyText(620);
    layout->addWidget(m_instructorBody, 1);
    return page;
}

QWidget* MainWindow::createFinalCapstonePage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Final Capstone Certification"));
    m_capstoneBody = readOnlyText(620);
    layout->addWidget(m_capstoneBody, 1);
    return page;
}

QWidget* MainWindow::createAdvancedLearningPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Advanced Learning Extension"));
    m_advancedBody = readOnlyText(620);
    layout->addWidget(m_advancedBody, 1);
    return page;
}

QWidget* MainWindow::createNotesPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Context Notes"));
    m_notesContext = new QLabel;
    m_notesContext->setWordWrap(true);
    m_notesEditor = new QTextEdit;
    QPushButton* save = new QPushButton("Save Notes For Current Lesson / Exercise / Quiz Context");
    layout->addWidget(m_notesContext);
    layout->addWidget(m_notesEditor, 1);
    layout->addWidget(save);
    connect(save, &QPushButton::clicked, this, [this]
    {
        m_progress.setNotesFor(currentContextId(), m_notesEditor->toPlainText());
        refreshAllTabs();
    });
    return page;
}

QWidget* MainWindow::createProjectGeneratorPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Project Generator"));
    m_projectGeneratorBody = readOnlyText(620);
    layout->addWidget(m_projectGeneratorBody, 1);
    return page;
}

void MainWindow::selectModule(int index)
{
    if (index < 0 || index >= m_modules.size()) return;
    m_currentModuleIndex = index;
    m_currentLessonIndex = 0;
    m_currentExerciseIndex = 0;
    m_currentQuizIndex = 0;
    refreshAllTabs();
}

void MainWindow::selectLesson(int index)
{
    if (!currentModule() || index < 0 || index >= currentModule()->lessons.size()) return;
    m_currentLessonIndex = index;
    if (index < currentModule()->exercises.size()) m_currentExerciseIndex = index;
    if (index < currentModule()->quiz.size()) m_currentQuizIndex = index;
    refreshAllTabs();
}

void MainWindow::selectExercise(int index)
{
    if (!currentModule() || index < 0 || index >= currentModule()->exercises.size()) return;
    m_currentExerciseIndex = index;
    refreshAllTabs();
}

void MainWindow::selectQuiz(int index)
{
    if (!currentModule() || index < 0 || index >= currentModule()->quiz.size()) return;
    m_currentQuizIndex = index;
    refreshAllTabs();
}

void MainWindow::selectLanguageTrack(int index)
{
    if (index < 0 || index >= m_languageTracks.size()) return;
    m_currentLanguageIndex = index;
    refreshAllTabs();
}

Module* MainWindow::currentModule()
{
    if (m_currentModuleIndex < 0 || m_currentModuleIndex >= m_modules.size()) return nullptr;
    return &m_modules[m_currentModuleIndex];
}

Lesson* MainWindow::currentLesson()
{
    Module* module = currentModule();
    if (!module || m_currentLessonIndex < 0 || m_currentLessonIndex >= module->lessons.size()) return nullptr;
    return &module->lessons[m_currentLessonIndex];
}

Exercise* MainWindow::currentExercise()
{
    Module* module = currentModule();
    if (!module || m_currentExerciseIndex < 0 || m_currentExerciseIndex >= module->exercises.size()) return nullptr;
    return &module->exercises[m_currentExerciseIndex];
}

QuizQuestion* MainWindow::currentQuizQuestion()
{
    Module* module = currentModule();
    if (!module || m_currentQuizIndex < 0 || m_currentQuizIndex >= module->quiz.size()) return nullptr;
    return &module->quiz[m_currentQuizIndex];
}

LanguageTrack* MainWindow::currentLanguageTrack()
{
    if (m_currentLanguageIndex < 0 || m_currentLanguageIndex >= m_languageTracks.size()) return nullptr;
    return &m_languageTracks[m_currentLanguageIndex];
}

QString MainWindow::currentContextId() const
{
    if (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size())
    {
        const Module& module = m_modules[m_currentModuleIndex];
        if (m_currentLessonIndex >= 0 && m_currentLessonIndex < module.lessons.size())
        {
            return module.lessons[m_currentLessonIndex].id;
        }
    }
    return "dashboard";
}

QString MainWindow::lessonDetailText(const Lesson& lesson) const
{
    QString text;
    text += "OBJECTIVE\n" + lesson.objective + "\n\n";
    text += "DETAILED EXPLANATION\n" + lesson.explanation + "\n\n";
    text += "HOW TO COMPLETE THIS OBJECTIVE\n";
    text += "1. Read the explanation slowly and rewrite the idea in your own words.\n";
    text += "2. Identify the vocabulary terms that appear in the objective.\n";
    text += "3. Build or trace a tiny example before attempting a larger exercise.\n";
    text += "4. Use the Practice Lab exercise connected to this module.\n";
    text += "5. Run the code in Exercise Runner, then use Verify Correct.\n";
    text += "6. Take the connected quiz question and read the explanation even if you got it right.\n";
    text += "7. Save notes for anything you could not explain without looking.\n\n";
    text += "CHECKLIST WITH HOW-TO STEPS\n";
    int step = 1;
    for (const QString& item : lesson.checklist)
    {
        text += QString::number(step++) + ". " + item + "\n";
        text += "   How to do it: define the term, write a one-line example, explain a failure case, then connect it to a real program.\n";
    }
    text += "\nPRACTICE ITEMS WITH INSTRUCTIONS\n";
    step = 1;
    for (const QString& item : lesson.practicePrompts)
    {
        text += QString::number(step++) + ". " + item + "\n";
        text += "   Do this by creating a tiny input, predicting the output, writing the code or notes, checking the result, and writing what changed in your understanding.\n";
    }
    return text;
}

QString MainWindow::exerciseDetailText(const Exercise& exercise) const
{
    QString text;
    text += "DIFFICULTY: " + exercise.difficulty + "\n\n";
    text += "PROMPT\n" + exercise.prompt + "\n\n";
    text += "EXPECTED CONCEPTS\n" + exercise.expectedConcepts + "\n\n";
    text += "HOW TO DO THIS PRACTICE\n";
    text += "1. Restate the problem in plain English.\n";
    text += "2. Write the input and output examples before coding.\n";
    text += "3. Write the smallest working solution first.\n";
    text += "4. Run it with the Exercise Runner.\n";
    text += "5. Use Verify Correct to check for the expected output token.\n";
    text += "6. Refactor only after it runs correctly.\n";
    text += "7. Save an attempt record with what failed and what you fixed.\n\n";
    text += "CORRECTNESS EXPECTATION\n";
    text += "The built-in verifier looks for this output token: " + expectedOutputTokenForExercise(exercise) + "\n";
    return text;
}

QString MainWindow::moduleSummaryText(const Module& module) const
{
    return module.title + "\nLevel: " + module.level + "\n\n" + module.summary + "\n\nLessons: " + QString::number(module.lessons.size()) + "\nExercises: " + QString::number(module.exercises.size()) + "\nQuiz questions: " + QString::number(module.quiz.size());
}

QString MainWindow::quizSummaryText() const
{
    const Module* module = (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size()) ? &m_modules[m_currentModuleIndex] : nullptr;
    if (!module) return {};
    return QString("Quiz bank for %1 contains %2 questions in v21. Questions now include v21 verification and debugging prompts tied to runnable exercise packs.").arg(module->title).arg(module->quiz.size());
}

QString MainWindow::expectedOutputTokenForExercise(const Exercise& exercise) const
{
    QString token = exercise.id.toUpper();
    if (token.startsWith("EX_"))
    {
        token = token.mid(3);
    }
    for (QChar& ch : token)
    {
        if (!ch.isLetterOrNumber())
        {
            ch = '_';
        }
    }
    return "PASS_" + token;
}

QString MainWindow::starterFolderForExercise(const QString& languageId, const Exercise& exercise) const
{
    const QString base = QCoreApplication::applicationDirPath() + "/examples/v21_verified_exercises";
    const QString folder = base + "/" + languageId + "/" + exercise.id;
    return folder;
}

QString MainWindow::commandForRunner(const QString& action) const
{
    const LanguageTrack* track = (m_currentLanguageIndex >= 0 && m_currentLanguageIndex < m_languageTracks.size()) ? &m_languageTracks[m_currentLanguageIndex] : nullptr;
    const Module* module = (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size()) ? &m_modules[m_currentModuleIndex] : nullptr;
    if (!track || !module || m_currentExerciseIndex < 0 || m_currentExerciseIndex >= module->exercises.size()) return {};
    const QString folder = starterFolderForExercise(track->id, module->exercises[m_currentExerciseIndex]);
    if (track->id.contains("python")) return action == "test" ? "python -m unittest" : "python main.py";
    if (track->id.contains("cpp")) return action == "build" ? "g++ -std=c++17 main.cpp -o exercise.exe" : "exercise.exe";
    if (track->id.contains("javascript")) return action == "test" ? "node test.js" : "node main.js";
    if (track->id.contains("typescript")) return action == "build" ? "npx tsc" : "node dist/main.js";
    if (track->id.contains("java") && !track->id.contains("javascript")) return action == "build" ? "javac Main.java" : "java Main";
    if (track->id.contains("csharp")) return action == "build" ? "dotnet build" : "dotnet run";
    if (track->id.contains("go")) return action == "test" ? "go test ./..." : "go run .";
    if (track->id.contains("rust")) return action == "test" ? "cargo test" : "cargo run";
    if (track->id.contains("sql")) return "sqlite3 practice.db < queries.sql";
    if (track->id.contains("kotlin")) return action == "build" ? "kotlinc Main.kt -include-runtime -d main.jar" : "java -jar main.jar";
    Q_UNUSED(folder);
    return {};
}

void MainWindow::copyExerciseToRunner()
{
    m_sidebar->setCurrentRow(3);
    refreshAllTabs();
}

void MainWindow::runRunnerAction(const QString& action)
{
    Exercise* exercise = currentExercise();
    LanguageTrack* track = currentLanguageTrack();
    if (!exercise || !track || !m_runnerProcess) return;
    const QString folder = starterFolderForExercise(track->id, *exercise);
    const QString command = commandForRunner(action == "build" ? "build" : action == "test" ? "test" : "run");
    QDir().mkpath(folder);
    m_lastRunnerOutput.clear();
    appendRunnerOutput("\n> Working folder: " + folder + "\n> " + command + "\n");
    m_runnerProcess->setWorkingDirectory(folder);
#ifdef Q_OS_WIN
    m_runnerProcess->start("cmd.exe", {"/C", command});
#else
    m_runnerProcess->start("/bin/sh", {"-lc", command});
#endif
}

void MainWindow::verifyRunnerOutput()
{
    Exercise* exercise = currentExercise();
    if (!exercise) return;
    const QString token = expectedOutputTokenForExercise(*exercise);
    const bool correct = m_lastRunnerOutput.contains(token, Qt::CaseInsensitive);
    appendRunnerOutput(correct ? "\n[VERIFY] Correct. Expected token found: " + token + "\n" : "\n[VERIFY] Not verified yet. Expected token missing: " + token + "\n");
    if (correct)
    {
        m_progress.setCompleted(exercise->id, true);
        recordRunnerAttempt("verified_correct");
    }
    else
    {
        recordRunnerAttempt("verification_failed");
    }
    refreshAllTabs();
}

void MainWindow::appendRunnerOutput(const QString& text)
{
    m_lastRunnerOutput += text;
    if (m_runnerOutput)
    {
        m_runnerOutput->append(text.trimmed());
    }
}

void MainWindow::recordRunnerAttempt(const QString& status)
{
    Exercise* exercise = currentExercise();
    LanguageTrack* track = currentLanguageTrack();
    Module* module = currentModule();
    if (!exercise || !track || !module) return;
    m_progress.recordCodeAttempt(track->name, module->title, exercise->id, exercise->difficulty, commandForRunner("run"), m_lastRunnerOutput.left(500), status, "Recorded from v21 verified exercise runner.");
}

void MainWindow::prepareAlgorithmSteps()
{
    m_algorithmSteps.clear();
    const QString alg = m_algorithmSelector ? m_algorithmSelector->currentText() : "Binary Search";
    if (alg == "Binary Search")
    {
        m_algorithmComplexity->setText("Binary Search: O(log n) time, O(1) iterative space.");
        m_algorithmSteps = {"Start with sorted values [1, 3, 5, 7, 9, 11, 13]. Target = 9.", "Check middle value 7.", "9 is larger than 7, so discard the left half.", "Check middle of remaining [9, 11, 13], value 11.", "9 is smaller than 11, so discard the right side.", "Found 9. Return its index."};
    }
    else if (alg == "Bubble Sort")
    {
        m_algorithmComplexity->setText("Bubble Sort: O(n^2) time, O(1) space.");
        m_algorithmSteps = {"Start with [5, 1, 4, 2].", "Compare 5 and 1; swap.", "Compare 5 and 4; swap.", "Compare 5 and 2; swap. Largest value is now at the end.", "Repeat passes until no swaps occur.", "Sorted result: [1, 2, 4, 5]."};
    }
    else
    {
        m_algorithmComplexity->setText(alg + ": trace the state, explain each operation, then compare time and space cost.");
        m_algorithmSteps = {"Define the data structure state.", "Apply the first operation.", "Record what changed.", "Explain why the operation is correct.", "State the time complexity.", "Connect the algorithm to a real app use case."};
    }
}

void MainWindow::resetAlgorithm()
{
    m_algorithmStepIndex = 0;
    prepareAlgorithmSteps();
    if (m_algorithmOutput) m_algorithmOutput->setPlainText("Press Next Step to walk through the algorithm.");
}

void MainWindow::nextAlgorithmStep()
{
    if (m_algorithmSteps.isEmpty()) prepareAlgorithmSteps();
    if (m_algorithmStepIndex < m_algorithmSteps.size())
    {
        m_algorithmOutput->append(QString::number(m_algorithmStepIndex + 1) + ". " + m_algorithmSteps[m_algorithmStepIndex]);
        ++m_algorithmStepIndex;
    }
    else
    {
        m_algorithmOutput->append("Done. Now explain the algorithm without looking, then implement it in your selected language track.");
    }
}

void MainWindow::exportProgressSummary()
{
    const QString folder = QCoreApplication::applicationDirPath() + "/progress_exports";
    QDir().mkpath(folder);
    QFile file(folder + "/v21_verified_progress_summary.md");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "# CS Bootcamp Desktop v21 Progress Summary\n\n";
        out << m_progress.exportMarkdownSummary();
        out << "\n\n## Code Attempts\n\n" << m_progress.codeAttemptMarkdown();
    }
    QMessageBox::information(this, "Exported", "Progress summary exported to progress_exports/v21_verified_progress_summary.md");
}

void MainWindow::refreshAllTabs()
{
    Module* module = currentModule();
    Lesson* lesson = currentLesson();
    Exercise* exercise = currentExercise();
    QuizQuestion* quiz = currentQuizQuestion();
    LanguageTrack* track = currentLanguageTrack();

    if (m_moduleSelector && m_moduleSelector->currentIndex() != m_currentModuleIndex) m_moduleSelector->setCurrentIndex(m_currentModuleIndex);
    if (m_lessonList)
    {
        m_lessonList->blockSignals(true);
        m_lessonList->clear();
        if (module) for (const Lesson& l : module->lessons) m_lessonList->addItem((m_progress.isCompleted(l.id) ? "✓ " : "□ ") + l.title);
        m_lessonList->setCurrentRow(m_currentLessonIndex);
        m_lessonList->blockSignals(false);
    }
    if (m_exerciseList)
    {
        m_exerciseList->blockSignals(true);
        m_exerciseList->clear();
        if (module) for (const Exercise& e : module->exercises) m_exerciseList->addItem((m_progress.isCompleted(e.id) ? "✓ " : "□ ") + e.title);
        m_exerciseList->setCurrentRow(m_currentExerciseIndex);
        m_exerciseList->blockSignals(false);
    }
    if (m_quizList)
    {
        m_quizList->blockSignals(true);
        m_quizList->clear();
        if (module) for (const QuizQuestion& q : module->quiz) m_quizList->addItem((m_progress.isCompleted(q.id) ? "✓ " : "□ ") + q.question.left(70));
        m_quizList->setCurrentRow(m_currentQuizIndex);
        m_quizList->blockSignals(false);
    }
    if (m_languageList)
    {
        m_languageList->blockSignals(true);
        m_languageList->clear();
        for (const LanguageTrack& t : m_languageTracks) m_languageList->addItem(t.name);
        m_languageList->setCurrentRow(m_currentLanguageIndex);
        m_languageList->blockSignals(false);
    }
    if (m_runnerLanguage && m_runnerLanguage->currentIndex() != m_currentLanguageIndex) m_runnerLanguage->setCurrentIndex(m_currentLanguageIndex);

    const int totalItems = [&]
    {
        int total = 0;
        for (const Module& m : m_modules) total += m.lessons.size() + m.exercises.size() + m.quiz.size();
        return total;
    }();
    const int completed = m_progress.completedCount();
    if (m_dashboardSummary) m_dashboardSummary->setText(QString("Selected module: %1\nSelected lesson: %2\nSelected exercise: %3\nSelected language: %4\nCompleted tracked items: %5")
        .arg(module ? module->title : "None")
        .arg(lesson ? lesson->title : "None")
        .arg(exercise ? exercise->title : "None")
        .arg(track ? track->name : "None")
        .arg(completed));
    if (m_dashboardProgress)
    {
        m_dashboardProgress->setRange(0, std::max(1, totalItems));
        m_dashboardProgress->setValue(std::min(completed, totalItems));
        m_dashboardProgress->setFormat(QString("%1 / %2 completed").arg(std::min(completed, totalItems)).arg(totalItems));
    }
    if (m_dashboardPlan) m_dashboardPlan->setPlainText("v21 keeps the simplified v20 tab structure and adds verified multi-language exercise packs. The remaining tabs share one selected module, lesson, exercise, quiz, and language. Pick a module in Learning Path, read the detailed objective/checklist/practice guidance, send the connected exercise to the Runner, verify the output, take the module quiz, save notes, and watch Progress Database update.\n\nv21 adds verified exercise starter packs across every major language track. Each folder includes a README, run script, test script when practical, and code that prints the exact PASS token the app expects. This lets the user learn the workflow first, then replace starter code with their own solution and verify it again.");

    if (m_lessonTitle && lesson) m_lessonTitle->setText(lesson->title);
    if (m_lessonBody && lesson) m_lessonBody->setPlainText(lessonDetailText(*lesson));
    if (m_exerciseTitle && exercise) m_exerciseTitle->setText(exercise->title);
    if (m_exerciseBody && exercise) m_exerciseBody->setPlainText(exerciseDetailText(*exercise));
    if (m_exerciseCode && exercise && m_exerciseCode->toPlainText().isEmpty()) m_exerciseCode->setPlainText(exercise->starterCode);

    if (m_runnerContext && module && exercise && track)
    {
        m_runnerContext->setText("Current context: " + module->title + " → " + exercise->title + " → " + track->name + ". Verification expects token: " + expectedOutputTokenForExercise(*exercise));
    }
    if (m_runnerCommandPreview && exercise && track)
    {
        m_runnerCommandPreview->setPlainText("Build: " + commandForRunner("build") + "\nRun: " + commandForRunner("run") + "\nTest: " + commandForRunner("test") + "\nFolder: " + starterFolderForExercise(track->id, *exercise));
    }

    if (m_quizTitle && quiz) m_quizTitle->setText("Question " + QString::number(m_currentQuizIndex + 1));
    if (m_quizBody && quiz) m_quizBody->setPlainText(quizSummaryText() + "\n\n" + quiz->question);
    if (m_quizChoices && quiz)
    {
        m_quizChoices->blockSignals(true);
        m_quizChoices->clear();
        for (const QString& choice : quiz->choices) m_quizChoices->addItem(choice);
        m_quizChoices->blockSignals(false);
    }
    if (m_quizFeedback) m_quizFeedback->setText("Choose an answer, then check it. The explanation is part of the learning process.");

    if (m_languageTitle && track) m_languageTitle->setText(track->name);
    if (m_languageBody && track)
    {
        m_languageBody->setPlainText("Professional use:\n" + track->professionalUse + "\n\nWhy learn it:\n" + track->whyLearnIt + "\n\nSetup command:\n" + track->setupCommand + "\n\nInstall checks:\n" + bullets(track->installChecks) + "\nRun commands:\n" + bullets(track->runCommands) + "\nStarter files:\n" + bullets(track->starterFiles) + "\nFirst-week plan:\n" + numbered(track->firstWeekPlan) + "\nCore topics:\n" + bullets(track->coreTopics) + "\nBeginner milestones:\n" + bullets(track->beginnerMilestones) + "\nProfessional milestones:\n" + bullets(track->professionalMilestones));
    }

    if (m_contentBody && module) m_contentBody->setPlainText("Current module content pack\n\n" + moduleSummaryText(*module) + "\n\nEvery lesson now includes detailed how-to guidance. Every checklist item has a concrete method: define it, build a tiny example, test it, and write evidence in notes. Add more content packs in content_packs/ without adding more cluttered tabs.");
    if (m_aiTutorBody && lesson && exercise) m_aiTutorBody->setPlainText("Offline tutor prompt for current context:\n\nExplain this lesson in simple terms: " + lesson->title + "\nObjective: " + lesson->objective + "\n\nThen give a hint ladder for this exercise: " + exercise->title + "\nPrompt: " + exercise->prompt + "\n\nDo not solve it immediately. Start with a concept hint, then a pseudocode hint, then a debugging checklist.");
    if (m_modelAdapterBody) m_modelAdapterBody->setPlainText("The model adapter remains optional. v21 keeps Offline Tutor as the default and connects AI prompts to the selected lesson/exercise context. Hosted providers can be added later without changing the learner workflow.");
    if (m_databaseBody) m_databaseBody->setPlainText("Database path:\n" + m_progress.databasePath() + "\n\nCompleted items: " + QString::number(m_progress.completedCount()) + "\nSaved notes: " + QString::number(m_progress.notesCount()) + "\nStudy events: " + QString::number(m_progress.studyEventCount()) + "\nCode attempts: " + QString::number(m_progress.codeAttemptCount()) + "\n\nRecent study events:\n" + m_progress.recentStudyEvents(8).join("\n") + "\n\nRecent code attempts:\n" + m_progress.codeAttemptRows(8).join("\n"));
    if (m_instructorBody && module) m_instructorBody->setPlainText("Instructor view for current module:\n\n" + module->title + "\n\nAssignment design:\n1. Require the learner to complete the detailed lesson checklist.\n2. Require a verified runner output token for the connected exercise.\n3. Require quiz mastery for the module.\n4. Require notes that explain what failed and how it was fixed.\n\nRubric: concept explanation, working code, verification evidence, debugging reflection, professional readability.");
    if (m_capstoneBody) m_capstoneBody->setPlainText("Final capstone now builds from verified practice history. The learner should choose one advanced capstone only after completing lessons, exercises, quizzes, and code-attempt records in the selected specialization.");
    if (m_advancedBody) m_advancedBody->setPlainText("Advanced learning extension: use the same workflow for senior topics. Read objective, complete checklist, implement practice, verify output, record attempt, write notes, then explain tradeoffs. Suggested advanced case studies: tiny database engine, job queue, interpreter, high-performance API, secure auth system, AI/RAG document system.");
    if (m_projectGeneratorBody && track && module) m_projectGeneratorBody->setPlainText("Project generator direction for current context:\n\nLanguage: " + track->name + "\nModule: " + module->title + "\n\nGenerate a starter repo that includes README, src, tests, run script, expected output token, and a verification checklist. v21 keeps this tab because it supports practice and verified learning rather than portfolio display.");
    if (m_notesContext) m_notesContext->setText("Notes are attached to current lesson context: " + currentContextId());
    if (m_notesEditor) m_notesEditor->setPlainText(m_progress.notesFor(currentContextId()));
    if (m_algorithmOutput && m_algorithmSteps.isEmpty()) resetAlgorithm();
}
