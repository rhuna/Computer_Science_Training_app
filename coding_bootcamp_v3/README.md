# CS Bootcamp Desktop v28 - One Task at a Time Bootcamp

CS Bootcamp Desktop v28 restructures the course into a gated, low-clutter workflow.

Instead of exposing every tool at once, the learner sees only the current task:

1. **Lesson + Coaching** - read one lesson, use the timer, and answer the coaching prompts.
2. **Questions** - prove understanding before code is unlocked.
3. **Testing + Verification** - write code and run the real verifier.
4. **Saved Review** - record what was learned, then move to the next lesson.

A left-hand history pane stores completed lessons, questions, tests, and review checkpoints so the learner can go back, view work, and edit reflection notes.

## Why v28 exists

The previous versions had strong components, but too many visible tools made the workflow feel scattered. v28 turns the app into a guided bootcamp sequence that behaves more like a patient instructor:

- one lesson at a time
- one coaching phase at a time
- one question gate before coding
- one test/verification gate before progress is saved
- history saved in a left-hand pane for review

## Main UI layout

```text
Left history pane        Right active task pane
-----------------        ----------------------
Saved lessons       ->   Lesson + coaching
Saved questions     ->   Questions
Saved tests         ->   Testing + verification
Saved reviews       ->   Saved review
```

## Build

```bat
rebuild_clean.bat
```

If your Qt path is different, edit `QT_PREFIX` and `MINGW_BIN` in the `.bat` files.

## New in v28

- Replaced the two-tab layout with a gated task stack.
- Added a left-hand completed-history pane.
- Added checkpoint saving for lessons, questions, testing, and review.
- Kept the real verifier from v23+.
- Kept the real-time timer and pop-up coaching from v25+.
- Updated the database to `progress_v28.sqlite`.
- Added docs for the gated workflow.
