# CS Bootcamp Desktop v13 - Optional AI Tutor Mode

v13 adds an offline-first AI Tutor Mode to the CS Bootcamp Desktop app.

The goal is not to make the bootcamp dependent on an AI provider. The goal is to create a professional tutoring workflow that works today without internet access and can later connect to OpenAI, Ollama, a local model, or a private company model through a small adapter layer.

## What the page does now

The new **AI Tutor Mode** page can generate structured coaching responses for:

- Explaining a CS concept
- Giving hints without giving away the full answer
- Debugging compiler, linker, runtime, or logic errors
- Reviewing a code/project submission
- Generating quiz prompts
- Creating a 7-day study plan
- Preparing for interviews

It also generates AI-ready prompt templates that can be copied into a model or wired into a future API adapter.

## Why it is optional

The app should remain usable as a normal C++/Qt desktop app even if the learner has no API key, no internet, and no local model installed. That is why v13 ships with an offline tutor response generator first.

## Future adapter plan

A later version can add an interface like this:

```cpp
class TutorProvider
{
public:
    virtual ~TutorProvider() = default;
    virtual QString name() const = 0;
    virtual QString generateTutorResponse(const TutorRequest& request) = 0;
};
```

Then the app can provide implementations such as:

- `OfflineTutorProvider`
- `OpenAITutorProvider`
- `OllamaTutorProvider`
- `PrivateCompanyTutorProvider`

## Professional learning workflow

The expected workflow is:

1. Try the lesson or exercise yourself first.
2. Ask the tutor for a hint, not the final answer.
3. Build a tiny working example.
4. Run tests or manual checks.
5. Record what you learned in Notes or the Progress Database.
6. Turn the result into portfolio evidence.

## Export behavior

The tutor can export a session to:

```txt
ai_tutor_exports/v13_ai_tutor_session.md
```
