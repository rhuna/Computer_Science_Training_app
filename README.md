# CS Bootcamp Desktop v1

A full C++/Qt desktop application that turns computer science into a guided bootcamp path. It is built to feel like the Cybersecurity Training Lab style: a real desktop repo, versionable, expandable, and structured for future professional upgrades.

## What v1 includes

- Dashboard with completion progress
- Curriculum map by module
- Lessons with objectives, explanations, checklists, and practice prompts
- Coding exercises with starter code and expected concepts
- Quiz trainer with answer checking and explanations
- Portfolio project track
- Local progress persistence using JSON
- Notes system tied to the current bootcamp item
- CMake project structure
- Windows build/run scripts
- Professional docs and roadmap

## Bootcamp path

1. C++ Foundations
2. Data Structures and Algorithms
3. Systems, OS, and Networking
4. Professional Engineering Practices
5. Capstone portfolio app

## Windows setup

Install:

- Visual Studio 2022 or MSYS2 MinGW
- Qt 6 for your compiler kit
- CMake 3.24+

This repo defaults to Qt paths similar to your previous projects. Edit the `QT_PREFIX` value in the batch files if your Qt install is somewhere else.

## Build with MinGW Qt

```bat
rebuild_clean.bat
```

or:

```bat
build_release_run.bat
```

## Manual CMake build

```bat
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:\Qt\6.11.0\mingw_64 -DCMAKE_BUILD_TYPE=Release
cmake --build build
build\CSBootcampDesktop.exe
```

## Recommended learning workflow

Use the app in this order:

1. Open Curriculum Map.
2. Pick the first module.
3. Read the first lesson.
4. Mark the lesson complete.
5. Do the matching exercise.
6. Use the Quiz Trainer.
7. Start the portfolio project.
8. Write notes for what confused you.
9. Move forward only after you can explain the topic out loud.

## Local save data

Progress is stored in your app data folder through Qt's `QStandardPaths::AppDataLocation` as `progress.json`.

## Repo structure

```text
CSBootcampDesktop_v1/
  CMakeLists.txt
  README.md
  rebuild_clean.bat
  build_release_run.bat
  build_debug_run.bat
  run_app.bat
  include/
    BootcampContent.h
    MainWindow.h
    ProgressStore.h
  src/
    BootcampContent.cpp
    MainWindow.cpp
    ProgressStore.cpp
    main.cpp
  data/
    curriculum_seed.json
  docs/
    ARCHITECTURE.md
    ROADMAP.md
    VERSION_PLAN.md
  scripts/
    clean_build_tree.bat
```

## Versioning direction

This v1 is intentionally a strong foundation. Future versions should add features without removing existing functionality.
