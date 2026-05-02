# V28 Build Notes

V28 keeps the Qt Widgets/CMake structure and changes the app workflow in `MainWindow.cpp`.

## Key source changes

- Added a left-side history pane.
- Added a `QStackedWidget` for gated course stages.
- Added checkpoint save helpers.
- Added stage advancement helpers.
- Updated runtime database name to `progress_v28.sqlite`.
- Updated starter exercise folder to `examples/v28_gated_course_exercises`.

## Build command

```bat
rebuild_clean.bat
```
