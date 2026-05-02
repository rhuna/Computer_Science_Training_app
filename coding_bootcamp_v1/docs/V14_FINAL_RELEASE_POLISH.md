# CS Bootcamp Desktop v15 - Professional Content Pack Expansion

v14 turns the CS Bootcamp Desktop project into a more complete Windows desktop product snapshot. It does not remove the v1-v13 features. It adds a release-polish layer around the existing multi-language curriculum, exercise runner, project generator, portfolio tools, career center, SQLite progress tracking, instructor mode, and optional AI tutor workflow.

## Added in v14

- Embedded app icon through `resources.qrc`.
- Splash screen shown at startup.
- New **Release Polish** page in the sidebar.
- First-run checklist inside the app.
- Final QA smoke-test checklist inside the app.
- Markdown export for the v14 smoke-test checklist.
- Help Center documentation.
- First-Run Guide documentation.
- Release packaging script.
- Smoke-test script.
- Safe menu script for common batch files.
- Release templates folder for future installer and deployment notes.

## Release process

1. Run `rebuild_clean.bat`.
2. Launch the app and verify the Dashboard shows v14.
3. Open every sidebar page.
4. Export the release smoke-test checklist from the Release Polish page.
5. Run `scripts\smoke_test_v15.bat` and manually confirm each item.
6. Run `scripts\package_release.bat` to create a clean release folder.
7. Zip the release folder only after the smoke test passes.

## Notes

The app still works offline. The AI Tutor remains optional and offline-first. Later versions can add hosted/local model provider adapters without breaking the current offline tutor workflows.
