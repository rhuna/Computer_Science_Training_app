# Architecture

CS Bootcamp Desktop v2 is a C++17 Qt Widgets desktop application.

## UI Layer
`MainWindow` owns the navigation shell and pages:

- Dashboard
- Curriculum Map
- Lessons
- Coding Exercises
- Quiz Trainer
- Portfolio Projects
- Language Tracks
- Career Paths
- Progress Tracker
- Notes

## Content Layer
`BootcampContent` returns built-in curriculum objects:

- Module
- Lesson
- Exercise
- QuizQuestion
- PortfolioProject
- LanguageTrack
- CareerPath

## Persistence Layer
`ProgressStore` saves completed item IDs and notes to a local JSON file using Qt's app data location.

## Design Rules

- Keep prior version behavior intact.
- Add new pages instead of replacing old pages.
- Keep content separate from UI where possible.
- Use Qt Widgets only, so Vulkan/QML are not required.
