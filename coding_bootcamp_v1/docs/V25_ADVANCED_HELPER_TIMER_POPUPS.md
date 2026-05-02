# v25 Advanced Helper, Pop-Ups, and Real-Time Timer

v25 adds an interactive helper layer to train faster problem-solving habits.

## Why this matters

A learner often wastes time by writing code before understanding the problem. The v25 helper forces a better sequence:

`Understand → Contract → Pattern → Trace → Code → Verify → Debug → Refactor → Explain`

## Advanced Helper tab

The tab includes:

- Current module / exercise / language context
- Real-time 20-minute timer
- Phase progress bar
- Guided phase selector
- Helper text for the current phase
- Pop-up checkpoints
- Next Phase button
- Shortcuts to Practice Lab, Exercise Runner, and Quiz Trainer

## Real-time timer

The timer uses Qt `QTimer` with a one-second interval. It updates the timer label and progress bar live.

Timer phase plan:

- 0:00-2:00 understand the prompt
- 2:00-4:00 define input/output contract
- 4:00-6:00 choose a pattern
- 6:00-8:00 trace a tiny example
- 8:00-14:00 implement
- 14:00-16:00 verify
- 16:00-18:00 debug
- 18:00-19:00 refactor
- 19:00-20:00 explain

## Pop-up coaching

Each phase has a focused pop-up. The pop-up asks the learner for a checkpoint before moving on. The goal is to build a disciplined professional process, not just produce code randomly.
