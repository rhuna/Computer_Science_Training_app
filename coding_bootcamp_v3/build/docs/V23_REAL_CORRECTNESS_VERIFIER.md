# v23 Real Correctness Verifier

v23 replaces the old marker-only verification workflow.

Older versions treated an exercise as correct when the console output contained a `PASS_*` token. That proved the runner launched, but it did not prove the learner's code solved the problem.

v23 now verifies behavior:

1. The app saves the code from the Practice Lab editor into the selected language exercise folder.
2. The app runs the language build command when the language needs compilation.
3. The app starts the program as a separate process.
4. The app feeds one or more test inputs through standard input.
5. The app captures standard output and standard error.
6. The app normalizes the output.
7. The app checks for expected result fragments from the real test cases.
8. The app records the attempt as passed, failed, or build-failed in SQLite.

This means printing `PASS_BASE_CONVERTER` by itself is no longer enough. For the base converter exercise, the program must actually produce correct binary and hexadecimal output for the tested inputs.

## Current built-in behavioral checks

The verifier includes real behavioral checks for common bootcamp exercises such as:

- Number Base Converter
- Word Frequency Counter
- Input Validator
- Two Sum
- LRU Cache
- CSV Reporter
- Advanced Tokenizer
- Rate Limiter
- Distributed Job Queue
- B-Tree Index
- RAG Pipeline

Other exercises use a professional output contract until a richer custom test pack is added.

## How to use

1. Pick a module.
2. Pick an exercise.
3. Pick a language.
4. Edit the source code in the Practice Lab editor.
5. Go to Exercise Runner.
6. Click **Verify Correct**.

The verification report will show every test case, the input used, the actual output, missing expected evidence, and whether the program passed.
