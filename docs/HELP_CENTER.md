# Help Center

## The Vulkan warning

If you see:

```txt
Could NOT find WrapVulkanHeaders (missing: Vulkan_INCLUDE_DIR)
```

that is usually a Qt optional dependency warning. For this Qt Widgets app, it is normally not the real build failure. Continue until you find the first actual compiler or linker error.

## The app does not start after building

Check that Qt DLLs were deployed. The build scripts try to run `windeployqt`. If DLLs are missing, run:

```bat
windeployqt build\CSBootcampDesktop.exe
```

## SQLite plugin missing

v11+ uses Qt SQL. If the app reports a SQLite driver issue, make sure the `sqldrivers` folder was copied beside the executable by `windeployqt`.

## Exercise Runner cannot run a language

The Exercise Runner launches local tools. Install the toolchain for the selected language, then reopen the app. For example:

- C++: MinGW or MSVC
- Python: Python 3
- JavaScript/TypeScript: Node.js
- Java/Kotlin: JDK
- C#: .NET SDK
- Go: Go toolchain
- Rust: Rustup/Cargo
- SQL: SQLite CLI

## Packaging a release

Use:

```bat
scripts\package_release.bat
```

The script builds the app, runs `windeployqt` when available, copies docs/templates, and creates a release folder.
