# CS Bootcamp Desktop v25 - Guided Problem Solving Course

v25 builds on the v24 problem-solving course and adds an **Advanced Helper** that keeps the learner moving through a professional coding workflow.

## What changed in v25

- Added the **Advanced Helper** tab.
- Added real-time deliberate-practice timer using Qt `QTimer`.
- Added pop-up checkpoints for every problem-solving phase.
- Connected the helper to the selected module, lesson, exercise, and language.
- Timer automatically advances through the workflow:
  1. Understand the prompt
  2. Define inputs and outputs
  3. Choose a pattern
  4. Trace a tiny example
  5. Implement the smallest correct version
  6. Run real verification
  7. Debug the first wrong state
  8. Refactor
  9. Explain correctness and complexity
- Updated examples folder to `examples/v25_guided_problem_solving_exercises`.
- Updated local progress database to `progress_v25.sqlite`.

## Recommended learning flow

1. Open **Learning Path** and read the selected lesson.
2. Open **Practice Lab** and inspect the selected exercise.
3. Open **Problem Solving Coach** to choose the right strategy.
4. Open **Advanced Helper**, start the timer, and follow the pop-ups.
5. Open **Exercise Runner** and run **Verify Correct**.
6. Open **Quiz Trainer** and check understanding.
7. Review evidence in **Progress Database**.

## Build

```bat
rebuild_clean.bat
```

## Package

```bat
scripts\package_release.bat
```

