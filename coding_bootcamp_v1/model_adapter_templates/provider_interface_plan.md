# Provider Interface Plan

## Goal

Create a provider abstraction so the AI Tutor can use offline logic, OpenAI, Ollama, or a private company gateway without rewriting the UI.

## Proposed files for a later version

```txt
include/ai/TutorProvider.h
include/ai/TutorRequest.h
include/ai/TutorResponse.h
src/ai/OfflineTutorProvider.cpp
src/ai/OpenAiTutorProvider.cpp
src/ai/OllamaTutorProvider.cpp
src/ai/ProviderRegistry.cpp
```

## Provider rules

- Provider code should never own UI widgets.
- UI builds a TutorRequest.
- Provider returns a TutorResponse.
- Secrets are read from environment variables.
- Prompt preview is shown before hosted-model calls.
- OfflineTutorProvider must always remain available.
