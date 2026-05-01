#include "BootcampContent.h"

namespace
{
    Lesson lesson(const QString& id, const QString& title, const QString& objective, const QString& explanation, QVector<QString> checklist, QVector<QString> practice)
    {
        return Lesson{id, title, objective, explanation, checklist, practice};
    }

    Exercise exercise(const QString& id, const QString& title, const QString& difficulty, const QString& prompt, const QString& starterCode, const QString& concepts)
    {
        return Exercise{id, title, difficulty, prompt, starterCode, concepts};
    }

    QuizQuestion quiz(const QString& id, const QString& question, QVector<QString> choices, int correctIndex, const QString& explanation)
    {
        return QuizQuestion{id, question, choices, correctIndex, explanation};
    }

    PortfolioProject project(const QString& id, const QString& title, const QString& level, const QString& description, QVector<QString> requirements, QVector<QString> stretchGoals)
    {
        return PortfolioProject{id, title, level, description, requirements, stretchGoals};
    }
}

QVector<Module> BootcampContent::createDefaultModules()
{
    QVector<Module> modules;

    modules.push_back(Module{
        "m01_cs_foundations",
        "01 - Computer Science Foundations",
        "Beginner to Bootcamp Ready",
        "The universal base: how computers represent data, execute instructions, store information, and run programs regardless of language.",
        {
            lesson("l_found_binary", "Binary, Bits, Bytes, and Data Representation", "Understand how numbers, text, images, and files become bytes.", "Computer science starts with representation. Binary is not just trivia; it explains overflow, encoding, file formats, compression, and why memory has limits. You will learn bits, bytes, signed and unsigned integers, floating point tradeoffs, Unicode, and the idea that every file is structured data.", {"Explain bit vs byte", "Convert simple binary values", "Describe integer overflow", "Explain ASCII and Unicode", "Describe why floating point can be imprecise"}, {"Convert 13 to binary", "Write notes explaining why 0.1 + 0.2 can be strange", "Inspect a text file as bytes"}),
            lesson("l_found_hardware", "CPU, RAM, Storage, and the OS", "Learn what actually happens when a program runs.", "A running program is loaded from storage into memory, scheduled by the operating system, and executed by the CPU. The OS protects memory, manages files, handles devices, and provides APIs that programs call.", {"Explain CPU role", "Explain RAM vs storage", "Explain process", "Explain system call", "Explain file path"}, {"Draw the path from source code to running process", "List programs currently running on your machine", "Find where an app stores data"}),
            lesson("l_found_builds", "Source Code, Compilation, Interpreters, and Runtimes", "Understand compiled, interpreted, JIT, and VM-based languages.", "C++ compiles to native code. Java compiles to bytecode that runs on the JVM. JavaScript usually runs in an engine such as V8. Python is interpreted through a runtime. Professional developers understand these differences because setup, debugging, packaging, and performance depend on them.", {"Define compiler", "Define interpreter", "Define runtime", "Explain bytecode", "Explain native executable"}, {"Compare C++, Python, Java, JavaScript", "Write a hello world in two languages", "Identify what runtime each language needs"})
        },
        {
            exercise("ex_base_converter", "Number Base Converter", "Beginner", "Create a function or small app that converts decimal numbers to binary and hexadecimal.", "// Write this in any language track you are studying.\n// Input: 42\n// Output: binary 101010, hex 2A\n", "Numbers, strings, loops, division, remainders"),
            exercise("ex_file_bytes", "File Byte Inspector", "Beginner", "Open a small text file and print the numeric byte values for each character.", "// C++ hint: use std::ifstream in binary mode.\n// Python hint: open(path, 'rb').\n", "Files, bytes, encoding")
        },
        {
            quiz("q_binary", "How many bits are in one byte?", {"4", "8", "16", "32"}, 1, "A byte is eight bits."),
            quiz("q_runtime", "Which language usually runs on the JVM?", {"C++", "Java", "SQL", "HTML"}, 1, "Java commonly compiles to bytecode that executes on the Java Virtual Machine.")
        },
        {
            project("p_found_cli_toolkit", "CS Foundations CLI Toolkit", "Starter Portfolio", "Build a small command-line toolkit with base conversion, file byte inspection, and text encoding notes.", {"Menu-driven interface", "At least three utilities", "Clear README", "Examples of input and output"}, {"Add GUI", "Add unit tests", "Add binary file header detection"})
        }
    });

    modules.push_back(Module{
        "m02_programming_core",
        "02 - Programming Core Across Languages",
        "Beginner to Junior",
        "Variables, control flow, functions, collections, error handling, debugging, and clean program structure in multiple languages.",
        {
            lesson("l_core_variables", "Variables, Types, and Control Flow", "Become comfortable with the core building blocks used in every major language.", "Every language has ways to name values, choose branches, repeat work, and group logic. Syntax changes, but the ideas remain stable: variables, types, if statements, loops, functions, and scopes.", {"Use variables", "Use if/else", "Use loops", "Write functions", "Explain scope"}, {"Solve fizz buzz in C++", "Solve fizz buzz in Python", "Write the same function in JavaScript"}),
            lesson("l_core_collections", "Arrays, Lists, Maps, and Sets", "Learn the everyday containers behind real apps.", "Most applications are data transformation machines. Lists store ordered items, maps associate keys with values, and sets prevent duplicates. These appear in C++, Python, Java, C#, JavaScript, Go, and Rust with different names but similar roles.", {"Choose list vs map", "Choose set for uniqueness", "Loop over collection", "Handle empty collection"}, {"Build a word frequency counter", "Build a to-do list", "Build a duplicate finder"}),
            lesson("l_core_errors", "Debugging and Error Handling", "Learn to diagnose problems instead of guessing.", "Professional programmers reproduce bugs, isolate the failing path, inspect state, explain the root cause, fix it, and verify the fix. Languages differ in exceptions, return values, panic systems, and result types, but the debugging mindset is universal.", {"Read stack traces", "Use breakpoints", "Add logging", "Handle invalid input", "Write reproducible steps"}, {"Fix an off-by-one error", "Handle bad file paths", "Write a bug report for your own code"})
        },
        {
            exercise("ex_word_frequency", "Word Frequency Counter", "Beginner", "Count how many times each word appears in a paragraph.", "// Use a map/dictionary/hash table.\n// Normalize case.\n// Print words sorted by count.\n", "Strings, maps, loops, sorting"),
            exercise("ex_input_validator", "Input Validator", "Beginner", "Ask for age, email, and username, then validate input with helpful error messages.", "// Keep asking until input is valid.\n", "Loops, conditionals, functions, error handling")
        },
        {
            quiz("q_map", "What collection is best for key/value lookup?", {"Array/list", "Map/dictionary", "Queue only", "String only"}, 1, "A map or dictionary is designed to associate keys with values."),
            quiz("q_debug", "What is the first step in disciplined debugging?", {"Rewrite everything", "Reproduce the problem", "Delete tests", "Change random lines"}, 1, "A bug you cannot reproduce is hard to isolate and verify." )
        },
        {
            project("p_multi_language_basics", "Same App, Three Languages", "Language Fluency", "Build the same small to-do list or habit tracker in C++, Python, and JavaScript so you can compare syntax and idioms.", {"One shared feature list", "Three implementations", "README comparing the languages", "Screenshots or sample output"}, {"Add Java or C# version", "Add tests", "Add persistence"})
        }
    });

    modules.push_back(Module{
        "m03_data_structures_algorithms",
        "03 - Data Structures and Algorithms",
        "Junior to Interview Ready",
        "Arrays, linked lists, stacks, queues, hash tables, trees, graphs, recursion, sorting, searching, Big-O, and problem-solving patterns.",
        {
            lesson("l_dsa_big_o", "Big-O and Performance Thinking", "Estimate how algorithms scale.", "Big-O helps you compare growth rates. It does not tell exact runtime, but it warns you when a design will collapse as input grows. You will practice O(1), O(log n), O(n), O(n log n), O(n^2), and exponential complexity.", {"Recognize loops", "Recognize nested loops", "Explain binary search", "Explain hash lookup", "Explain recursion cost"}, {"Classify 10 snippets", "Replace nested lookup with a map", "Measure simple runtimes"}),
            lesson("l_dsa_linear", "Stacks, Queues, Linked Lists, and Dynamic Arrays", "Understand core linear structures.", "Arrays give indexed access. Linked lists make insertion patterns explicit. Stacks support last-in-first-out behavior. Queues support first-in-first-out behavior. These ideas show up everywhere from browser history to job queues.", {"Implement stack", "Implement queue", "Use dynamic array", "Explain linked list tradeoffs"}, {"Build undo history", "Build print queue", "Reverse a linked list"}),
            lesson("l_dsa_trees_graphs", "Trees, Graphs, BFS, DFS, and Shortest Paths", "Model hierarchical and networked data.", "Trees model parent-child relationships. Graphs model connected systems. BFS is useful for shortest paths in unweighted graphs; DFS is useful for traversal, backtracking, and cycle detection.", {"Represent adjacency list", "Implement BFS", "Implement DFS", "Use visited set", "Explain tree traversal"}, {"Solve maze BFS", "Build file tree viewer", "Detect graph cycle"})
        },
        {
            exercise("ex_two_sum_multi", "Two Sum in Multiple Languages", "Interview Foundation", "Solve Two Sum in C++, Python, JavaScript, Java, and C#.", "// Pattern: store previously seen values in a hash map.\n", "Hash maps, complements, single-pass algorithms"),
            exercise("ex_lru_cache", "LRU Cache", "Advanced Interview", "Implement an LRU cache using a hash map plus linked list concept.", "// Focus on O(1) get and put operations.\n", "Hash maps, linked list, performance design")
        },
        {
            quiz("q_bigo_sort", "What is the typical average complexity of merge sort?", {"O(1)", "O(n)", "O(n log n)", "O(n^2)"}, 2, "Merge sort usually runs in O(n log n)."),
            quiz("q_bfs_structure", "Which data structure is commonly used for BFS?", {"Queue", "Stack", "Set only", "Compiler"}, 0, "BFS explores level by level, which naturally uses a queue.")
        },
        {
            project("p_algorithm_lab", "Algorithm Lab Desktop Visualizer", "Portfolio", "Build a visualizer for sorting, searching, BFS, DFS, and pathfinding.", {"At least four algorithms", "Step-through mode", "Speed slider", "Metrics display"}, {"Add A*", "Add custom maps", "Export comparison charts"})
        }
    });

    modules.push_back(Module{
        "m04_systems_os_networking",
        "04 - Systems, OS, Networking, and Databases",
        "Junior to Professional",
        "Processes, threads, memory, files, sockets, HTTP, APIs, SQL, indexing, transactions, and production data flow.",
        {
            lesson("l_systems_process", "Processes, Threads, Concurrency, and Memory", "Learn how real programs run and share work.", "Concurrency allows programs to do multiple things, but shared state can create race conditions. Professional code protects shared data, avoids deadlocks, and keeps ownership clear.", {"Explain process", "Explain thread", "Use mutex", "Identify race condition", "Explain deadlock"}, {"Build thread-safe counter", "Write producer-consumer queue", "Explain a race in plain English"}),
            lesson("l_network_http", "Networking, HTTP, APIs, and JSON", "Understand how apps communicate.", "Modern software is networked. Clients send requests, servers respond, APIs define contracts, JSON carries structured data, and HTTP status codes describe outcomes.", {"Explain client/server", "Explain TCP", "Explain HTTP verbs", "Read JSON", "Handle status codes"}, {"Call a public API", "Design REST endpoints", "Write API error responses"}),
            lesson("l_database_sql", "Databases, SQL, Indexes, and Transactions", "Learn how persistent application data is modeled and queried.", "SQL databases store relational data. Indexes speed lookup but cost writes and storage. Transactions protect consistency. Backend and desktop developers both need data modeling skills.", {"Write SELECT", "Write INSERT", "Explain primary key", "Explain foreign key", "Explain transaction"}, {"Design task app schema", "Query by date", "Add index to search column"})
        },
        {
            exercise("ex_http_client", "HTTP Client Drill", "Intermediate", "Fetch JSON from an API and display selected fields.", "// C++ option: use Qt Network later.\n// JavaScript option: fetch().\n// Python option: requests.\n", "HTTP, JSON, error handling"),
            exercise("ex_sql_schema", "Design a Learning Tracker Database", "Intermediate", "Design tables for users, lessons, exercises, quiz attempts, and notes.", "-- Write CREATE TABLE statements here.\n", "SQL schema design, keys, relationships")
        },
        {
            quiz("q_transaction", "What is a database transaction used for?", {"Changing font size", "Grouping operations so they succeed or fail together", "Compiling code", "Running GPU shaders"}, 1, "Transactions protect consistency when multiple database operations belong together."),
            quiz("q_http_404", "What does HTTP 404 usually mean?", {"OK", "Created", "Not found", "Server is on fire"}, 2, "404 indicates the requested resource was not found.")
        },
        {
            project("p_fullstack_tracker", "Full-Stack Learning Tracker", "Professional Portfolio", "Build a backend API plus frontend that tracks lessons, notes, quiz results, and project progress.", {"Database schema", "REST API", "Frontend UI", "Authentication plan", "README"}, {"Add Docker", "Add CI", "Add deployment guide"})
        }
    });

    modules.push_back(Module{
        "m05_software_engineering",
        "05 - Software Engineering and Architecture",
        "Professional Readiness",
        "Git, testing, clean architecture, design patterns, documentation, CI/CD, observability, security basics, and production delivery.",
        {
            lesson("l_eng_git", "Git, Branching, Code Review, and Releases", "Work like a professional developer.", "Professional teams use source control to collaborate safely. Small commits, meaningful branches, reviews, tags, changelogs, and release notes make software maintainable.", {"Create branch", "Write commit message", "Open PR mentally", "Tag version", "Write changelog"}, {"Make 5 focused commits", "Write release notes", "Resolve a fake merge conflict"}),
            lesson("l_eng_testing", "Testing Strategy", "Protect behavior as the project grows.", "Unit tests check small logic. Integration tests check components together. End-to-end tests verify user flows. Regression tests make old bugs stay fixed.", {"Write unit test", "Write integration test idea", "Use test data", "Explain regression", "Measure coverage carefully"}, {"Write tests for a calculator", "Add edge-case tests", "Create bug reproduction test"}),
            lesson("l_eng_architecture", "Architecture, Design Patterns, and Maintainability", "Design code that survives growth.", "Architecture is about boundaries, dependencies, and change. Good systems separate UI, business logic, persistence, and infrastructure so each can evolve safely.", {"Separate concerns", "Use interfaces", "Recognize MVC/MVVM", "Avoid god objects", "Document decisions"}, {"Refactor a large function", "Draw module dependency diagram", "Write an ADR"})
        },
        {
            exercise("ex_ci_pipeline", "CI Pipeline Plan", "Professional", "Write a CI checklist that builds, tests, packages, and archives artifacts.", "# Example stages:\n# configure\n# build\n# test\n# package\n", "Automation, release engineering"),
            exercise("ex_arch_refactor", "Refactor a God Class", "Professional", "Split a single oversized class into UI, service, model, and persistence layers.", "// Identify responsibilities first, then extract classes.\n", "Architecture, refactoring, maintainability")
        },
        {
            quiz("q_unit_test", "What is a regression test?", {"A test that proves a bug stays fixed", "A design pattern", "A compiler flag", "A database table"}, 0, "A regression test protects against the return of a previously fixed bug."),
            quiz("q_arch", "Why separate UI from business logic?", {"To make code longer", "To make behavior easier to test and reuse", "To avoid compiling", "To remove all classes"}, 1, "Separation makes the core logic less dependent on widgets and easier to test." )
        },
        {
            project("p_professional_capstone", "Professional Capstone System", "Job Ready", "Build a polished app in your chosen track with clean architecture, tests, docs, and release packaging.", {"Architecture doc", "Tests", "Persistent data", "Professional README", "Release script", "Screenshots"}, {"Installer", "Crash-safe saves", "GitHub Actions", "Telemetry/logging"})
        }
    });

    modules.push_back(Module{
        "m06_specializations",
        "06 - Specializations: Web, Mobile, AI, Games, Security, Cloud",
        "Career Direction",
        "Choose a specialization path after foundations: full-stack, backend, systems, data/AI, mobile, game development, cybersecurity, DevOps, or desktop software.",
        {
            lesson("l_spec_web", "Full-Stack Web", "Understand frontend, backend, APIs, databases, auth, hosting, and deployment.", "Full-stack developers connect UI, server logic, data storage, and deployment. The common professional stack includes TypeScript, React, Node.js, SQL, APIs, testing, and cloud hosting.", {"Build frontend", "Build API", "Use database", "Handle auth", "Deploy app"}, {"Clone a simple SaaS dashboard", "Build CRUD API", "Deploy static frontend"}),
            lesson("l_spec_ai", "Data, AI, and Automation", "Learn Python-driven data processing, model usage, and LLM app patterns.", "AI engineering combines programming, data handling, APIs, evaluation, and product design. You should learn Python, SQL, vector search concepts, prompt/eval workflows, and deployment basics.", {"Use Python", "Use pandas conceptually", "Call model API", "Evaluate output", "Store embeddings conceptually"}, {"Build document Q&A", "Build CSV analyzer", "Build eval checklist"}),
            lesson("l_spec_games", "Game and Simulation Development", "Learn loops, rendering, input, assets, physics, ECS, and tooling.", "Game development teaches architecture under pressure: real-time loops, input, simulation, rendering, content pipelines, and editor tools. C++, C#, and scripting languages are common.", {"Explain game loop", "Explain ECS", "Load assets", "Handle input", "Separate editor/runtime"}, {"Build top-down prototype", "Build level editor", "Build save system"})
        },
        {
            exercise("ex_choose_track", "Choose a 90-Day Professional Track", "Planning", "Pick one specialization and define weekly deliverables for 90 days.", "// Track:\n// Languages:\n// Weekly deliverables:\n// Capstone:\n", "Goal setting, roadmapping, portfolio planning"),
            exercise("ex_capstone_pitch", "Capstone Pitch Document", "Professional", "Write a one-page pitch for a portfolio project that solves a real problem.", "// Problem\n// Users\n// Features\n// Tech stack\n// Milestones\n", "Product thinking, planning, communication")
        },
        {
            quiz("q_specialization", "When should you specialize?", {"Before learning variables", "After enough foundations to build small complete projects", "Never", "Only after ten years"}, 1, "Foundations make specialization easier because every stack still uses data, logic, debugging, and architecture."),
            quiz("q_cloud", "What does deployment mean?", {"Making software available to users", "Only writing comments", "Changing a variable", "Deleting source code"}, 0, "Deployment means packaging and running software where users or systems can access it." )
        },
        {
            project("p_track_capstone", "Specialization Capstone", "Career Portfolio", "Build one serious project in your chosen specialization and polish it enough to show an employer or client.", {"Clear problem", "Working app", "Professional docs", "Screenshots/video", "Build/run instructions"}, {"Public demo", "Automated tests", "Monitoring/logging", "User feedback loop"})
        }
    });

    modules.push_back(Module{
        "m07_web_engineering",
        "07 - Web Engineering: Frontend, Backend, APIs, and Auth",
        "Junior to Professional",
        "HTML/CSS concepts, JavaScript/TypeScript, frontend state, backend APIs, authentication, authorization, validation, and deployment-ready web architecture.",
        {
            lesson("l_web_frontend", "Frontend Architecture and UI State", "Understand how professional web frontends are organized.", "A frontend is more than screens. It has components, state, routes, forms, validation, API calls, loading states, error states, accessibility, and responsive layout. TypeScript is commonly used so teams can catch bugs earlier.", {"Explain component", "Explain state", "Handle form validation", "Handle loading state", "Consider accessibility"}, {"Build a profile form", "Add validation messages", "Write loading and error UI states"}),
            lesson("l_web_backend", "Backend APIs and Service Boundaries", "Design APIs that are predictable and maintainable.", "Backends expose operations through routes, controllers, services, repositories, and database models. Professional APIs validate input, return consistent errors, protect data, and separate business logic from transport details.", {"Design REST route", "Validate request body", "Return status code", "Separate controller/service", "Document endpoint"}, {"Design CRUD endpoints", "Write error response examples", "Sketch service boundaries"}),
            lesson("l_web_auth", "Authentication, Authorization, and Sessions", "Learn the difference between knowing who a user is and what they can do.", "Authentication proves identity. Authorization checks permissions. Web apps use sessions, tokens, password hashing, roles, CSRF protection, and careful error handling to protect accounts and data.", {"Explain authn vs authz", "Explain password hashing", "Explain role", "Explain session", "Avoid leaking sensitive errors"}, {"Design a login flow", "List protected routes", "Write role checks for an admin page"})
        },
        {
            exercise("ex_rest_design", "Design a REST API", "Intermediate", "Design endpoints for a learning tracker with lessons, exercises, quiz attempts, and notes.", "// Example: GET /api/lessons, POST /api/quiz-attempts\n", "REST, status codes, resource modeling"),
            exercise("ex_frontend_states", "Frontend State Checklist", "Intermediate", "Create a UI plan that handles empty, loading, success, error, and unauthorized states.", "// Screen:\n// Empty:\n// Loading:\n// Error:\n", "UX states, reliability, accessibility")
        },
        {
            quiz("q_auth_difference", "What is authorization?", {"Checking what an authenticated user can access", "Compiling TypeScript", "Creating a database index", "Styling a button"}, 0, "Authorization determines permissions after identity is known."),
            quiz("q_api_validation", "Where should input validation happen?", {"Only in the UI", "Only in the database", "At least on the server, and often also in the UI", "Never"}, 2, "Server-side validation protects the system even when clients are buggy or malicious.")
        },
        {
            project("p_web_saas", "Mini SaaS Dashboard", "Portfolio", "Build a small web dashboard with login flow, CRUD data, API routes, validation, and a deployment checklist.", {"Frontend screens", "Backend API", "Database schema", "Auth plan", "Tests", "README"}, {"Role-based permissions", "Docker", "CI/CD", "Production logging"})
        }
    });

    modules.push_back(Module{
        "m08_data_ai_engineering",
        "08 - Data, AI, Automation, and RAG Engineering",
        "Professional Specialization",
        "Python automation, data cleaning, APIs, evaluation, vector-search concepts, RAG workflows, and practical AI product engineering.",
        {
            lesson("l_data_pipeline", "Data Pipelines and Cleaning", "Turn messy input into dependable output.", "Data work starts with reading files, validating columns, handling missing values, transforming records, and writing repeatable outputs. The same principles power reports, analytics, ETL jobs, and AI preprocessing.", {"Read CSV", "Validate schema", "Clean nulls", "Transform records", "Export result"}, {"Clean a messy CSV", "Write data quality checks", "Create a summary report"}),
            lesson("l_ai_rag", "RAG and Document Q&A Concepts", "Understand the moving parts behind document chat systems.", "Retrieval-augmented generation combines parsing, chunking, indexing, search, context assembly, answer generation, and citations. Professional systems also need evaluations, failure handling, and observability.", {"Explain chunking", "Explain embedding concept", "Explain retrieval", "Explain citation", "Explain evaluation"}, {"Design a RAG pipeline", "Write five evaluation questions", "Create a failure-mode checklist"}),
            lesson("l_ai_eval", "AI Evaluation and Guardrails", "Learn how to measure whether an AI feature is useful and safe enough.", "AI features need tests just like normal software. You define expected behavior, collect representative examples, measure accuracy or usefulness, inspect failures, and add guardrails for privacy, hallucinations, and unsafe actions.", {"Define eval set", "Score answer quality", "Track failures", "Add guardrails", "Review privacy risk"}, {"Create an eval spreadsheet", "Write red-team prompts", "Define pass/fail rules"})
        },
        {
            exercise("ex_csv_reporter", "CSV Reporter", "Intermediate", "Write a script that reads a CSV, validates required columns, and outputs a summary report.", "# Python recommended for this drill.\n", "Files, validation, aggregation"),
            exercise("ex_rag_design_doc", "RAG Design Document", "Professional", "Write the architecture for a document Q&A app including ingestion, chunking, search, citations, and evaluations.", "# Sections: ingestion, indexing, retrieval, generation, evals, risks\n", "AI architecture, evaluation, product thinking")
        },
        {
            quiz("q_rag_retrieval", "In RAG, what does retrieval do?", {"Find relevant source material before answering", "Draw UI icons", "Compile C++", "Delete user data"}, 0, "Retrieval searches source material so the answer can be grounded."),
            quiz("q_ai_eval", "Why do AI features need evaluation sets?", {"To measure behavior across representative examples", "To make buttons blue", "To avoid writing any code", "To replace all testing"}, 0, "Evaluation sets let you compare changes and catch regressions.")
        },
        {
            project("p_doc_qa", "Document Q&A Assistant", "Advanced Portfolio", "Build a local or API-backed document Q&A prototype with citations, saved conversations, and an evaluation checklist.", {"Ingestion plan", "Search/retrieval layer", "Answer UI", "Citation display", "Eval examples"}, {"Queue workers", "Vector database", "Admin dashboard", "Cost tracking"})
        }
    });

    modules.push_back(Module{
        "m09_security_and_reliability",
        "09 - Secure Coding, Reliability, and Defensive Engineering",
        "Professional Readiness",
        "Threat modeling, input validation, secrets handling, logging, error handling, backups, secure defaults, and building software that fails safely.",
        {
            lesson("l_sec_threat_model", "Threat Modeling for Developers", "Think about what can go wrong before shipping.", "A threat model asks what you are protecting, who might attack it, where trust boundaries exist, and which controls reduce risk. It is practical design work, not paranoia.", {"Identify assets", "Identify users", "Identify trust boundary", "List abuse cases", "Choose mitigations"}, {"Threat model a login page", "Threat model file upload", "Threat model admin dashboard"}),
            lesson("l_sec_input", "Input Validation and Injection Prevention", "Treat external input as untrusted.", "Many vulnerabilities begin when programs trust input. Validate data, use parameterized queries, avoid shell injection, escape output in the correct context, and fail closed when uncertain.", {"Validate type", "Validate range", "Use parameterized query", "Avoid raw shell strings", "Return safe errors"}, {"Fix an unsafe SQL string", "Design validation for signup", "List dangerous file upload cases"}),
            lesson("l_rel_ops", "Logging, Monitoring, Backups, and Recovery", "Operate software after it leaves your machine.", "Professional software needs logs, health checks, metrics, backups, restore drills, and incident notes. Reliability is a design feature, not something added at the end.", {"Write useful log", "Define health check", "Plan backup", "Plan restore", "Write incident note"}, {"Design app logs", "Create backup checklist", "Write postmortem template"})
        },
        {
            exercise("ex_safe_login_review", "Secure Login Review", "Professional", "Review a login design and identify security issues, missing controls, and reliability risks.", "// Check: passwords, sessions, lockouts, logging, reset flow, rate limits\n", "Secure design, auth, reliability"),
            exercise("ex_incident_postmortem", "Incident Postmortem", "Professional", "Write a blameless postmortem for a fake outage where the database filled up.", "// Timeline, impact, root cause, fixes, prevention\n", "Operations, communication, reliability")
        },
        {
            quiz("q_parameterized", "What helps prevent SQL injection?", {"Parameterized queries", "Longer variable names", "Bigger monitor", "Deleting logs"}, 0, "Parameterized queries keep data separate from SQL commands."),
            quiz("q_backup", "A backup is only proven when what has happened?", {"It has been restored successfully", "It has a nice filename", "It is mentioned in a meeting", "It is stored beside the original only"}, 0, "Restore testing proves backups are actually usable.")
        },
        {
            project("p_secure_notes", "Secure Notes Prototype", "Portfolio", "Build a notes app design with authentication, validation, secure storage plan, backup plan, and audit logging.", {"Threat model", "Data model", "Validation rules", "Logging plan", "Backup/restore plan"}, {"Encryption design", "Role model", "Automated security checklist", "Rate limiting"})
        }
    });

    modules.push_back(Module{
        "m10_cloud_devops_delivery",
        "10 - Cloud, DevOps, CI/CD, Containers, and Deployment",
        "Professional Delivery",
        "Git workflows, build automation, Docker concepts, CI/CD pipelines, environments, deployment checklists, observability, and release discipline.",
        {
            lesson("l_devops_gitflow", "Professional Git Workflow", "Use branches and releases without chaos.", "A professional workflow uses small commits, branch names, pull requests, review notes, tags, changelogs, and rollback plans. Even solo developers benefit from this discipline.", {"Create feature branch", "Write small commit", "Write PR summary", "Tag release", "Plan rollback"}, {"Write a changelog", "Create release checklist", "Simulate code review comments"}),
            lesson("l_devops_docker", "Containers and Environment Consistency", "Understand why containers are used.", "Containers package an application with a predictable runtime environment. They help reduce 'works on my machine' problems and make local development closer to deployment.", {"Explain image", "Explain container", "Explain volume", "Explain port mapping", "Explain env var"}, {"Write a Dockerfile outline", "List env vars", "Draw service diagram"}),
            lesson("l_devops_ci", "CI/CD Pipelines", "Automate build, test, package, and release steps.", "CI catches mistakes automatically. CD moves release steps from memory into repeatable scripts. Good pipelines are boring, readable, and dependable.", {"Configure build step", "Configure test step", "Archive artifact", "Fail on error", "Document pipeline"}, {"Write pipeline pseudo-yaml", "Add smoke test step", "Define artifact name"})
        },
        {
            exercise("ex_release_checklist", "Release Checklist", "Professional", "Create a release checklist for this CS Bootcamp app.", "// Build, test, package, smoke test, changelog, rollback\n", "Release engineering"),
            exercise("ex_docker_plan", "Containerization Plan", "Intermediate", "Write a Docker plan for a web API plus database.", "// Services, ports, volumes, env vars, health checks\n", "Containers, environments, deployment")
        },
        {
            quiz("q_ci", "What should CI normally do?", {"Automatically build and test changes", "Only change wallpapers", "Hide errors", "Delete source code"}, 0, "CI should make build and test feedback automatic."),
            quiz("q_env_var", "What are environment variables often used for?", {"Configuration such as connection strings or feature flags", "Drawing pixels only", "Replacing source control", "Removing all settings"}, 0, "Environment variables commonly inject configuration without hard-coding it.")
        },
        {
            project("p_deployable_api", "Deployable API Service", "Portfolio", "Build an API with tests, Docker plan, CI checklist, environment config, and production README.", {"API", "Tests", "Dockerfile or plan", "CI checklist", "Deploy notes"}, {"Health endpoint", "Metrics", "Rollback plan", "Load test notes"})
        }
    });

    modules.push_back(Module{
        "m11_capstone_portfolio_career",
        "11 - Capstone, Portfolio, Interview, and Career Readiness",
        "Job Ready",
        "Portfolio positioning, project polish, interview practice, system design basics, resume bullets, project demos, and professional communication.",
        {
            lesson("l_career_portfolio", "Portfolio That Proves Skill", "Turn projects into evidence.", "A strong portfolio is not a pile of random repos. It explains the problem, users, architecture, tradeoffs, screenshots, setup, tests, and what you would improve next.", {"Problem statement", "Screenshots", "Architecture notes", "Build steps", "Testing notes"}, {"Improve one README", "Add screenshots list", "Write tradeoff section"}),
            lesson("l_interview_patterns", "Coding Interview Patterns", "Practice patterns instead of memorizing answers.", "Common interview problems reuse patterns: hash maps, two pointers, sliding windows, stacks, binary search, BFS, DFS, dynamic programming, and intervals. Learn to identify the pattern, state complexity, and explain tradeoffs.", {"Use hash map", "Use two pointers", "Use sliding window", "Use BFS/DFS", "State Big-O"}, {"Solve two-pointer drill", "Solve sliding-window drill", "Explain BFS aloud"}),
            lesson("l_system_design_intro", "System Design for Beginners", "Explain a system clearly at a junior-friendly level.", "System design starts with requirements, users, data, APIs, components, storage, reliability, and tradeoffs. You do not need to know everything; you need to reason clearly.", {"Gather requirements", "Estimate scale", "Draw components", "Choose storage", "Discuss tradeoffs"}, {"Design URL shortener", "Design study app", "Design notification service"})
        },
        {
            exercise("ex_resume_bullets", "Resume Bullet Generator", "Career", "Turn one project into five measurable resume bullets.", "// Built X using Y to accomplish Z.\n", "Career communication"),
            exercise("ex_system_design_prompt", "System Design Drill", "Interview", "Design a bootcamp progress tracking system with APIs, storage, and reliability concerns.", "// Requirements, data model, APIs, services, risks\n", "System design, architecture")
        },
        {
            quiz("q_portfolio", "What makes a portfolio project stronger?", {"Clear problem, working demo, docs, tests, and tradeoffs", "No README", "Only screenshots with no code", "Random folders"}, 0, "Employers need evidence that you can build, explain, and maintain software."),
            quiz("q_system_design", "What should you clarify first in system design?", {"Requirements", "Button color", "Variable names only", "Which laptop to buy"}, 0, "Requirements guide every technical decision.")
        },
        {
            project("p_final_capstone", "Final Professional Capstone", "Job Ready", "Build one complete, polished, documented project in your chosen track and prepare it for portfolio presentation.", {"Working app", "Tests", "Architecture doc", "README", "Screenshots", "Demo script", "Resume bullets"}, {"Hosted demo", "CI/CD", "Installer", "Analytics/monitoring", "User feedback"})
        }
    });

    return modules;
}

QVector<LanguageTrack> BootcampContent::createLanguageTracks()
{
    return {
        {
            "lang_cpp", "C++",
            "Systems, game engines, desktop apps, high-performance software, embedded, finance, tools",
            "C++ teaches memory, performance, builds, linking, and professional native application structure.",
            "Use Qt Creator or CMake + MinGW/MSVC on Windows.",
            {"g++ --version", "cmake --version", "where mingw32-make", "Verify Qt bin folder is on PATH when building Qt apps"},
            {"g++ main.cpp -std=c++17 -o app.exe", "cmake -S . -B build -G \"MinGW Makefiles\"", "cmake --build build", "ctest --test-dir build"},
            {"main.cpp", "CMakeLists.txt", "include/app/App.h", "src/App.cpp", "tests/basic_tests.cpp"},
            {"Day 1: console I/O and functions", "Day 2: vectors, maps, and files", "Day 3: classes and RAII", "Day 4: CMake multi-file project", "Day 5: tests and debugging", "Day 6: small Qt or CLI project", "Day 7: README and refactor"},
            {"Build pipeline", "Pointers/references", "RAII", "STL", "OOP", "Templates", "Concurrency", "CMake"},
            {"Console utilities", "Multi-file projects", "File persistence", "Basic data structures"},
            {"Qt desktop app", "Game engine module", "Networking tool", "Performance profiler"},
            {"Desktop bootcamp app", "Algorithm visualizer", "Local network chat", "2D game engine"}
        },
        {
            "lang_python", "Python",
            "Automation, scripting, data, AI, backend APIs, testing, DevOps glue",
            "Python gets you productive quickly and is essential for data, AI, automation, and backend tooling.",
            "Install Python, then use venv and pip.",
            {"python --version", "pip --version", "python -m venv .venv", ".venv\\Scripts\\python -m pip install pytest"},
            {"python main.py", "python -m pytest", "python -m pip freeze > requirements.txt", "python -m venv .venv"},
            {"main.py", "requirements.txt", "src/app.py", "tests/test_app.py", "README.md"},
            {"Day 1: variables, lists, dictionaries", "Day 2: functions and modules", "Day 3: files and CSV", "Day 4: requests/API basics", "Day 5: pytest", "Day 6: automation mini-project", "Day 7: package cleanup"},
            {"Variables", "Functions", "Lists/dicts", "Files", "Packages", "Virtual environments", "Testing", "APIs"},
            {"CLI scripts", "CSV automation", "File organizer", "API caller"},
            {"FastAPI backend", "Data analyzer", "LLM/RAG prototype", "Automation toolkit"},
            {"Document Q&A app", "Budget analyzer", "Study question generator", "Ops automation scripts"}
        },
        {
            "lang_javascript", "JavaScript",
            "Frontend web, backend Node.js, full-stack apps, browser automation",
            "JavaScript is the language of the web and lets you build interactive frontends and Node backends.",
            "Install Node.js, then use npm create vite@latest.",
            {"node --version", "npm --version", "npm init -y", "npm install --save-dev vitest"},
            {"node index.js", "npm run dev", "npm test", "npm run build"},
            {"index.html", "src/main.js", "src/app.js", "package.json", "tests/app.test.js"},
            {"Day 1: values, functions, arrays", "Day 2: DOM and events", "Day 3: async/await and fetch", "Day 4: modules and npm", "Day 5: Node CLI", "Day 6: small frontend app", "Day 7: tests and deploy notes"},
            {"DOM", "Events", "Async/await", "Modules", "Fetch", "Node", "npm", "Testing"},
            {"Interactive webpage", "To-do app", "Fetch API demo", "Node CLI"},
            {"React app", "Express API", "Full-stack dashboard", "Real-time chat"},
            {"Nurse study web app", "LTC dashboard prototype", "Portfolio website", "Full-stack tracker"}
        },
        {
            "lang_typescript", "TypeScript",
            "Professional frontend/backend JavaScript with safer types",
            "TypeScript is what many professional web teams use because it catches mistakes before runtime.",
            "Install Node.js; use TypeScript through Vite, Next.js, or ts-node.",
            {"node --version", "npm --version", "npx tsc --version", "npm create vite@latest"},
            {"npx tsc --noEmit", "npm run dev", "npm test", "npm run build"},
            {"src/main.ts", "src/types.ts", "src/api.ts", "tsconfig.json", "package.json"},
            {"Day 1: annotations and inference", "Day 2: interfaces and models", "Day 3: narrowing and unions", "Day 4: typed API calls", "Day 5: React props/state", "Day 6: full typed feature", "Day 7: strict mode cleanup"},
            {"Types", "Interfaces", "Generics", "Narrowing", "React props", "API contracts", "Build tooling"},
            {"Typed functions", "Typed API response", "Small React component", "Form validation"},
            {"Next.js app", "Typed Express API", "Shared client/server models", "Design system"},
            {"SaaS dashboard", "Admin portal", "Typed study platform", "Realtime project board"}
        },
        {
            "lang_java", "Java",
            "Enterprise backend, Android foundations, large corporate systems",
            "Java teaches strong OOP, packages, tooling, APIs, and large-scale backend structure.",
            "Install JDK and IntelliJ or use Maven/Gradle.",
            {"java --version", "javac --version", "mvn --version", "gradle --version"},
            {"javac Main.java", "java Main", "mvn test", "mvn spring-boot:run"},
            {"src/main/java/app/Main.java", "src/main/java/app/Service.java", "src/test/java/app/ServiceTest.java", "pom.xml"},
            {"Day 1: classes and methods", "Day 2: collections", "Day 3: exceptions", "Day 4: files and packages", "Day 5: JUnit", "Day 6: small service", "Day 7: layered cleanup"},
            {"Classes", "Interfaces", "Collections", "Streams", "Exceptions", "Maven/Gradle", "Spring basics"},
            {"Console app", "Collections drills", "File parser", "Unit tests"},
            {"Spring Boot API", "Database-backed service", "Authentication service", "Enterprise-style layered app"},
            {"Inventory API", "Learning tracker backend", "Scheduling service", "Healthcare operations API"}
        },
        {
            "lang_csharp", "C#",
            "Windows apps, enterprise backend, Unity games, .NET services",
            "C# is excellent for professional desktop, backend, and game development with strong tooling.",
            "Install Visual Studio or .NET SDK; use dotnet new.",
            {"dotnet --version", "dotnet new console -n Scratch", "dotnet test", "Verify Visual Studio workload if building desktop apps"},
            {"dotnet run", "dotnet test", "dotnet new webapi", "dotnet publish -c Release"},
            {"Program.cs", "AppService.cs", "AppModels.cs", "App.Tests/AppTests.cs", "README.md"},
            {"Day 1: classes and records", "Day 2: lists and LINQ", "Day 3: async/await", "Day 4: file persistence", "Day 5: unit tests", "Day 6: WPF/API mini-project", "Day 7: publish build"},
            {"Classes", "LINQ", "Async/await", ".NET", "WPF/WinUI", "ASP.NET", "Entity Framework"},
            {"Console tools", "LINQ drills", "File persistence", "Simple GUI"},
            {"ASP.NET API", "WPF desktop app", "Unity prototype", "Database app"},
            {"Operations dashboard", "Scheduling app", "Unity learning game", "REST API service"}
        },
        {
            "lang_go", "Go",
            "Cloud services, networking tools, DevOps, distributed systems",
            "Go is simple, fast to compile, and common in cloud infrastructure.",
            "Install Go; use go mod init and go test.",
            {"go version", "go env GOPATH", "go mod init example.com/app", "go test ./..."},
            {"go run .", "go test ./...", "go build ./...", "go fmt ./..."},
            {"main.go", "internal/app/service.go", "internal/app/service_test.go", "go.mod"},
            {"Day 1: packages and functions", "Day 2: structs and interfaces", "Day 3: errors", "Day 4: HTTP server", "Day 5: goroutines", "Day 6: CLI/service project", "Day 7: tests and formatting"},
            {"Packages", "Structs", "Interfaces", "Goroutines", "Channels", "HTTP servers", "Testing"},
            {"CLI tool", "HTTP server", "JSON parser", "Concurrent worker"},
            {"Microservice", "Log processor", "DevOps tool", "Concurrent crawler"},
            {"API gateway", "Monitoring agent", "Job queue", "Deployment helper"}
        },
        {
            "lang_rust", "Rust",
            "Systems, safe performance, CLI tools, WebAssembly, infrastructure",
            "Rust teaches memory safety without garbage collection and is valued for secure systems work.",
            "Install rustup; use cargo new and cargo test.",
            {"rustc --version", "cargo --version", "cargo new scratch", "cargo test"},
            {"cargo run", "cargo test", "cargo build --release", "cargo fmt"},
            {"src/main.rs", "src/lib.rs", "tests/integration_test.rs", "Cargo.toml"},
            {"Day 1: ownership basics", "Day 2: structs and enums", "Day 3: Result and errors", "Day 4: traits", "Day 5: file CLI", "Day 6: parser project", "Day 7: tests and docs"},
            {"Ownership", "Borrowing", "Lifetimes", "Enums", "Pattern matching", "Traits", "Cargo", "Error handling"},
            {"CLI utilities", "Text parser", "File scanner", "Unit tests"},
            {"High-performance CLI", "WASM component", "Network service", "Parser library"},
            {"Secure file tool", "Markdown parser", "Log analyzer", "Tiny database"}
        },
        {
            "lang_sql", "SQL",
            "Databases, analytics, backend engineering, reporting",
            "SQL is required for almost every serious data-backed application.",
            "Install SQLite or PostgreSQL; practice SELECT/INSERT/UPDATE/JOIN.",
            {"sqlite3 --version", "psql --version", "Create a practice database", "Run a SELECT query"},
            {"sqlite3 bootcamp.db < schema.sql", "sqlite3 bootcamp.db < seed.sql", "sqlite3 bootcamp.db \"SELECT * FROM students;\"", "Use EXPLAIN QUERY PLAN"},
            {"schema.sql", "seed.sql", "queries.sql", "migrations/001_init.sql", "README.md"},
            {"Day 1: tables and SELECT", "Day 2: WHERE and aggregates", "Day 3: joins", "Day 4: keys and constraints", "Day 5: indexes", "Day 6: reporting project", "Day 7: schema cleanup"},
            {"Tables", "Primary keys", "Foreign keys", "SELECT", "JOIN", "Indexes", "Transactions"},
            {"CRUD queries", "Simple reports", "Table design", "Aggregations"},
            {"Normalized schema", "Performance tuning", "Migrations", "Reporting dashboard"},
            {"Learning tracker database", "Budget reporting DB", "LTC ops schema", "Analytics workbook"}
        },
        {
            "lang_kotlin", "Kotlin",
            "Android apps, JVM backend, modern mobile development",
            "Kotlin is a modern professional language for Android and JVM services.",
            "Install Android Studio or IntelliJ with Kotlin.",
            {"kotlinc -version", "gradle --version", "Verify Android Studio SDK if building Android", "Create a Kotlin console project"},
            {"kotlinc Main.kt -include-runtime -d app.jar", "java -jar app.jar", "gradle test", "gradle build"},
            {"src/main/kotlin/Main.kt", "src/main/kotlin/AppService.kt", "src/test/kotlin/AppServiceTest.kt", "build.gradle.kts"},
            {"Day 1: null safety", "Day 2: data classes", "Day 3: collections", "Day 4: coroutines overview", "Day 5: tests", "Day 6: Android/console project", "Day 7: UI/state cleanup"},
            {"Null safety", "Data classes", "Collections", "Coroutines", "Android lifecycle", "Compose basics"},
            {"Console Kotlin", "Simple Android screen", "Form validation", "Local storage"},
            {"Android app", "Ktor API", "Offline-first mobile app", "Compose UI"},
            {"Study flashcard app", "Habit tracker mobile", "Nursing skills app", "Medication reminder prototype"}
        }
    };
}

QVector<CareerPath> BootcampContent::createCareerPaths()
{
    return {
        {"career_fullstack", "Full-Stack Software Engineer", "Build complete web applications from UI to database to deployment.", {"HTML/CSS", "TypeScript", "React", "Node or Java/C#", "SQL", "Testing", "Deployment"}, {"TypeScript", "JavaScript", "SQL", "Python"}, {"SaaS dashboard", "Learning management app", "Operations tracker"}},
        {"career_backend", "Backend/API Engineer", "Design reliable APIs, databases, services, authentication, and integration workflows.", {"HTTP", "REST", "SQL", "Auth", "Testing", "Caching", "Observability"}, {"Java", "C#", "Go", "Python", "SQL"}, {"REST API with database", "Job queue service", "Authentication service"}},
        {"career_systems", "Systems/Desktop Engineer", "Build native tools, desktop apps, engines, and performance-sensitive software.", {"C++", "Memory", "Concurrency", "Build systems", "Profiling", "OS APIs"}, {"C++", "Rust", "C#", "SQL"}, {"Qt desktop app", "File indexer", "Local network tool"}},
        {"career_ai", "AI/Data Engineer", "Build data pipelines, AI tools, RAG systems, evaluations, and automation workflows.", {"Python", "SQL", "APIs", "Data cleaning", "Vector search concepts", "Evaluation", "Deployment"}, {"Python", "SQL", "TypeScript"}, {"Document Q&A", "CSV insight app", "Study question generator"}},
        {"career_mobile", "Mobile Developer", "Build Android/iOS-style app experiences with offline data, APIs, and polished UX.", {"UI lifecycle", "State", "Local storage", "APIs", "Notifications", "Testing"}, {"Kotlin", "Swift", "TypeScript", "C#"}, {"Flashcard app", "Scheduling app", "Offline notes app"}},
        {"career_games", "Game/Simulation Developer", "Build interactive real-time worlds, tools, simulation systems, and content pipelines.", {"Game loop", "Rendering", "Input", "Assets", "ECS", "Physics", "Editor tools"}, {"C++", "C#", "Python", "Lua"}, {"2D RPG", "World builder", "Simulation sandbox"}},
        {"career_security", "Security-Minded Software Engineer", "Write safer software and understand common vulnerabilities, secure design, and defensive testing.", {"Secure coding", "Threat modeling", "Networking", "Linux", "Testing", "Logging"}, {"Python", "C++", "Go", "JavaScript"}, {"Secure login demo", "Log analyzer", "Vulnerability lab notes app"}},
        {"career_devops", "DevOps/Cloud Engineer", "Automate builds, deployments, monitoring, containers, and infrastructure.", {"Linux", "Shell", "Docker", "CI/CD", "Cloud basics", "Monitoring", "Networking"}, {"Go", "Python", "Bash", "YAML"}, {"CI pipeline", "Containerized API", "Monitoring dashboard"}}
    };
}
