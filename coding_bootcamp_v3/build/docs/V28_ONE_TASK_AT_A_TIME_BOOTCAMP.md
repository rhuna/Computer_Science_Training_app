# V29 - Clean Step-by-Step Bootcamp

V29 changes the user experience from a tabbed toolbox into a gated learning path.

## Learner flow

```text
Lesson + Coaching -> Questions -> Testing + Verification -> Saved Review -> Next Lesson
```

## Design goals

- Keep most functionality behind the scenes until the learner needs it.
- Prevent jumping into code before understanding the problem.
- Prevent claiming progress before tests prove correctness.
- Save every completed checkpoint into a left-hand pane.
- Allow the learner to revisit and edit review notes from previous lessons and tests.

## Left history pane

The history pane displays completed:

- lessons
- question checkpoints
- verified tests
- saved reviews

Selecting an item shows the saved checkpoint notes in the review editor.

## Gated progression

### Gate 1 - Lesson + Coaching

The learner reads one lesson, uses the helper timer, and follows one coaching phase at a time.

### Gate 2 - Questions

The learner answers a checkpoint question. Correct answers unlock testing.

### Gate 3 - Testing + Verification

The learner writes code, runs build/run/test actions, then uses the real verifier.

### Gate 4 - Saved Review

The learner writes what failed, what fixed it, and what pattern was used. The checkpoint is saved before moving forward.
