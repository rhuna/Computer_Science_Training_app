# v21 Verified Exercise Packs

This release expands the v20 unified workflow with runnable starter exercises for every major industry language track.

## Goal

The user should be able to select a lesson, open a connected exercise, choose a language, run the starter, and verify correctness using the exact `PASS_*` token expected by the app.

## Pack structure

Each exercise folder follows this layout where possible:

```text
examples/v21_verified_exercises/<language_id>/<exercise_id>/
  README.md
  run.bat
  test.bat
  source files
```

## Professional workflow

1. Read the lesson objective.
2. Read the checklist item and how-to guidance.
3. Open the matching exercise.
4. Run the starter folder to prove the toolchain works.
5. Replace the starter implementation with your own code.
6. Run again.
7. Verify the expected `PASS_*` token.
8. Save notes explaining what failed and how it was fixed.

## Supported language tracks

- C++
- Python
- JavaScript
- TypeScript
- Java
- C#
- Go
- Rust
- SQL
- Kotlin

## Why this matters

A bootcamp app should not only describe coding. It should create a feedback loop: instruction, implementation, execution, verification, reflection, and progress tracking.
