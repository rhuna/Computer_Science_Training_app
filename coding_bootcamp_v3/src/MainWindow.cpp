#include "MainWindow.h"

#include <algorithm>

#include <QApplication>
#include <QCoreApplication>
#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QEventLoop>
#include <QRegularExpression>
#include <QFile>
#include <QFileInfo>
#include <QFrame>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QStandardPaths>
#include <QSplitter>
#include <QTimer>
#include <QTextStream>
#include <QTabWidget>
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

    struct VerificationCase
    {
        QString name;
        QString input;
        QStringList expectedFragments;
    };

    QString normalizedText(QString value)
    {
        value.replace("\r\n", "\n");
        value.replace("\r", "\n");
        value = value.toLower();
        value.replace(QRegularExpression("[^a-z0-9_\\-\\.]+"), " ");
        value.replace(QRegularExpression("\\s+"), " ");
        return value.trimmed();
    }

    QVector<VerificationCase> verificationCasesForExerciseId(const QString& exerciseId)
    {
        if (exerciseId == "ex_base_converter")
        {
            return {{"42 converts to binary and hex", "42\n", {"101010", "2a"}}, {"15 converts to binary and hex", "15\n", {"1111", "f"}}};
        }
        if (exerciseId == "ex_word_frequency")
        {
            return {{"counts repeated words", "red blue red green blue red\n", {"red", "3", "blue", "2", "green", "1"}}, {"normalizes case", "Cat cat dog CAT\n", {"cat", "3", "dog", "1"}}};
        }
        if (exerciseId == "ex_input_validator")
        {
            return {{"accepts valid profile", "25\nbrandon@example.com\nbrandon_user\n", {"valid"}}, {"rejects invalid age/email", "15\nnot-email\nbo\n", {"invalid"}}};
        }
        if (exerciseId == "ex_two_sum_multi")
        {
            return {{"finds pair for 9", "2 7 11 15\n9\n", {"0", "1"}}, {"finds pair for 6", "3 2 4\n6\n", {"1", "2"}}};
        }
        if (exerciseId == "ex_lru_cache")
        {
            return {{"evicts least recently used key", "", {"1", "-1", "3", "4"}}};
        }
        if (exerciseId == "ex_csv_reporter")
        {
            return {{"summarizes CSV values", "name,value\na,10\nb,20\nc,5\n", {"35", "20", "3"}}};
        }
        if (exerciseId == "ex_adv_tokenizer")
        {
            return {{"tokenizes expression", "let total = 3 + 4;\n", {"identifier", "total", "number", "3", "plus"}}};
        }
        if (exerciseId == "ex_adv_rate_limiter")
        {
            return {{"allows and blocks requests", "", {"allow", "allow", "block"}}};
        }
        if (exerciseId == "ex_adv_job_queue")
        {
            return {{"processes jobs in order", "", {"queued", "processing", "complete"}}};
        }
        if (exerciseId == "ex_adv_btree_index")
        {
            return {{"finds indexed keys", "", {"insert", "search", "found"}}};
        }
        if (exerciseId == "ex_adv_rag_pipeline")
        {
            return {{"retrieves and cites chunks", "What is retrieval?\n", {"retrieve", "rank", "cite"}}};
        }
        return {{"professional output contract", "", {exerciseId, "correct"}}};
    }


    QFrame* card()
    {
        QFrame* frame = new QFrame;
        frame->setObjectName("card");
        return frame;
    }


    QScrollArea* scrollable(QWidget* content)
    {
        QScrollArea* area = new QScrollArea;
        area->setWidgetResizable(true);
        area->setFrameShape(QFrame::NoFrame);
        area->setObjectName("stageScrollArea");
        area->setWidget(content);
        return area;
    }
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_modules(BootcampContent::createDefaultModules())
    , m_languageTracks(BootcampContent::createLanguageTracks())
    , m_progress(QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).filePath("progress_v35.sqlite"))
{
    QDir().mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    m_progress.load();
    buildLayout();
    applyAppStyle();
    refreshAllTabs();
    setWindowTitle("CS Bootcamp Desktop v35 - Split-Topic Deep Lessons");
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
    m_sidebar->hide();
    layout->addWidget(m_pages, 1);
    setCentralWidget(root);
}

void MainWindow::buildSidebar()
{
    // v35 keeps the sidebar object for compatibility with older helper methods,
    // but the learner-facing workflow is now a single guided course workspace.
    m_sidebar = new QListWidget;
    m_sidebar->setObjectName("sidebar");
    m_sidebar->setFixedWidth(0);
    m_sidebar->addItem("Guided Bootcamp");
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
    m_pages->addWidget(createGuidedBootcampPage());
}

void MainWindow::applyAppStyle()
{
    qApp->setStyleSheet(R"(
        QWidget { font-family: Segoe UI, Arial; font-size: 15px; color: #172033; }
        QMainWindow, QWidget { background: #eef3fb; }
        QScrollArea#stageScrollArea { background: transparent; border: none; }
        QScrollArea#stageScrollArea QWidget { background: transparent; }
        QListWidget#sidebar { background: #111827; color: #e5e7eb; border-radius: 18px; padding: 10px; }
        QListWidget#sidebar::item { padding: 13px 12px; border-radius: 12px; margin: 3px; }
        QListWidget#sidebar::item:selected { background: #2563eb; color: white; }
        QFrame#card { background: #ffffff; border: 1px solid #d8deea; border-radius: 22px; padding: 18px; }
        QLabel#pageHeader { font-size: 28px; font-weight: 900; color: #0f172a; letter-spacing: -0.3px; }
        QLabel#smallTitle { font-size: 17px; font-weight: 850; color: #1d4ed8; }
        QLabel#timerLabel { font-size: 42px; font-weight: 900; color: #0f172a; padding: 12px; background: #f8fafc; border-radius: 18px; }
        QPushButton { background: #2563eb; color: white; border: none; border-radius: 14px; padding: 12px 16px; font-weight: 800; }
        QPushButton:hover { background: #1d4ed8; }
        QTextEdit { background: #fbfdff; border: 1px solid #cbd5e1; border-radius: 16px; padding: 12px; line-height: 1.45; }
        QListWidget, QComboBox { background: #ffffff; border: 1px solid #cbd5e1; border-radius: 14px; padding: 8px; }
        QListWidget::item { padding: 9px; border-radius: 10px; margin: 2px; }
        QListWidget::item:selected { background: #dbeafe; color: #0f172a; }
        QProgressBar { border: 1px solid #cbd5e1; border-radius: 12px; height: 28px; text-align: center; background: white; font-weight: 800; }
        QProgressBar::chunk { background: #22c55e; border-radius: 12px; }
    )");
}

QWidget* MainWindow::createGuidedBootcampPage()
{
    QWidget* outer = new QWidget;
    QVBoxLayout* outerLayout = new QVBoxLayout(outer);
    outerLayout->setContentsMargins(14, 14, 14, 14);
    outerLayout->setSpacing(12);

    outerLayout->addWidget(header("CS Bootcamp Desktop v35 - Split-Topic Deep Lessons"));

    QLabel* intro = new QLabel(
        "v35 makes every section explicit and objective-aligned. You see one required task at a time, and each task connects back to the selected lesson objective. "
        "The left panel is only for available lessons. The right panel is only for finished lessons and saved reviews.");
    intro->setWordWrap(true);
    outerLayout->addWidget(intro);

    QFrame* topChooser = card();
    QGridLayout* topLayout = new QGridLayout(topChooser);
    topLayout->setSpacing(10);
    m_moduleSelector = new QComboBox;
    for (const Module& module : m_modules) m_moduleSelector->addItem(module.title);
    m_runnerLanguage = new QComboBox;
    for (const LanguageTrack& track : m_languageTracks) m_runnerLanguage->addItem(track.name, track.id);
    topLayout->addWidget(smallTitle("Course module"), 0, 0);
    topLayout->addWidget(m_moduleSelector, 1, 0);
    topLayout->addWidget(smallTitle("Coding language"), 0, 1);
    topLayout->addWidget(m_runnerLanguage, 1, 1);
    outerLayout->addWidget(topChooser);

    QSplitter* split = new QSplitter;
    split->setOrientation(Qt::Horizontal);

    QFrame* lessonsCard = card();
    QVBoxLayout* lessonsLayout = new QVBoxLayout(lessonsCard);
    lessonsLayout->addWidget(smallTitle("Available lessons / course path"));
    QLabel* lessonHint = new QLabel("Choose one lesson. The center panel will reveal only the current step for that lesson.");
    lessonHint->setWordWrap(true);
    lessonsLayout->addWidget(lessonHint);
    m_lessonList = new QListWidget;
    m_lessonList->setMinimumWidth(290);
    lessonsLayout->addWidget(m_lessonList, 1);
    split->addWidget(lessonsCard);

    QFrame* taskCard = card();
    QVBoxLayout* taskLayout = new QVBoxLayout(taskCard);
    m_courseStageTitle = header("Current required task");
    m_courseGateLabel = new QLabel;
    m_courseGateLabel->setWordWrap(true);
    taskLayout->addWidget(m_courseStageTitle);
    taskLayout->addWidget(m_courseGateLabel);

    QProgressBar* gateProgress = new QProgressBar;
    gateProgress->setRange(0, 4);
    gateProgress->setValue(0);
    gateProgress->setFormat("1 Lesson  >  2 Coaching  >  3 Testing  >  4 Verification  >  5 Save");
    taskLayout->addWidget(gateProgress);

    m_courseTaskStack = new QStackedWidget;

    QWidget* lessonStage = new QWidget;
    QVBoxLayout* lessonLayout = new QVBoxLayout(lessonStage);
    lessonLayout->addWidget(smallTitle("1. Lesson"));
    QLabel* lessonOnlyHint = new QLabel("Read the lesson. This screen is for explanation, examples, and the concept. No questions and no coding yet.");
    lessonOnlyHint->setWordWrap(true);
    lessonLayout->addWidget(lessonOnlyHint);
    m_lessonTitle = smallTitle("Lesson");
    lessonLayout->addWidget(m_lessonTitle);
    m_currentTaskBody = readOnlyText(620);
    m_lessonBody = m_currentTaskBody;
    lessonLayout->addWidget(m_currentTaskBody, 1);
    QPushButton* lessonNext = new QPushButton("Next: Coaching");
    lessonLayout->addWidget(lessonNext);
    m_courseTaskStack->addWidget(scrollable(lessonStage));

    QWidget* coachingStage = new QWidget;
    QVBoxLayout* coachingLayout = new QVBoxLayout(coachingStage);
    coachingLayout->addWidget(smallTitle("2. Coaching: Problem + Solution Walkthrough"));
    QLabel* coachingHint = new QLabel("This step is not a quiz. It gives you one clearly defined coding problem, then walks you through how to solve it before you start coding.");
    coachingHint->setWordWrap(true);
    coachingLayout->addWidget(coachingHint);
    m_helperContextLabel = new QLabel;
    m_helperContextLabel->setWordWrap(true);
    coachingLayout->addWidget(m_helperContextLabel);
    QHBoxLayout* timerRow = new QHBoxLayout;
    m_helperTimerLabel = new QLabel("00:00 / 20:00");
    m_helperTimerLabel->setObjectName("timerLabel");
    m_helperTimerLabel->setAlignment(Qt::AlignCenter);
    m_helperPhaseProgress = new QProgressBar;
    m_helperPhaseProgress->setRange(0, m_helperTargetSeconds);
    timerRow->addWidget(m_helperTimerLabel);
    timerRow->addWidget(m_helperPhaseProgress, 1);
    coachingLayout->addLayout(timerRow);
    m_helperPhaseSelector = new QComboBox;
    m_helperPhaseSelector->addItems({
        "1. Understand the Prompt",
        "2. Define Inputs and Outputs",
        "3. Choose a Pattern",
        "4. Trace a Tiny Example",
        "5. Implement the Smallest Correct Version",
        "6. Run Real Verification",
        "7. Debug the First Wrong State",
        "8. Refactor for Clarity",
        "9. Explain Correctness and Complexity"
    });
    m_helperBody = readOnlyText(440);
    coachingLayout->addWidget(m_helperPhaseSelector);
    coachingLayout->addWidget(m_helperBody, 1);
    coachingLayout->addWidget(smallTitle("My solution plan"));
    m_coachingResponseEditor = new QTextEdit;
    m_coachingResponseEditor->setMinimumHeight(150);
    m_coachingResponseEditor->setPlaceholderText("Write your solution plan here after reading the walkthrough: input, output, pattern, steps, edge cases, complexity.");
    coachingLayout->addWidget(m_coachingResponseEditor);
    QHBoxLayout* helperButtons = new QHBoxLayout;
    QPushButton* startTimer = new QPushButton("Start timer");
    QPushButton* pauseTimer = new QPushButton("Pause");
    QPushButton* resetTimer = new QPushButton("Reset");
    QPushButton* popup = new QPushButton("Walkthrough pop-up");
    helperButtons->addWidget(startTimer);
    helperButtons->addWidget(pauseTimer);
    helperButtons->addWidget(resetTimer);
    helperButtons->addWidget(popup);
    coachingLayout->addLayout(helperButtons);
    QPushButton* coachingNext = new QPushButton("Next: Testing");
    coachingLayout->addWidget(coachingNext);
    m_courseTaskStack->addWidget(scrollable(coachingStage));

    QWidget* testingStage = new QWidget;
    QVBoxLayout* testingLayout = new QVBoxLayout(testingStage);
    testingLayout->addWidget(smallTitle("3. Testing: Questions + Coding Attempt"));
    QLabel* testingHint = new QLabel("Now the app tests what you just learned. Answer the lesson-matched question, then code the exercise, build, run, and submit the attempt.");
    testingHint->setWordWrap(true);
    testingLayout->addWidget(testingHint);

    m_quizTitle = smallTitle("Lesson question");
    m_quizBody = readOnlyText(180);
    m_quizChoices = new QListWidget;
    m_quizChoices->setMinimumHeight(125);
    m_quizFeedback = new QLabel("Choose an answer, then check it before submitting your coding attempt.");
    m_quizFeedback->setWordWrap(true);
    QPushButton* checkAnswer = new QPushButton("Check Answer");
    testingLayout->addWidget(m_quizTitle);
    testingLayout->addWidget(m_quizBody);
    testingLayout->addWidget(m_quizChoices);
    testingLayout->addWidget(m_quizFeedback);
    testingLayout->addWidget(checkAnswer);

    testingLayout->addWidget(smallTitle("Coding exercise"));
    m_exerciseList = new QListWidget;
    m_exerciseList->setMaximumHeight(90);
    m_exerciseTitle = smallTitle("Exercise");
    m_exerciseBody = readOnlyText(145);
    m_exerciseCode = new QTextEdit;
    m_exerciseCode->setMinimumHeight(330);
    testingLayout->addWidget(m_exerciseList);
    testingLayout->addWidget(m_exerciseTitle);
    testingLayout->addWidget(m_exerciseBody);
    testingLayout->addWidget(smallTitle("Code editor"));
    testingLayout->addWidget(m_exerciseCode, 1);
    QHBoxLayout* runButtons = new QHBoxLayout;
    QPushButton* build = new QPushButton("Build / Compile");
    QPushButton* run = new QPushButton("Run");
    QPushButton* test = new QPushButton("Language Test");
    QPushButton* stop = new QPushButton("Stop");
    runButtons->addWidget(build);
    runButtons->addWidget(run);
    runButtons->addWidget(test);
    runButtons->addWidget(stop);
    testingLayout->addLayout(runButtons);
    QPushButton* submitAttempt = new QPushButton("Submit Attempt → Verification");
    testingLayout->addWidget(submitAttempt);
    m_courseTaskStack->addWidget(scrollable(testingStage));

    QWidget* verificationStage = new QWidget;
    QVBoxLayout* verificationLayout = new QVBoxLayout(verificationStage);
    verificationLayout->addWidget(smallTitle("4. Verification: Prove Correctness"));
    QLabel* verifyHint = new QLabel("Verification runs real test cases and asks you to interpret the result. Fix the code until the real behavior matches the expected outputs.");
    verifyHint->setWordWrap(true);
    verificationLayout->addWidget(verifyHint);
    m_runnerContext = new QLabel;
    m_runnerContext->setWordWrap(true);
    m_runnerCommandPreview = readOnlyText(120);
    QPushButton* verifyCorrect = new QPushButton("Verify Correct");
    m_runnerOutput = new QTextEdit;
    m_runnerOutput->setMinimumHeight(500);
    verificationLayout->addWidget(m_runnerContext);
    verificationLayout->addWidget(m_runnerCommandPreview);
    verificationLayout->addWidget(verifyCorrect);
    verificationLayout->addWidget(m_runnerOutput, 1);
    m_courseTaskStack->addWidget(scrollable(verificationStage));

    QWidget* saveStage = new QWidget;
    QVBoxLayout* saveLayout = new QVBoxLayout(saveStage);
    saveLayout->addWidget(smallTitle("5. Save Finished Lesson"));
    QLabel* saveHint = new QLabel("Save the completed lesson only after lesson, coaching, testing, and verification are finished. Your saved work appears in the finished-lessons panel.");
    saveHint->setWordWrap(true);
    saveLayout->addWidget(saveHint);
    m_databaseBody = readOnlyText(300);
    saveLayout->addWidget(m_databaseBody, 1);
    QPushButton* saveFinished = new QPushButton("Save Finished Lesson");
    QPushButton* nextLesson = new QPushButton("Next Lesson");
    QHBoxLayout* saveButtons = new QHBoxLayout;
    saveButtons->addWidget(saveFinished);
    saveButtons->addWidget(nextLesson);
    saveLayout->addLayout(saveButtons);
    m_courseTaskStack->addWidget(scrollable(saveStage));

    taskLayout->addWidget(m_courseTaskStack, 1);
    split->addWidget(taskCard);

    QFrame* savedCard = card();
    QVBoxLayout* savedLayout = new QVBoxLayout(savedCard);
    savedLayout->addWidget(smallTitle("Finished lessons / saved work"));
    QLabel* savedHint = new QLabel("This panel is separate from the available lessons. It only shows completed lessons, test attempts, and saved reflections.");
    savedHint->setWordWrap(true);
    savedLayout->addWidget(savedHint);
    m_completedHistoryList = new QListWidget;
    m_completedHistoryList->setMinimumWidth(310);
    savedLayout->addWidget(m_completedHistoryList, 1);
    savedLayout->addWidget(smallTitle("Saved notes / reflection"));
    m_reviewEditor = new QTextEdit;
    m_reviewEditor->setMinimumHeight(230);
    m_reviewEditor->setPlaceholderText("Review or edit notes for a finished lesson here.");
    savedLayout->addWidget(m_reviewEditor);
    QPushButton* saveNotesOnly = new QPushButton("Save Notes");
    savedLayout->addWidget(saveNotesOnly);
    split->addWidget(savedCard);

    split->setStretchFactor(0, 0);
    split->setStretchFactor(1, 1);
    split->setStretchFactor(2, 0);
    outerLayout->addWidget(split, 1);

    m_runnerProcess = new QProcess(this);
    m_helperTimer = new QTimer(this);
    m_helperTimer->setInterval(1000);

    connect(m_moduleSelector, &QComboBox::currentIndexChanged, this, [this](int index) { m_courseStageIndex = 0; selectModule(index); });
    connect(m_runnerLanguage, &QComboBox::currentIndexChanged, this, [this](int index) { selectLanguageTrack(index); });
    connect(m_lessonList, &QListWidget::currentRowChanged, this, [this](int index) { m_courseStageIndex = 0; selectLesson(index); });
    connect(m_exerciseList, &QListWidget::currentRowChanged, this, [this](int index) { selectExercise(index); });
    connect(m_completedHistoryList, &QListWidget::currentRowChanged, this, [this](int index) { selectHistoryItem(index); });
    connect(m_helperPhaseSelector, &QComboBox::currentTextChanged, this, [this] { refreshAllTabs(); });
    connect(m_helperTimer, &QTimer::timeout, this, [this] { tickHelperTimer(); });

    connect(checkAnswer, &QPushButton::clicked, this, [this]
    {
        QuizQuestion* quiz = currentQuizQuestion();
        if (!quiz || !m_quizChoices || !m_quizFeedback) return;
        const int selected = m_quizChoices->currentRow();
        if (selected == quiz->correctIndex)
        {
            m_quizFeedback->setText("Correct. " + quiz->explanation + " Now prove it by coding and running the connected exercise.");
            m_progress.setCompleted(quiz->id, true);
            m_progress.recordStudyEvent(quiz->id, "testing_question_passed", 5, quiz->question);
        }
        else
        {
            m_quizFeedback->setText("Not yet. " + quiz->explanation + " Reconnect this answer to the lesson and coaching walkthrough before submitting your code.");
        }
    });

    connect(lessonNext, &QPushButton::clicked, this, [this] { advanceCourseStage(); });
    connect(coachingNext, &QPushButton::clicked, this, [this] { advanceCourseStage(); });
    connect(submitAttempt, &QPushButton::clicked, this, [this]
    {
        saveSourceCodeForRunner();
        recordRunnerAttempt("submitted_for_verification");
        saveCurrentCourseCheckpoint("testing_submitted");
        m_courseStageIndex = 3;
        refreshAllTabs();
    });
    connect(saveFinished, &QPushButton::clicked, this, [this]
    {
        saveCurrentCourseCheckpoint("finished_lesson_saved");
        QMessageBox::information(this, "Saved", "Finished lesson saved. You can find it in the Finished lessons / saved work panel.");
        refreshAllTabs();
    });
    connect(nextLesson, &QPushButton::clicked, this, [this]
    {
        saveCurrentCourseCheckpoint("lesson_sequence_finished");
        Module* module = currentModule();
        if (module && m_currentLessonIndex + 1 < module->lessons.size())
        {
            ++m_currentLessonIndex;
            if (m_currentLessonIndex < module->exercises.size()) m_currentExerciseIndex = m_currentLessonIndex;
            if (m_currentLessonIndex < module->quiz.size()) m_currentQuizIndex = m_currentLessonIndex;
            m_courseStageIndex = 0;
            if (m_exerciseCode) m_exerciseCode->clear();
        }
        refreshAllTabs();
    });
    connect(saveNotesOnly, &QPushButton::clicked, this, [this] { saveCurrentCourseCheckpoint("notes_updated"); });

    connect(startTimer, &QPushButton::clicked, this, [this] { startHelperTimer(); });
    connect(pauseTimer, &QPushButton::clicked, this, [this] { pauseHelperTimer(); });
    connect(resetTimer, &QPushButton::clicked, this, [this] { resetHelperTimer(); });
    connect(popup, &QPushButton::clicked, this, [this] { showHelperPopup(); });
    connect(build, &QPushButton::clicked, this, [this] { runRunnerAction("build"); });
    connect(run, &QPushButton::clicked, this, [this] { runRunnerAction("run"); });
    connect(test, &QPushButton::clicked, this, [this] { runRunnerAction("test"); });
    connect(verifyCorrect, &QPushButton::clicked, this, [this] { verifyRunnerOutput(); });
    connect(stop, &QPushButton::clicked, this, [this] { if (m_runnerProcess) m_runnerProcess->kill(); });
    connect(m_runnerProcess, &QProcess::readyReadStandardOutput, this, [this] { appendRunnerOutput(QString::fromLocal8Bit(m_runnerProcess->readAllStandardOutput())); });
    connect(m_runnerProcess, &QProcess::readyReadStandardError, this, [this] { appendRunnerOutput(QString::fromLocal8Bit(m_runnerProcess->readAllStandardError())); });
    connect(m_runnerProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this](int code, QProcess::ExitStatus)
    {
        appendRunnerOutput(QString("\n[process finished with exit code %1]\n").arg(code));
    });

    Q_UNUSED(gateProgress);
    return outer;
}

QWidget* MainWindow::createDashboardPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setSpacing(12);
    layout->addWidget(header("CS Bootcamp Desktop v35 - Split-Topic Deep Lessons"));
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

QWidget* MainWindow::createProblemSolvingCoachPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setSpacing(12);
    layout->addWidget(header("Problem Solving Coach"));

    QLabel* intro = new QLabel("This tab turns the selected lesson and exercise into a repeatable coding problem-solving process: understand, plan, trace, implement, test, debug, refactor, and explain.");
    intro->setWordWrap(true);
    layout->addWidget(intro);

    m_problemPatternSelector = new QComboBox;
    m_problemPatternSelector->addItems({
        "Universal Problem-Solving Loop",
        "Input / Output Modeling",
        "Brute Force to Optimized",
        "Two Pointers",
        "Hash Map Lookup",
        "Stack / Queue State",
        "Tree / Graph Traversal",
        "Dynamic Programming",
        "Debugging Failed Tests",
        "Complexity and Tradeoff Review"
    });

    layout->addWidget(smallTitle("Problem-solving pattern"));
    layout->addWidget(m_problemPatternSelector);

    m_problemCoachBody = readOnlyText(560);
    layout->addWidget(m_problemCoachBody, 1);

    QHBoxLayout* buttons = new QHBoxLayout;
    QPushButton* openPractice = new QPushButton("Open Practice Lab");
    QPushButton* openRunner = new QPushButton("Open Runner");
    QPushButton* openQuiz = new QPushButton("Open Quiz");
    QPushButton* recordDrill = new QPushButton("Record 20-Min Problem Drill");
    buttons->addWidget(openPractice);
    buttons->addWidget(openRunner);
    buttons->addWidget(openQuiz);
    buttons->addWidget(recordDrill);
    layout->addLayout(buttons);

    connect(m_problemPatternSelector, &QComboBox::currentTextChanged, this, [this] { refreshAllTabs(); });
    connect(openPractice, &QPushButton::clicked, this, [this] { m_sidebar->setCurrentRow(2); });
    connect(openRunner, &QPushButton::clicked, this, [this] { m_sidebar->setCurrentRow(5); });
    connect(openQuiz, &QPushButton::clicked, this, [this] { m_sidebar->setCurrentRow(6); });
    connect(recordDrill, &QPushButton::clicked, this, [this] { recordProblemSolvingDrill(); });
    return page;
}


QWidget* MainWindow::createAdvancedHelperPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setSpacing(12);

    layout->addWidget(header("Advanced Helper - Guided Coding Pop-Ups and Real-Time Timer"));

    m_helperContextLabel = new QLabel;
    m_helperContextLabel->setWordWrap(true);
    layout->addWidget(m_helperContextLabel);

    QFrame* timerCard = card();
    QVBoxLayout* timerLayout = new QVBoxLayout(timerCard);
    timerLayout->addWidget(smallTitle("Real-time deliberate practice timer"));

    m_helperTimerLabel = new QLabel("00:00 / 20:00");
    m_helperTimerLabel->setObjectName("timerLabel");
    m_helperTimerLabel->setAlignment(Qt::AlignCenter);

    m_helperPhaseProgress = new QProgressBar;
    m_helperPhaseProgress->setRange(0, m_helperTargetSeconds);
    m_helperPhaseProgress->setValue(0);
    m_helperPhaseProgress->setFormat("%p% of 20-minute problem-solving loop");

    QHBoxLayout* timerButtons = new QHBoxLayout;
    QPushButton* start = new QPushButton("Start Timer");
    QPushButton* pause = new QPushButton("Pause");
    QPushButton* reset = new QPushButton("Reset");
    timerButtons->addWidget(start);
    timerButtons->addWidget(pause);
    timerButtons->addWidget(reset);

    timerLayout->addWidget(m_helperTimerLabel);
    timerLayout->addWidget(m_helperPhaseProgress);
    timerLayout->addLayout(timerButtons);
    layout->addWidget(timerCard);

    layout->addWidget(smallTitle("Current guided phase"));
    m_helperPhaseSelector = new QComboBox;
    m_helperPhaseSelector->addItems({
        "1. Understand the Prompt",
        "2. Define Inputs and Outputs",
        "3. Choose a Pattern",
        "4. Trace a Tiny Example",
        "5. Implement the Smallest Correct Version",
        "6. Run Real Verification",
        "7. Debug the First Wrong State",
        "8. Refactor for Clarity and Efficiency",
        "9. Explain Correctness and Complexity"
    });
    layout->addWidget(m_helperPhaseSelector);

    m_helperBody = readOnlyText(360);
    layout->addWidget(m_helperBody, 1);

    QHBoxLayout* helperButtons = new QHBoxLayout;
    QPushButton* popup = new QPushButton("Show Helper Pop-Up");
    QPushButton* nextPhase = new QPushButton("Next Phase");
    QPushButton* openPractice = new QPushButton("Open Practice Lab");
    QPushButton* openRunner = new QPushButton("Open Exercise Runner");
    QPushButton* openQuiz = new QPushButton("Open Quiz");
    helperButtons->addWidget(popup);
    helperButtons->addWidget(nextPhase);
    helperButtons->addWidget(openPractice);
    helperButtons->addWidget(openRunner);
    helperButtons->addWidget(openQuiz);
    layout->addLayout(helperButtons);

    m_helperTimer = new QTimer(this);
    m_helperTimer->setInterval(1000);

    connect(m_helperTimer, &QTimer::timeout, this, [this] { tickHelperTimer(); });
    connect(start, &QPushButton::clicked, this, [this] { startHelperTimer(); });
    connect(pause, &QPushButton::clicked, this, [this] { pauseHelperTimer(); });
    connect(reset, &QPushButton::clicked, this, [this] { resetHelperTimer(); });
    connect(popup, &QPushButton::clicked, this, [this] { showHelperPopup(); });
    connect(nextPhase, &QPushButton::clicked, this, [this] { advanceHelperPhase(); });
    connect(openPractice, &QPushButton::clicked, this, [this] { m_sidebar->setCurrentRow(2); });
    connect(openRunner, &QPushButton::clicked, this, [this] { m_sidebar->setCurrentRow(5); });
    connect(openQuiz, &QPushButton::clicked, this, [this] { m_sidebar->setCurrentRow(6); });
    connect(m_helperPhaseSelector, &QComboBox::currentTextChanged, this, [this] { refreshAllTabs(); });

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
    m_algorithmSelector->addItems({"Binary Search", "Bubble Sort", "Hash Table Lookup", "BFS Traversal", "DFS Traversal", "Stack Operations", "Queue Operations", "LRU Cache", "Dijkstra Shortest Path", "Database B-Tree Index", "Compiler Tokenizer", "Distributed Job Queue", "Rate Limiter", "RAG Retrieval Pipeline"});
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
    connect(openRunner, &QPushButton::clicked, this, [this] { m_sidebar->setCurrentRow(5); });
    return page;
}

QWidget* MainWindow::createContentPackPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(header("Course Content Packs"));
    m_contentBody = readOnlyText(620);
    layout->addWidget(m_contentBody, 1);
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
    if (m_exerciseCode) m_exerciseCode->clear();
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
    if (m_exerciseCode) m_exerciseCode->clear();
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
    text += "OBJECTIVE\n";
    text += lesson.objective + "\n\n";

    text += "WHAT YOU ARE LEARNING\n";
    text += lesson.explanation + "\n\n";

    text += "WHY THIS MATTERS\n";
    text += "This objective connects directly to the coding problem, the testing question, and the verifier. Do not treat this as reading-only material. By the end of this lesson you should be able to explain the concept, recognize when to use it, solve the connected problem, and prove the solution with tests.\n\n";

    text += "EXAMPLE\n";
    text += lesson.workedExample.isEmpty()
        ? QString("Trace one small input by hand. Name the input, expected output, state, and rule used at each step.\n\n")
        : lesson.workedExample + "\n\n";

    text += "LESSON MAP\n";
    text += "1. Lesson: learn the objective and example.\n";
    text += "2. Coaching: study one coding problem and its solution walkthrough.\n";
    text += "3. Testing: answer a question that checks this exact objective, then code the connected exercise.\n";
    text += "4. Verification: run real behavior checks that prove the objective was learned.\n";
    text += "5. Save: record what you learned and move to the next lesson.\n\n";

    text += "CHECKLIST: WHAT MUST BE TRUE BEFORE YOU CONTINUE\n";
    int step = 1;
    for (const QString& item : lesson.checklist)
    {
        text += QString::number(step++) + ". " + item + "\n";
    }

    text += "\nPRACTICE BEFORE COACHING\n";
    step = 1;
    for (const QString& item : lesson.practicePrompts)
    {
        text += QString::number(step++) + ". " + item + "\n";
    }

    text += "\nCONNECTED COACHING PROBLEM\n";
    text += lesson.coachedProblem.isEmpty()
        ? QString("The next step will show the coding problem and walkthrough for this objective.\n")
        : lesson.coachedProblem + "\n";

    text += "\nNEXT ACTION\n";
    text += "Click Next: Coaching only when you can say the objective, the example, and the expected behavior in plain English.\n";
    return text;
}

QString MainWindow::exerciseDetailText(const Exercise& exercise) const
{
    QString text;
    const Module* module = (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size()) ? &m_modules[m_currentModuleIndex] : nullptr;
    const Lesson* lesson = (module && m_currentLessonIndex >= 0 && m_currentLessonIndex < module->lessons.size()) ? &module->lessons[m_currentLessonIndex] : nullptr;

    text += "OBJECTIVE BEING TESTED\n";
    text += lesson ? lesson->objective + "\n\n" : QString("No lesson objective selected.\n\n");

    text += "CODING TASK\n";
    text += exercise.prompt + "\n\n";

    text += "CONCEPTS YOU MUST USE\n";
    text += exercise.expectedConcepts + "\n\n";

    text += "TESTING STAGE CHECKLIST\n";
    text += "1. Answer the lesson-matched question above before coding.\n";
    text += "2. Write the smallest solution that satisfies the task.\n";
    text += "3. Build or run the program in the selected language.\n";
    text += "4. Read any error message and fix the first real cause.\n";
    text += "5. Submit the attempt to move into Verification.\n\n";

    text += "WHAT VERIFICATION WILL LOOK FOR\n";
    text += "The verifier checks real behavior: input is provided, your program runs, output is captured, and expected evidence is compared. A fake PASS marker alone is not accepted as proof.\n";
    return text;
}

QString MainWindow::patternGuideText(const QString& pattern) const
{
    if (pattern == "Input / Output Modeling")
    {
        return "Pattern: Input / Output Modeling\n\nUse this when you are not sure how to start.\n\n1. Write every input value the program receives.\n2. Write the exact output the verifier expects.\n3. Build a two-column table: input state -> output evidence.\n4. Decide whether the solution needs parsing, validation, counting, searching, or transformation.\n5. Make the program print only useful final evidence so automated checks are reliable.\n\nEfficiency habit: most slow solutions start from unclear I/O. Lock down the contract first.";
    }
    if (pattern == "Brute Force to Optimized")
    {
        return "Pattern: Brute Force to Optimized\n\n1. Write the obvious solution first, even if it is slow.\n2. Identify repeated work.\n3. Replace repeated scans with a map, set, sorted order, prefix table, cache, or queue.\n4. Compare complexity before and after.\n5. Keep the brute-force version as a mental verifier for small cases.\n\nEfficiency habit: optimize the repeated work, not random lines of code.";
    }
    if (pattern == "Two Pointers")
    {
        return "Pattern: Two Pointers\n\nUse this for sorted arrays, windows, pairs, or scanning from both ends.\n\n1. Decide what each pointer means.\n2. Write the movement rule.\n3. Prove the rule does not skip a valid answer.\n4. Trace three iterations by hand.\n5. Handle empty, one-item, and duplicate-value cases.\n\nCommon bug: moving both pointers when only one side should move.";
    }
    if (pattern == "Hash Map Lookup")
    {
        return "Pattern: Hash Map Lookup\n\nUse this when the problem asks for fast membership, counts, grouping, or lookup by key.\n\n1. Choose the key.\n2. Choose the value stored with the key.\n3. Decide when to insert and when to query.\n4. Trace collisions conceptually, even though the library handles them.\n5. Explain average O(1) lookup and the memory tradeoff.\n\nCommon bug: using the wrong key, such as the index when the value should be the key.";
    }
    if (pattern == "Stack / Queue State")
    {
        return "Pattern: Stack / Queue State\n\nUse stack for last-in-first-out problems and queue for first-in-first-out workflows.\n\n1. Write the invariant: what does the structure contain after each step?\n2. Trace push/pop or enqueue/dequeue operations.\n3. Check empty-state behavior.\n4. Print final evidence that proves the order is correct.\n\nCommon bug: reading from an empty structure or using stack when queue order is required.";
    }
    if (pattern == "Tree / Graph Traversal")
    {
        return "Pattern: Tree / Graph Traversal\n\nUse this for connected objects, dependency graphs, folders, maps, routes, and state spaces.\n\n1. Define nodes and edges.\n2. Choose BFS for shortest unweighted paths or level order; choose DFS for deep exploration/backtracking.\n3. Track visited nodes.\n4. Write the visit order by hand before coding.\n5. Prove termination.\n\nCommon bug: forgetting visited tracking and creating an infinite traversal.";
    }
    if (pattern == "Dynamic Programming")
    {
        return "Pattern: Dynamic Programming\n\nUse this when the problem has overlapping subproblems and an optimal substructure.\n\n1. Define the state in one sentence.\n2. Define the recurrence.\n3. Define base cases.\n4. Choose top-down memoization or bottom-up table.\n5. Trace the table for a small input.\n\nEfficiency habit: if you cannot define the state clearly, do not start coding yet.";
    }
    if (pattern == "Debugging Failed Tests")
    {
        return "Pattern: Debugging Failed Tests\n\n1. Copy the failing input.\n2. Write expected output and actual output side by side.\n3. Identify the first point where the program state becomes wrong.\n4. Classify the bug: parsing, boundary, state update, edge case, output format, or algorithm.\n5. Make the smallest fix.\n6. Re-run all tests, not only the failed one.\n\nEfficiency habit: never change multiple things before re-running tests.";
    }
    if (pattern == "Complexity and Tradeoff Review")
    {
        return "Pattern: Complexity and Tradeoff Review\n\n1. Count loops and nested loops.\n2. Identify library operations that hide cost: sort, map lookup, string split, database query.\n3. Estimate time and space complexity.\n4. Decide what input size would break the solution.\n5. Pick a tradeoff: more memory for speed, simpler code for maintainability, or preprocessing for faster queries.\n\nEfficiency habit: Big-O is a decision tool, not a decoration.";
    }
    return "Pattern: Universal Problem-Solving Loop\n\n1. Understand the problem.\n2. Define input, output, constraints, and examples.\n3. Choose a pattern.\n4. Trace before coding.\n5. Implement the smallest correct solution.\n6. Verify with real tests.\n7. Debug by isolating the first wrong state.\n8. Refactor for clarity and efficiency.\n9. Explain the approach, correctness, and complexity.\n\nUse this loop on every exercise until it becomes automatic.";
}

QString MainWindow::problemSolvingCoachText() const
{
    const Module* module = (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size()) ? &m_modules[m_currentModuleIndex] : nullptr;
    const Lesson* lesson = nullptr;
    const Exercise* exercise = nullptr;
    if (module)
    {
        if (m_currentLessonIndex >= 0 && m_currentLessonIndex < module->lessons.size()) lesson = &module->lessons[m_currentLessonIndex];
        if (m_currentExerciseIndex >= 0 && m_currentExerciseIndex < module->exercises.size()) exercise = &module->exercises[m_currentExerciseIndex];
    }

    const QString pattern = m_problemPatternSelector ? m_problemPatternSelector->currentText() : "Universal Problem-Solving Loop";

    QString text;
    text += "CURRENT COURSE CONTEXT\n";
    text += "Module: " + (module ? module->title : "None") + "\n";
    text += "Lesson: " + (lesson ? lesson->title : "None") + "\n";
    text += "Exercise: " + (exercise ? exercise->title : "None") + "\n\n";
    text += patternGuideText(pattern) + "\n\n";

    text += "20-MINUTE DELIBERATE PRACTICE DRILL\n";
    text += "0:00-2:00  Read the prompt and underline the action words.\n";
    text += "2:00-4:00  Write input, output, constraints, and one edge case.\n";
    text += "4:00-7:00  Choose the pattern and hand-trace one example.\n";
    text += "7:00-14:00 Implement the smallest correct solution.\n";
    text += "14:00-17:00 Run Verify Correct and inspect failures.\n";
    text += "17:00-19:00 Fix one issue and rerun.\n";
    text += "19:00-20:00 Write approach, correctness reason, and complexity.\n\n";

    text += "WHAT TO WRITE BEFORE CODING\n";
    text += "Problem type: counting / search / traversal / parsing / validation / optimization / simulation\n";
    text += "Inputs:\nOutputs:\nConstraints:\nTiny example:\nEdge case:\nChosen pattern:\nExpected complexity:\n\n";

    text += "WHEN YOU GET STUCK\n";
    text += "1. Shrink the input.\n";
    text += "2. Print or inspect the state after each step.\n";
    text += "3. Compare expected state to actual state.\n";
    text += "4. Fix the first wrong transition.\n";
    text += "5. Rerun all tests.\n";
    return text;
}


QString MainWindow::currentHelperPhase() const
{
    return m_helperPhaseSelector ? m_helperPhaseSelector->currentText() : "1. Understand the Prompt";
}

QString MainWindow::formatHelperTimer() const
{
    const int minutes = m_helperElapsedSeconds / 60;
    const int seconds = m_helperElapsedSeconds % 60;
    const int targetMinutes = m_helperTargetSeconds / 60;
    const int targetSeconds = m_helperTargetSeconds % 60;
    return QString("%1:%2 / %3:%4")
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'))
        .arg(targetMinutes, 2, 10, QChar('0'))
        .arg(targetSeconds, 2, 10, QChar('0'));
}

QString MainWindow::helperPopupText(const QString& phase) const
{
    const Module* module = (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size()) ? &m_modules[m_currentModuleIndex] : nullptr;
    const Lesson* lesson = nullptr;
    const Exercise* exercise = nullptr;
    if (module)
    {
        if (m_currentLessonIndex >= 0 && m_currentLessonIndex < module->lessons.size()) lesson = &module->lessons[m_currentLessonIndex];
        if (m_currentExerciseIndex >= 0 && m_currentExerciseIndex < module->exercises.size()) exercise = &module->exercises[m_currentExerciseIndex];
    }

    QString text;
    text += "Current module: " + QString(module ? module->title : "None") + "\n";
    text += "Current lesson: " + QString(lesson ? lesson->title : "None") + "\n";
    text += "Current exercise: " + QString(exercise ? exercise->title : "None") + "\n\n";

    if (phase.contains("Understand"))
    {
        text += "Do this before touching the keyboard:\n";
        text += "1. Rewrite the problem in your own words.\n";
        text += "2. Circle the action verb: count, find, convert, validate, traverse, optimize, parse, or simulate.\n";
        text += "3. Identify what would make a solution obviously wrong.\n\n";
        text += "Pop-up checkpoint: Can you explain the problem to someone else in one sentence?";
    }
    else if (phase.contains("Inputs"))
    {
        text += "Write the contract:\n";
        text += "Input type, output type, constraints, normal case, edge case, and invalid case.\n\n";
        text += "Pop-up checkpoint: If the verifier sends hidden input, do you know what shape that input will have?";
    }
    else if (phase.contains("Pattern"))
    {
        text += "Pick the strategy before coding:\n";
        text += "Counting usually means hash map. Sorted pair search often means two pointers. Shortest path means graph. Repeated subproblems may mean dynamic programming. Parsing means tokenizer/state machine.\n\n";
        text += "Pop-up checkpoint: What pattern are you using, and why is it better than guessing?";
    }
    else if (phase.contains("Trace"))
    {
        text += "Trace a tiny example by hand:\n";
        text += "Use 3-5 values, write every state change, and predict final output before running code.\n\n";
        text += "Pop-up checkpoint: What should the first state, middle state, and final state look like?";
    }
    else if (phase.contains("Implement"))
    {
        text += "Build the smallest correct version:\n";
        text += "Avoid clever code. Make input handling clear. Make each variable name explain its job. Print only what the verifier needs.\n\n";
        text += "Pop-up checkpoint: Can this code solve the tiny traced example?";
    }
    else if (phase.contains("Verification"))
    {
        text += "Use Verify Correct, not just Run:\n";
        text += "Run shows that the program starts. Verify Correct proves behavior against test cases by feeding input and checking expected output evidence.\n\n";
        text += "Pop-up checkpoint: Did every real test pass, or are you only seeing a successful process exit?";
    }
    else if (phase.contains("Debug"))
    {
        text += "Debug one state at a time:\n";
        text += "Find the first wrong state, not the last wrong output. Shrink the input. Print or inspect state after each transition. Fix one issue and rerun all tests.\n\n";
        text += "Pop-up checkpoint: What is the first line where actual state differs from expected state?";
    }
    else if (phase.contains("Refactor"))
    {
        text += "Improve without changing behavior:\n";
        text += "Rename confusing variables, extract repeated logic, remove debug prints, and reconsider time/space complexity. Rerun verification after every refactor.\n\n";
        text += "Pop-up checkpoint: Is the code easier to read and still verified correct?";
    }
    else
    {
        text += "Explain like a professional:\n";
        text += "State the approach, why it is correct, time complexity, space complexity, and one tradeoff or limitation.\n\n";
        text += "Pop-up checkpoint: Could you defend this solution in an interview or code review?";
    }

    return text;
}

QString MainWindow::advancedHelperText() const
{
    const Module* module = (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size()) ? &m_modules[m_currentModuleIndex] : nullptr;
    const Lesson* lesson = (module && m_currentLessonIndex >= 0 && m_currentLessonIndex < module->lessons.size()) ? &module->lessons[m_currentLessonIndex] : nullptr;
    const Exercise* exercise = (module && m_currentExerciseIndex >= 0 && m_currentExerciseIndex < module->exercises.size()) ? &module->exercises[m_currentExerciseIndex] : nullptr;

    QString text;
    text += "COACHING STEP\n";
    text += "This screen has only two jobs: define the coding problem and walk you through the solution approach. Questions and grading happen later in Testing and Verification.\n\n";

    text += "OBJECTIVE\n";
    text += lesson ? lesson->objective + "\n\n" : QString("No lesson selected.\n\n");

    text += "CODING PROBLEM\n";
    if (lesson && !lesson->coachedProblem.isEmpty()) text += lesson->coachedProblem + "\n\n";
    if (exercise)
    {
        text += "Connected exercise: " + exercise->title + "\n";
        text += exercise->prompt + "\n\n";
    }

    text += "SOLUTION WALKTHROUGH\n";
    text += "1. Restate the required output. If you cannot describe the output, do not code yet.\n";
    text += "2. Identify the input shape: single value, list, text, graph, table, request, or design artifact.\n";
    text += "3. Choose the pattern that matches the objective: counting, lookup, traversal, parsing, validation, simulation, design, or dynamic programming.\n";
    text += "4. Name the state you must maintain: counter, map, set, stack, queue, index boundaries, visited set, table row, or current object.\n";
    text += "5. Trace the provided example by hand and write the expected output before coding.\n";
    text += "6. Implement the smallest correct version first. Do not optimize until behavior is verified.\n";
    text += "7. Use the verifier result to locate the first wrong assumption, not to randomly rewrite the program.\n";
    text += "8. After passing, explain time complexity, space complexity, and why the output is correct.\n\n";

    text += "SOLUTION PLAN TO WRITE BEFORE TESTING\n";
    text += "Input: ____\n";
    text += "Output: ____\n";
    text += "Pattern: ____\n";
    text += "State/data structure: ____\n";
    text += "Algorithm steps: 1) ____ 2) ____ 3) ____\n";
    text += "Edge cases: ____\n";
    text += "Complexity: ____\n\n";

    text += "TIMER PHASE\n" + currentHelperPhase() + "\n";
    text += helperPopupText(currentHelperPhase()) + "\n\n";
    text += "NEXT ACTION\nClick Next: Testing when your solution plan is clear enough that you could explain it to an interviewer before writing code.";
    return text;
}


QString MainWindow::moduleSummaryText(const Module& module) const
{
    return module.title + "\nLevel: " + module.level + "\n\n" + module.summary + "\n\nLessons: " + QString::number(module.lessons.size()) + "\nExercises: " + QString::number(module.exercises.size()) + "\nQuiz questions: " + QString::number(module.quiz.size());
}

QString MainWindow::quizSummaryText() const
{
    const Module* module = (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size()) ? &m_modules[m_currentModuleIndex] : nullptr;
    const Lesson* lesson = (module && m_currentLessonIndex >= 0 && m_currentLessonIndex < module->lessons.size()) ? &module->lessons[m_currentLessonIndex] : nullptr;
    if (!module) return {};
    QString text;
    text += "This question checks the same objective you just learned and coached.\n";
    if (lesson) text += "Objective: " + lesson->objective + "\n";
    text += "Module: " + module->title + "\n";
    text += "Answer it before relying on the code editor. The point is to prove you understand the idea, not just that the program can run.";
    return text;
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
    const QString base = QCoreApplication::applicationDirPath() + "/examples/v35_objective_aligned_exercises";
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

QString MainWindow::sourceFileForRunner() const
{
    const LanguageTrack* track = (m_currentLanguageIndex >= 0 && m_currentLanguageIndex < m_languageTracks.size()) ? &m_languageTracks[m_currentLanguageIndex] : nullptr;
    const Module* module = (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size()) ? &m_modules[m_currentModuleIndex] : nullptr;
    if (!track || !module || m_currentExerciseIndex < 0 || m_currentExerciseIndex >= module->exercises.size()) return {};
    const QString folder = starterFolderForExercise(track->id, module->exercises[m_currentExerciseIndex]);
    if (track->id.contains("python")) return folder + "/main.py";
    if (track->id.contains("cpp")) return folder + "/main.cpp";
    if (track->id.contains("javascript")) return folder + "/main.js";
    if (track->id.contains("typescript")) return folder + "/main.ts";
    if (track->id.contains("java") && !track->id.contains("javascript")) return folder + "/Main.java";
    if (track->id.contains("csharp")) return folder + "/Program.cs";
    if (track->id.contains("go")) return folder + "/main.go";
    if (track->id.contains("rust")) return folder + "/src/main.rs";
    if (track->id.contains("sql")) return folder + "/queries.sql";
    if (track->id.contains("kotlin")) return folder + "/Main.kt";
    return {};
}

QString MainWindow::loadSourceCodeForRunner() const
{
    const QString path = sourceFileForRunner();
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QString::fromUtf8(file.readAll());
    }
    const Module* module = (m_currentModuleIndex >= 0 && m_currentModuleIndex < m_modules.size()) ? &m_modules[m_currentModuleIndex] : nullptr;
    if (!module || m_currentExerciseIndex < 0 || m_currentExerciseIndex >= module->exercises.size()) return {};
    return module->exercises[m_currentExerciseIndex].starterCode;
}

bool MainWindow::saveSourceCodeForRunner()
{
    if (!m_exerciseCode) return true;
    const QString path = sourceFileForRunner();
    if (path.isEmpty()) return false;
    QFileInfo info(path);
    QDir().mkpath(info.absolutePath());
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        appendRunnerOutput("\n[save failed] Could not write source file: " + path + "\n");
        return false;
    }
    QTextStream out(&file);
    out << m_exerciseCode->toPlainText();
    appendRunnerOutput("\n[save] Wrote editor code to: " + path + "\n");
    return true;
}

void MainWindow::copyExerciseToRunner()
{
    m_sidebar->setCurrentRow(5);
    refreshAllTabs();
}

void MainWindow::runRunnerAction(const QString& action)
{
    Exercise* exercise = currentExercise();
    LanguageTrack* track = currentLanguageTrack();
    if (!exercise || !track || !m_runnerProcess) return;
    if (!saveSourceCodeForRunner()) return;
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
    LanguageTrack* track = currentLanguageTrack();
    if (!exercise || !track) return;
    if (!saveSourceCodeForRunner()) return;

    const QString folder = starterFolderForExercise(track->id, *exercise);
    const QString buildCommand = commandForRunner("build");
    const QString runCommand = commandForRunner("run");
    const QVector<VerificationCase> cases = verificationCasesForExerciseId(exercise->id);

    m_lastRunnerOutput.clear();
    appendRunnerOutput("\n[VERIFY] v35 lesson-aligned verifier started. It checks behavior practiced in the lesson, coaching walkthrough, and testing stage.\n");
    appendRunnerOutput("[VERIFY] Source file: " + sourceFileForRunner() + "\n");
    appendRunnerOutput("[VERIFY] Working folder: " + folder + "\n");

    auto execute = [&](const QString& command, const QString& input, int timeoutMs, QString* combinedOutput, int* exitCode) -> bool
    {
        QProcess process;
        process.setWorkingDirectory(folder);
#ifdef Q_OS_WIN
        process.start("cmd.exe", {"/C", command});
#else
        process.start("/bin/sh", {"-lc", command});
#endif
        if (!process.waitForStarted(5000))
        {
            *combinedOutput = "Process could not start.";
            *exitCode = -999;
            return false;
        }
        if (!input.isEmpty())
        {
            process.write(input.toUtf8());
        }
        process.closeWriteChannel();
        const bool finished = process.waitForFinished(timeoutMs);
        if (!finished)
        {
            process.kill();
            process.waitForFinished(2000);
        }
        *exitCode = finished ? process.exitCode() : -998;
        *combinedOutput = QString::fromLocal8Bit(process.readAllStandardOutput()) + QString::fromLocal8Bit(process.readAllStandardError());
        return finished && process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0;
    };

    if (!buildCommand.isEmpty() && buildCommand != runCommand && !buildCommand.contains("unittest", Qt::CaseInsensitive) && !buildCommand.contains("pytest", Qt::CaseInsensitive))
    {
        QString buildOutput;
        int buildExit = 0;
        appendRunnerOutput("\n[BUILD] " + buildCommand + "\n");
        const bool buildOk = execute(buildCommand, "", 30000, &buildOutput, &buildExit);
        appendRunnerOutput(buildOutput.trimmed() + "\n");
        if (!buildOk)
        {
            appendRunnerOutput(QString("\n[VERIFY] Build failed. Exit code: %1. Fix compiler errors before correctness tests can run.\n").arg(buildExit));
            recordRunnerAttempt("verification_build_failed");
            refreshAllTabs();
            return;
        }
    }

    bool allPassed = true;
    int passed = 0;
    int number = 1;
    for (const VerificationCase& testCase : cases)
    {
        QString output;
        int exitCode = 0;
        appendRunnerOutput(QString("\n[TEST %1] %2\n").arg(number).arg(testCase.name));
        appendRunnerOutput("Input:\n" + (testCase.input.isEmpty() ? QString("<no stdin>\n") : testCase.input));
        const bool ran = execute(runCommand, testCase.input, 15000, &output, &exitCode);
        const QString normalizedOutput = normalizedText(output);
        bool fragmentsPresent = ran;
        QStringList missing;
        for (const QString& fragment : testCase.expectedFragments)
        {
            if (!normalizedOutput.contains(normalizedText(fragment)))
            {
                fragmentsPresent = false;
                missing << fragment;
            }
        }
        appendRunnerOutput("Output:\n" + output.trimmed() + "\n");
        if (fragmentsPresent)
        {
            appendRunnerOutput("Result: PASS\n");
            ++passed;
        }
        else
        {
            allPassed = false;
            appendRunnerOutput(QString("Result: FAIL\nExit code: %1\nMissing expected evidence: %2\n").arg(exitCode).arg(missing.join(", ")));
        }
        ++number;
    }

    appendRunnerOutput(QString("\n[VERIFY] Passed %1 / %2 real test case(s).\n").arg(passed).arg(cases.size()));
    if (allPassed)
    {
        appendRunnerOutput("[VERIFY] Correct. The program produced the expected behavior for every verification case.\n");
        m_progress.setCompleted(exercise->id, true);
        recordRunnerAttempt("verified_correct_by_real_tests");
        saveCurrentCourseCheckpoint("verification_passed");
        m_courseStageIndex = 4;
    }
    else
    {
        appendRunnerOutput("[VERIFY] Not correct yet. Fix the code so the actual output matches the expected behavior, not just a marker string.\n");
        recordRunnerAttempt("verification_failed_real_tests");
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
    m_progress.recordCodeAttempt(track->name, module->title, exercise->id, exercise->difficulty, commandForRunner("run"), m_lastRunnerOutput.left(500), status, "Recorded from v35 complete-curriculum step-by-step testing and verification stage.");
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
    else if (alg == "LRU Cache")
    {
        m_algorithmComplexity->setText("LRU Cache: O(1) average get/put using a hash map plus doubly linked list.");
        m_algorithmSteps = {"Capacity = 3. Start empty.", "put(A): add A to the front and map A to its node.", "put(B), put(C): newest item stays at the front; oldest moves toward the back.", "get(A): return A and move A to the front because it is recently used.", "put(D): capacity is exceeded, so evict the least recently used item.", "Explain why the map gives lookup speed and the list gives fast reordering."};
    }
    else if (alg == "Dijkstra Shortest Path")
    {
        m_algorithmComplexity->setText("Dijkstra: O((V + E) log V) with a priority queue for non-negative weighted graphs.");
        m_algorithmSteps = {"Set the start distance to 0 and all other nodes to infinity.", "Push the start node into a priority queue.", "Pop the lowest-distance node.", "Relax each outgoing edge: if the new path is cheaper, update the distance.", "Continue until the queue is empty or the target is finalized.", "Use it for routing, dependency costs, game maps, and network paths."};
    }
    else if (alg == "Database B-Tree Index")
    {
        m_algorithmComplexity->setText("B-Tree Index: O(log n) lookup with disk/page-friendly branching.");
        m_algorithmSteps = {"Start at the root page with sorted separator keys.", "Choose the child pointer whose range can contain the target key.", "Repeat through internal nodes until a leaf page is reached.", "Scan the leaf entries for the exact key or range start.", "Return row pointers or continue leaf traversal for a range query.", "Explain why indexes speed reads but add write and storage cost."};
    }
    else if (alg == "Compiler Tokenizer")
    {
        m_algorithmComplexity->setText("Tokenizer/Lexer: O(n) over the source text for most languages.");
        m_algorithmSteps = {"Read the first character of the source file.", "Classify it as whitespace, identifier, number, string, operator, or punctuation.", "Consume characters while the current token rule still matches.", "Emit a token with type, lexeme, and source position.", "Repeat until end of file.", "Use clear error messages when a token is malformed."};
    }
    else if (alg == "Distributed Job Queue")
    {
        m_algorithmComplexity->setText("Job Queue: throughput depends on queue operations, workers, retry policy, and idempotency.");
        m_algorithmSteps = {"Producer creates a job with type, payload, id, and retry count.", "Queue stores the job durably.", "Worker claims one job and marks it in progress.", "Worker runs the task and records success or failure.", "On failure, retry with backoff or move to a dead-letter queue.", "Design every job to be idempotent so retries do not corrupt data."};
    }
    else if (alg == "Rate Limiter")
    {
        m_algorithmComplexity->setText("Token Bucket Rate Limiter: O(1) per request in the common case.");
        m_algorithmSteps = {"Each user or key has a bucket with capacity and refill rate.", "Refill tokens according to elapsed time.", "When a request arrives, check whether at least one token is available.", "If available, consume one token and allow the request.", "If empty, reject or delay the request.", "Use it to protect APIs, login forms, and expensive backend services."};
    }
    else if (alg == "RAG Retrieval Pipeline")
    {
        m_algorithmComplexity->setText("RAG Retrieval: cost depends on chunk count, index type, embedding model, reranking, and context size.");
        m_algorithmSteps = {"Parse documents into clean text.", "Chunk the text with useful metadata and source locations.", "Create embeddings or searchable indexes for each chunk.", "Search for chunks relevant to the user question.", "Rerank or filter results, then assemble context with citations.", "Evaluate answer quality with representative questions and known sources."};
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
    QFile file(folder + "/v35_complete_curriculum_progress_summary.md");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "# CS Bootcamp Desktop v35 Progress Summary\n\n";
        out << m_progress.exportMarkdownSummary();
        out << "\n\n## Code Attempts\n\n" << m_progress.codeAttemptMarkdown();
    }
    QMessageBox::information(this, "Exported", "Progress summary exported to progress_exports/v35_complete_curriculum_progress_summary.md");
}

void MainWindow::recordProblemSolvingDrill()
{
    Exercise* exercise = currentExercise();
    Module* module = currentModule();
    const QString itemId = exercise ? exercise->id : currentContextId();
    const QString moduleName = module ? module->title : "Problem Solving";
    const QString pattern = m_problemPatternSelector ? m_problemPatternSelector->currentText() : "Universal Problem-Solving Loop";

    m_progress.recordStudyEvent(itemId, "problem_solving_drill", 20, "Completed v35 drill using pattern: " + pattern);
    m_progress.updateSkillMastery(moduleName + " - Problem Solving", 65, "Practiced classification, planning, tracing, verification, debugging, and explanation.");

    QMessageBox::information(this, "Drill Recorded", "Recorded a 20-minute problem-solving drill for the current course context.");
    refreshAllTabs();
}


void MainWindow::startHelperTimer()
{
    if (!m_helperTimer) return;
    if (!m_helperTimer->isActive())
    {
        m_helperTimer->start();
    }
    if (m_helperBody) m_helperBody->setPlainText(advancedHelperText());
}

void MainWindow::pauseHelperTimer()
{
    if (m_helperTimer)
    {
        m_helperTimer->stop();
    }
    if (m_helperBody) m_helperBody->setPlainText(advancedHelperText());
}

void MainWindow::resetHelperTimer()
{
    if (m_helperTimer)
    {
        m_helperTimer->stop();
    }
    m_helperElapsedSeconds = 0;
    if (m_helperPhaseSelector)
    {
        m_helperPhaseSelector->setCurrentIndex(0);
    }
    if (m_helperTimerLabel) m_helperTimerLabel->setText(formatHelperTimer());
    if (m_helperPhaseProgress) m_helperPhaseProgress->setValue(0);
    if (m_helperBody) m_helperBody->setPlainText(advancedHelperText());
}

void MainWindow::tickHelperTimer()
{
    if (m_helperElapsedSeconds < m_helperTargetSeconds)
    {
        ++m_helperElapsedSeconds;
    }

    if (m_helperTimerLabel) m_helperTimerLabel->setText(formatHelperTimer());
    if (m_helperPhaseProgress) m_helperPhaseProgress->setValue(m_helperElapsedSeconds);

    if (m_helperPhaseSelector)
    {
        const int second = m_helperElapsedSeconds;
        int phase = 0;
        if (second >= 19 * 60) phase = 8;
        else if (second >= 18 * 60) phase = 7;
        else if (second >= 16 * 60) phase = 6;
        else if (second >= 14 * 60) phase = 5;
        else if (second >= 8 * 60) phase = 4;
        else if (second >= 6 * 60) phase = 3;
        else if (second >= 4 * 60) phase = 2;
        else if (second >= 2 * 60) phase = 1;

        if (m_helperPhaseSelector->currentIndex() != phase)
        {
            m_helperPhaseSelector->setCurrentIndex(phase);
            showHelperPopup();
        }
    }

    if (m_helperBody) m_helperBody->setPlainText(advancedHelperText());

    if (m_helperElapsedSeconds >= m_helperTargetSeconds)
    {
        if (m_helperTimer) m_helperTimer->stop();
        QMessageBox::information(this, "Problem-Solving Timer Complete", "The 20-minute deliberate practice loop is complete. Run verification, record the drill, and write your explanation.");
        recordProblemSolvingDrill();
    }
}

void MainWindow::showHelperPopup()
{
    QMessageBox::information(this, "Advanced Helper - " + currentHelperPhase(), helperPopupText(currentHelperPhase()));
}

void MainWindow::advanceHelperPhase()
{
    if (!m_helperPhaseSelector) return;
    const int next = std::min(m_helperPhaseSelector->currentIndex() + 1, m_helperPhaseSelector->count() - 1);
    m_helperPhaseSelector->setCurrentIndex(next);
    showHelperPopup();
    if (m_helperBody) m_helperBody->setPlainText(advancedHelperText());
}



void MainWindow::advanceCourseStage()
{
    if (m_courseStageIndex == 0)
    {
        if (Lesson* lesson = currentLesson())
        {
            m_progress.recordStudyEvent(lesson->id, "lesson_read", 10, "Finished the lesson explanation step in v35.");
        }
        saveCurrentCourseCheckpoint("lesson_step_completed");
        m_courseStageIndex = 1;
    }
    else if (m_courseStageIndex == 1)
    {
        if (Lesson* lesson = currentLesson())
        {
            m_progress.recordStudyEvent(lesson->id, "coaching_walkthrough_completed", 10, "Finished the problem and solution walkthrough before testing in v35.");
        }
        saveCurrentCourseCheckpoint("coaching_walkthrough_completed");
        m_courseStageIndex = 2;
    }
    else if (m_courseStageIndex == 2)
    {
        saveSourceCodeForRunner();
        recordRunnerAttempt("submitted_for_verification");
        saveCurrentCourseCheckpoint("testing_submitted");
        m_courseStageIndex = 3;
    }
    else if (m_courseStageIndex == 3)
    {
        QMessageBox::information(this, "Verification step", "Run Verify Correct. When the real tests pass, save the finished lesson.");
    }
    else
    {
        saveCurrentCourseCheckpoint("finished_lesson_saved");
        Module* module = currentModule();
        if (module && m_currentLessonIndex + 1 < module->lessons.size())
        {
            ++m_currentLessonIndex;
            if (m_currentLessonIndex < module->exercises.size()) m_currentExerciseIndex = m_currentLessonIndex;
            if (m_currentLessonIndex < module->quiz.size()) m_currentQuizIndex = m_currentLessonIndex;
        }
        m_courseStageIndex = 0;
        if (m_exerciseCode) m_exerciseCode->clear();
    }
    refreshAllTabs();
}


void MainWindow::saveCurrentCourseCheckpoint(const QString& status)
{
    const QString lessonId = currentLesson() ? currentLesson()->id : currentContextId();
    const QString exerciseId = currentExercise() ? currentExercise()->id : lessonId;
    const QString language = currentLanguageTrack() ? currentLanguageTrack()->name : "No language selected";
    const QString moduleName = currentModule() ? currentModule()->title : "No module selected";
    const QString lessonName = currentLesson() ? currentLesson()->title : "No lesson selected";
    const QString exerciseName = currentExercise() ? currentExercise()->title : "No exercise selected";
    const QString notes = m_reviewEditor ? m_reviewEditor->toPlainText().trimmed() : QString();
    const QString checkpointText = QString("Module: %1\nLesson: %2\nExercise: %3\nLanguage: %4\nStage: %5\nStatus: %6\n\nLearner notes:\n%7")
        .arg(moduleName, lessonName, exerciseName, language, QString::number(m_courseStageIndex + 1), status, notes.isEmpty() ? "No notes yet." : notes);
    m_progress.setNotesFor(lessonId + "_v35_checkpoint", checkpointText);
    m_progress.recordStudyEvent(lessonId, status, 5, checkpointText.left(900));
    if (status.contains("completed") || status.contains("passed") || status.contains("saved") || status.contains("finished"))
    {
        m_progress.setCompleted(lessonId + "_v35_" + status, true);
        if (status.contains("finished")) m_progress.setCompleted(lessonId, true);
    }
    refreshHistoryPane();
}

void MainWindow::refreshHistoryPane()
{
    if (!m_completedHistoryList) return;
    m_completedHistoryList->blockSignals(true);
    m_completedHistoryList->clear();
    for (const Module& module : m_modules)
    {
        for (const Lesson& lesson : module.lessons)
        {
            if (m_progress.isCompleted(lesson.id) || !m_progress.notesFor(lesson.id + "_v35_checkpoint").isEmpty())
            {
                m_completedHistoryList->addItem("✓ Lesson: " + lesson.title);
            }
        }
        for (const QuizQuestion& q : module.quiz)
        {
            if (m_progress.isCompleted(q.id))
            {
                m_completedHistoryList->addItem("✓ Question: " + q.question.left(65));
            }
        }
        for (const Exercise& e : module.exercises)
        {
            if (m_progress.isCompleted(e.id))
            {
                m_completedHistoryList->addItem("✓ Test: " + e.title);
            }
        }
    }
    if (m_completedHistoryList->count() == 0)
    {
        m_completedHistoryList->addItem("No completed checkpoints yet. Finish the current lesson gate to start history.");
    }
    m_completedHistoryList->blockSignals(false);
}

void MainWindow::selectHistoryItem(int index)
{
    if (!m_completedHistoryList || !m_reviewEditor || index < 0) return;
    const QString label = m_completedHistoryList->item(index)->text();
    QString found;
    for (const Module& module : m_modules)
    {
        for (const Lesson& lesson : module.lessons)
        {
            if (label.contains(lesson.title))
            {
                found = m_progress.notesFor(lesson.id + "_v35_checkpoint");
                if (found.isEmpty()) found = "Completed lesson: " + lesson.title + "\n\n" + lessonDetailText(lesson).left(1200);
                break;
            }
        }
        if (!found.isEmpty()) break;
    }
    if (found.isEmpty()) found = "Saved checkpoint:\n" + label + "\n\nUse this pane to review prior work and add reflections before saving another checkpoint.";
    m_reviewEditor->setPlainText(found);
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
    if (m_courseTaskStack)
    {
        m_courseStageIndex = std::max(0, std::min(m_courseStageIndex, m_courseTaskStack->count() - 1));
        m_courseTaskStack->setCurrentIndex(m_courseStageIndex);
    }
    if (m_courseStageTitle)
    {
        const QStringList names = {"Lesson", "Coaching", "Testing", "Verification", "Save"};
        m_courseStageTitle->setText("Step: " + names.value(m_courseStageIndex, "Course task"));
    }
    if (m_courseGateLabel)
    {
        m_courseGateLabel->setText(QString("One required step is shown at a time. The lesson, coaching, testing, and verification all target the same objective. Context: %1 → %2 → %3")
            .arg(module ? module->title : "No module")
            .arg(lesson ? lesson->title : "No lesson")
            .arg(track ? track->name : "No language"));
    }
    refreshHistoryPane();

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
    if (m_dashboardPlan) m_dashboardPlan->setPlainText("v35 focuses the app on becoming faster and more disciplined at coding problem solving. The course now follows one gated loop: lesson, coaching walkthrough, testing questions plus coding, verification, then saved review history in the right pane.\n\nUse the helper on every exercise: start the 20-minute timer, move through each phase, read the pop-up checkpoints, implement the smallest correct version, run real verification, debug the first wrong state, refactor, and explain complexity.");

    if (m_lessonTitle && lesson) m_lessonTitle->setText(lesson->title);
    if (m_lessonBody && lesson) m_lessonBody->setPlainText(lessonDetailText(*lesson));
    if (m_exerciseTitle && exercise) m_exerciseTitle->setText(exercise->title);
    if (m_exerciseBody && exercise) m_exerciseBody->setPlainText(exerciseDetailText(*exercise));
    if (m_exerciseCode && exercise && m_exerciseCode->toPlainText().isEmpty()) m_exerciseCode->setPlainText(loadSourceCodeForRunner());
    if (m_problemCoachBody) m_problemCoachBody->setPlainText(problemSolvingCoachText());
    if (m_helperContextLabel)
    {
        m_helperContextLabel->setText(QString("Current guided context: %1 → %2 → %3. Use the timer and pop-ups before you jump into code.")
            .arg(module ? module->title : "None")
            .arg(exercise ? exercise->title : "None")
            .arg(track ? track->name : "None"));
    }
    if (m_helperTimerLabel) m_helperTimerLabel->setText(formatHelperTimer());
    if (m_helperPhaseProgress)
    {
        m_helperPhaseProgress->setRange(0, m_helperTargetSeconds);
        m_helperPhaseProgress->setValue(std::min(m_helperElapsedSeconds, m_helperTargetSeconds));
    }
    if (m_helperBody) m_helperBody->setPlainText(advancedHelperText());
    if (m_coachingResponseEditor && lesson && m_coachingResponseEditor->toPlainText().isEmpty())
    {
        QString worksheet;
        worksheet += "My answers for: " + lesson->title + "\n\n";
        worksheet += "Input: ____\nOutput: ____\nPattern: ____\nData structure: ____\nEdge case: ____\nVerification test: ____\nCode plan: ____\n";
        m_coachingResponseEditor->setPlainText(worksheet);
    }

    if (m_runnerContext && module && exercise && track)
    {
        m_runnerContext->setText("Current context: " + module->title + " → " + exercise->title + " → " + track->name + ". Verification runs real compile/run/output checks for this exercise");
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

    if (m_contentBody && module) m_contentBody->setPlainText("Current module content pack\n\n" + moduleSummaryText(*module) + "\n\nEvery lesson now has a clear objective, a topic-specific explanation, a connected coaching problem, a matched testing question, and a verifier task that checks the same skill.");
    if (m_databaseBody) m_databaseBody->setPlainText("Database path:\n" + m_progress.databasePath() + "\n\nCompleted items: " + QString::number(m_progress.completedCount()) + "\nSaved notes from older versions: " + QString::number(m_progress.notesCount()) + "\nStudy events: " + QString::number(m_progress.studyEventCount()) + "\nCode attempts: " + QString::number(m_progress.codeAttemptCount()) + "\n\nRecent study events:\n" + m_progress.recentStudyEvents(8).join("\n") + "\n\nRecent code attempts:\n" + m_progress.codeAttemptRows(8).join("\n"));
    if (m_instructorBody && module) m_instructorBody->setPlainText("Instructor view for current module:\n\n" + module->title + "\n\nAssignment design:\n1. Require the learner to complete the detailed lesson checklist.\n2. Require real verifier evidence from the connected exercise runner.\n3. Require quiz mastery for the module.\n4. Require a v35 problem-solving drill record explaining classification, chosen pattern, failed test, fix, and complexity.\n\nRubric: concept explanation, working code, verification evidence, debugging reflection, professional readability.");
    if (m_capstoneBody) m_capstoneBody->setPlainText("Final capstone now builds from verified practice history. The learner should choose one advanced capstone only after completing lessons, exercises, quizzes, and code-attempt records in the selected specialization.");
    if (m_algorithmOutput && m_algorithmSteps.isEmpty()) resetAlgorithm();
}
