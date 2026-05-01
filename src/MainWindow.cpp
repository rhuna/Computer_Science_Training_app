#include "MainWindow.h"

#include <algorithm>

#include <QApplication>
#include <QBoxLayout>
#include <QDir>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
#include <QFormLayout>
#include <QCoreApplication>
#include <QUrl>
#include <QTextCursor>
#include <QStringList>
#include <QFileDialog>
#include <QFrame>
#include <QCoreApplication>
#include <QUrl>
#include <QTextCursor>
#include <QStringList>
#include <QGroupBox>
#include <QMessageBox>
#include <QScrollArea>
#include <QTextStream>
#include <QStandardPaths>
#include <QtGlobal>

namespace
{
    QLabel* makeHeader(const QString& text)
    {
        QLabel* label = new QLabel(text);
        label->setObjectName("pageHeader");
        label->setWordWrap(true);
        return label;
    }

    QTextEdit* makeReadOnlyText(int minimumHeight = 240)
    {
        QTextEdit* text = new QTextEdit;
        text->setReadOnly(true);
        text->setMinimumHeight(minimumHeight);
        return text;
    }

    QString bulletList(const QVector<QString>& values)
    {
        QString output;
        for (const QString& value : values)
        {
            output += "• " + value + "\n";
        }
        return output;
    }

    QString numberedList(const QVector<QString>& values)
    {
        QString output;
        int number = 1;
        for (const QString& value : values)
        {
            output += QString::number(number++) + ". " + value + "\n";
        }
        return output;
    }
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_modules(BootcampContent::createDefaultModules())
    , m_languageTracks(BootcampContent::createLanguageTracks())
    , m_careerPaths(BootcampContent::createCareerPaths())
    , m_progress(QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).filePath("progress_v7.json"))
{
    QDir().mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    m_progress.load();
    buildLayout();
    applyAppStyle();
    refreshAllPages();
    setWindowTitle("CS Bootcamp Desktop v7 - Multi-Language Project Generator");
    resize(1480, 900);
}

void MainWindow::buildLayout()
{
    QWidget* root = new QWidget;
    QHBoxLayout* rootLayout = new QHBoxLayout(root);
    rootLayout->setContentsMargins(14, 14, 14, 14);
    rootLayout->setSpacing(14);

    buildSidebar();
    buildPages();

    rootLayout->addWidget(m_sidebar, 0);
    rootLayout->addWidget(m_pages, 1);
    setCentralWidget(root);
}

void MainWindow::buildSidebar()
{
    m_sidebar = new QListWidget;
    m_sidebar->setObjectName("sidebar");
    m_sidebar->setFixedWidth(280);
    m_sidebar->addItems({
        "Dashboard",
        "Curriculum Map",
        "Lessons",
        "Coding Exercises",
        "Exercise Runner",
        "Algorithm Visualizer",
        "Quiz Trainer",
        "Portfolio Projects",
        "Language Tracks",
        "Language Workspace",
        "Career Paths",
        "Progress Tracker",
        "Notes",
        "Project Generator"
    });
    m_sidebar->setCurrentRow(0);

    connect(m_sidebar, &QListWidget::currentRowChanged, this, [this](int row)
    {
        if (row >= 0 && row < m_pages->count())
        {
            m_pages->setCurrentIndex(row);
            refreshAllPages();
        }
    });
}

void MainWindow::buildPages()
{
    m_pages = new QStackedWidget;
    m_pages->addWidget(createDashboardPage());
    m_pages->addWidget(createCurriculumPage());
    m_pages->addWidget(createLessonPage());
    m_pages->addWidget(createExercisePage());
    m_pages->addWidget(createExerciseRunnerPage());
    m_pages->addWidget(createAlgorithmVisualizerPage());
    m_pages->addWidget(createQuizPage());
    m_pages->addWidget(createProjectsPage());
    m_pages->addWidget(createLanguageTracksPage());
    m_pages->addWidget(createLanguageWorkspacePage());
    m_pages->addWidget(createCareerPathsPage());
    m_pages->addWidget(createProgressPage());
    m_pages->addWidget(createNotesPage());
    m_pages->addWidget(createProjectGeneratorPage());
}

void MainWindow::applyAppStyle()
{
    qApp->setStyleSheet(R"(
        QWidget { font-family: Segoe UI, Arial; font-size: 14px; color: #172033; }
        QMainWindow, QWidget { background: #f4f6fb; }
        QListWidget#sidebar { background: #111827; color: #e5e7eb; border-radius: 18px; padding: 10px; }
        QListWidget#sidebar::item { padding: 14px 12px; border-radius: 12px; margin: 3px; }
        QListWidget#sidebar::item:selected { background: #2563eb; color: white; }
        QFrame#card, QGroupBox { background: white; border: 1px solid #d8deea; border-radius: 18px; padding: 14px; }
        QLabel#pageHeader { font-size: 26px; font-weight: 800; color: #0f172a; }
        QLabel#sectionTitle { font-size: 18px; font-weight: 700; color: #1d4ed8; }
        QLabel#smallTitle { font-size: 15px; font-weight: 800; color: #334155; }
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
    layout->setSpacing(14);

    m_dashboardTitle = makeHeader("Computer Science Bootcamp Dashboard");
    m_dashboardSummary = new QLabel;
    m_dashboardSummary->setWordWrap(true);
    m_dashboardRoadmap = new QLabel;
    m_dashboardRoadmap->setWordWrap(true);
    m_dashboardRoadmap->setObjectName("sectionTitle");
    m_dashboardProgress = new QProgressBar;

    QFrame* card = new QFrame;
    card->setObjectName("card");
    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->addWidget(m_dashboardSummary);
    cardLayout->addWidget(m_dashboardProgress);
    cardLayout->addWidget(m_dashboardRoadmap);

    QLabel* howToUse = new QLabel("Use this like a serious bootcamp: foundations first, then programming core, algorithms, systems, engineering practices, and finally one specialization. Choose a language track, build the same core exercises in multiple languages, then finish with a capstone that proves you can ship professional software.");
    howToUse->setWordWrap(true);

    QLabel* languageNote = new QLabel("v7 adds a multi-language project generator that creates starter repositories with README files, source folders, test folders, and run scripts. v6 expands the platform into a visual algorithm trainer with Big-O practice, sorting walkthroughs, search tracing, stack/queue models, graph traversal drills, and hash table reasoning. v5 expanded the platform into a deeper professional CS curriculum while keeping major industry language tracks plus a hands-on Language Workspace: C++, Python, JavaScript, TypeScript, Java, C#, Go, Rust, SQL, and Kotlin. The curriculum is no longer only C++; C++ remains the app implementation language and one professional track, while the workspace shows setup checks, starter files, and a first-week plan; the Exercise Runner can launch local run, build, and test commands for trusted starter folders.");
    languageNote->setWordWrap(true);
    languageNote->setObjectName("sectionTitle");

    layout->addWidget(m_dashboardTitle);
    layout->addWidget(card);
    layout->addWidget(howToUse);
    layout->addWidget(languageNote);
    layout->addStretch();
    return page;
}

QWidget* MainWindow::createCurriculumPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setSpacing(12);
    layout->addWidget(makeHeader("Extensive CS Curriculum Map"));

    m_moduleSelector = new QComboBox;
    for (const Module& module : m_modules)
    {
        m_moduleSelector->addItem(module.title);
    }
    connect(m_moduleSelector, &QComboBox::currentIndexChanged, this, [this](int index){ selectModule(index); });

    m_moduleSummary = new QLabel;
    m_moduleSummary->setWordWrap(true);
    m_moduleSummary->setObjectName("sectionTitle");

    m_lessonList = new QListWidget;
    m_exerciseList = new QListWidget;
    m_quizList = new QListWidget;
    m_projectList = new QListWidget;

    connect(m_lessonList, &QListWidget::currentRowChanged, this, [this](int index){ selectLesson(index); });
    connect(m_exerciseList, &QListWidget::currentRowChanged, this, [this](int index){ selectExercise(index); });
    connect(m_quizList, &QListWidget::currentRowChanged, this, [this](int index){ selectQuizQuestion(index); });
    connect(m_projectList, &QListWidget::currentRowChanged, this, [this](int index){ selectProject(index); });

    QHBoxLayout* lists = new QHBoxLayout;
    auto addListCard = [lists](const QString& title, QListWidget* list)
    {
        QGroupBox* box = new QGroupBox(title);
        QVBoxLayout* boxLayout = new QVBoxLayout(box);
        boxLayout->addWidget(list);
        lists->addWidget(box);
    };

    addListCard("Lessons", m_lessonList);
    addListCard("Exercises", m_exerciseList);
    addListCard("Quiz", m_quizList);
    addListCard("Projects", m_projectList);

    layout->addWidget(m_moduleSelector);
    layout->addWidget(m_moduleSummary);
    layout->addLayout(lists, 1);
    return page;
}

QWidget* MainWindow::createLessonPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    m_lessonTitle = makeHeader("Lesson");
    m_lessonBody = makeReadOnlyText(420);
    m_lessonCompleteButton = new QPushButton("Mark Lesson Complete");
    connect(m_lessonCompleteButton, &QPushButton::clicked, this, [this]
    {
        if (Lesson* lesson = currentLesson())
        {
            m_progress.setCompleted(lesson->id, !m_progress.isCompleted(lesson->id));
            refreshAllPages();
        }
    });
    layout->addWidget(m_lessonTitle);
    layout->addWidget(m_lessonBody, 1);
    layout->addWidget(m_lessonCompleteButton);
    return page;
}

QWidget* MainWindow::createExercisePage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    m_exerciseTitle = makeHeader("Coding Exercise");
    m_exerciseBody = makeReadOnlyText(260);
    m_codeEditor = new QTextEdit;
    m_codeEditor->setPlaceholderText("Write or paste your solution here. v4 adds run, build, and test launchers per language.");
    m_codeEditor->setMinimumHeight(260);
    m_exerciseCompleteButton = new QPushButton("Mark Exercise Complete");
    connect(m_exerciseCompleteButton, &QPushButton::clicked, this, [this]
    {
        if (Exercise* exercise = currentExercise())
        {
            m_progress.setCompleted(exercise->id, !m_progress.isCompleted(exercise->id));
            refreshAllPages();
        }
    });
    layout->addWidget(m_exerciseTitle);
    layout->addWidget(m_exerciseBody);
    layout->addWidget(new QLabel("Practice editor:"));
    layout->addWidget(m_codeEditor, 1);
    layout->addWidget(m_exerciseCompleteButton);
    return page;
}


QWidget* MainWindow::createExerciseRunnerPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setSpacing(12);

    layout->addWidget(makeHeader("Exercise Runner - Build, Run, Test"));

    QLabel* warning = new QLabel("v4 can launch local commands for the starter folders that ship with this repo. Only run commands in folders you trust. This runner is designed for your own bootcamp exercises, not unknown code from the internet.");
    warning->setWordWrap(true);
    warning->setObjectName("sectionTitle");
    layout->addWidget(warning);

    QGroupBox* controls = new QGroupBox("Runner Controls");
    QVBoxLayout* controlsLayout = new QVBoxLayout(controls);

    m_runnerLanguageSelector = new QComboBox;
    for (const LanguageTrack& track : m_languageTracks)
    {
        m_runnerLanguageSelector->addItem(track.name);
    }
    connect(m_runnerLanguageSelector, &QComboBox::currentIndexChanged, this, [this](int index)
    {
        refreshRunnerForLanguage(index);
    });

    m_runnerWorkingDirectory = new QLineEdit;
    m_runnerWorkingDirectory->setPlaceholderText("Folder containing the exercise files for the selected language.");

    QPushButton* browseButton = new QPushButton("Browse Folder");
    connect(browseButton, &QPushButton::clicked, this, [this]
    {
        browseRunnerWorkingDirectory();
    });

    QPushButton* openButton = new QPushButton("Open Folder");
    connect(openButton, &QPushButton::clicked, this, [this]
    {
        openRunnerWorkingDirectory();
    });

    QHBoxLayout* folderRow = new QHBoxLayout;
    folderRow->addWidget(m_runnerWorkingDirectory, 1);
    folderRow->addWidget(browseButton);
    folderRow->addWidget(openButton);

    m_runnerRunButton = new QPushButton("Run");
    m_runnerBuildButton = new QPushButton("Build / Compile");
    m_runnerTestButton = new QPushButton("Test / Check");
    m_runnerStopButton = new QPushButton("Stop Process");

    connect(m_runnerRunButton, &QPushButton::clicked, this, [this]
    {
        const int index = m_runnerLanguageSelector ? m_runnerLanguageSelector->currentIndex() : -1;
        if (index >= 0 && index < m_languageTracks.size()) runRunnerCommand(commandForTrack(m_languageTracks[index], "run"));
    });
    connect(m_runnerBuildButton, &QPushButton::clicked, this, [this]
    {
        const int index = m_runnerLanguageSelector ? m_runnerLanguageSelector->currentIndex() : -1;
        if (index >= 0 && index < m_languageTracks.size()) runRunnerCommand(commandForTrack(m_languageTracks[index], "build"));
    });
    connect(m_runnerTestButton, &QPushButton::clicked, this, [this]
    {
        const int index = m_runnerLanguageSelector ? m_runnerLanguageSelector->currentIndex() : -1;
        if (index >= 0 && index < m_languageTracks.size()) runRunnerCommand(commandForTrack(m_languageTracks[index], "test"));
    });
    connect(m_runnerStopButton, &QPushButton::clicked, this, [this]
    {
        if (m_runnerProcess && m_runnerProcess->state() != QProcess::NotRunning)
        {
            m_runnerOutput->append("\n[runner] Stop requested. Terminating process...");
            m_runnerProcess->terminate();
        }
    });

    QHBoxLayout* buttonRow = new QHBoxLayout;
    buttonRow->addWidget(m_runnerRunButton);
    buttonRow->addWidget(m_runnerBuildButton);
    buttonRow->addWidget(m_runnerTestButton);
    buttonRow->addWidget(m_runnerStopButton);

    controlsLayout->addWidget(new QLabel("Language:"));
    controlsLayout->addWidget(m_runnerLanguageSelector);
    controlsLayout->addWidget(new QLabel("Working folder:"));
    controlsLayout->addLayout(folderRow);
    controlsLayout->addLayout(buttonRow);
    layout->addWidget(controls);

    m_runnerCommandPreview = makeReadOnlyText(130);
    m_runnerOutput = makeReadOnlyText(280);
    m_runnerOutput->setPlaceholderText("Command output will appear here after you press Run, Build, or Test.");

    QGroupBox* commandBox = new QGroupBox("Selected Language Commands");
    QVBoxLayout* commandLayout = new QVBoxLayout(commandBox);
    commandLayout->addWidget(m_runnerCommandPreview);

    QGroupBox* outputBox = new QGroupBox("Console Output");
    QVBoxLayout* outputLayout = new QVBoxLayout(outputBox);
    outputLayout->addWidget(m_runnerOutput);

    layout->addWidget(commandBox);
    layout->addWidget(outputBox, 1);

    m_runnerProcess = new QProcess(this);
    m_runnerProcess->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_runnerProcess, &QProcess::readyReadStandardOutput, this, [this]
    {
        if (!m_runnerOutput || !m_runnerProcess) return;
        m_runnerOutput->moveCursor(QTextCursor::End);
        m_runnerOutput->insertPlainText(QString::fromLocal8Bit(m_runnerProcess->readAllStandardOutput()));
        m_runnerOutput->moveCursor(QTextCursor::End);
    });
    connect(m_runnerProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this](int exitCode, QProcess::ExitStatus status)
    {
        if (!m_runnerOutput) return;
        const QString statusText = status == QProcess::NormalExit ? "normal exit" : "crashed";
        m_runnerOutput->append(QString("\n[runner] Process finished with exit code %1 (%2).").arg(exitCode).arg(statusText));
    });
    connect(m_runnerProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error)
    {
        if (!m_runnerOutput) return;
        m_runnerOutput->append(QString("\n[runner] Process error: %1. Check that the tool is installed and on PATH.").arg(static_cast<int>(error)));
    });

    if (m_runnerLanguageSelector->count() > 0)
    {
        m_runnerLanguageSelector->setCurrentIndex(0);
        refreshRunnerForLanguage(0);
    }

    return page;
}
QWidget* MainWindow::createAlgorithmVisualizerPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setSpacing(12);

    layout->addWidget(makeHeader("Algorithm Trainer and Visualizer"));

    QLabel* intro = new QLabel("v6 adds a visual practice station for the algorithms that appear constantly in CS courses, interviews, backend engineering, systems work, game engines, AI/data pipelines, and security tooling. Use it to step through the logic before you implement the same idea in C++, Python, JavaScript, Java, C#, Go, Rust, SQL, or Kotlin.");
    intro->setWordWrap(true);
    intro->setObjectName("sectionTitle");
    layout->addWidget(intro);

    QGroupBox* controls = new QGroupBox("Visualization Controls");
    QVBoxLayout* controlsLayout = new QVBoxLayout(controls);

    m_algorithmSelector = new QComboBox;
    m_algorithmSelector->addItems({
        "Bubble Sort - compare and swap",
        "Selection Sort - find the minimum",
        "Binary Search - halve the range",
        "Stack - LIFO push/pop",
        "Queue - FIFO enqueue/dequeue",
        "BFS Graph Traversal - breadth first",
        "DFS Graph Traversal - depth first",
        "Hash Table Lookup - key to bucket"
    });

    m_algorithmInput = new QLineEdit;
    m_algorithmInput->setPlaceholderText("Numbers or keys. Example: 7, 2, 9, 1, 5");
    m_algorithmInput->setText("7, 2, 9, 1, 5");

    QHBoxLayout* selectorRow = new QHBoxLayout;
    selectorRow->addWidget(new QLabel("Algorithm:"));
    selectorRow->addWidget(m_algorithmSelector, 1);

    QHBoxLayout* inputRow = new QHBoxLayout;
    inputRow->addWidget(new QLabel("Input:"));
    inputRow->addWidget(m_algorithmInput, 1);

    m_algorithmResetButton = new QPushButton("Reset Visualization");
    m_algorithmStepButton = new QPushButton("Next Step");

    QHBoxLayout* buttonRow = new QHBoxLayout;
    buttonRow->addWidget(m_algorithmResetButton);
    buttonRow->addWidget(m_algorithmStepButton);
    buttonRow->addStretch();

    controlsLayout->addLayout(selectorRow);
    controlsLayout->addLayout(inputRow);
    controlsLayout->addLayout(buttonRow);
    layout->addWidget(controls);

    m_algorithmComplexity = new QLabel;
    m_algorithmComplexity->setWordWrap(true);
    m_algorithmComplexity->setObjectName("smallTitle");
    layout->addWidget(m_algorithmComplexity);

    m_algorithmOutput = makeReadOnlyText(420);
    m_algorithmOutput->setPlaceholderText("Press Reset Visualization, then Next Step to walk through the selected algorithm.");
    layout->addWidget(m_algorithmOutput, 1);

    QLabel* assignment = new QLabel("Professional assignment: after stepping through an algorithm here, implement it in two languages, write a tiny test suite, document Big-O time/space complexity, and explain when you would not use that algorithm in production.");
    assignment->setWordWrap(true);
    layout->addWidget(assignment);

    connect(m_algorithmSelector, &QComboBox::currentIndexChanged, this, [this](int)
    {
        resetAlgorithmVisualizer();
    });
    connect(m_algorithmInput, &QLineEdit::returnPressed, this, [this]
    {
        resetAlgorithmVisualizer();
    });
    connect(m_algorithmResetButton, &QPushButton::clicked, this, [this]
    {
        resetAlgorithmVisualizer();
    });
    connect(m_algorithmStepButton, &QPushButton::clicked, this, [this]
    {
        advanceAlgorithmVisualizer();
    });

    resetAlgorithmVisualizer();
    return page;
}

QWidget* MainWindow::createQuizPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    m_quizTitle = makeHeader("Quiz Trainer");
    m_quizBody = makeReadOnlyText(140);
    m_quizChoices = new QListWidget;
    m_quizFeedback = new QLabel;
    m_quizFeedback->setWordWrap(true);
    m_quizCheckButton = new QPushButton("Check Answer");
    m_quizCompleteButton = new QPushButton("Mark Quiz Question Complete");

    connect(m_quizCheckButton, &QPushButton::clicked, this, [this]
    {
        QuizQuestion* q = currentQuizQuestion();
        if (!q || m_quizChoices->currentRow() < 0)
        {
            m_quizFeedback->setText("Choose an answer first.");
            return;
        }
        const bool correct = m_quizChoices->currentRow() == q->correctIndex;
        m_quizFeedback->setText(QString(correct ? "Correct. " : "Not yet. ") + q->explanation);
    });

    connect(m_quizCompleteButton, &QPushButton::clicked, this, [this]
    {
        if (QuizQuestion* q = currentQuizQuestion())
        {
            m_progress.setCompleted(q->id, !m_progress.isCompleted(q->id));
            refreshAllPages();
        }
    });

    layout->addWidget(m_quizTitle);
    layout->addWidget(m_quizBody);
    layout->addWidget(m_quizChoices);
    layout->addWidget(m_quizFeedback);
    layout->addWidget(m_quizCheckButton);
    layout->addWidget(m_quizCompleteButton);
    return page;
}

QWidget* MainWindow::createProjectsPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    m_projectTitle = makeHeader("Portfolio Project");
    m_projectBody = makeReadOnlyText(480);
    m_projectCompleteButton = new QPushButton("Mark Project Complete");
    connect(m_projectCompleteButton, &QPushButton::clicked, this, [this]
    {
        if (PortfolioProject* project = currentProject())
        {
            m_progress.setCompleted(project->id, !m_progress.isCompleted(project->id));
            refreshAllPages();
        }
    });
    layout->addWidget(m_projectTitle);
    layout->addWidget(m_projectBody, 1);
    layout->addWidget(m_projectCompleteButton);
    return page;
}

QWidget* MainWindow::createLanguageTracksPage()
{
    QWidget* page = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(page);
    layout->setSpacing(14);

    m_languageList = new QListWidget;
    m_languageList->setMinimumWidth(260);
    for (const LanguageTrack& track : m_languageTracks)
    {
        m_languageList->addItem(track.name);
    }
    connect(m_languageList, &QListWidget::currentRowChanged, this, [this](int index){ selectLanguageTrack(index); });

    QVBoxLayout* details = new QVBoxLayout;
    m_languageTitle = makeHeader("Language Tracks");
    m_languageBody = makeReadOnlyText(560);
    details->addWidget(m_languageTitle);
    details->addWidget(m_languageBody, 1);

    layout->addWidget(m_languageList);
    layout->addLayout(details, 1);
    if (m_languageList->count() > 0) m_languageList->setCurrentRow(0);
    return page;
}


QWidget* MainWindow::createLanguageWorkspacePage()
{
    QWidget* page = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(page);
    layout->setSpacing(14);

    m_workspaceLanguageList = new QListWidget;
    m_workspaceLanguageList->setMinimumWidth(280);
    for (const LanguageTrack& track : m_languageTracks)
    {
        m_workspaceLanguageList->addItem(track.name);
    }
    connect(m_workspaceLanguageList, &QListWidget::currentRowChanged, this, [this](int index){ selectWorkspaceTrack(index); });

    QVBoxLayout* details = new QVBoxLayout;
    m_workspaceTitle = makeHeader("Language Workspace");
    m_workspaceBody = makeReadOnlyText(620);
    details->addWidget(m_workspaceTitle);
    details->addWidget(m_workspaceBody, 1);

    QLabel* note = new QLabel("Use this page as your hands-on setup checklist. v4 includes an optional local command runner for your own starter folders. It also gives you the exact terminal commands, starter file layout, and weekly sprint for each language so you can build safely in your normal project folders.");
    note->setWordWrap(true);
    note->setObjectName("sectionTitle");
    details->addWidget(note);

    layout->addWidget(m_workspaceLanguageList);
    layout->addLayout(details, 1);
    if (m_workspaceLanguageList->count() > 0) m_workspaceLanguageList->setCurrentRow(0);
    return page;
}

QWidget* MainWindow::createCareerPathsPage()
{
    QWidget* page = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(page);
    layout->setSpacing(14);

    m_careerList = new QListWidget;
    m_careerList->setMinimumWidth(310);
    for (const CareerPath& path : m_careerPaths)
    {
        m_careerList->addItem(path.title);
    }
    connect(m_careerList, &QListWidget::currentRowChanged, this, [this](int index){ selectCareerPath(index); });

    QVBoxLayout* details = new QVBoxLayout;
    m_careerTitle = makeHeader("Career Paths");
    m_careerBody = makeReadOnlyText(560);
    details->addWidget(m_careerTitle);
    details->addWidget(m_careerBody, 1);

    layout->addWidget(m_careerList);
    layout->addLayout(details, 1);
    if (m_careerList->count() > 0) m_careerList->setCurrentRow(0);
    return page;
}

QWidget* MainWindow::createProgressPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(makeHeader("Progress Tracker"));
    m_progressStats = new QLabel;
    m_progressStats->setObjectName("sectionTitle");
    m_progressStats->setWordWrap(true);
    m_progressList = new QListWidget;
    layout->addWidget(m_progressStats);
    layout->addWidget(m_progressList, 1);
    return page;
}

QWidget* MainWindow::createNotesPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(makeHeader("Bootcamp Notes"));
    m_notesContext = new QLabel;
    m_notesContext->setWordWrap(true);
    m_notesEditor = new QTextEdit;
    QPushButton* save = new QPushButton("Save Notes for Current Item");
    connect(save, &QPushButton::clicked, this, [this]
    {
        const QString itemId = currentItemIdForNotes();
        if (!itemId.isEmpty())
        {
            m_progress.setNotesFor(itemId, m_notesEditor->toPlainText());
            QMessageBox::information(this, "Notes Saved", "Your notes were saved to the local progress file.");
        }
    });
    layout->addWidget(m_notesContext);
    layout->addWidget(m_notesEditor, 1);
    layout->addWidget(save);
    return page;
}

void MainWindow::refreshAllPages()
{
    selectModule(m_currentModuleIndex);
    selectLanguageTrack(m_currentLanguageIndex);
    selectWorkspaceTrack(m_currentWorkspaceIndex);
    selectCareerPath(m_currentCareerIndex);

    const int total = totalTrackableItems();
    const int complete = m_progress.completedCount();
    const int percent = total == 0 ? 0 : (complete * 100) / total;

    if (m_dashboardSummary)
    {
        m_dashboardSummary->setText(QString("You have completed %1 of %2 trackable bootcamp items across CS foundations, programming, algorithms, systems, engineering, and specialization work.").arg(complete).arg(total));
    }
    if (m_dashboardProgress)
    {
        m_dashboardProgress->setRange(0, 100);
        m_dashboardProgress->setValue(percent);
        m_dashboardProgress->setFormat(QString("%1% complete").arg(percent));
    }
    if (m_dashboardRoadmap)
    {
        m_dashboardRoadmap->setText("Recommended progression: Foundations → Programming Core → Algorithms → Systems/Databases → Engineering Practices → Language Track → Career Capstone.");
    }

    if (m_progressStats && m_progressList)
    {
        m_progressStats->setText(QString("Completed: %1 / %2 items. Language tracks, the workspace, and career paths are reference maps in v4; lesson, exercise, quiz, and project items are trackable.").arg(complete).arg(total));
        m_progressList->clear();
        for (const Module& module : m_modules)
        {
            m_progressList->addItem("== " + module.title + " ==");
            for (const Lesson& lessonItem : module.lessons)
                m_progressList->addItem(QString("%1 Lesson: %2").arg(m_progress.isCompleted(lessonItem.id) ? "✅" : "⬜").arg(lessonItem.title));
            for (const Exercise& exerciseItem : module.exercises)
                m_progressList->addItem(QString("%1 Exercise: %2").arg(m_progress.isCompleted(exerciseItem.id) ? "✅" : "⬜").arg(exerciseItem.title));
            for (const QuizQuestion& quizItem : module.quiz)
                m_progressList->addItem(QString("%1 Quiz: %2").arg(m_progress.isCompleted(quizItem.id) ? "✅" : "⬜").arg(quizItem.question));
            for (const PortfolioProject& projectItem : module.projects)
                m_progressList->addItem(QString("%1 Project: %2").arg(m_progress.isCompleted(projectItem.id) ? "✅" : "⬜").arg(projectItem.title));
        }
    }

    if (m_notesContext && m_notesEditor)
    {
        const QString itemId = currentItemIdForNotes();
        m_notesContext->setText("Current notes target: " + itemId);
        m_notesEditor->setPlainText(m_progress.notesFor(itemId));
    }
}

void MainWindow::selectModule(int index)
{
    if (index < 0 || index >= m_modules.size()) return;
    m_currentModuleIndex = index;
    Module& module = m_modules[index];
    if (m_moduleSelector && m_moduleSelector->currentIndex() != index)
        m_moduleSelector->setCurrentIndex(index);
    if (m_moduleSummary)
        m_moduleSummary->setText(module.level + " — " + module.summary);

    auto refill = [](QListWidget* list, const QVector<QString>& names)
    {
        if (!list) return;
        const int previousRow = list->currentRow();
        list->clear();
        for (const QString& name : names) list->addItem(name);
        if (list->count() > 0) list->setCurrentRow(qBound(0, previousRow, list->count() - 1));
    };

    QVector<QString> lessonNames, exerciseNames, quizNames, projectNames;
    for (const Lesson& item : module.lessons) lessonNames.push_back(item.title);
    for (const Exercise& item : module.exercises) exerciseNames.push_back(item.title);
    for (const QuizQuestion& item : module.quiz) quizNames.push_back(item.question);
    for (const PortfolioProject& item : module.projects) projectNames.push_back(item.title);

    refill(m_lessonList, lessonNames);
    refill(m_exerciseList, exerciseNames);
    refill(m_quizList, quizNames);
    refill(m_projectList, projectNames);

    selectLesson(m_currentLessonIndex);
    selectExercise(m_currentExerciseIndex);
    selectQuizQuestion(m_currentQuizIndex);
    selectProject(m_currentProjectIndex);
}

void MainWindow::selectLesson(int index)
{
    Module* module = currentModule();
    if (!module || index < 0 || index >= module->lessons.size()) return;
    m_currentLessonIndex = index;
    Lesson& selectedLesson = module->lessons[index];
    if (m_lessonTitle) m_lessonTitle->setText(selectedLesson.title);
    if (m_lessonBody)
    {
        m_lessonBody->setPlainText("Module:\n" + module->title + "\n\nObjective:\n" + selectedLesson.objective + "\n\nExplanation:\n" + selectedLesson.explanation + "\n\nChecklist:\n" + bulletList(selectedLesson.checklist) + "\nPractice:\n" + bulletList(selectedLesson.practicePrompts));
    }
    if (m_lessonCompleteButton)
    {
        m_lessonCompleteButton->setText(m_progress.isCompleted(selectedLesson.id) ? "Mark Lesson Incomplete" : "Mark Lesson Complete");
    }
}

void MainWindow::selectExercise(int index)
{
    Module* module = currentModule();
    if (!module || index < 0 || index >= module->exercises.size()) return;
    m_currentExerciseIndex = index;
    Exercise& selectedExercise = module->exercises[index];
    if (m_exerciseTitle) m_exerciseTitle->setText(selectedExercise.title + " — " + selectedExercise.difficulty);
    if (m_exerciseBody)
    {
        m_exerciseBody->setPlainText("Module:\n" + module->title + "\n\nPrompt:\n" + selectedExercise.prompt + "\n\nExpected concepts:\n" + selectedExercise.expectedConcepts + "\n\nStarter code:\n" + selectedExercise.starterCode);
    }
    if (m_codeEditor) m_codeEditor->setPlainText(selectedExercise.starterCode);
    if (m_exerciseCompleteButton)
    {
        m_exerciseCompleteButton->setText(m_progress.isCompleted(selectedExercise.id) ? "Mark Exercise Incomplete" : "Mark Exercise Complete");
    }
}

void MainWindow::selectQuizQuestion(int index)
{
    Module* module = currentModule();
    if (!module || index < 0 || index >= module->quiz.size()) return;
    m_currentQuizIndex = index;
    QuizQuestion& q = module->quiz[index];
    if (m_quizTitle) m_quizTitle->setText("Quiz: " + module->title);
    if (m_quizBody) m_quizBody->setPlainText(q.question);
    if (m_quizChoices)
    {
        m_quizChoices->clear();
        m_quizChoices->addItems(q.choices);
    }
    if (m_quizFeedback) m_quizFeedback->clear();
    if (m_quizCompleteButton)
    {
        m_quizCompleteButton->setText(m_progress.isCompleted(q.id) ? "Mark Quiz Question Incomplete" : "Mark Quiz Question Complete");
    }
}

void MainWindow::selectProject(int index)
{
    Module* module = currentModule();
    if (!module || index < 0 || index >= module->projects.size()) return;
    m_currentProjectIndex = index;
    PortfolioProject& selectedProject = module->projects[index];
    if (m_projectTitle) m_projectTitle->setText(selectedProject.title + " — " + selectedProject.level);
    if (m_projectBody)
    {
        m_projectBody->setPlainText("Module:\n" + module->title + "\n\n" + selectedProject.description + "\n\nRequirements:\n" + bulletList(selectedProject.requirements) + "\nStretch goals:\n" + bulletList(selectedProject.stretchGoals));
    }
    if (m_projectCompleteButton)
    {
        m_projectCompleteButton->setText(m_progress.isCompleted(selectedProject.id) ? "Mark Project Incomplete" : "Mark Project Complete");
    }
}

void MainWindow::selectLanguageTrack(int index)
{
    if (index < 0 || index >= m_languageTracks.size()) return;
    m_currentLanguageIndex = index;
    const LanguageTrack& track = m_languageTracks[index];
    if (m_languageList && m_languageList->currentRow() != index) m_languageList->setCurrentRow(index);
    if (m_languageTitle) m_languageTitle->setText(track.name + " Track");
    if (m_languageBody)
    {
        m_languageBody->setPlainText(
            "Professional use:\n" + track.professionalUse +
            "\n\nWhy learn it:\n" + track.whyLearnIt +
            "\n\nSetup direction:\n" + track.setupCommand +
            "\n\nSetup checks:\n" + bulletList(track.installChecks) +
            "\nRun/build commands:\n" + bulletList(track.runCommands) +
            "\nStarter files:\n" + bulletList(track.starterFiles) +
            "\nFirst-week sprint:\n" + numberedList(track.firstWeekPlan) +
            "\nCore topics:\n" + bulletList(track.coreTopics) +
            "\nBeginner milestones:\n" + numberedList(track.beginnerMilestones) +
            "\nProfessional milestones:\n" + numberedList(track.professionalMilestones) +
            "\nPortfolio projects:\n" + bulletList(track.portfolioProjects));
    }
}


void MainWindow::selectWorkspaceTrack(int index)
{
    if (index < 0 || index >= m_languageTracks.size()) return;
    m_currentWorkspaceIndex = index;
    const LanguageTrack& track = m_languageTracks[index];
    if (m_workspaceLanguageList && m_workspaceLanguageList->currentRow() != index) m_workspaceLanguageList->setCurrentRow(index);
    if (m_workspaceTitle) m_workspaceTitle->setText(track.name + " Workspace");
    if (m_workspaceBody)
    {
        m_workspaceBody->setPlainText(
            "Goal:\nUse this workspace to create a real practice folder for " + track.name + ". Do not just read. Build, run, break, debug, test, and document.\n\n" +
            "Professional use:\n" + track.professionalUse +
            "\n\nInstall/setup direction:\n" + track.setupCommand +
            "\n\nEnvironment checks to run in a terminal:\n" + bulletList(track.installChecks) +
            "\nCore run/build/test commands:\n" + bulletList(track.runCommands) +
            "\nRecommended starter file layout:\n" + bulletList(track.starterFiles) +
            "\nSeven-day sprint for this language:\n" + numberedList(track.firstWeekPlan) +
            "\nStarter assignment:\nBuild the Word Frequency Counter, Input Validator, and File Byte Inspector in " + track.name + ". Then write a README explaining what felt different compared with C++ and Python.\n\n" +
            "Professional upgrade assignment:\nTurn one starter exercise into a small portfolio-quality app with tests, error handling, sample input/output, and a clean README.");
    }
}

void MainWindow::selectCareerPath(int index)
{
    if (index < 0 || index >= m_careerPaths.size()) return;
    m_currentCareerIndex = index;
    const CareerPath& path = m_careerPaths[index];
    if (m_careerList && m_careerList->currentRow() != index) m_careerList->setCurrentRow(index);
    if (m_careerTitle) m_careerTitle->setText(path.title);
    if (m_careerBody)
    {
        m_careerBody->setPlainText(
            "Summary:\n" + path.summary +
            "\n\nRequired skills:\n" + bulletList(path.requiredSkills) +
            "\nRecommended languages:\n" + bulletList(path.recommendedLanguages) +
            "\nCapstone ideas:\n" + numberedList(path.capstones));
    }
}


static QStringList splitVisualizationInput(const QString& text)
{
    QStringList raw = text.split(',', Qt::SkipEmptyParts);
    QStringList values;
    for (QString value : raw)
    {
        value = value.trimmed();
        if (!value.isEmpty()) values.push_back(value);
    }
    if (values.isEmpty()) values = {"7", "2", "9", "1", "5"};
    return values;
}

static QVector<int> parseAlgorithmNumbers(const QString& text)
{
    QVector<int> numbers;
    const QStringList values = splitVisualizationInput(text);
    for (const QString& value : values)
    {
        bool ok = false;
        const int parsed = value.toInt(&ok);
        if (ok) numbers.push_back(parsed);
    }
    if (numbers.isEmpty()) numbers = {7, 2, 9, 1, 5};
    return numbers;
}

static QString renderNumbers(const QVector<int>& values, int first = -1, int second = -1)
{
    QStringList parts;
    for (int i = 0; i < values.size(); ++i)
    {
        QString item = QString::number(values[i]);
        if (i == first || i == second) item = "[" + item + "]";
        parts.push_back(item);
    }
    return parts.join("  ");
}

void MainWindow::prepareAlgorithmSteps()
{
    m_algorithmSteps.clear();
    m_algorithmStepIndex = 0;

    const int algorithmIndex = m_algorithmSelector ? m_algorithmSelector->currentIndex() : 0;
    const QString input = m_algorithmInput ? m_algorithmInput->text() : "7, 2, 9, 1, 5";

    if (algorithmIndex == 0)
    {
        QVector<int> values = parseAlgorithmNumbers(input);
        m_algorithmSteps << "Bubble sort repeatedly compares neighboring values and swaps them when the left value is larger.";
        for (int pass = 0; pass < values.size(); ++pass)
        {
            bool swapped = false;
            for (int i = 0; i + 1 < values.size() - pass; ++i)
            {
                m_algorithmSteps << QString("Compare indexes %1 and %2: %3").arg(i).arg(i + 1).arg(renderNumbers(values, i, i + 1));
                if (values[i] > values[i + 1])
                {
                    std::swap(values[i], values[i + 1]);
                    swapped = true;
                    m_algorithmSteps << QString("Swap because left is larger: %1").arg(renderNumbers(values, i, i + 1));
                }
            }
            m_algorithmSteps << QString("End of pass %1: %2").arg(pass + 1).arg(renderNumbers(values));
            if (!swapped) break;
        }
        m_algorithmSteps << "Sorted result: " + renderNumbers(values);
        if (m_algorithmComplexity) m_algorithmComplexity->setText("Bubble Sort Big-O: average/worst O(n^2), best O(n) with early exit, space O(1). Use it to learn swaps, not for large production data.");
        return;
    }

    if (algorithmIndex == 1)
    {
        QVector<int> values = parseAlgorithmNumbers(input);
        m_algorithmSteps << "Selection sort grows a sorted prefix by finding the smallest remaining value and moving it into position.";
        for (int i = 0; i < values.size(); ++i)
        {
            int minIndex = i;
            m_algorithmSteps << QString("Start position %1. Current array: %2").arg(i).arg(renderNumbers(values, i));
            for (int j = i + 1; j < values.size(); ++j)
            {
                m_algorithmSteps << QString("Compare current min index %1 with candidate index %2: %3").arg(minIndex).arg(j).arg(renderNumbers(values, minIndex, j));
                if (values[j] < values[minIndex])
                {
                    minIndex = j;
                    m_algorithmSteps << QString("New minimum found at index %1.").arg(minIndex);
                }
            }
            if (minIndex != i) std::swap(values[i], values[minIndex]);
            m_algorithmSteps << QString("Place minimum into position %1: %2").arg(i).arg(renderNumbers(values, i));
        }
        m_algorithmSteps << "Sorted result: " + renderNumbers(values);
        if (m_algorithmComplexity) m_algorithmComplexity->setText("Selection Sort Big-O: O(n^2) comparisons, O(1) space. Useful for teaching invariants and sorted prefixes.");
        return;
    }

    if (algorithmIndex == 2)
    {
        QVector<int> values = parseAlgorithmNumbers(input);
        std::sort(values.begin(), values.end());
        const int target = values[values.size() / 2];
        int low = 0;
        int high = values.size() - 1;
        m_algorithmSteps << QString("Binary search requires sorted input. Sorted array: %1. Target: %2").arg(renderNumbers(values)).arg(target);
        while (low <= high)
        {
            const int mid = low + (high - low) / 2;
            m_algorithmSteps << QString("Range low=%1, high=%2, mid=%3 -> %4").arg(low).arg(high).arg(mid).arg(renderNumbers(values, mid));
            if (values[mid] == target)
            {
                m_algorithmSteps << QString("Found target %1 at index %2.").arg(target).arg(mid);
                break;
            }
            if (values[mid] < target)
            {
                low = mid + 1;
                m_algorithmSteps << "Target is larger, discard the left half.";
            }
            else
            {
                high = mid - 1;
                m_algorithmSteps << "Target is smaller, discard the right half.";
            }
        }
        if (m_algorithmComplexity) m_algorithmComplexity->setText("Binary Search Big-O: O(log n) time, O(1) iterative space. Only works when the search space is sorted or monotonic.");
        return;
    }

    if (algorithmIndex == 3 || algorithmIndex == 4)
    {
        const QStringList values = splitVisualizationInput(input);
        const bool stackMode = algorithmIndex == 3;
        m_algorithmSteps << (stackMode ? "Stack uses last-in, first-out behavior." : "Queue uses first-in, first-out behavior.");
        QStringList container;
        for (const QString& value : values)
        {
            container.push_back(value);
            m_algorithmSteps << QString(stackMode ? "push(%1): top is the right side -> %2" : "enqueue(%1): back is the right side -> %2").arg(value).arg(container.join(" <- "));
        }
        while (!container.isEmpty())
        {
            const QString removed = stackMode ? container.takeLast() : container.takeFirst();
            m_algorithmSteps << QString(stackMode ? "pop() returns %1. Remaining: %2" : "dequeue() returns %1. Remaining: %2").arg(removed).arg(container.join(" <- "));
        }
        if (m_algorithmComplexity) m_algorithmComplexity->setText(stackMode ? "Stack operations: push/pop/top are O(1). Used in undo systems, parsers, DFS, call stacks, and expression evaluation." : "Queue operations: enqueue/dequeue/front are O(1) with the right structure. Used in BFS, job queues, event loops, and producer/consumer systems.");
        return;
    }

    if (algorithmIndex == 5)
    {
        m_algorithmSteps << "Graph: A connects to B and C; B connects to D and E; C connects to F.";
        m_algorithmSteps << "Start BFS at A. Queue: A. Visited: empty.";
        m_algorithmSteps << "Visit A, enqueue B and C. Queue: B, C. Visited: A.";
        m_algorithmSteps << "Visit B, enqueue D and E. Queue: C, D, E. Visited: A, B.";
        m_algorithmSteps << "Visit C, enqueue F. Queue: D, E, F. Visited: A, B, C.";
        m_algorithmSteps << "Visit D, then E, then F. BFS order: A, B, C, D, E, F.";
        if (m_algorithmComplexity) m_algorithmComplexity->setText("BFS Big-O: O(V + E) time and O(V) space. Used for shortest path in unweighted graphs, crawlers, peer distance, and level-order traversal.");
        return;
    }

    if (algorithmIndex == 6)
    {
        m_algorithmSteps << "Graph: A connects to B and C; B connects to D and E; C connects to F.";
        m_algorithmSteps << "Start DFS at A. Stack/call: A.";
        m_algorithmSteps << "Visit A, go deep to B.";
        m_algorithmSteps << "Visit B, go deep to D. D has no unvisited children, backtrack.";
        m_algorithmSteps << "Back at B, visit E. E has no unvisited children, backtrack to A.";
        m_algorithmSteps << "Visit C, then F. DFS order: A, B, D, E, C, F.";
        if (m_algorithmComplexity) m_algorithmComplexity->setText("DFS Big-O: O(V + E) time and O(V) space. Used for graph search, cycle detection, topological sort, backtracking, and connected components.");
        return;
    }

    const QStringList keys = splitVisualizationInput(input);
    m_algorithmSteps << "Hash table lookup maps a key through a hash function to a bucket index.";
    for (const QString& key : keys)
    {
        int sum = 0;
        for (QChar ch : key) sum += ch.unicode();
        const int bucket = sum % 7;
        m_algorithmSteps << QString("hash('%1') = character sum % 7 = bucket %2. Store or look up the value in that bucket.").arg(key).arg(bucket);
    }
    m_algorithmSteps << "Production hash tables handle collisions with chaining, probing, resizing, and good hash functions.";
    if (m_algorithmComplexity) m_algorithmComplexity->setText("Hash Table Big-O: expected O(1) insert/search/delete, worst-case O(n). Used in maps, caches, indexes, compilers, web sessions, and deduplication.");
}

void MainWindow::showAlgorithmStep()
{
    if (!m_algorithmOutput) return;
    if (m_algorithmSteps.isEmpty()) prepareAlgorithmSteps();

    QString text;
    text += QString("Step %1 of %2\n\n").arg(qMin(m_algorithmStepIndex + 1, m_algorithmSteps.size())).arg(m_algorithmSteps.size());
    for (int i = 0; i <= m_algorithmStepIndex && i < m_algorithmSteps.size(); ++i)
    {
        text += QString::number(i + 1) + ". " + m_algorithmSteps[i] + "\n\n";
    }
    if (m_algorithmStepIndex >= m_algorithmSteps.size() - 1)
    {
        text += "Finished. Now implement the same algorithm in your selected language track and add tests.\n";
    }
    m_algorithmOutput->setPlainText(text);
}

void MainWindow::resetAlgorithmVisualizer()
{
    prepareAlgorithmSteps();
    showAlgorithmStep();
}

void MainWindow::advanceAlgorithmVisualizer()
{
    if (m_algorithmSteps.isEmpty()) prepareAlgorithmSteps();
    if (m_algorithmStepIndex + 1 < m_algorithmSteps.size())
    {
        ++m_algorithmStepIndex;
    }
    showAlgorithmStep();
}

void MainWindow::refreshRunnerForLanguage(int index)
{
    if (index < 0 || index >= m_languageTracks.size()) return;
    const LanguageTrack& track = m_languageTracks[index];

    if (m_runnerWorkingDirectory)
    {
        m_runnerWorkingDirectory->setText(defaultRunnerDirectoryForTrack(track));
    }

    if (m_runnerCommandPreview)
    {
        m_runnerCommandPreview->setPlainText(
            "Language: " + track.name +
            "\nRun command:\n  " + commandForTrack(track, "run") +
            "\n\nBuild/check command:\n  " + commandForTrack(track, "build") +
            "\n\nTest/check command:\n  " + commandForTrack(track, "test") +
            "\n\nStarter folder:\n  " + defaultRunnerDirectoryForTrack(track) +
            "\n\nSetup checks:\n" + bulletList(track.installChecks));
    }
}

void MainWindow::browseRunnerWorkingDirectory()
{
    const QString start = m_runnerWorkingDirectory ? m_runnerWorkingDirectory->text() : QDir::homePath();
    const QString selected = QFileDialog::getExistingDirectory(this, "Choose Exercise Folder", start);
    if (!selected.isEmpty() && m_runnerWorkingDirectory)
    {
        m_runnerWorkingDirectory->setText(selected);
    }
}

void MainWindow::openRunnerWorkingDirectory()
{
    if (!m_runnerWorkingDirectory) return;
    const QString path = m_runnerWorkingDirectory->text().trimmed();
    if (path.isEmpty()) return;
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::runRunnerCommand(const QString& command)
{
    if (!m_runnerProcess || !m_runnerWorkingDirectory || !m_runnerOutput) return;

    if (command.trimmed().isEmpty())
    {
        m_runnerOutput->append("[runner] No command is configured for this action yet.");
        return;
    }

    if (m_runnerProcess->state() != QProcess::NotRunning)
    {
        m_runnerOutput->append("[runner] A command is already running. Stop it before starting another one.");
        return;
    }

    const QString workingDir = m_runnerWorkingDirectory->text().trimmed();
    if (!QDir(workingDir).exists())
    {
        m_runnerOutput->append("[runner] Working folder does not exist: " + workingDir);
        return;
    }

    m_runnerOutput->clear();
    m_runnerOutput->append("[runner] Working folder: " + workingDir);
    m_runnerOutput->append("[runner] Command: " + command + "\n");

#ifdef Q_OS_WIN
    const QString program = "cmd.exe";
    const QStringList arguments = {"/C", command};
#else
    const QString program = "/bin/sh";
    const QStringList arguments = {"-lc", command};
#endif

    m_runnerProcess->setWorkingDirectory(workingDir);
    m_runnerProcess->start(program, arguments);
}

QString MainWindow::runnerFolderNameForTrack(const LanguageTrack& track) const
{
    QString folder = track.id;
    folder.remove("lang_");
    return folder;
}

QString MainWindow::defaultRunnerDirectoryForTrack(const LanguageTrack& track) const
{
    const QString folder = runnerFolderNameForTrack(track);
    return QDir(QCoreApplication::applicationDirPath()).filePath("examples/languages/" + folder);
}

QString MainWindow::commandForTrack(const LanguageTrack& track, const QString& action) const
{
    const QString folder = runnerFolderNameForTrack(track);

    if (folder == "cpp")
    {
        if (action == "run") return "if not exist build mkdir build && cmake -S . -B build -G \"MinGW Makefiles\" && cmake --build build && build\\CppWorkspaceStarter.exe";
        if (action == "build") return "if not exist build mkdir build && cmake -S . -B build -G \"MinGW Makefiles\" && cmake --build build";
        if (action == "test") return "g++ --version && cmake --version";
    }
    if (folder == "python")
    {
        if (action == "run") return "python main.py";
        if (action == "build") return "python -m py_compile main.py";
        if (action == "test") return "python --version";
    }
    if (folder == "javascript")
    {
        if (action == "run") return "node index.js";
        if (action == "build") return "node --check index.js";
        if (action == "test") return "node --version && npm --version";
    }
    if (folder == "typescript")
    {
        if (action == "run") return "npm install && npx ts-node main.ts";
        if (action == "build") return "npm install && npx tsc --noEmit main.ts";
        if (action == "test") return "node --version && npx tsc --version";
    }
    if (folder == "java")
    {
        if (action == "run") return "javac Main.java && java Main";
        if (action == "build") return "javac Main.java";
        if (action == "test") return "java --version && javac --version";
    }
    if (folder == "csharp")
    {
        if (action == "run") return "dotnet run";
        if (action == "build") return "dotnet build";
        if (action == "test") return "dotnet --version";
    }
    if (folder == "go")
    {
        if (action == "run") return "go run main.go";
        if (action == "build") return "go build -o go_starter.exe .";
        if (action == "test") return "go version";
    }
    if (folder == "rust")
    {
        if (action == "run") return "rustc src_main.rs -o rust_starter.exe && rust_starter.exe";
        if (action == "build") return "rustc src_main.rs -o rust_starter.exe";
        if (action == "test") return "rustc --version && cargo --version";
    }
    if (folder == "sql")
    {
        if (action == "run") return "sqlite3 bootcamp.db < schema.sql";
        if (action == "build") return "sqlite3 --version";
        if (action == "test") return "sqlite3 bootcamp.db \".tables\"";
    }
    if (folder == "kotlin")
    {
        if (action == "run") return "kotlinc Main.kt -include-runtime -d kotlin_starter.jar && java -jar kotlin_starter.jar";
        if (action == "build") return "kotlinc Main.kt -include-runtime -d kotlin_starter.jar";
        if (action == "test") return "kotlinc -version";
    }

    if (!track.runCommands.isEmpty()) return track.runCommands.first();
    return {};
}
QWidget* MainWindow::createProjectGeneratorPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setSpacing(14);

    layout->addWidget(makeHeader("Project Generator - Create Multi-Language Starter Repos"));

    QLabel* intro = new QLabel("v7 turns the bootcamp into a project factory. Pick a language, choose a project type, enter a name, and generate a clean starter repository with source folders, tests, README notes, and Windows run scripts.");
    intro->setWordWrap(true);
    layout->addWidget(intro);

    QGroupBox* formBox = new QGroupBox("Generator Settings");
    QFormLayout* form = new QFormLayout(formBox);

    QComboBox* languageBox = new QComboBox;
    for (const LanguageTrack& track : m_languageTracks) languageBox->addItem(track.name);

    QComboBox* projectTypeBox = new QComboBox;
    projectTypeBox->addItems({
        "CLI Fundamentals Lab",
        "API / Backend Starter",
        "Data Structures Practice Pack",
        "Testing and Debugging Lab",
        "Portfolio Capstone Starter"
    });

    QLineEdit* nameEdit = new QLineEdit("MyBootcampProject");
    QLineEdit* outputEdit = new QLineEdit(QDir(QCoreApplication::applicationDirPath()).filePath("generated_projects"));
    QPushButton* browseButton = new QPushButton("Browse Output Folder");

    QWidget* outputRow = new QWidget;
    QHBoxLayout* outputLayout = new QHBoxLayout(outputRow);
    outputLayout->setContentsMargins(0, 0, 0, 0);
    outputLayout->addWidget(outputEdit, 1);
    outputLayout->addWidget(browseButton);

    form->addRow("Language:", languageBox);
    form->addRow("Project type:", projectTypeBox);
    form->addRow("Project name:", nameEdit);
    form->addRow("Output folder:", outputRow);
    layout->addWidget(formBox);

    QTextEdit* preview = makeReadOnlyText(260);
    layout->addWidget(preview, 1);

    QPushButton* generateButton = new QPushButton("Generate Project");
    QPushButton* openButton = new QPushButton("Open Output Folder");
    QHBoxLayout* buttonRow = new QHBoxLayout;
    buttonRow->addWidget(generateButton);
    buttonRow->addWidget(openButton);
    buttonRow->addStretch(1);
    layout->addLayout(buttonRow);

    auto safeName = [](QString value)
    {
        value = value.trimmed();
        if (value.isEmpty()) value = "BootcampProject";
        value.replace(" ", "_");
        value.remove(QRegularExpression("[^A-Za-z0-9_\\-]"));
        return value.isEmpty() ? QString("BootcampProject") : value;
    };

    auto folderNameForLanguage = [](QString language)
    {
        QString folder = language.toLower();
        folder.replace("#", "sharp");
        folder.remove("+");
        folder.replace("/", "_");
        folder.replace(" ", "_");
        return folder;
    };

    auto writeFile = [](const QString& path, const QString& text)
    {
        QDir().mkpath(QFileInfo(path).absolutePath());
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
        QTextStream stream(&file);
        stream << text;
        return true;
    };

    auto buildPreview = [=]()
    {
        const QString language = languageBox->currentText();
        const QString projectType = projectTypeBox->currentText();
        const QString projectName = safeName(nameEdit->text());
        const QString root = QDir(outputEdit->text()).filePath(projectName);
        const QString folder = folderNameForLanguage(language);

        QString text;
        text += "Generated repo preview\n";
        text += "======================\n\n";
        text += "Language: " + language + "\n";
        text += "Project type: " + projectType + "\n";
        text += "Folder: " + root + "\n\n";
        text += "Planned structure:\n";
        text += "  README.md\n";
        text += "  run.bat\n";
        text += "  test.bat\n";
        text += "  src/\n";
        text += "  tests/\n";
        text += "  docs/LEARNING_GOALS.md\n";
        if (folder == "cpp") text += "  CMakeLists.txt\n  src/main.cpp\n";
        else if (folder == "python") text += "  src/main.py\n  tests/test_smoke.py\n";
        else if (folder == "javascript") text += "  package.json\n  src/index.js\n";
        else if (folder == "typescript") text += "  package.json\n  tsconfig.json\n  src/index.ts\n";
        else if (folder == "java") text += "  src/Main.java\n";
        else if (folder == "csharp") text += "  " + projectName + ".csproj\n  Program.cs\n";
        else if (folder == "go") text += "  go.mod\n  main.go\n";
        else if (folder == "rust") text += "  Cargo.toml\n  src/main.rs\n";
        else if (folder == "sql") text += "  schema.sql\n  queries.sql\n";
        else if (folder == "kotlin") text += "  Main.kt\n";
        text += "\nProfessional workflow:\n";
        text += "1. Generate the project.\n";
        text += "2. Open it in VS Code or your IDE.\n";
        text += "3. Run run.bat.\n";
        text += "4. Complete the TODOs.\n";
        text += "5. Add tests, commit to Git, and document your decisions.\n";
        preview->setPlainText(text);
    };

    auto generateProject = [=]()
    {
        const QString language = languageBox->currentText();
        const QString projectType = projectTypeBox->currentText();
        const QString projectName = safeName(nameEdit->text());
        const QString folder = folderNameForLanguage(language);
        const QString root = QDir(outputEdit->text()).filePath(projectName);
        QDir().mkpath(root);
        QDir().mkpath(QDir(root).filePath("src"));
        QDir().mkpath(QDir(root).filePath("tests"));
        QDir().mkpath(QDir(root).filePath("docs"));

        const QString readme = "# " + projectName + "\n\n"
            "Generated by CS Bootcamp Desktop v7.\n\n"
            "## Track\n\n"
            "- Language: " + language + "\n"
            "- Project type: " + projectType + "\n\n"
            "## Goal\n\n"
            "Build this from a starter into a portfolio-quality project. Keep the README updated, write tests, and commit small improvements.\n\n"
            "## Professional checklist\n\n"
            "- [ ] The project runs from a clean checkout.\n"
            "- [ ] The README explains what the project does.\n"
            "- [ ] There is at least one test or validation command.\n"
            "- [ ] Errors are handled intentionally.\n"
            "- [ ] Code is organized into small functions or classes.\n";
        writeFile(QDir(root).filePath("README.md"), readme);
        writeFile(QDir(root).filePath("docs/LEARNING_GOALS.md"), "# Learning Goals\n\n- Practice " + language + " syntax.\n- Build a working project, not just a snippet.\n- Add tests and documentation.\n- Refactor toward professional structure.\n");

        if (folder == "cpp")
        {
            writeFile(QDir(root).filePath("CMakeLists.txt"), "cmake_minimum_required(VERSION 3.20)\nproject(" + projectName + " LANGUAGES CXX)\nset(CMAKE_CXX_STANDARD 17)\nadd_executable(" + projectName + " src/main.cpp)\n");
            writeFile(QDir(root).filePath("src/main.cpp"), "#include <iostream>\n#include <vector>\n#include <string>\n\nint main() {\n    std::vector<std::string> tasks = {\"learn\", \"build\", \"test\"};\n    for (const auto& task : tasks) std::cout << task << '\\n';\n    return 0;\n}\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\nif not exist build mkdir build\ncmake -S . -B build -G \"MinGW Makefiles\"\ncmake --build build\nbuild\\" + projectName + ".exe\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\ng++ --version\ncmake --version\n");
        }
        else if (folder == "python")
        {
            writeFile(QDir(root).filePath("src/main.py"), "def main():\n    tasks = ['learn', 'build', 'test']\n    for task in tasks:\n        print(task)\n\nif __name__ == '__main__':\n    main()\n");
            writeFile(QDir(root).filePath("tests/test_smoke.py"), "from src.main import main\n\ndef test_smoke():\n    assert callable(main)\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\npython src\\main.py\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\npython -m py_compile src\\main.py\n");
        }
        else if (folder == "javascript")
        {
            writeFile(QDir(root).filePath("package.json"), "{\n  \"scripts\": { \"start\": \"node src/index.js\", \"test\": \"node --check src/index.js\" }\n}\n");
            writeFile(QDir(root).filePath("src/index.js"), "const tasks = ['learn', 'build', 'test'];\nfor (const task of tasks) console.log(task);\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\nnpm start\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\nnpm test\n");
        }
        else if (folder == "typescript")
        {
            writeFile(QDir(root).filePath("package.json"), "{\n  \"devDependencies\": { \"typescript\": \"latest\", \"ts-node\": \"latest\" },\n  \"scripts\": { \"start\": \"npx ts-node src/index.ts\", \"test\": \"npx tsc --noEmit\" }\n}\n");
            writeFile(QDir(root).filePath("tsconfig.json"), "{ \"compilerOptions\": { \"target\": \"ES2020\", \"module\": \"CommonJS\", \"strict\": true } }\n");
            writeFile(QDir(root).filePath("src/index.ts"), "const tasks: string[] = ['learn', 'build', 'test'];\ntasks.forEach(task => console.log(task));\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\nnpm install\nnpm start\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\nnpm install\nnpm test\n");
        }
        else if (folder == "java")
        {
            writeFile(QDir(root).filePath("src/Main.java"), "import java.util.List;\n\npublic class Main {\n    public static void main(String[] args) {\n        for (String task : List.of(\"learn\", \"build\", \"test\")) {\n            System.out.println(task);\n        }\n    }\n}\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\njavac src\\Main.java\njava -cp src Main\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\njavac src\\Main.java\n");
        }
        else if (folder == "csharp")
        {
            writeFile(QDir(root).filePath(projectName + ".csproj"), "<Project Sdk=\"Microsoft.NET.Sdk\">\n  <PropertyGroup>\n    <OutputType>Exe</OutputType>\n    <TargetFramework>net8.0</TargetFramework>\n    <Nullable>enable</Nullable>\n  </PropertyGroup>\n</Project>\n");
            writeFile(QDir(root).filePath("Program.cs"), "var tasks = new[] { \"learn\", \"build\", \"test\" };\nforeach (var task in tasks) Console.WriteLine(task);\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\ndotnet run\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\ndotnet build\n");
        }
        else if (folder == "go")
        {
            writeFile(QDir(root).filePath("go.mod"), "module " + projectName.toLower() + "\n\ngo 1.22\n");
            writeFile(QDir(root).filePath("main.go"), "package main\n\nimport \"fmt\"\n\nfunc main() {\n    for _, task := range []string{\"learn\", \"build\", \"test\"} {\n        fmt.Println(task)\n    }\n}\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\ngo run .\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\ngo test ./...\n");
        }
        else if (folder == "rust")
        {
            writeFile(QDir(root).filePath("Cargo.toml"), "[package]\nname = \"" + projectName.toLower() + "\"\nversion = \"0.1.0\"\nedition = \"2021\"\n");
            writeFile(QDir(root).filePath("src/main.rs"), "fn main() {\n    let tasks = [\"learn\", \"build\", \"test\"];\n    for task in tasks {\n        println!(\"{}\", task);\n    }\n}\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\ncargo run\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\ncargo test\n");
        }
        else if (folder == "sql")
        {
            writeFile(QDir(root).filePath("schema.sql"), "CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, name TEXT NOT NULL);\nINSERT INTO tasks(name) VALUES ('learn'), ('build'), ('test');\n");
            writeFile(QDir(root).filePath("queries.sql"), "SELECT * FROM tasks;\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\nsqlite3 bootcamp.db < schema.sql\nsqlite3 bootcamp.db < queries.sql\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\nsqlite3 --version\n");
        }
        else
        {
            writeFile(QDir(root).filePath("Main.kt"), "fun main() {\n    val tasks = listOf(\"learn\", \"build\", \"test\")\n    tasks.forEach { println(it) }\n}\n");
            writeFile(QDir(root).filePath("run.bat"), "@echo off\nkotlinc Main.kt -include-runtime -d app.jar\njava -jar app.jar\n");
            writeFile(QDir(root).filePath("test.bat"), "@echo off\nkotlinc -version\n");
        }

        preview->append("\nGenerated project at:\n" + root);
        QMessageBox::information(page, "Project generated", "Generated starter repo:\n" + root);
    };

    connect(languageBox, &QComboBox::currentIndexChanged, page, buildPreview);
    connect(projectTypeBox, &QComboBox::currentIndexChanged, page, buildPreview);
    connect(nameEdit, &QLineEdit::textChanged, page, buildPreview);
    connect(outputEdit, &QLineEdit::textChanged, page, buildPreview);
    connect(browseButton, &QPushButton::clicked, page, [=]()
    {
        const QString folder = QFileDialog::getExistingDirectory(page, "Choose output folder", outputEdit->text());
        if (!folder.isEmpty()) outputEdit->setText(folder);
    });
    connect(generateButton, &QPushButton::clicked, page, generateProject);
    connect(openButton, &QPushButton::clicked, page, [=]()
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(outputEdit->text()));
    });

    buildPreview();
    return page;
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

PortfolioProject* MainWindow::currentProject()
{
    Module* module = currentModule();
    if (!module || m_currentProjectIndex < 0 || m_currentProjectIndex >= module->projects.size()) return nullptr;
    return &module->projects[m_currentProjectIndex];
}

QString MainWindow::currentItemIdForNotes() const
{
    if (m_pages && m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size())
    {
        const Module& module = m_modules[m_currentModuleIndex];
        if (m_pages->currentIndex() == 3 && m_currentExerciseIndex >= 0 && m_currentExerciseIndex < module.exercises.size()) return module.exercises[m_currentExerciseIndex].id;
        if (m_pages->currentIndex() == 6 && m_currentQuizIndex >= 0 && m_currentQuizIndex < module.quiz.size()) return module.quiz[m_currentQuizIndex].id;
        if (m_pages->currentIndex() == 7 && m_currentProjectIndex >= 0 && m_currentProjectIndex < module.projects.size()) return module.projects[m_currentProjectIndex].id;
        if (m_currentLessonIndex >= 0 && m_currentLessonIndex < module.lessons.size()) return module.lessons[m_currentLessonIndex].id;
    }
    return {};
}

int MainWindow::totalTrackableItems() const
{
    int total = 0;
    for (const Module& module : m_modules)
    {
        total += module.lessons.size();
        total += module.exercises.size();
        total += module.quiz.size();
        total += module.projects.size();
    }
    return total;
}
