cmake_minimum_required(VERSION 3.24)

# CSBootcampDesktop is a Qt Widgets desktop application written in modern C++.
# The project is intentionally structured like a professional app so future versions
# can add modules without replacing this foundation.
project(CSBootcampDesktop VERSION 25.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt handles generated code for resources, UI forms, and meta-object support.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

add_executable(CSBootcampDesktop
    src/main.cpp
    src/MainWindow.cpp
    src/BootcampContent.cpp
    src/ProgressStore.cpp
    resources.qrc
)

target_include_directories(CSBootcampDesktop PRIVATE include)

target_link_libraries(CSBootcampDesktop PRIVATE Qt6::Widgets Qt6::Sql)

# On Windows, make the release build start like a normal desktop app.
if(WIN32)
    set_target_properties(CSBootcampDesktop PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Copy static data next to the built executable so the app can grow into
# file-backed curriculum content in later versions.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data
            $<TARGET_FILE_DIR:CSBootcampDesktop>/data
)

# v6 keeps copying starter exercise workspaces beside the executable so the in-app
# exercise runner can point at real folders when the app launches from build/.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/examples
            $<TARGET_FILE_DIR:CSBootcampDesktop>/examples
)


# v9 ships reusable engineering workflow templates for CI, Docker, and release readiness.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/devops_templates
            $<TARGET_FILE_DIR:CSBootcampDesktop>/devops_templates
)

# v11 ships schema reference files for the new SQLite progress database.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/database_templates
            $<TARGET_FILE_DIR:CSBootcampDesktop>/database_templates
)

# v12 ships instructor templates for cohort assignment and learner progress reviews.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/instructor_templates
            $<TARGET_FILE_DIR:CSBootcampDesktop>/instructor_templates
)




# v15 ships the professional content pack library beside the app for offline use.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/content_packs
            $<TARGET_FILE_DIR:CSBootcampDesktop>/content_packs
)


# v16 ships code attempt tracking templates for portfolio review, debugging history,
# and instructor/self-review workflows.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/attempt_templates
            $<TARGET_FILE_DIR:CSBootcampDesktop>/attempt_templates
)


add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/docs
            $<TARGET_FILE_DIR:CSBootcampDesktop>/docs
)

# v18 ships capstone and certification templates for final completion mode.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/capstone_templates
            $<TARGET_FILE_DIR:CSBootcampDesktop>/capstone_templates
)

add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/certification_templates
            $<TARGET_FILE_DIR:CSBootcampDesktop>/certification_templates
)

# v25 ships the guided helper, real-time timer, and popup coaching content as integrated course material.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/advanced_learning_packs
            $<TARGET_FILE_DIR:CSBootcampDesktop>/advanced_learning_packs
)
