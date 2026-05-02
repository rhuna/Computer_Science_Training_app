#include "BootcampContent.h"

namespace
{
    Lesson lesson(const QString& id, const QString& title, const QString& objective, const QString& explanation, QVector<QString> checklist, QVector<QString> practice)
    {
        return Lesson{id, title, objective, explanation, checklist, practice};
    }

    Lesson lessonFull(const QString& id, const QString& title, const QString& objective, const QString& explanation, QVector<QString> checklist, QVector<QString> practice, const QString& workedExample, const QString& coachedProblem, QVector<QString> guidedQuestions, QVector<QString> fillInBlanks, QVector<QString> dropdownPrompts, const QString& codeCompletion)
    {
        return Lesson{id, title, objective, explanation, checklist, practice, workedExample, coachedProblem, guidedQuestions, fillInBlanks, dropdownPrompts, codeCompletion};
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
        QString::fromUtf8(R"CS(m01_problem_contracts)CS"),
        QString::fromUtf8(R"CS(01 - Problem Contracts)CS"),
        QString::fromUtf8(R"CS(Beginner Foundation)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for problem contracts. Objective: Write a precise problem contract before coding.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m01_problem_contracts_lesson)CS"), QString::fromUtf8(R"CS(01 - Problem Contracts)CS"), QString::fromUtf8(R"CS(Write a precise problem contract before coding.)CS"), QString::fromUtf8(R"CS(A problem contract turns an English prompt into something testable. It states the input, output, constraints, examples, edge cases, and what proof of correctness will look like. This matters because most beginner mistakes happen before coding starts: the learner solves a slightly different problem than the one being asked. A professional developer does not start by typing code; they first clarify what correct behavior means. For example, in “return the first non-repeating character,” the contract must say whether the answer is an index or a character, whether the string can be empty, and what to do when no unique character exists. Once the contract is clear, the algorithm can be judged objectively instead of by guessing.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 01 - Problem Contracts: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Given a short coding prompt, produce a clear contract with INPUT, OUTPUT, CONSTRAINTS, EXAMPLES, EDGE CASES, and VERIFICATION PLAN sections.

Solution walkthrough: Read the prompt once for meaning, then rewrite it as facts. Identify the data coming in, the exact result expected, and any assumptions. Add two examples: one normal case and one edge case. The verification plan should say what tests will prove the solution is correct.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_problem_contracts)CS"), QString::fromUtf8(R"CS(01 - Problem Contracts Practice)CS"), QString::fromUtf8(R"CS(Beginner)CS"), QString::fromUtf8(R"CS(Given a short coding prompt, produce a clear contract with INPUT, OUTPUT, CONSTRAINTS, EXAMPLES, EDGE CASES, and VERIFICATION PLAN sections.)CS"), QString::fromUtf8(R"CS(// 01 - Problem Contracts
// Objective: Write a precise problem contract before coding.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(problem contracts)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m01_problem_contracts_q)CS"), QString::fromUtf8(R"CS(What is the main purpose of a problem contract?)CS"), QVector<QString>{QString::fromUtf8(R"CS(To define testable behavior before coding)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(To define testable behavior before coding. This directly supports the lesson objective: Write a precise problem contract before coding.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m02_variables)CS"),
        QString::fromUtf8(R"CS(02 - Variables)CS"),
        QString::fromUtf8(R"CS(Beginner Foundation)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for variables. Objective: Use variables as named state that changes predictably.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m02_variables_lesson)CS"), QString::fromUtf8(R"CS(02 - Variables)CS"), QString::fromUtf8(R"CS(Use variables as named state that changes predictably.)CS"), QString::fromUtf8(R"CS(A variable is a named piece of state. It stores a value so the program can use or change that value later. Good variable use is not just syntax; it is about meaning. A variable named total should represent the running sum. A variable named count should represent how many items have been seen. Bugs happen when variables are uninitialized, reused for unrelated meanings, or updated in the wrong place. In professional code, every variable should have a reason to exist and a narrow purpose. When tracing code, ask: what is this variable before the line runs, what changes after the line runs, and why?

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 02 - Variables: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read integers and maintain count and total variables, then print both values.

Solution walkthrough: Initialize count and total to zero. For each input number, increase count by one and add the value to total. After input ends, print count and total. The key is to update both variables exactly once per item.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_variables)CS"), QString::fromUtf8(R"CS(02 - Variables Practice)CS"), QString::fromUtf8(R"CS(Beginner)CS"), QString::fromUtf8(R"CS(Read integers and maintain count and total variables, then print both values.)CS"), QString::fromUtf8(R"CS(// 02 - Variables
// Objective: Use variables as named state that changes predictably.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(variables)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m02_variables_q)CS"), QString::fromUtf8(R"CS(Why should a variable have one clear meaning?)CS"), QVector<QString>{QString::fromUtf8(R"CS(So its state can be traced and debugged reliably)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(So its state can be traced and debugged reliably. This directly supports the lesson objective: Use variables as named state that changes predictably.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m03_types)CS"),
        QString::fromUtf8(R"CS(03 - Types and Values)CS"),
        QString::fromUtf8(R"CS(Beginner Foundation)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for types. Objective: Choose correct types for values and operations.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m03_types_lesson)CS"), QString::fromUtf8(R"CS(03 - Types and Values)CS"), QString::fromUtf8(R"CS(Choose correct types for values and operations.)CS"), QString::fromUtf8(R"CS(A type describes what kind of value something is and what operations are allowed. Integers are good for counts and indexes. Floating point numbers represent measurements but can have rounding behavior. Strings hold text. Booleans represent true/false decisions. Choosing the wrong type can cause bugs: integer division may drop decimals, unsigned indexes may behave badly when subtracting, and text numbers cannot be added until parsed. Types also communicate intent to other developers. A professional solution chooses types that match the domain and make invalid states harder to represent.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 03 - Types and Values: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read a value and classify it as integer-like, decimal-like, boolean-like, or text-like.

Solution walkthrough: Check the form of the input. If it is true/false, classify as boolean. If it contains only digits with optional sign, classify as integer. If it has a decimal point and numeric parts, classify as decimal. Otherwise classify as text.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_types)CS"), QString::fromUtf8(R"CS(03 - Types and Values Practice)CS"), QString::fromUtf8(R"CS(Beginner)CS"), QString::fromUtf8(R"CS(Read a value and classify it as integer-like, decimal-like, boolean-like, or text-like.)CS"), QString::fromUtf8(R"CS(// 03 - Types and Values
// Objective: Choose correct types for values and operations.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(types)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m03_types_q)CS"), QString::fromUtf8(R"CS(What does a type tell the programmer?)CS"), QVector<QString>{QString::fromUtf8(R"CS(What kind of value is stored and what operations are valid)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(What kind of value is stored and what operations are valid. This directly supports the lesson objective: Choose correct types for values and operations.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m04_conditionals)CS"),
        QString::fromUtf8(R"CS(04 - Conditionals)CS"),
        QString::fromUtf8(R"CS(Beginner Foundation)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for conditionals. Objective: Use if/else logic to choose correct behavior.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m04_conditionals_lesson)CS"), QString::fromUtf8(R"CS(04 - Conditionals)CS"), QString::fromUtf8(R"CS(Use if/else logic to choose correct behavior.)CS"), QString::fromUtf8(R"CS(Conditionals let a program choose between paths. The important skill is not simply writing if statements, but designing mutually clear conditions. Conditions should be ordered from most specific to most general when order matters. Each branch should represent a meaningful case in the problem. For example, grading logic might check invalid score first, then A, B, C, D, and F ranges. A common bug is overlapping branches or forgetting the boundary values. Professional developers test each branch, especially the edges where one branch changes into another.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 04 - Conditionals: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read a numeric score and print INVALID, A, B, C, D, or F.

Solution walkthrough: First handle scores below 0 or above 100 as INVALID. Then check grade thresholds from highest to lowest. Test 90, 89, 80, 79, 0, 100, and invalid values.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_conditionals)CS"), QString::fromUtf8(R"CS(04 - Conditionals Practice)CS"), QString::fromUtf8(R"CS(Beginner)CS"), QString::fromUtf8(R"CS(Read a numeric score and print INVALID, A, B, C, D, or F.)CS"), QString::fromUtf8(R"CS(// 04 - Conditionals
// Objective: Use if/else logic to choose correct behavior.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(conditionals)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m04_conditionals_q)CS"), QString::fromUtf8(R"CS(Why should boundary values be tested in conditionals?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Because many bugs occur where one branch changes to another)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Because many bugs occur where one branch changes to another. This directly supports the lesson objective: Use if/else logic to choose correct behavior.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m05_loops)CS"),
        QString::fromUtf8(R"CS(05 - Loops)CS"),
        QString::fromUtf8(R"CS(Beginner Foundation)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for loops. Objective: Use loops to repeat work while preserving correct state.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m05_loops_lesson)CS"), QString::fromUtf8(R"CS(05 - Loops)CS"), QString::fromUtf8(R"CS(Use loops to repeat work while preserving correct state.)CS"), QString::fromUtf8(R"CS(A loop repeats a block of logic. The professional skill is to define what changes each iteration and what stays true. That truth is called a loop invariant. In a sum loop, after each iteration the total equals the sum of values already processed. Loops commonly fail because of off-by-one errors, missing updates, or incorrect stopping conditions. When solving a loop problem, identify the collection or range, the per-item action, and the final result. Trace a small example manually before trusting the code.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 05 - Loops: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read numbers until input ends and print the largest number, or EMPTY when no input exists.

Solution walkthrough: Track whether at least one number has been seen. For the first number, set largest to it. For each later number, update largest only if the value is greater. Print EMPTY if no numbers were read.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_loops)CS"), QString::fromUtf8(R"CS(05 - Loops Practice)CS"), QString::fromUtf8(R"CS(Beginner)CS"), QString::fromUtf8(R"CS(Read numbers until input ends and print the largest number, or EMPTY when no input exists.)CS"), QString::fromUtf8(R"CS(// 05 - Loops
// Objective: Use loops to repeat work while preserving correct state.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(loops)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m05_loops_q)CS"), QString::fromUtf8(R"CS(What is a loop invariant?)CS"), QVector<QString>{QString::fromUtf8(R"CS(A statement that remains true after each loop iteration)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(A statement that remains true after each loop iteration. This directly supports the lesson objective: Use loops to repeat work while preserving correct state.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m06_functions)CS"),
        QString::fromUtf8(R"CS(06 - Functions)CS"),
        QString::fromUtf8(R"CS(Beginner Foundation)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for functions. Objective: Design small functions with clear input, output, and responsibility.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m06_functions_lesson)CS"), QString::fromUtf8(R"CS(06 - Functions)CS"), QString::fromUtf8(R"CS(Design small functions with clear input, output, and responsibility.)CS"), QString::fromUtf8(R"CS(A function is a named promise. Given inputs, it should produce a result or perform one focused action. Good functions reduce complexity because the caller does not need to know every internal detail. A professional function has one responsibility, a clear name, predictable behavior, and testable inputs and outputs. For example, normalizeWord should only clean and lowercase one word; it should not also print reports or read files. Keeping functions small makes debugging easier because failures can be isolated.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 06 - Functions: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Write a function that converts a word to lowercase and removes leading/trailing punctuation.

Solution walkthrough: Separate the word-cleaning logic from input/output. The function receives one string, removes punctuation at the ends, lowercases remaining letters, and returns the cleaned word. Then the main flow can call it for each token.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_functions)CS"), QString::fromUtf8(R"CS(06 - Functions Practice)CS"), QString::fromUtf8(R"CS(Beginner)CS"), QString::fromUtf8(R"CS(Write a function that converts a word to lowercase and removes leading/trailing punctuation.)CS"), QString::fromUtf8(R"CS(// 06 - Functions
// Objective: Design small functions with clear input, output, and responsibility.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(functions)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m06_functions_q)CS"), QString::fromUtf8(R"CS(Why should a function usually do one job?)CS"), QVector<QString>{QString::fromUtf8(R"CS(It becomes easier to test, reuse, debug, and explain)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(It becomes easier to test, reuse, debug, and explain. This directly supports the lesson objective: Design small functions with clear input, output, and responsibility.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m07_strings)CS"),
        QString::fromUtf8(R"CS(07 - Strings)CS"),
        QString::fromUtf8(R"CS(Beginner Data Structures)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for strings. Objective: Process text using indexes, characters, and normalization.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m07_strings_lesson)CS"), QString::fromUtf8(R"CS(07 - Strings)CS"), QString::fromUtf8(R"CS(Process text using indexes, characters, and normalization.)CS"), QString::fromUtf8(R"CS(A string is an ordered sequence of characters. String problems usually involve scanning, comparing, slicing, normalizing, or building new text. The key is to be precise about indexes and character rules. For example, palindrome checking should say whether spaces and punctuation matter and whether uppercase equals lowercase. Text processing is common in real applications: parsing logs, validating forms, searching documents, and cleaning user input. Strong developers avoid vague “it looks right” checks and define exact text rules.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 07 - Strings: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read a word and print whether it is a palindrome after lowercasing it.

Solution walkthrough: Normalize the input to lowercase. Use two indexes: one starting at the front and one at the back. Compare characters while moving inward. If any pair differs, it is not a palindrome.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_strings)CS"), QString::fromUtf8(R"CS(07 - Strings Practice)CS"), QString::fromUtf8(R"CS(Beginner)CS"), QString::fromUtf8(R"CS(Read a word and print whether it is a palindrome after lowercasing it.)CS"), QString::fromUtf8(R"CS(// 07 - Strings
// Objective: Process text using indexes, characters, and normalization.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(strings)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m07_strings_q)CS"), QString::fromUtf8(R"CS(What makes string problems tricky?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Index boundaries and unclear character rules)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Index boundaries and unclear character rules. This directly supports the lesson objective: Process text using indexes, characters, and normalization.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m08_arrays_vectors)CS"),
        QString::fromUtf8(R"CS(08 - Arrays and Vectors)CS"),
        QString::fromUtf8(R"CS(Beginner Data Structures)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for arrays and vectors. Objective: Use ordered collections when position matters.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m08_arrays_vectors_lesson)CS"), QString::fromUtf8(R"CS(08 - Arrays and Vectors)CS"), QString::fromUtf8(R"CS(Use ordered collections when position matters.)CS"), QString::fromUtf8(R"CS(An array or vector stores values in order. It is ideal when you need index-based access, iteration in original order, or compact storage. Vectors are common in C++ because they grow dynamically while still supporting fast indexed access. The main mistakes are out-of-bounds access and confusing an index with a value. If the problem asks for “the third item,” “the first item greater than X,” or “scan all numbers,” a vector is often appropriate.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 08 - Arrays and Vectors: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read integers into a vector and print them in reverse order.

Solution walkthrough: Append each input number to a vector. Then loop from the last valid index down to zero and print each value. Handle the empty vector by printing EMPTY.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_arrays_vectors)CS"), QString::fromUtf8(R"CS(08 - Arrays and Vectors Practice)CS"), QString::fromUtf8(R"CS(Beginner)CS"), QString::fromUtf8(R"CS(Read integers into a vector and print them in reverse order.)CS"), QString::fromUtf8(R"CS(// 08 - Arrays and Vectors
// Objective: Use ordered collections when position matters.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(arrays and vectors)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m08_arrays_vectors_q)CS"), QString::fromUtf8(R"CS(When is a vector a good choice?)CS"), QVector<QString>{QString::fromUtf8(R"CS(When ordered storage and indexed access matter)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(When ordered storage and indexed access matter. This directly supports the lesson objective: Use ordered collections when position matters.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m09_hash_maps)CS"),
        QString::fromUtf8(R"CS(09 - Hash Maps)CS"),
        QString::fromUtf8(R"CS(Intermediate Data Structures)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for hash maps. Objective: Use key-value counting and lookup for fast association.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m09_hash_maps_lesson)CS"), QString::fromUtf8(R"CS(09 - Hash Maps)CS"), QString::fromUtf8(R"CS(Use key-value counting and lookup for fast association.)CS"), QString::fromUtf8(R"CS(A hash map stores values by key. It is useful when you need to count, group, or look up information quickly. For word frequency, the word is the key and the count is the value. The important mental model is “given this key, what value should I retrieve or update?” Hash maps are often average O(1) for insert and lookup, which is much faster than scanning a list for each lookup. Professional use also considers normalization: “Apple” and “apple” may need to become the same key.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 09 - Hash Maps: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read words and print each word with its frequency count.

Solution walkthrough: Normalize each word if required. For every word, increment map[word]. After reading all input, output the key/count pairs. To make output testable, sort keys before printing.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_hash_maps)CS"), QString::fromUtf8(R"CS(09 - Hash Maps Practice)CS"), QString::fromUtf8(R"CS(Intermediate)CS"), QString::fromUtf8(R"CS(Read words and print each word with its frequency count.)CS"), QString::fromUtf8(R"CS(// 09 - Hash Maps
// Objective: Use key-value counting and lookup for fast association.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(hash maps)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m09_hash_maps_q)CS"), QString::fromUtf8(R"CS(When should you use a hash map?)CS"), QVector<QString>{QString::fromUtf8(R"CS(When you need fast lookup, counting, grouping, or key-value association)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(When you need fast lookup, counting, grouping, or key-value association. This directly supports the lesson objective: Use key-value counting and lookup for fast association.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m10_sets)CS"),
        QString::fromUtf8(R"CS(10 - Sets)CS"),
        QString::fromUtf8(R"CS(Intermediate Data Structures)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for sets. Objective: Use sets to track uniqueness without caring about counts.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m10_sets_lesson)CS"), QString::fromUtf8(R"CS(10 - Sets)CS"), QString::fromUtf8(R"CS(Use sets to track uniqueness without caring about counts.)CS"), QString::fromUtf8(R"CS(A set stores unique values. Unlike a hash map, it does not store a separate value for each key; membership itself is the information. Sets are perfect for questions like “have I seen this before?”, “which unique tags exist?”, or “does this collection contain duplicates?” A beginner may use a vector and repeatedly search it, but that becomes slower as the data grows. A set communicates intent: this problem is about uniqueness.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 10 - Sets: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read words and print the number of unique words.

Solution walkthrough: Create a set. For each input word, insert it into the set. Because sets ignore duplicates, the final size is the number of unique words. Normalize case if the problem says words should be case-insensitive.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_sets)CS"), QString::fromUtf8(R"CS(10 - Sets Practice)CS"), QString::fromUtf8(R"CS(Intermediate)CS"), QString::fromUtf8(R"CS(Read words and print the number of unique words.)CS"), QString::fromUtf8(R"CS(// 10 - Sets
// Objective: Use sets to track uniqueness without caring about counts.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(sets)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m10_sets_q)CS"), QString::fromUtf8(R"CS(How is a set different from a hash map?)CS"), QVector<QString>{QString::fromUtf8(R"CS(A set tracks unique membership; a hash map associates keys with values)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(A set tracks unique membership; a hash map associates keys with values. This directly supports the lesson objective: Use sets to track uniqueness without caring about counts.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m11_unordered_sets)CS"),
        QString::fromUtf8(R"CS(11 - Unordered Sets)CS"),
        QString::fromUtf8(R"CS(Intermediate Data Structures)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for unordered sets. Objective: Use unordered_set for average constant-time membership checks.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m11_unordered_sets_lesson)CS"), QString::fromUtf8(R"CS(11 - Unordered Sets)CS"), QString::fromUtf8(R"CS(Use unordered_set for average constant-time membership checks.)CS"), QString::fromUtf8(R"CS(An unordered_set is a hash-table-backed set. It stores unique values and provides average O(1) insert and lookup, but it does not keep values sorted. This distinction matters. If you need fast “have I seen this?” checks, unordered_set is often ideal. If you need sorted output, you may need std::set or sort values after collecting them. Professional developers choose based on behavior: uniqueness, speed, and ordering requirements.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 11 - Unordered Sets: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read integers and print DUPLICATE if any value appears twice; otherwise print UNIQUE.

Solution walkthrough: Create an unordered_set called seen. For each number, check whether it is already in seen. If yes, a duplicate exists. If not, insert it. If the loop finishes with no duplicate, print UNIQUE.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_unordered_sets)CS"), QString::fromUtf8(R"CS(11 - Unordered Sets Practice)CS"), QString::fromUtf8(R"CS(Intermediate)CS"), QString::fromUtf8(R"CS(Read integers and print DUPLICATE if any value appears twice; otherwise print UNIQUE.)CS"), QString::fromUtf8(R"CS(// 11 - Unordered Sets
// Objective: Use unordered_set for average constant-time membership checks.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(unordered sets)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m11_unordered_sets_q)CS"), QString::fromUtf8(R"CS(Why use unordered_set for duplicate detection?)CS"), QVector<QString>{QString::fromUtf8(R"CS(It provides fast average membership checks while tracking uniqueness)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(It provides fast average membership checks while tracking uniqueness. This directly supports the lesson objective: Use unordered_set for average constant-time membership checks.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m12_stacks)CS"),
        QString::fromUtf8(R"CS(12 - Stacks)CS"),
        QString::fromUtf8(R"CS(Intermediate Data Structures)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for stacks. Objective: Use LIFO state for nested or reversible operations.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m12_stacks_lesson)CS"), QString::fromUtf8(R"CS(12 - Stacks)CS"), QString::fromUtf8(R"CS(Use LIFO state for nested or reversible operations.)CS"), QString::fromUtf8(R"CS(A stack follows last-in, first-out behavior. The most recent item added is the first one removed. This matches nested structures such as parentheses, undo operations, function calls, and depth-first traversal. When reading parentheses, every opening symbol is pushed, and each closing symbol must match the latest unmatched opening symbol. A stack is powerful because it models “what is currently open or waiting to be finished.”

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 12 - Stacks: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read a string of brackets and print BALANCED or NOT_BALANCED.

Solution walkthrough: Push opening brackets onto a stack. For a closing bracket, the stack must not be empty and the top must be the matching opening bracket. Pop on a match. At the end, the stack must be empty.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_stacks)CS"), QString::fromUtf8(R"CS(12 - Stacks Practice)CS"), QString::fromUtf8(R"CS(Intermediate)CS"), QString::fromUtf8(R"CS(Read a string of brackets and print BALANCED or NOT_BALANCED.)CS"), QString::fromUtf8(R"CS(// 12 - Stacks
// Objective: Use LIFO state for nested or reversible operations.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(stacks)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m12_stacks_q)CS"), QString::fromUtf8(R"CS(What problem pattern suggests using a stack?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Nested, last-opened-first-closed, or undo-style state)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Nested, last-opened-first-closed, or undo-style state. This directly supports the lesson objective: Use LIFO state for nested or reversible operations.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m13_queues)CS"),
        QString::fromUtf8(R"CS(13 - Queues)CS"),
        QString::fromUtf8(R"CS(Intermediate Data Structures)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for queues. Objective: Use FIFO order for fair processing.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m13_queues_lesson)CS"), QString::fromUtf8(R"CS(13 - Queues)CS"), QString::fromUtf8(R"CS(Use FIFO order for fair processing.)CS"), QString::fromUtf8(R"CS(A queue follows first-in, first-out behavior. The earliest item added is processed first. This models lines, task scheduling, breadth-first search, print jobs, and event processing. Queues are useful when fairness or level-order processing matters. In BFS, the queue holds nodes discovered but not yet processed, ensuring that closer nodes are visited before farther ones.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 13 - Queues: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Simulate customer service: ENQUEUE name adds a person, SERVE removes and prints the next person.

Solution walkthrough: Use a queue. On ENQUEUE, push the name at the back. On SERVE, if the queue is empty print EMPTY; otherwise print and remove the front item.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_queues)CS"), QString::fromUtf8(R"CS(13 - Queues Practice)CS"), QString::fromUtf8(R"CS(Intermediate)CS"), QString::fromUtf8(R"CS(Simulate customer service: ENQUEUE name adds a person, SERVE removes and prints the next person.)CS"), QString::fromUtf8(R"CS(// 13 - Queues
// Objective: Use FIFO order for fair processing.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(queues)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m13_queues_q)CS"), QString::fromUtf8(R"CS(What does FIFO mean?)CS"), QVector<QString>{QString::fromUtf8(R"CS(First in, first out)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(First in, first out. This directly supports the lesson objective: Use FIFO order for fair processing.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m14_big_o)CS"),
        QString::fromUtf8(R"CS(14 - Big-O)CS"),
        QString::fromUtf8(R"CS(Core Algorithms)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for big-o. Objective: Compare algorithms by growth as input size increases.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m14_big_o_lesson)CS"), QString::fromUtf8(R"CS(14 - Big-O)CS"), QString::fromUtf8(R"CS(Compare algorithms by growth as input size increases.)CS"), QString::fromUtf8(R"CS(Big-O describes how runtime or memory grows as input size grows. It ignores machine-specific details and focuses on the dominant growth pattern. O(n) usually scales much better than O(n²). Big-O does not mean exact seconds; it means how work changes as the problem gets larger. For example, checking every pair in a list is O(n²), while counting with a hash map is O(n). Professional developers use Big-O to avoid designs that work on 10 items but fail on 10 million.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 14 - Big-O: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Given simple loop descriptions, classify them as O(1), O(n), O(n log n), or O(n²).

Solution walkthrough: Count how many times work repeats relative to input size. A single loop over n items is O(n). Nested loops over the same n are often O(n²). Fixed-size work is O(1).

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_big_o)CS"), QString::fromUtf8(R"CS(14 - Big-O Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Given simple loop descriptions, classify them as O(1), O(n), O(n log n), or O(n²).)CS"), QString::fromUtf8(R"CS(// 14 - Big-O
// Objective: Compare algorithms by growth as input size increases.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(big-o)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m14_big_o_q)CS"), QString::fromUtf8(R"CS(What does Big-O measure?)CS"), QVector<QString>{QString::fromUtf8(R"CS(How work or memory grows as input size increases)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(How work or memory grows as input size increases. This directly supports the lesson objective: Compare algorithms by growth as input size increases.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m15_sorting)CS"),
        QString::fromUtf8(R"CS(15 - Sorting)CS"),
        QString::fromUtf8(R"CS(Core Algorithms)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for sorting. Objective: Sort data to enable ordered processing and efficient search.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m15_sorting_lesson)CS"), QString::fromUtf8(R"CS(15 - Sorting)CS"), QString::fromUtf8(R"CS(Sort data to enable ordered processing and efficient search.)CS"), QString::fromUtf8(R"CS(Sorting places items into a defined order. Once data is sorted, many tasks become easier: binary search, duplicate grouping, ranking, merging, and reporting. The key is to understand why sorting helps and what it costs. Simple sorts such as selection sort are easy to learn but O(n²). Professional libraries use more advanced algorithms. In interviews, sorting can be an intentional tradeoff: pay O(n log n) once to make later logic simpler.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 15 - Sorting: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read integers, sort them ascending, and print the sorted values.

Solution walkthrough: Store numbers in a vector, sort the vector, and print values in order. Test empty input, one number, duplicates, and negative values.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_sorting)CS"), QString::fromUtf8(R"CS(15 - Sorting Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Read integers, sort them ascending, and print the sorted values.)CS"), QString::fromUtf8(R"CS(// 15 - Sorting
// Objective: Sort data to enable ordered processing and efficient search.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(sorting)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m15_sorting_q)CS"), QString::fromUtf8(R"CS(Why might sorting be useful before solving a problem?)CS"), QVector<QString>{QString::fromUtf8(R"CS(It creates order that can simplify searching, grouping, or comparison)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(It creates order that can simplify searching, grouping, or comparison. This directly supports the lesson objective: Sort data to enable ordered processing and efficient search.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m16_binary_search)CS"),
        QString::fromUtf8(R"CS(16 - Binary Search)CS"),
        QString::fromUtf8(R"CS(Core Algorithms)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for binary search. Objective: Search sorted data by repeatedly cutting the search space in half.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m16_binary_search_lesson)CS"), QString::fromUtf8(R"CS(16 - Binary Search)CS"), QString::fromUtf8(R"CS(Search sorted data by repeatedly cutting the search space in half.)CS"), QString::fromUtf8(R"CS(Binary search works only when the data is sorted or the search condition is monotonic. It compares the target with the middle item and discards half of the remaining search space each step. That gives O(log n) time, much faster than linear search for large data. The main bugs are incorrect low/high updates and infinite loops. A professional implementation states whether high is inclusive or exclusive and keeps that convention consistent.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 16 - Binary Search: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read a sorted list and a target, then print the target index or -1.

Solution walkthrough: Set low to 0 and high to size - 1. While low <= high, compute mid safely. If value equals target, return mid. If value is too small, move low. If too large, move high.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_binary_search)CS"), QString::fromUtf8(R"CS(16 - Binary Search Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Read a sorted list and a target, then print the target index or -1.)CS"), QString::fromUtf8(R"CS(// 16 - Binary Search
// Objective: Search sorted data by repeatedly cutting the search space in half.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(binary search)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m16_binary_search_q)CS"), QString::fromUtf8(R"CS(What must be true before binary search works?)CS"), QVector<QString>{QString::fromUtf8(R"CS(The data must be sorted or the predicate must be monotonic)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(The data must be sorted or the predicate must be monotonic. This directly supports the lesson objective: Search sorted data by repeatedly cutting the search space in half.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m17_trees)CS"),
        QString::fromUtf8(R"CS(17 - Trees)CS"),
        QString::fromUtf8(R"CS(Intermediate Algorithms)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for trees. Objective: Model hierarchical data with parent-child relationships.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m17_trees_lesson)CS"), QString::fromUtf8(R"CS(17 - Trees)CS"), QString::fromUtf8(R"CS(Model hierarchical data with parent-child relationships.)CS"), QString::fromUtf8(R"CS(A tree is a hierarchy with nodes connected by parent-child edges and no cycles. Trees model folders, UI layouts, organization charts, syntax trees, and decision processes. The common operations are traversal, search, insert, and aggregation. Recursion often fits trees because each subtree is itself a smaller tree. The important question is which traversal order matches the task: preorder for processing parent before children, inorder for binary search tree sorted order, and postorder for children before parent.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 17 - Trees: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Given parent-child relationships, print a preorder traversal from the root.

Solution walkthrough: Build an adjacency list from each parent to children. Start at the root, print it, then recursively visit each child in order. Handle missing children as a base case.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_trees)CS"), QString::fromUtf8(R"CS(17 - Trees Practice)CS"), QString::fromUtf8(R"CS(Intermediate)CS"), QString::fromUtf8(R"CS(Given parent-child relationships, print a preorder traversal from the root.)CS"), QString::fromUtf8(R"CS(// 17 - Trees
// Objective: Model hierarchical data with parent-child relationships.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(trees)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m17_trees_q)CS"), QString::fromUtf8(R"CS(Why is recursion natural for trees?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Each subtree has the same structure as the whole tree)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Each subtree has the same structure as the whole tree. This directly supports the lesson objective: Model hierarchical data with parent-child relationships.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m18_graphs)CS"),
        QString::fromUtf8(R"CS(18 - Graphs)CS"),
        QString::fromUtf8(R"CS(Intermediate Algorithms)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for graphs. Objective: Model networks of connected things with nodes and edges.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m18_graphs_lesson)CS"), QString::fromUtf8(R"CS(18 - Graphs)CS"), QString::fromUtf8(R"CS(Model networks of connected things with nodes and edges.)CS"), QString::fromUtf8(R"CS(A graph contains nodes and edges. Unlike trees, graphs may have cycles and multiple paths between nodes. Graphs model roads, dependencies, friendships, networks, state transitions, and game maps. The key challenge is avoiding repeated visits and infinite cycles. Most graph algorithms begin with a representation: adjacency list or matrix. Then they use traversal such as BFS or DFS with a visited set.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 18 - Graphs: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read edges and determine whether two nodes are connected.

Solution walkthrough: Build an adjacency list. Start from the source node. Use BFS or DFS while tracking visited nodes. If the target is reached, print CONNECTED; otherwise print NOT_CONNECTED.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_graphs)CS"), QString::fromUtf8(R"CS(18 - Graphs Practice)CS"), QString::fromUtf8(R"CS(Intermediate)CS"), QString::fromUtf8(R"CS(Read edges and determine whether two nodes are connected.)CS"), QString::fromUtf8(R"CS(// 18 - Graphs
// Objective: Model networks of connected things with nodes and edges.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(graphs)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m18_graphs_q)CS"), QString::fromUtf8(R"CS(Why do graph traversals need a visited set?)CS"), QVector<QString>{QString::fromUtf8(R"CS(To avoid revisiting nodes and looping forever in cycles)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(To avoid revisiting nodes and looping forever in cycles. This directly supports the lesson objective: Model networks of connected things with nodes and edges.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m19_recursion)CS"),
        QString::fromUtf8(R"CS(19 - Recursion)CS"),
        QString::fromUtf8(R"CS(Intermediate Algorithms)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for recursion. Objective: Solve a problem by defining base cases and smaller subproblems.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m19_recursion_lesson)CS"), QString::fromUtf8(R"CS(19 - Recursion)CS"), QString::fromUtf8(R"CS(Solve a problem by defining base cases and smaller subproblems.)CS"), QString::fromUtf8(R"CS(Recursion is when a function solves a problem by calling itself on a smaller version of the problem. Every recursive function needs a base case that stops and a progress step that moves toward that base case. Recursion is useful for trees, divide-and-conquer, backtracking, and problems with repeated structure. The danger is infinite recursion or excessive repeated work. Professional recursion is not magic; it is a disciplined contract: what does this call solve, and what smaller call does it depend on?

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 19 - Recursion: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read n and print factorial(n) using recursion.

Solution walkthrough: Base case: factorial(0) and factorial(1) are 1. Recursive case: factorial(n)=n*factorial(n-1). Validate n is nonnegative. Trace n=4 by hand.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_recursion)CS"), QString::fromUtf8(R"CS(19 - Recursion Practice)CS"), QString::fromUtf8(R"CS(Intermediate)CS"), QString::fromUtf8(R"CS(Read n and print factorial(n) using recursion.)CS"), QString::fromUtf8(R"CS(// 19 - Recursion
// Objective: Solve a problem by defining base cases and smaller subproblems.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(recursion)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m19_recursion_q)CS"), QString::fromUtf8(R"CS(What two parts must recursion have?)CS"), QVector<QString>{QString::fromUtf8(R"CS(A base case and a recursive step that makes progress)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(A base case and a recursive step that makes progress. This directly supports the lesson objective: Solve a problem by defining base cases and smaller subproblems.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m20_dynamic_programming)CS"),
        QString::fromUtf8(R"CS(20 - Dynamic Programming)CS"),
        QString::fromUtf8(R"CS(Advanced Algorithms)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for dynamic programming. Objective: Use stored subproblem results to avoid repeated work.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m20_dynamic_programming_lesson)CS"), QString::fromUtf8(R"CS(20 - Dynamic Programming)CS"), QString::fromUtf8(R"CS(Use stored subproblem results to avoid repeated work.)CS"), QString::fromUtf8(R"CS(Dynamic programming solves problems with overlapping subproblems and optimal substructure. Instead of recomputing the same answers, it stores them in a table or memo. The skill is to define state clearly. For climbing stairs, state dp[i] means the number of ways to reach step i. The recurrence is dp[i]=dp[i-1]+dp[i-2]. DP is hard because beginners try to memorize formulas instead of defining what the state means.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 20 - Dynamic Programming: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Read n and print the number of ways to climb n stairs taking 1 or 2 steps.

Solution walkthrough: Define dp[0]=1 and dp[1]=1. For each i from 2 to n, compute dp[i]=dp[i-1]+dp[i-2]. Print dp[n]. Explain what each dp entry means.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_dynamic_programming)CS"), QString::fromUtf8(R"CS(20 - Dynamic Programming Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Read n and print the number of ways to climb n stairs taking 1 or 2 steps.)CS"), QString::fromUtf8(R"CS(// 20 - Dynamic Programming
// Objective: Use stored subproblem results to avoid repeated work.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(dynamic programming)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m20_dynamic_programming_q)CS"), QString::fromUtf8(R"CS(What is the most important first step in DP?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Define the state meaning clearly)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Define the state meaning clearly. This directly supports the lesson objective: Use stored subproblem results to avoid repeated work.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m21_memory_model)CS"),
        QString::fromUtf8(R"CS(21 - Memory Model)CS"),
        QString::fromUtf8(R"CS(Systems)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for memory. Objective: Explain stack, heap, lifetime, and ownership.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m21_memory_model_lesson)CS"), QString::fromUtf8(R"CS(21 - Memory Model)CS"), QString::fromUtf8(R"CS(Explain stack, heap, lifetime, and ownership.)CS"), QString::fromUtf8(R"CS(Programs use memory to store instructions and data. Local function variables often live on the stack and disappear when the function returns. Dynamically allocated data often lives on the heap and must have clear ownership. Bugs such as dangling pointers, leaks, and out-of-bounds access come from misunderstanding lifetime and ownership. Even in managed languages, memory concepts matter because objects still consume resources and references affect lifetime.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 21 - Memory Model: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Classify variables and objects as stack-like, heap-like, static, or external resource.

Solution walkthrough: Read descriptions. If a value is a local variable, classify stack-like. If created dynamically, heap-like. If global/static, static. If it refers to file/socket/db handle, external resource.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_memory_model)CS"), QString::fromUtf8(R"CS(21 - Memory Model Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Classify variables and objects as stack-like, heap-like, static, or external resource.)CS"), QString::fromUtf8(R"CS(// 21 - Memory Model
// Objective: Explain stack, heap, lifetime, and ownership.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(memory)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m21_memory_model_q)CS"), QString::fromUtf8(R"CS(Why does memory lifetime matter?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Using data after its lifetime ends can crash or corrupt behavior)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Using data after its lifetime ends can crash or corrupt behavior. This directly supports the lesson objective: Explain stack, heap, lifetime, and ownership.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m22_os_processes)CS"),
        QString::fromUtf8(R"CS(22 - Operating Systems)CS"),
        QString::fromUtf8(R"CS(Systems)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for operating systems. Objective: Understand processes, threads, files, and OS resources.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m22_os_processes_lesson)CS"), QString::fromUtf8(R"CS(22 - Operating Systems)CS"), QString::fromUtf8(R"CS(Understand processes, threads, files, and OS resources.)CS"), QString::fromUtf8(R"CS(An operating system manages hardware resources and gives programs safe abstractions: processes, threads, files, memory, sockets, and permissions. A process is a running program with its own memory space. Threads are execution paths inside a process. Files and sockets are OS resources that must be opened, used, and closed. Application developers need OS knowledge to diagnose crashes, hangs, file errors, permissions issues, and performance bottlenecks.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 22 - Operating Systems: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Given event descriptions, classify them as process, thread, file, memory, or permission concerns.

Solution walkthrough: Read each scenario. Identify the resource involved. If it is about separate running programs, process. Concurrent execution inside one app, thread. Disk access, file. Access denied, permission.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_os_processes)CS"), QString::fromUtf8(R"CS(22 - Operating Systems Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Given event descriptions, classify them as process, thread, file, memory, or permission concerns.)CS"), QString::fromUtf8(R"CS(// 22 - Operating Systems
// Objective: Understand processes, threads, files, and OS resources.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(operating systems)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m22_os_processes_q)CS"), QString::fromUtf8(R"CS(Why should application developers understand OS resources?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Because many real bugs involve files, permissions, memory, processes, or threads)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Because many real bugs involve files, permissions, memory, processes, or threads. This directly supports the lesson objective: Understand processes, threads, files, and OS resources.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m23_networking)CS"),
        QString::fromUtf8(R"CS(23 - Networking)CS"),
        QString::fromUtf8(R"CS(Backend Foundation)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for networking. Objective: Explain how clients and servers communicate over networks.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m23_networking_lesson)CS"), QString::fromUtf8(R"CS(23 - Networking)CS"), QString::fromUtf8(R"CS(Explain how clients and servers communicate over networks.)CS"), QString::fromUtf8(R"CS(Networking lets programs communicate across machines. A client sends a request, a server receives it, processes it, and sends a response. Important layers include IP addressing, ports, DNS names, TCP connections, TLS encryption, and application protocols. Beginners often say “the API is down,” but a professional troubleshoots DNS, connectivity, authentication, request format, server errors, and timeout behavior separately.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 23 - Networking: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Classify failed web requests by likely cause: DNS, connection, TLS, auth, validation, or server error.

Solution walkthrough: Inspect the symptom. Name resolution failure suggests DNS. Connection refused suggests server/port. 401/403 suggests auth. 400 suggests validation. 500 suggests server failure.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_networking)CS"), QString::fromUtf8(R"CS(23 - Networking Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Classify failed web requests by likely cause: DNS, connection, TLS, auth, validation, or server error.)CS"), QString::fromUtf8(R"CS(// 23 - Networking
// Objective: Explain how clients and servers communicate over networks.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(networking)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m23_networking_q)CS"), QString::fromUtf8(R"CS(Why separate network failure types?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Different causes require different fixes)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Different causes require different fixes. This directly supports the lesson objective: Explain how clients and servers communicate over networks.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m24_http_apis)CS"),
        QString::fromUtf8(R"CS(24 - HTTP and APIs)CS"),
        QString::fromUtf8(R"CS(Backend Foundation)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for HTTP APIs. Objective: Design predictable request/response behavior for APIs.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m24_http_apis_lesson)CS"), QString::fromUtf8(R"CS(24 - HTTP and APIs)CS"), QString::fromUtf8(R"CS(Design predictable request/response behavior for APIs.)CS"), QString::fromUtf8(R"CS(HTTP APIs expose application behavior through requests and responses. A request has a method, path, headers, and sometimes a body. A response has a status code, headers, and body. Good APIs are predictable: GET reads, POST creates, PUT/PATCH updates, DELETE removes. Status codes communicate outcome. Professional API design also includes validation, error messages, pagination, authentication, and versioning.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 24 - HTTP and APIs: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Design endpoints for a task tracker API and print method/path/status expectations.

Solution walkthrough: List resources first: tasks and users. Define GET /tasks, POST /tasks, PATCH /tasks/{id}, DELETE /tasks/{id}. For each, state success and error status codes.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_http_apis)CS"), QString::fromUtf8(R"CS(24 - HTTP and APIs Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Design endpoints for a task tracker API and print method/path/status expectations.)CS"), QString::fromUtf8(R"CS(// 24 - HTTP and APIs
// Objective: Design predictable request/response behavior for APIs.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(HTTP APIs)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m24_http_apis_q)CS"), QString::fromUtf8(R"CS(What should an HTTP status code communicate?)CS"), QVector<QString>{QString::fromUtf8(R"CS(The outcome category of the request)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(The outcome category of the request. This directly supports the lesson objective: Design predictable request/response behavior for APIs.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m25_sql_tables)CS"),
        QString::fromUtf8(R"CS(25 - SQL Tables)CS"),
        QString::fromUtf8(R"CS(Data Systems)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for SQL tables. Objective: Design normalized tables with primary and foreign keys.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m25_sql_tables_lesson)CS"), QString::fromUtf8(R"CS(25 - SQL Tables)CS"), QString::fromUtf8(R"CS(Design normalized tables with primary and foreign keys.)CS"), QString::fromUtf8(R"CS(A table stores rows of one kind of thing. A primary key uniquely identifies a row. A foreign key references another table and models relationships. Good schema design reduces duplication and prevents inconsistent data. For example, storing a user name repeatedly in every task row is weaker than storing user_id and referencing a users table. A normalized design makes updates safer and queries more reliable.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 25 - SQL Tables: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Write SQL tables for users and tasks using primary and foreign keys.

Solution walkthrough: Create users(id,name). Create tasks(id,user_id,title,completed). Make user_id reference users(id). Insert sample users and tasks. Query tasks for one user.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_sql_tables)CS"), QString::fromUtf8(R"CS(25 - SQL Tables Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Write SQL tables for users and tasks using primary and foreign keys.)CS"), QString::fromUtf8(R"CS(// 25 - SQL Tables
// Objective: Design normalized tables with primary and foreign keys.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(SQL tables)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m25_sql_tables_q)CS"), QString::fromUtf8(R"CS(Why use a foreign key?)CS"), QVector<QString>{QString::fromUtf8(R"CS(To represent and protect a relationship between tables)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(To represent and protect a relationship between tables. This directly supports the lesson objective: Design normalized tables with primary and foreign keys.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m26_sql_queries)CS"),
        QString::fromUtf8(R"CS(26 - SQL Queries)CS"),
        QString::fromUtf8(R"CS(Data Systems)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for SQL queries. Objective: Retrieve and summarize data with SELECT, WHERE, JOIN, and GROUP BY.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m26_sql_queries_lesson)CS"), QString::fromUtf8(R"CS(26 - SQL Queries)CS"), QString::fromUtf8(R"CS(Retrieve and summarize data with SELECT, WHERE, JOIN, and GROUP BY.)CS"), QString::fromUtf8(R"CS(SQL queries answer questions about data. SELECT chooses columns, FROM chooses tables, WHERE filters rows, JOIN combines related tables, GROUP BY summarizes rows, and ORDER BY controls output order. Query writing is a core professional skill because applications constantly need reports, dashboards, validations, and lookups. A good query states exactly what question it answers and avoids retrieving unnecessary data.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 26 - SQL Queries: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Write a query that returns each user and their count of incomplete tasks.

Solution walkthrough: Join users to tasks on user id. Filter completed=false if needed, group by user, and count tasks. Use LEFT JOIN if users with zero tasks should appear.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_sql_queries)CS"), QString::fromUtf8(R"CS(26 - SQL Queries Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Write a query that returns each user and their count of incomplete tasks.)CS"), QString::fromUtf8(R"CS(// 26 - SQL Queries
// Objective: Retrieve and summarize data with SELECT, WHERE, JOIN, and GROUP BY.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(SQL queries)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m26_sql_queries_q)CS"), QString::fromUtf8(R"CS(When should you use GROUP BY?)CS"), QVector<QString>{QString::fromUtf8(R"CS(When summarizing rows by category or key)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(When summarizing rows by category or key. This directly supports the lesson objective: Retrieve and summarize data with SELECT, WHERE, JOIN, and GROUP BY.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m27_testing)CS"),
        QString::fromUtf8(R"CS(27 - Testing)CS"),
        QString::fromUtf8(R"CS(Software Engineering)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for testing. Objective: Write tests that prove behavior instead of manually guessing.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m27_testing_lesson)CS"), QString::fromUtf8(R"CS(27 - Testing)CS"), QString::fromUtf8(R"CS(Write tests that prove behavior instead of manually guessing.)CS"), QString::fromUtf8(R"CS(Testing is how developers prove code still works after changes. A good test has input, expected output, and a reason it matters. Manual testing once is not enough because humans forget cases and future changes can break old behavior. Unit tests focus on small functions. Integration tests check pieces working together. Regression tests protect against bugs that already happened. Professional developers test normal cases, edge cases, and failure cases.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 27 - Testing: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Create test cases for a word frequency function.

Solution walkthrough: Test a normal sentence, repeated words, mixed case, punctuation, and empty input. For each test, write expected output before running code.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_testing)CS"), QString::fromUtf8(R"CS(27 - Testing Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Create test cases for a word frequency function.)CS"), QString::fromUtf8(R"CS(// 27 - Testing
// Objective: Write tests that prove behavior instead of manually guessing.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(testing)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m27_testing_q)CS"), QString::fromUtf8(R"CS(Why are tests more valuable than running the app once?)CS"), QVector<QString>{QString::fromUtf8(R"CS(They are repeatable proof that behavior still works)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(They are repeatable proof that behavior still works. This directly supports the lesson objective: Write tests that prove behavior instead of manually guessing.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m28_debugging)CS"),
        QString::fromUtf8(R"CS(28 - Debugging)CS"),
        QString::fromUtf8(R"CS(Software Engineering)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for debugging. Objective: Find the first wrong state instead of randomly changing code.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m28_debugging_lesson)CS"), QString::fromUtf8(R"CS(28 - Debugging)CS"), QString::fromUtf8(R"CS(Find the first wrong state instead of randomly changing code.)CS"), QString::fromUtf8(R"CS(Debugging is the process of locating where reality first diverges from expectation. Weak debugging means changing random lines until the symptom disappears. Strong debugging starts with a failing test, predicts expected state, observes actual state, and narrows the search. Logs, breakpoints, assertions, and small inputs help. The goal is not only to fix the bug but also to understand why the bug existed.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 28 - Debugging: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Given a failed output, write a debugging trace plan.

Solution walkthrough: State expected output, actual output, suspected variables, checkpoints to print, and the first line where state should be verified.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_debugging)CS"), QString::fromUtf8(R"CS(28 - Debugging Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Given a failed output, write a debugging trace plan.)CS"), QString::fromUtf8(R"CS(// 28 - Debugging
// Objective: Find the first wrong state instead of randomly changing code.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(debugging)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m28_debugging_q)CS"), QString::fromUtf8(R"CS(What is the first wrong state?)CS"), QVector<QString>{QString::fromUtf8(R"CS(The earliest point where actual program state differs from expected state)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(The earliest point where actual program state differs from expected state. This directly supports the lesson objective: Find the first wrong state instead of randomly changing code.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m29_refactoring)CS"),
        QString::fromUtf8(R"CS(29 - Refactoring)CS"),
        QString::fromUtf8(R"CS(Software Engineering)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for refactoring. Objective: Improve code structure without changing behavior.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m29_refactoring_lesson)CS"), QString::fromUtf8(R"CS(29 - Refactoring)CS"), QString::fromUtf8(R"CS(Improve code structure without changing behavior.)CS"), QString::fromUtf8(R"CS(Refactoring changes internal structure while preserving external behavior. It makes code easier to read, test, reuse, and change. Common refactors include extracting functions, renaming variables, removing duplication, and separating parsing from logic. Tests are essential because they prove the refactor did not change behavior. Professional developers refactor after correctness, not before understanding the problem.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 29 - Refactoring: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Refactor a word frequency solution into parse, normalize, count, and print steps.

Solution walkthrough: Identify separate responsibilities. Move each responsibility into a function. Keep tests passing after every change.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_refactoring)CS"), QString::fromUtf8(R"CS(29 - Refactoring Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Refactor a word frequency solution into parse, normalize, count, and print steps.)CS"), QString::fromUtf8(R"CS(// 29 - Refactoring
// Objective: Improve code structure without changing behavior.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(refactoring)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m29_refactoring_q)CS"), QString::fromUtf8(R"CS(Why should behavior stay the same during refactoring?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Because refactoring improves structure, not the feature result)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Because refactoring improves structure, not the feature result. This directly supports the lesson objective: Improve code structure without changing behavior.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m30_security)CS"),
        QString::fromUtf8(R"CS(30 - Security Basics)CS"),
        QString::fromUtf8(R"CS(Professional Engineering)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for security. Objective: Recognize trust boundaries, validation, and common vulnerabilities.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m30_security_lesson)CS"), QString::fromUtf8(R"CS(30 - Security Basics)CS"), QString::fromUtf8(R"CS(Recognize trust boundaries, validation, and common vulnerabilities.)CS"), QString::fromUtf8(R"CS(Security starts with assuming input can be hostile, malformed, or unexpected. A trust boundary is where data moves from less trusted to more trusted code, such as user input entering a server. Professional software validates input, protects secrets, avoids injection, checks authorization, logs safely, and fails closed when needed. Security is not a final polish step; it affects design from the beginning.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 30 - Security Basics: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Classify scenarios as validation, authentication, authorization, injection, secret handling, or logging risk.

Solution walkthrough: Read each scenario and ask what asset is at risk and where trust changes. Match the issue to the proper category and state the safer design.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_security)CS"), QString::fromUtf8(R"CS(30 - Security Basics Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Classify scenarios as validation, authentication, authorization, injection, secret handling, or logging risk.)CS"), QString::fromUtf8(R"CS(// 30 - Security Basics
// Objective: Recognize trust boundaries, validation, and common vulnerabilities.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(security)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m30_security_q)CS"), QString::fromUtf8(R"CS(What is a trust boundary?)CS"), QVector<QString>{QString::fromUtf8(R"CS(A point where data crosses from one trust level to another)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(A point where data crosses from one trust level to another. This directly supports the lesson objective: Recognize trust boundaries, validation, and common vulnerabilities.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m31_cloud_devops)CS"),
        QString::fromUtf8(R"CS(31 - Cloud and DevOps)CS"),
        QString::fromUtf8(R"CS(Professional Engineering)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for cloud devops. Objective: Understand deployment, CI/CD, containers, and observability.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m31_cloud_devops_lesson)CS"), QString::fromUtf8(R"CS(31 - Cloud and DevOps)CS"), QString::fromUtf8(R"CS(Understand deployment, CI/CD, containers, and observability.)CS"), QString::fromUtf8(R"CS(Cloud and DevOps practices move software from a developer machine to reliable production systems. CI runs tests automatically. CD packages and deploys changes. Containers package applications with their dependencies. Observability uses logs, metrics, and traces to understand system health. A well-rounded developer knows how code behaves after shipping, not only how it runs locally.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 31 - Cloud and DevOps: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Design a simple deployment checklist for an API service.

Solution walkthrough: Include build, test, environment variables, database migration, container image, deployment step, health check, logs, rollback plan, and monitoring.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_cloud_devops)CS"), QString::fromUtf8(R"CS(31 - Cloud and DevOps Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Design a simple deployment checklist for an API service.)CS"), QString::fromUtf8(R"CS(// 31 - Cloud and DevOps
// Objective: Understand deployment, CI/CD, containers, and observability.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(cloud devops)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m31_cloud_devops_q)CS"), QString::fromUtf8(R"CS(What does observability help you understand?)CS"), QVector<QString>{QString::fromUtf8(R"CS(What the system is doing in production and why failures happen)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(What the system is doing in production and why failures happen. This directly supports the lesson objective: Understand deployment, CI/CD, containers, and observability.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m32_ui_ux_accessibility)CS"),
        QString::fromUtf8(R"CS(32 - UI, UX, and Accessibility)CS"),
        QString::fromUtf8(R"CS(Product Engineering)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for UI UX accessibility. Objective: Build interfaces that are clear, usable, and inclusive.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m32_ui_ux_accessibility_lesson)CS"), QString::fromUtf8(R"CS(32 - UI, UX, and Accessibility)CS"), QString::fromUtf8(R"CS(Build interfaces that are clear, usable, and inclusive.)CS"), QString::fromUtf8(R"CS(Good UI helps users accomplish tasks with less confusion. UX is about the whole experience: what users see, what they understand, how errors are handled, and whether the workflow matches their goal. Accessibility ensures people with different abilities can use the software through keyboard navigation, contrast, readable labels, and screen-reader-friendly structure. Professional developers treat UI text, spacing, and error states as part of the product, not decoration.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 32 - UI, UX, and Accessibility: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Evaluate a form and list improvements for clarity, validation, and accessibility.

Solution walkthrough: Check labels, required fields, tab order, error messages, contrast, spacing, and whether the user knows what to do next.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_ui_ux_accessibility)CS"), QString::fromUtf8(R"CS(32 - UI, UX, and Accessibility Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Evaluate a form and list improvements for clarity, validation, and accessibility.)CS"), QString::fromUtf8(R"CS(// 32 - UI, UX, and Accessibility
// Objective: Build interfaces that are clear, usable, and inclusive.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(UI UX accessibility)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m32_ui_ux_accessibility_q)CS"), QString::fromUtf8(R"CS(Why is accessibility part of professional engineering?)CS"), QVector<QString>{QString::fromUtf8(R"CS(Because software should be usable by people with different abilities and contexts)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(Because software should be usable by people with different abilities and contexts. This directly supports the lesson objective: Build interfaces that are clear, usable, and inclusive.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m33_distributed_systems)CS"),
        QString::fromUtf8(R"CS(33 - Distributed Systems)CS"),
        QString::fromUtf8(R"CS(Advanced Systems)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for distributed systems. Objective: Reason about services that communicate and fail independently.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m33_distributed_systems_lesson)CS"), QString::fromUtf8(R"CS(33 - Distributed Systems)CS"), QString::fromUtf8(R"CS(Reason about services that communicate and fail independently.)CS"), QString::fromUtf8(R"CS(A distributed system is made of multiple machines or services that communicate over a network. The difficult part is that partial failure is normal: one service may be slow, one request may timeout, one message may duplicate, and one database may be temporarily unavailable. Professional systems use retries, timeouts, idempotency, queues, health checks, and observability to manage uncertainty. The key mindset is that the network is unreliable and every dependency can fail.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 33 - Distributed Systems: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Design a reliable job queue worker that handles retries and duplicate jobs.

Solution walkthrough: Define job states, retry count, timeout, idempotency key, dead-letter behavior, and logging. Explain how the worker avoids processing the same job twice dangerously.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_distributed_systems)CS"), QString::fromUtf8(R"CS(33 - Distributed Systems Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Design a reliable job queue worker that handles retries and duplicate jobs.)CS"), QString::fromUtf8(R"CS(// 33 - Distributed Systems
// Objective: Reason about services that communicate and fail independently.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(distributed systems)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m33_distributed_systems_q)CS"), QString::fromUtf8(R"CS(Why are retries dangerous without idempotency?)CS"), QVector<QString>{QString::fromUtf8(R"CS(The same operation may run more than once and cause duplicate side effects)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(The same operation may run more than once and cause duplicate side effects. This directly supports the lesson objective: Reason about services that communicate and fail independently.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m34_compilers)CS"),
        QString::fromUtf8(R"CS(34 - Compilers and Interpreters)CS"),
        QString::fromUtf8(R"CS(Advanced Systems)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for compilers. Objective: Understand tokenizing, parsing, and evaluating simple languages.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m34_compilers_lesson)CS"), QString::fromUtf8(R"CS(34 - Compilers and Interpreters)CS"), QString::fromUtf8(R"CS(Understand tokenizing, parsing, and evaluating simple languages.)CS"), QString::fromUtf8(R"CS(A compiler or interpreter translates source text into something executable or understandable. Tokenizing breaks text into meaningful pieces. Parsing checks structure. Evaluation or code generation performs meaning. Even if you never write a production compiler, these concepts improve your understanding of programming languages, syntax errors, expression evaluation, and tooling. Many developer tools—linters, formatters, query parsers, config readers—use compiler-like techniques.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 34 - Compilers and Interpreters: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Build a tokenizer that classifies numbers, identifiers, operators, and parentheses.

Solution walkthrough: Scan characters left to right. Group digits into number tokens, letters into identifier tokens, and single symbols into operator or parenthesis tokens. Ignore whitespace. Report unknown characters.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_compilers)CS"), QString::fromUtf8(R"CS(34 - Compilers and Interpreters Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Build a tokenizer that classifies numbers, identifiers, operators, and parentheses.)CS"), QString::fromUtf8(R"CS(// 34 - Compilers and Interpreters
// Objective: Understand tokenizing, parsing, and evaluating simple languages.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(compilers)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m34_compilers_q)CS"), QString::fromUtf8(R"CS(What does a tokenizer do?)CS"), QVector<QString>{QString::fromUtf8(R"CS(It converts raw source text into meaningful tokens)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(It converts raw source text into meaningful tokens. This directly supports the lesson objective: Understand tokenizing, parsing, and evaluating simple languages.)CS"))
        },
        {}
    });

    modules.push_back(Module{
        QString::fromUtf8(R"CS(m35_ai_rag)CS"),
        QString::fromUtf8(R"CS(35 - AI, Data, and RAG Systems)CS"),
        QString::fromUtf8(R"CS(Advanced Applied AI)CS"),
        QString::fromUtf8(R"CS(Topic-specific lesson for AI RAG systems. Objective: Understand retrieval-augmented generation as search plus generation plus evaluation.)CS"),
        {
            lessonFull(QString::fromUtf8(R"CS(m35_ai_rag_lesson)CS"), QString::fromUtf8(R"CS(35 - AI, Data, and RAG Systems)CS"), QString::fromUtf8(R"CS(Understand retrieval-augmented generation as search plus generation plus evaluation.)CS"), QString::fromUtf8(R"CS(A RAG system answers questions using retrieved documents instead of relying only on a model. The pipeline usually ingests documents, chunks them, embeds or indexes them, retrieves relevant chunks, builds a prompt with citations, generates an answer, and evaluates whether the answer is grounded. The software engineering challenge is not just calling an AI API; it is data quality, retrieval quality, latency, safety, citation accuracy, and evaluation.

Detailed learning path: First, understand the vocabulary of the topic. Second, connect that vocabulary to a small concrete example. Third, decide what state must be stored while solving the problem. Fourth, write the smallest correct algorithm. Finally, prove the behavior with tests. This lesson is intentionally separated from neighboring topics so you are not trying to learn several ideas at once.)CS"), QVector<QString>{QString::fromUtf8(R"CS(Read the objective and restate it in one sentence.)CS"), QString::fromUtf8(R"CS(Identify the exact input, output, constraints, and edge cases for this lesson.)CS"), QString::fromUtf8(R"CS(Trace the worked example before writing code.)CS"), QString::fromUtf8(R"CS(Use the coaching walkthrough to form a solution plan.)CS"), QString::fromUtf8(R"CS(Run the testing and verification stage to prove the objective was learned.)CS")}, QVector<QString>{QString::fromUtf8(R"CS(Write a five-step plain-English algorithm before coding.)CS"), QString::fromUtf8(R"CS(Create one normal test case, one edge case, and one failure case.)CS"), QString::fromUtf8(R"CS(Explain which data structure or pattern is used and why.)CS"), QString::fromUtf8(R"CS(After verification, write what failed first and how you fixed it.)CS")}, QString::fromUtf8(R"CS(Worked example for 35 - AI, Data, and RAG Systems: Start with a tiny input, identify the current state, update the state one step at a time, and compare the final result to the required output. The point is to see why the algorithm works, not just memorize syntax.)CS"), QString::fromUtf8(R"CS(Coding problem: Given a user question and document snippets, choose which snippets should be retrieved and explain why.

Solution walkthrough: Identify the question intent, extract keywords/entities, rank snippets by relevance, reject unrelated snippets, and state what evidence supports the answer.

Before coding, write the input/output contract, the state you will maintain, the branch or loop rules, the edge cases, and the expected complexity. Then implement the smallest correct version and move to testing.)CS"), QVector<QString>{}, QVector<QString>{}, QVector<QString>{}, QString::fromUtf8(R"CS()CS"))
        },
        {
            exercise(QString::fromUtf8(R"CS(ex_ai_rag)CS"), QString::fromUtf8(R"CS(35 - AI, Data, and RAG Systems Practice)CS"), QString::fromUtf8(R"CS(Advanced)CS"), QString::fromUtf8(R"CS(Given a user question and document snippets, choose which snippets should be retrieved and explain why.)CS"), QString::fromUtf8(R"CS(// 35 - AI, Data, and RAG Systems
// Objective: Understand retrieval-augmented generation as search plus generation plus evaluation.
// TODO: Replace this scaffold with your own working solution.
// Use the lesson contract, coaching walkthrough, and verification tests.

)CS"), QString::fromUtf8(R"CS(AI RAG systems)CS"))
        },
        {
            quiz(QString::fromUtf8(R"CS(m35_ai_rag_q)CS"), QString::fromUtf8(R"CS(What is the purpose of retrieval in RAG?)CS"), QVector<QString>{QString::fromUtf8(R"CS(To ground the generated answer in relevant source material)CS"), QString::fromUtf8(R"CS(Because it makes the program longer)CS"), QString::fromUtf8(R"CS(Because it avoids the need for testing)CS"), QString::fromUtf8(R"CS(Because every language handles it the same way)CS")}, 0, QString::fromUtf8(R"CS(To ground the generated answer in relevant source material. This directly supports the lesson objective: Understand retrieval-augmented generation as search plus generation plus evaluation.)CS"))
        },
        {}
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
