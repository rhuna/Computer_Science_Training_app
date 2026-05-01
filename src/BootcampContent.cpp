#include "BootcampContent.h"

QVector<Module> BootcampContent::createDefaultModules()
{
    QVector<Module> modules;

    modules.push_back(Module{
        "m01_cpp_foundations",
        "01 - C++ Foundations",
        "Beginner to Junior",
        "Build a strong base in how C++ programs are written, compiled, linked, debugged, and organized.",
        {
            Lesson{
                "l_cpp_build_pipeline",
                "How C++ Builds Work",
                "Understand preprocessing, compiling, assembling, linking, headers, libraries, and executables.",
                "Professional C++ developers need to understand the build pipeline because many real-world failures are linker, dependency, or configuration issues. A header declares what exists, a source file defines behavior, the compiler turns translation units into object files, and the linker combines object files and libraries into the final executable.",
                {"Explain what a .h file does", "Explain what a .cpp file does", "Describe object files", "Describe static libraries", "Describe linker errors"},
                {"Draw your own build pipeline", "Create a two-file C++ program", "Intentionally break a declaration and fix the compiler error", "Intentionally break a definition and fix the linker error"}
            },
            Lesson{
                "l_cpp_memory",
                "Variables, Memory, and Ownership",
                "Learn stack values, heap allocation, references, pointers, RAII, and safe resource ownership.",
                "Most professional C++ code is about controlling lifetime. Prefer values, references, smart pointers, and RAII. Use raw pointers mainly for non-owning access. Avoid manual new/delete in application code when standard containers or smart pointers can own resources safely.",
                {"Use std::vector instead of manual arrays", "Explain pointer vs reference", "Use std::unique_ptr", "Explain RAII", "Avoid dangling references"},
                {"Write a small class that opens and closes a resource", "Replace raw new/delete with std::unique_ptr", "Trace stack vs heap variables in a function"}
            },
            Lesson{
                "l_cpp_classes",
                "Classes and Interfaces",
                "Design small classes with clear responsibilities and predictable public APIs.",
                "A class should make invalid states harder to represent. Keep private data private, expose intentional operations, and use constructors to create valid objects. Professional class design favors clarity over cleverness.",
                {"Create a class with private fields", "Use const member functions", "Separate interface and implementation", "Avoid god classes"},
                {"Create a BankAccount class", "Move implementation into a .cpp file", "Write tests manually in main"}
            }
        },
        {
            Exercise{"ex_cpp_vector_stats", "Vector Statistics", "Beginner", "Write functions that compute min, max, sum, and average for a std::vector<int>.", "#include <vector>\n#include <optional>\n\nint sum(const std::vector<int>& values) {\n    // TODO\n    return 0;\n}\n", "Loops, const references, return values, edge cases"},
            Exercise{"ex_cpp_library_layout", "Split a Program into Headers and Sources", "Beginner", "Create MathTools.h and MathTools.cpp, then call the functions from main.cpp.", "// MathTools.h\n#pragma once\nint add(int a, int b);\n", "Declarations, definitions, translation units, linker behavior"}
        },
        {
            QuizQuestion{"q_cpp_header", "What is the main purpose of a header file?", {"To store compiled machine code", "To declare interfaces other files can use", "To replace the linker", "To run the program"}, 1, "Headers usually declare functions, classes, constants, and interfaces that source files can include."},
            QuizQuestion{"q_cpp_linker", "Which stage usually reports unresolved external symbol errors?", {"Preprocessor", "Compiler parser", "Linker", "Runtime garbage collector"}, 2, "An unresolved external usually means something was declared but no matching definition was linked."}
        },
        {
            PortfolioProject{"p_cpp_cli_tracker", "Command-Line Habit Tracker", "Junior Portfolio", "Build a small C++ program that stores habits, marks days complete, and saves progress to a file.", {"Use multiple .h/.cpp files", "Use std::vector", "Persist data", "Provide a menu loop"}, {"Add CSV export", "Add weekly statistics", "Add unit tests"}}
        }
    });

    modules.push_back(Module{
        "m02_algorithms",
        "02 - Data Structures and Algorithms",
        "Junior to Interview Ready",
        "Learn arrays, linked structures, stacks, queues, hash maps, trees, graphs, sorting, searching, Big-O, and interview-style problem solving.",
        {
            Lesson{"l_big_o", "Big-O Thinking", "Estimate how code scales as input grows.", "Big-O describes growth rate, not exact speed. O(1), O(log n), O(n), O(n log n), O(n^2), and O(2^n) are common categories. Professional engineers use Big-O to avoid designs that collapse under realistic data.", {"Identify loops", "Spot nested loops", "Explain hash lookup average case", "Compare sort costs"}, {"Classify five code snippets", "Rewrite an O(n^2) search using a hash set"}},
            Lesson{"l_trees_graphs", "Trees and Graphs", "Understand hierarchical and connected data.", "Trees model parent-child relationships. Graphs model networks. Breadth-first search is useful for shortest paths in unweighted graphs; depth-first search is useful for traversal, cycle detection, and backtracking.", {"Implement DFS", "Implement BFS", "Explain visited sets", "Represent adjacency lists"}, {"Build a file tree walker", "Solve a maze with BFS"}}
        },
        {
            Exercise{"ex_two_sum", "Two Sum with a Hash Map", "Interview Foundation", "Return indices of two numbers that add to a target.", "std::pair<int,int> twoSum(const std::vector<int>& nums, int target) {\n    // TODO: use std::unordered_map\n    return {-1, -1};\n}\n", "Hash maps, complements, single-pass algorithms"},
            Exercise{"ex_bfs_grid", "Shortest Path in a Grid", "Intermediate", "Use BFS to find the shortest path from S to E in a grid with walls.", "// Represent positions as row/column pairs.\n// Use std::queue for BFS.\n", "Queues, visited states, grid traversal"}
        },
        {
            QuizQuestion{"q_big_o_nested", "What is the usual complexity of two nested loops over n items?", {"O(1)", "O(log n)", "O(n)", "O(n^2)"}, 3, "A loop inside another loop commonly performs n times n work."},
            QuizQuestion{"q_bfs", "Which structure does BFS usually use?", {"Stack", "Queue", "Priority-only heap", "Raw pointer table"}, 1, "BFS explores level by level, and a queue naturally supports that order."}
        },
        {
            PortfolioProject{"p_algo_visualizer", "Algorithm Visualizer", "Portfolio", "Create a desktop visualizer for sorting and pathfinding algorithms.", {"Visualize bubble, insertion, merge, and quick sort", "Visualize BFS on a grid", "Allow speed control"}, {"Add A*", "Add random maze generation", "Export run metrics"}}
        }
    });

    modules.push_back(Module{
        "m03_systems",
        "03 - Systems, OS, and Networking",
        "Junior to Professional",
        "Understand processes, threads, memory, files, sockets, protocols, and the operating system concepts behind real applications.",
        {
            Lesson{"l_process_threads", "Processes and Threads", "Understand execution units and concurrency hazards.", "A process owns memory and resources. A thread runs within a process and shares memory with other threads in that process. Shared memory makes concurrency powerful but dangerous when race conditions exist.", {"Explain process vs thread", "Use std::thread", "Use mutexes", "Avoid data races"}, {"Create two worker threads", "Protect shared counter with a mutex"}},
            Lesson{"l_networking", "Networking Basics", "Learn clients, servers, sockets, TCP, UDP, ports, and protocols.", "Most network applications use a client-server model. TCP provides reliable ordered byte streams. UDP sends datagrams with lower overhead but no built-in delivery guarantee.", {"Explain IP and port", "Describe TCP", "Describe UDP", "Explain request/response"}, {"Write pseudocode for a chat server", "Use curl to inspect HTTP responses"}}
        },
        {
            Exercise{"ex_thread_counter", "Thread-Safe Counter", "Intermediate", "Create a counter incremented by multiple threads without losing increments.", "#include <mutex>\nclass Counter {\npublic:\n    void increment();\n    int value() const;\nprivate:\n    mutable std::mutex mutex_;\n    int value_ = 0;\n};\n", "std::thread, std::mutex, lock_guard, race conditions"},
            Exercise{"ex_file_indexer", "File Indexer", "Intermediate", "Scan a folder and build a simple searchable index of filenames and extensions.", "// Use std::filesystem to walk directories.\n", "Filesystem APIs, maps, error handling"}
        },
        {
            QuizQuestion{"q_tcp", "What does TCP primarily provide?", {"Reliable ordered byte stream", "Guaranteed encryption", "Image rendering", "Database indexing"}, 0, "TCP handles reliable ordered delivery, but encryption requires protocols such as TLS."},
            QuizQuestion{"q_mutex", "What is a mutex used for?", {"Compiling templates", "Protecting shared data", "Drawing UI widgets", "Compressing files"}, 1, "A mutex prevents multiple threads from entering a critical section at the same time."}
        },
        {
            PortfolioProject{"p_local_chat", "Local Network Chat", "Professional Foundation", "Build a small client/server chat app to understand sockets and message flow.", {"Server accepts multiple clients", "Clients send names and messages", "Log messages", "Handle disconnects"}, {"Add rooms", "Add simple authentication", "Add GUI client"}}
        }
    });

    modules.push_back(Module{
        "m04_professional_engineering",
        "04 - Professional Engineering Practices",
        "Professional Readiness",
        "Move from writing code to engineering maintainable software: Git, testing, architecture, debugging, CI, documentation, and release packaging.",
        {
            Lesson{"l_git_workflow", "Git Workflow", "Work like a professional developer using branches, commits, reviews, and clean history.", "Git is not just storage. It is a collaboration system. Small commits, meaningful messages, branches, pull requests, and tags make a project easier to review, debug, and release.", {"Create a feature branch", "Write useful commits", "Resolve conflicts", "Tag releases"}, {"Make three small commits", "Write a changelog entry"}},
            Lesson{"l_testing", "Testing and Debugging", "Use repeatable checks to protect your work from regression.", "Testing gives confidence that changes did not break existing behavior. Debugging is the disciplined process of reproducing, isolating, explaining, fixing, and verifying a problem.", {"Write unit tests", "Create reproducible bug steps", "Use debugger breakpoints", "Add logging"}, {"Write tests for vector stats", "Debug an intentional off-by-one bug"}}
        },
        {
            Exercise{"ex_test_harness", "Tiny Test Harness", "Professional", "Write a minimal assert-based test runner for your own C++ functions.", "#define CHECK(expr) do { if (!(expr)) return false; } while(false)\n", "Testing, assertions, regression safety"},
            Exercise{"ex_release_package", "Release Folder Builder", "Professional", "Create a script that copies an executable, data folder, and README into a release folder.", "// Use a .bat or CMake install step.\n", "Packaging, deployment, documentation"}
        },
        {
            QuizQuestion{"q_tests", "What is the main value of automated tests?", {"They make code impossible to break", "They replace design", "They catch regressions and document expected behavior", "They remove the need for debugging"}, 2, "Tests are not magic, but they make expected behavior repeatable and protect against accidental breakage."},
            QuizQuestion{"q_git_commit", "What makes a good commit?", {"Huge mixed changes", "A small focused change with a meaningful message", "Only generated files", "No explanation"}, 1, "Focused commits make review and rollback much easier."}
        },
        {
            PortfolioProject{"p_capstone", "Professional Capstone App", "Job Ready", "Build a polished desktop application with clean architecture, tests, docs, release packaging, and a GitHub-ready README.", {"Use CMake", "Use multiple modules", "Persist data", "Add tests or a test harness", "Write architecture docs", "Create release scripts"}, {"Add installer", "Add crash-safe saves", "Add CI workflow", "Add issue templates"}}
        }
    });

    return modules;
}
