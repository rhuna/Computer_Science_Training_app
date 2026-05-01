# Architecture

## Goal

CS Bootcamp Desktop is designed as a local C++ desktop bootcamp application. The long-term goal is to help a learner move from fundamentals to professional engineering through structured content, exercises, quizzes, projects, progress, and eventually code execution.

## Main components

### `BootcampContent`

Owns the built-in curriculum for v1. It returns plain data structures rather than UI widgets. This keeps curriculum data separated from presentation code.

Future versions can replace or supplement this with:

- JSON files
- SQLite database
- Markdown lessons
- Downloaded curriculum packs
- User-created tracks

### `MainWindow`

Owns the desktop shell and user interface:

- Sidebar navigation
- Dashboard
- Curriculum map
- Lesson page
- Exercise page
- Quiz page
- Project page
- Progress page
- Notes page

The class currently builds the UI in C++ code. This avoids `.ui` designer files and keeps the repo easy to inspect and modify.

### `ProgressStore`

Persists completion state and notes to local JSON. This is the first step toward analytics and mastery tracking.

Future versions can add:

- Multiple users
- Skill scores
- Quiz history
- Study streaks
- Spaced repetition scheduling
- Exportable progress reports

## Why Qt Widgets

Qt Widgets is a good fit for this project because it gives you a professional Windows desktop application with mature controls, layouts, persistence helpers, and CMake support.

## Upgrade rules

Future versions should follow these rules:

1. Preserve existing pages unless intentionally superseded.
2. Add new pages as modules instead of bloating one file.
3. Keep data models separate from UI widgets.
4. Keep build scripts working.
5. Keep old curriculum content unless replacing it with a richer version.
6. Do not remove user progress compatibility without a migration step.
