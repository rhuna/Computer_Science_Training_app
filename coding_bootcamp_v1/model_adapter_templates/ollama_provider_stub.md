# Ollama Provider Stub Plan

## Settings

```txt
provider_name: Ollama Local
endpoint: http://localhost:11434/api/generate
model_name: llama3.1
api_key_env: none
enabled: false by default
```

## Implementation notes

- Local models are useful for offline study.
- Still preview prompts before sending.
- Add timeout controls before calling a local model.
- Keep Offline Tutor as the fallback when Ollama is not running.
