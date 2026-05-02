# First-Run Guide

## 1. Build the app

Open Command Prompt in the repo root and run:

```bat
rebuild_clean.bat
```

## 2. Confirm Qt path settings

The default scripts expect:

```bat
QT_PREFIX=C:\Qt\6.11.0\mingw_64
MINGW_BIN=C:\Qt\Tools\mingw1310_64\bin
```

If your Qt install is different, edit the `.bat` files and update those two variables.

## 3. Launch the app

After a successful build, the script should start:

```txt
build\CSBootcampDesktop.exe
```

## 4. Verify the main workflow

Open these pages from the sidebar:

- Dashboard
- Curriculum Map
- Language Workspace
- Exercise Runner
- Algorithm Visualizer
- Project Generator
- Portfolio Builder
- Career Readiness Center
- Progress Database
- Instructor / Bootcamp Mode
- AI Tutor Mode
- Release Polish

## 5. Use the app like a bootcamp

Start with Language Workspace, follow the weekly plan, run exercises in Exercise Runner, generate portfolio projects, track progress in SQLite, then use Career Readiness when you have projects to show.
