# CS Bootcamp Desktop v12 — Instructor / Bootcamp Mode

v12 turns CS Bootcamp Desktop into a cohort-ready learning platform while preserving the self-study workflow from v1-v11.

## New capabilities

- Create cohort assignments.
- Attach rubrics and due dates.
- Record learner scores and instructor feedback.
- Store assignment and score data in the local SQLite database.
- Export a Markdown instructor report.
- Keep the same learner progress database, language tracks, exercise runner, project generator, portfolio builder, and career readiness pages.

## Instructor workflow

1. Create a weekly assignment for a cohort.
2. Attach a rubric with clear scoring categories.
3. Have learners use the Exercise Runner, Project Generator, and Portfolio Builder.
4. Record scores and feedback in Instructor / Bootcamp Mode.
5. Export the instructor report for review meetings or records.

## Database tables added in v12

- `instructor_assignments`
- `instructor_scores`

These tables are intentionally simple so later versions can add submissions, attachments, richer rubrics, due-date notifications, and cohort analytics without replacing the existing schema.
