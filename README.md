# CS Bootcamp Desktop v7

A professional-style C++/Qt desktop application for learning computer science like a serious bootcamp. The app itself is written in C++, but the curriculum is not limited to C++: it includes major industry language tracks, career paths, an exercise runner, an algorithm visualizer, and now a multi-language project generator.

v7 builds on v6 and adds the **Multi-Language Project Generator**.

## What v7 Adds

- New **Project Generator** page in the desktop app.
- Generates starter repos for C++, Python, JavaScript, TypeScript, Java, C#, Go, Rust, SQL, and Kotlin.
- Each generated project includes a README, source folder, test/validation command, learning-goals doc, and Windows run/test scripts.
- Supports project types such as CLI Fundamentals Lab, API/Backend Starter, Data Structures Practice Pack, Testing and Debugging Lab, and Portfolio Capstone Starter.
- Keeps the v6 Algorithm Visualizer, v5 deep curriculum, v4 Exercise Runner, Language Workspace, progress tracker, notes system, and multi-language tracks intact.

## Major Curriculum Areas

1. Computer Science Foundations
2. Programming Core Across Languages
3. Data Structures and Algorithms
4. Systems, OS, Networking, and Databases
5. Software Engineering and Architecture
6. Specializations: Web, Mobile, AI, Games, Security, Cloud
7. Web Engineering: Frontend, Backend, APIs, and Auth
8. Data, AI, Automation, and RAG Engineering
9. Secure Coding, Reliability, and Defensive Engineering
10. Cloud, DevOps, CI/CD, Containers, and Deployment
11. Capstone, Portfolio, Interview, and Career Readiness

## Language Tracks

- C++
- Python
- JavaScript
- TypeScript
- Java
- C#
- Go
- Rust
- SQL
- Kotlin

## Build on Windows

The default scripts assume this Qt layout:

```bat
C:\Qt\6.11.0\mingw_64
C:\Qt\Tools\mingw1310_64\bin
```

Run:

```bat
rebuild_clean.bat
```

If your Qt path is different, update `QT_PREFIX` and `MINGW_BIN` inside the `.bat` files.

## Vulkan Warning

If you see this during configure:

```txt
Could NOT find WrapVulkanHeaders (missing: Vulkan_INCLUDE_DIR)
```

that is usually only an optional Qt warning for this Widgets app. Continue to the first real compiler or linker error if the build stops.

## Project Generator Notes

The Project Generator writes files into `generated_projects` beside the executable by default. You can choose another output folder.

Generated projects are intentionally small but professional: they give you a clean place to practice, run, test, document, and eventually push to GitHub.

## Main Version Roadmap

- v7: Multi-language project generator
- v8: Portfolio builder
- v9: Git/testing/CI/deployment lab
- v10: Career readiness center
- v11: SQLite progress database
- v12: Instructor mode
- v13: Optional AI tutor mode
- v14: Final release polish
