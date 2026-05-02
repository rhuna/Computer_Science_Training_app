# CS Bootcamp Desktop v20 - Unified Learning System

v20 restructures the app around the way a learner actually studies.

## Removed tabs

The following tabs were intentionally removed from the sidebar because they made the app feel scattered:

- Portfolio Projects
- Portfolio Builder
- Git Testing CI/CD Lab
- Career Readiness Center
- Release Polish
- Career Paths

The related content can still exist as documentation or templates, but it is no longer part of the main learner workflow.

## Unified workflow

Every major tab now shares the same selected context:

1. Selected module
2. Selected lesson
3. Selected exercise
4. Selected quiz question
5. Selected language track

That means the user can choose a module in **Learning Path**, then move through **Practice Lab**, **Exercise Runner**, **Quiz Trainer**, **AI Tutor**, **Notes**, and **Progress Database** without reselecting everything.

## Deeper lesson guidance

Each lesson now displays:

- Objective
- Detailed explanation
- How to complete the objective
- Checklist items with how-to instructions
- Practice items with step-by-step guidance

## Exercise verification

The Exercise Runner now supports a correctness workflow:

- Run/build/test local starter folders
- Capture console output
- Verify that the expected `PASS_*` token appears
- Mark the exercise complete only after successful verification
- Record the attempt in SQLite

Starter files live in:

```text
examples/v20_verified_exercises/
```

## Quiz expansion

Each module receives additional v20 quiz questions covering:

- Objective mastery
- Checklist execution
- Practice strategy
- Verification
- Notes and reflection
- Debugging workflow
- Cross-language learning
- Evidence of mastery

## Professional design goal

The app should feel like this:

```text
Learn -> Practice -> Run -> Verify -> Quiz -> Notes -> Progress
```

not like a loose collection of unrelated pages.
