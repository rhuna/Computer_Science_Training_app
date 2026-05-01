# CS Bootcamp Desktop v21

A C++/Qt desktop computer science bootcamp platform designed to take a learner from fundamentals toward professional-level software development across multiple industry languages.

## v21 focus

**Verified Exercise Packs.**

v21 keeps the simplified v20 workflow and adds runnable starter packs for the major language tracks. The app now points the Exercise Runner at:

```text
examples/v21_verified_exercises/
```

Each exercise pack is designed around this loop:

```text
Lesson -> Practice -> Run -> Verify PASS token -> Save notes -> Progress
```

## Major improvements

- Verified starter folders for C++, Python, JavaScript, TypeScript, Java, C#, Go, Rust, SQL, and Kotlin.
- Each pack includes a README explaining the practice goal and expected token.
- Each pack includes `run.bat` and `test.bat` when practical.
- The app now computes unique expected tokens from each exercise ID, such as `PASS_BASE_CONVERTER` or `PASS_WORD_FREQUENCY`.
- Quiz banks include additional v21 verification/debugging questions.
- Progress summaries export as `v21_verified_progress_summary.md`.

## Build

```bat
rebuild_clean.bat
```

## Run

```bat
run_app.bat
```

## Important note

Qt is required to compile this project locally. The app links Qt Widgets and Qt SQL.
