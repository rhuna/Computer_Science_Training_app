# v25 Build Notes

## Major code changes

- Added `createAdvancedHelperPage()`.
- Added `QTimer`-backed real-time timer.
- Added helper phase selector and progress bar.
- Added modal pop-up coaching via `QMessageBox::information`.
- Added helper text generation methods:
  - `advancedHelperText`
  - `helperPopupText`
  - `currentHelperPhase`
  - `formatHelperTimer`
- Updated sidebar order and navigation shortcuts.
- Updated progress database filename to `progress_v25.sqlite`.

## Manual QA checklist

1. The app launches and shows the v25 title.
2. Sidebar includes Advanced Helper after Problem Solving Coach.
3. Start Timer increments every second.
4. Pause stops the timer.
5. Reset returns to 00:00.
6. Next Phase changes the helper content and opens a popup.
7. Timer automatically changes phases as elapsed time passes.
8. Exercise Runner still points at `examples/v25_guided_problem_solving_exercises`.
