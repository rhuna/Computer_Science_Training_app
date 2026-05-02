# CS Bootcamp Desktop v17 - Local and Hosted Model Adapter

v17 adds a professional adapter layer around the existing offline AI Tutor workflow.

## What this version adds

- Model Adapter Lab page
- Provider settings stored in SQLite
- Offline Tutor as the safe default
- OpenAI provider scaffolding
- Ollama/local-model provider scaffolding
- Private company model scaffolding
- Custom HTTP adapter slot
- Prompt preview before any hosted-provider workflow
- AI tutor review summaries saved to SQLite
- Exportable model adapter report

## Safety rules

1. Do not hard-code API keys.
2. Store the environment variable name only, such as `OPENAI_API_KEY`.
3. Preview the prompt before sending anything to a hosted model.
4. Do not paste credentials, private resident/patient information, or protected company code.
5. Save summaries by default instead of full external responses.
6. Keep Offline Tutor usable without internet.

## Professional architecture direction

The finished adapter should have a small interface like this:

```cpp
class TutorProvider
{
public:
    virtual ~TutorProvider() = default;
    virtual QString providerName() const = 0;
    virtual QString generateTutorResponse(const TutorRequest& request) = 0;
};
```

The app can then ship providers such as:

- OfflineTutorProvider
- OpenAiTutorProvider
- OllamaTutorProvider
- CompanyGatewayTutorProvider

v17 does not force network calls yet. It creates the UI, database history, settings flow, and template architecture needed to add them cleanly later.
