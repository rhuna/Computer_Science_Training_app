-- CS Bootcamp Desktop v11 schema reference.
-- The app creates these tables automatically through ProgressStore.

CREATE TABLE learner_profiles (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    display_name TEXT NOT NULL UNIQUE,
    target_role TEXT NOT NULL DEFAULT 'Junior Software Engineer',
    created_at TEXT NOT NULL
);

CREATE TABLE completed_items (
    profile_id INTEGER NOT NULL,
    item_id TEXT NOT NULL,
    completed_at TEXT NOT NULL,
    PRIMARY KEY(profile_id, item_id)
);

CREATE TABLE item_notes (
    profile_id INTEGER NOT NULL,
    item_id TEXT NOT NULL,
    notes TEXT NOT NULL,
    updated_at TEXT NOT NULL,
    PRIMARY KEY(profile_id, item_id)
);

CREATE TABLE study_events (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    profile_id INTEGER NOT NULL,
    item_id TEXT NOT NULL,
    event_type TEXT NOT NULL,
    minutes INTEGER NOT NULL DEFAULT 0,
    notes TEXT NOT NULL DEFAULT '',
    created_at TEXT NOT NULL
);

CREATE TABLE skill_mastery (
    profile_id INTEGER NOT NULL,
    skill_name TEXT NOT NULL,
    mastery_percent INTEGER NOT NULL DEFAULT 0,
    evidence TEXT NOT NULL DEFAULT '',
    updated_at TEXT NOT NULL,
    PRIMARY KEY(profile_id, skill_name)
);

CREATE TABLE code_attempts (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    profile_id INTEGER NOT NULL,
    language TEXT NOT NULL,
    exercise_id TEXT NOT NULL,
    result TEXT NOT NULL,
    created_at TEXT NOT NULL
);


-- v16 code attempt tracking and review history.
CREATE TABLE IF NOT EXISTS code_attempt_reviews (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    profile_id INTEGER NOT NULL,
    language TEXT NOT NULL,
    topic TEXT NOT NULL,
    exercise_id TEXT NOT NULL,
    difficulty TEXT NOT NULL,
    command_text TEXT NOT NULL,
    output_summary TEXT NOT NULL,
    review_status TEXT NOT NULL,
    review_notes TEXT NOT NULL,
    created_at TEXT NOT NULL,
    FOREIGN KEY(profile_id) REFERENCES learner_profiles(id) ON DELETE CASCADE
);

-- v17 AI provider settings and tutor review history.
CREATE TABLE IF NOT EXISTS ai_provider_settings (
    profile_id INTEGER NOT NULL,
    provider_name TEXT NOT NULL,
    endpoint TEXT NOT NULL DEFAULT '',
    model_name TEXT NOT NULL DEFAULT '',
    api_key_env TEXT NOT NULL DEFAULT '',
    enabled INTEGER NOT NULL DEFAULT 0,
    safety_notes TEXT NOT NULL DEFAULT '',
    updated_at TEXT NOT NULL,
    PRIMARY KEY(profile_id, provider_name)
);

CREATE TABLE IF NOT EXISTS ai_tutor_reviews (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    profile_id INTEGER NOT NULL,
    provider_name TEXT NOT NULL,
    mode TEXT NOT NULL,
    language TEXT NOT NULL,
    topic TEXT NOT NULL,
    prompt_preview TEXT NOT NULL,
    response_summary TEXT NOT NULL,
    status TEXT NOT NULL,
    created_at TEXT NOT NULL
);
