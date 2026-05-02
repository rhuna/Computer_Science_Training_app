# v11 - SQLite Progress Database

v11 upgrades CS Bootcamp Desktop from early-file progress tracking into a professional local persistence layer.

## New database file

The app writes progress to a local `progress_v11.sqlite` file. The exact path is displayed inside the new **Progress Database** page.

## Tables

- `learner_profiles` - learner identity and target role
- `completed_items` - completed lessons, exercises, quizzes, and projects
- `item_notes` - notes attached to the currently selected learning item
- `study_events` - study-session history and timeline events
- `skill_mastery` - skill score rows for professional readiness tracking
- `code_attempts` - prepared for future exercise-runner attempt history

## New app page

The new **Progress Database** page shows the active profile, database path, completed count, notes count, study event count, tracked skill count, recent study history, and skill mastery rows.

## New actions

- Seed core skill mastery rows
- Record a 25-minute focused study session
- Export a Markdown database summary
- Open the database folder

## Why this matters

This is the foundation for later versions that need charts, streaks, spaced repetition, saved code attempts, multiple profiles, instructor mode, and more accurate readiness scoring.
