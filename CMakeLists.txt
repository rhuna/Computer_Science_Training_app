cmake_minimum_required(VERSION 3.24)

# CSBootcampDesktop is a Qt Widgets desktop application written in modern C++.
# The project is intentionally structured like a professional app so future versions
# can add modules without replacing this foundation.
project(CSBootcampDesktop VERSION 7.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt handles generated code for resources, UI forms, and meta-object support.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(CSBootcampDesktop
    src/main.cpp
    src/MainWindow.cpp
    src/BootcampContent.cpp
    src/ProgressStore.cpp
)

target_include_directories(CSBootcampDesktop PRIVATE include)

target_link_libraries(CSBootcampDesktop PRIVATE Qt6::Widgets)

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

# v7 also ships project templates so the generator can create starter repos
# from the same folder layout used by the curriculum examples.
add_custom_command(TARGET CSBootcampDesktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/project_templates
            $<TARGET_FILE_DIR:CSBootcampDesktop>/project_templates
)
