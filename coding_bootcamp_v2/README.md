# CS Bootcamp Desktop v27 - Learning / Testing Course Mode

This version restructures the app so the learner does not have to jump through a long sidebar of separate tools. The main workflow is now one guided course screen.

## Main goal

Make the app feel like a real coding bootcamp instructor sitting beside the learner:

1. Pick the module.
2. Read one focused lesson.
3. Answer one Google-style checkpoint.
4. Plan the solution.
5. Code in the same screen.
6. Build/run/verify with real tests.
7. Take the connected quiz.
8. Step through the related algorithm model.
9. Record progress evidence.

## What changed in v27

- Replaced the multi-tab workflow with one guided course workspace.
- Hid the sidebar from the learner-facing UI.
- Kept the old helper/runner/progress systems internally so functionality is preserved.
- Integrated lesson, helper pop-ups, real-time timer, code editor, verifier, quiz, algorithm model, and progress evidence into one scrollable screen.
- Updated the app title and database to `progress_v27.sqlite`.
- Updated the exercise workspace to `examples/v27_learning_testing_course_exercises`.

## v27 Learning / Testing Tab Split

V27 keeps the simplified bootcamp course workflow but separates it into two focused tabs:

- **Learning + Coaching**: lesson, objective walkthrough, advanced helper, real-time timer, guided pop-ups, problem-solving pattern, and algorithm mental model.
- **Testing + Verification**: exercise code editor, build/run/test controls, real correctness verifier, quiz checkpoint, and progress evidence.

This reduces clutter while still keeping the course connected through the same selected module, lesson, exercise, language, quiz, and progress database.

## Build

```bat
rebuild_clean.bat
```

If needed, update the Qt paths inside the batch files.

## Recommended learner flow

Use the app like an interview practice room. Do not code first. Move through each phase in order: understand, define inputs/outputs, choose pattern, trace, implement, verify, debug, refactor, explain.
