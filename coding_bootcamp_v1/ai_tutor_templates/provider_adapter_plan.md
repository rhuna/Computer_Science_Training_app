# Future Tutor Provider Adapter Plan

v13 intentionally avoids requiring an online model.

Future versions can add provider implementations behind one interface:

- Offline provider: current deterministic coaching templates.
- OpenAI provider: hosted model for rich explanations and code review.
- Ollama provider: local model for private/offline tutoring.
- Enterprise provider: company-approved internal model.

The UI should not care which provider is active. It should send a TutorRequest and receive TutorResponse markdown.
