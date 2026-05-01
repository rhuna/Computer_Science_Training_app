#include "MainWindow.h"

#include <QApplication>
#include <QBoxLayout>
#include <QDir>
#include <QFileInfo>
#include <QFrame>
#include <QGroupBox>
#include <QMessageBox>
#include <QScrollArea>
#include <QStandardPaths>

namespace
{
    QLabel* makeHeader(const QString& text)
    {
        QLabel* label = new QLabel(text);
        label->setObjectName("pageHeader");
        label->setWordWrap(true);
        return label;
    }

    QTextEdit* makeReadOnlyText()
    {
        QTextEdit* text = new QTextEdit;
        text->setReadOnly(true);
        text->setMinimumHeight(220);
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
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_modules(BootcampContent::createDefaultModules())
    , m_progress(QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).filePath("progress.json"))
{
    QDir().mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    m_progress.load();
    buildLayout();
    applyAppStyle();
    refreshAllPages();
    setWindowTitle("CS Bootcamp Desktop - C++ Professional Track v1");
    resize(1320, 820);
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
    m_sidebar->setFixedWidth(245);
    m_sidebar->addItems({
        "Dashboard",
        "Curriculum Map",
        "Lessons",
        "Coding Exercises",
        "Quiz Trainer",
        "Portfolio Projects",
        "Progress Tracker",
        "Notes"
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
    m_pages->addWidget(createQuizPage());
    m_pages->addWidget(createProjectsPage());
    m_pages->addWidget(createProgressPage());
    m_pages->addWidget(createNotesPage());
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
    m_dashboardProgress = new QProgressBar;

    QLabel* path = new QLabel("Recommended path: C++ Foundations → Algorithms → Systems → Professional Engineering → Capstone.");
    path->setWordWrap(true);
    path->setObjectName("sectionTitle");

    QFrame* card = new QFrame;
    card->setObjectName("card");
    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->addWidget(m_dashboardSummary);
    cardLayout->addWidget(m_dashboardProgress);
    cardLayout->addWidget(path);

    QLabel* howToUse = new QLabel("Use this app like a real bootcamp: read one lesson, complete one exercise, answer quiz questions, then build a portfolio project. Mark items complete as you go. Later versions can add compilation, tests, interview drills, and project review scoring.");
    howToUse->setWordWrap(true);

    layout->addWidget(m_dashboardTitle);
    layout->addWidget(card);
    layout->addWidget(howToUse);
    layout->addStretch();
    return page;
}

QWidget* MainWindow::createCurriculumPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setSpacing(12);

    layout->addWidget(makeHeader("Curriculum Map"));

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
    m_lessonBody = makeReadOnlyText();
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
    m_exerciseBody = makeReadOnlyText();
    m_codeEditor = new QTextEdit;
    m_codeEditor->setPlaceholderText("Write or paste your solution here. v1 saves progress separately; v2 can add compile/run support.");
    m_codeEditor->setMinimumHeight(210);
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

QWidget* MainWindow::createQuizPage()
{
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);
    m_quizTitle = makeHeader("Quiz Trainer");
    m_quizBody = makeReadOnlyText();
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
    m_projectBody = makeReadOnlyText();
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

    const int total = totalTrackableItems();
    const int complete = m_progress.completedCount();
    const int percent = total == 0 ? 0 : (complete * 100) / total;
    m_dashboardSummary->setText(QString("You have completed %1 of %2 trackable bootcamp items. Keep moving through lessons, exercises, quizzes, and projects until your capstone is portfolio-ready.").arg(complete).arg(total));
    m_dashboardProgress->setRange(0, 100);
    m_dashboardProgress->setValue(percent);
    m_dashboardProgress->setFormat(QString("%1% complete").arg(percent));

    if (m_progressStats && m_progressList)
    {
        m_progressStats->setText(QString("Completed: %1 / %2 items").arg(complete).arg(total));
        m_progressList->clear();
        for (const Module& module : m_modules)
        {
            m_progressList->addItem("== " + module.title + " ==");
            for (const Lesson& lesson : module.lessons)
                m_progressList->addItem(QString("%1 Lesson: %2").arg(m_progress.isCompleted(lesson.id) ? "✅" : "⬜").arg(lesson.title));
            for (const Exercise& exercise : module.exercises)
                m_progressList->addItem(QString("%1 Exercise: %2").arg(m_progress.isCompleted(exercise.id) ? "✅" : "⬜").arg(exercise.title));
            for (const QuizQuestion& quiz : module.quiz)
                m_progressList->addItem(QString("%1 Quiz: %2").arg(m_progress.isCompleted(quiz.id) ? "✅" : "⬜").arg(quiz.question));
            for (const PortfolioProject& project : module.projects)
                m_progressList->addItem(QString("%1 Project: %2").arg(m_progress.isCompleted(project.id) ? "✅" : "⬜").arg(project.title));
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
        list->clear();
        for (const QString& name : names) list->addItem(name);
        if (list->count() > 0) list->setCurrentRow(0);
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
    Lesson& lesson = module->lessons[index];
    if (m_lessonTitle) m_lessonTitle->setText(lesson.title);
    if (m_lessonBody)
    {
        m_lessonBody->setPlainText("Objective:\n" + lesson.objective + "\n\nExplanation:\n" + lesson.explanation + "\n\nChecklist:\n" + bulletList(lesson.checklist) + "\nPractice:\n" + bulletList(lesson.practicePrompts));
    }
    if (m_lessonCompleteButton)
    {
        m_lessonCompleteButton->setText(m_progress.isCompleted(lesson.id) ? "Mark Lesson Incomplete" : "Mark Lesson Complete");
    }
}

void MainWindow::selectExercise(int index)
{
    Module* module = currentModule();
    if (!module || index < 0 || index >= module->exercises.size()) return;
    m_currentExerciseIndex = index;
    Exercise& exercise = module->exercises[index];
    if (m_exerciseTitle) m_exerciseTitle->setText(exercise.title + " — " + exercise.difficulty);
    if (m_exerciseBody)
    {
        m_exerciseBody->setPlainText("Prompt:\n" + exercise.prompt + "\n\nExpected concepts:\n" + exercise.expectedConcepts + "\n\nStarter code:\n" + exercise.starterCode);
    }
    if (m_codeEditor) m_codeEditor->setPlainText(exercise.starterCode);
    if (m_exerciseCompleteButton)
    {
        m_exerciseCompleteButton->setText(m_progress.isCompleted(exercise.id) ? "Mark Exercise Incomplete" : "Mark Exercise Complete");
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
    PortfolioProject& project = module->projects[index];
    if (m_projectTitle) m_projectTitle->setText(project.title + " — " + project.level);
    if (m_projectBody)
    {
        m_projectBody->setPlainText(project.description + "\n\nRequirements:\n" + bulletList(project.requirements) + "\nStretch goals:\n" + bulletList(project.stretchGoals));
    }
    if (m_projectCompleteButton)
    {
        m_projectCompleteButton->setText(m_progress.isCompleted(project.id) ? "Mark Project Incomplete" : "Mark Project Complete");
    }
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
    if (m_pages && m_pages->currentIndex() == 3)
    {
        const Module& module = m_modules[m_currentModuleIndex];
        if (m_currentExerciseIndex >= 0 && m_currentExerciseIndex < module.exercises.size()) return module.exercises[m_currentExerciseIndex].id;
    }
    if (m_pages && m_pages->currentIndex() == 4)
    {
        const Module& module = m_modules[m_currentModuleIndex];
        if (m_currentQuizIndex >= 0 && m_currentQuizIndex < module.quiz.size()) return module.quiz[m_currentQuizIndex].id;
    }
    if (m_pages && m_pages->currentIndex() == 5)
    {
        const Module& module = m_modules[m_currentModuleIndex];
        if (m_currentProjectIndex >= 0 && m_currentProjectIndex < module.projects.size()) return module.projects[m_currentProjectIndex].id;
    }
    const Module& module = m_modules[m_currentModuleIndex];
    if (m_currentLessonIndex >= 0 && m_currentLessonIndex < module.lessons.size()) return module.lessons[m_currentLessonIndex].id;
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
