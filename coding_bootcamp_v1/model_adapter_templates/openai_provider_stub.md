# OpenAI Provider Stub Plan

This file is intentionally a plan, not a hard-coded API integration.

## Settings

```txt
provider_name: OpenAI
endpoint: https://api.openai.com/v1/responses
model_name: company-approved-openai-model
api_key_env: OPENAI_API_KEY
enabled: false by default
```

## Implementation notes

- Read the API key from `qEnvironmentVariable("OPENAI_API_KEY")`.
- Use Qt Network in a later version if a live call is added.
- Keep prompts visible to the learner before sending.
- Store response summaries in SQLite.
- Do not store API keys in the database.
