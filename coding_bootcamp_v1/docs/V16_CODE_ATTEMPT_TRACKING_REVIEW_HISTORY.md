# v16 - Code Attempt Tracking and Review History

v16 turns practice into evidence. Learners can now save each meaningful coding attempt into the local SQLite progress database with language, topic, exercise/project id, difficulty, command/output notes, review status, and reviewer notes.

## Why this matters

Professional developers improve by tracking errors, fixes, test results, and review feedback. This page creates a permanent practice record that can be exported for portfolio reviews, instructor reviews, mock interviews, or personal retrospectives.

## Workflow

1. Choose the language and topic.
2. Run/build/test the exercise in the Exercise Runner or terminal.
3. Paste the command or workflow used.
4. Summarize the output or failure.
5. Mark the review status.
6. Add self-review or instructor notes.
7. Export the Markdown history before portfolio or career-readiness reviews.

## Review statuses

- Needs Work
- Revised
- Reviewed
- Portfolio Ready
- Archived

## Database table

The new `code_attempt_reviews` table supplements the earlier v11 `code_attempts` placeholder and stores a richer review history.
