# CS Bootcamp Desktop v24 - Problem Solving Efficiency Course

v24 keeps the simplified guided bootcamp direction and improves the app specifically for coding problem-solving efficiency.

## What changed in v24

The app now teaches a repeatable professional loop:

```txt
Learn → Classify → Plan → Trace → Code → Verify → Debug → Refactor → Explain
```

## New main feature

A new **Problem Solving Coach** tab connects the currently selected module, lesson, exercise, language, verifier, quiz, and progress database.

It includes pattern guides for:

- Universal problem-solving loop
- Input/output modeling
- Brute force to optimized
- Two pointers
- Hash map lookup
- Stack/queue state
- Tree/graph traversal
- Dynamic programming
- Debugging failed tests
- Complexity and tradeoff review

## Exercise verification

The Exercise Runner still performs real correctness checks from v23:

1. Saves the learner code.
2. Builds or runs it.
3. Feeds real test input.
4. Captures output.
5. Compares expected behavior.
6. Records the attempt in SQLite.

## Build

```bat
rebuild_clean.bat
```

## Docs

See:

```txt
docs/V24_PROBLEM_SOLVING_EFFICIENCY.md
docs/V23_REAL_CORRECTNESS_VERIFIER.md
```
