cmake_minimum_required(VERSION 3.14)
project(vs-logger VERSION 1.0.0 LANGUAGES CXX)

# =============================================================================
# Set C++ Standard and Compiler Flags
# =============================================================================
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enforce strict compiler warnings. Treat warnings as errors in CI/Release.
set(VS_LOGGER_CXX_WARNINGS -Wall -Wextra -Wpedantic)
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    list(APPEND VS_LOGGER_CXX_WARNINGS -Werror)
endif()

# =============================================================================
# Project Options
# =============================================================================
option(VS_LOGGER_ENABLE_STATIC_ANALYSIS "Enable static analysis with clang-tidy." ON)
option(VS_LOGGER_ENABLE_TESTING "Build unit tests for the library." ON)
option(VS_LOGGER_BUILD_EXAMPLES "Build example applications." ON)
option(BUILD_SHARED_LIBS "Build shared libraries (.so/.dll) instead of static ones." OFF)

# =============================================================================
# Static Analysis (clang-tidy) Integration
# =============================================================================
if(VS_LOGGER_ENABLE_STATIC_ANALYSIS)
    find_program(CLANG_TIDY_EXE clang-tidy)
    if(CLANG_TIDY_EXE)
        message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
        # Apply clang-tidy to our source files.
        # This will run clang-tidy during the build process.
        set(CMAKE_CXX_CLANG_TIDY
            "${CLANG_TIDY_EXE}"
            "-p=${CMAKE_BINARY_DIR}"
            "-header-filter=^${CMAKE_SOURCE_DIR}/(include|src)/.*$")
    else()
        message(WARNING "clang-tidy not found. Static analysis will be skipped.")
    endif()
endif()

# =============================================================================
# Subdirectory Processing
# =============================================================================
# Add the public headers to the include path for all targets.
include_directories(include)

# Add the source code directory which contains the library definition.
add_subdirectory(src)

# Add tests if enabled.
if(VS_LOGGER_ENABLE_TESTING)
    # Enable the CTest framework.
    enable_testing()
    # Fetch GoogleTest dependency.
    include(FetchContent)
    FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
    )
    FetchContent_MakeAvailable(gtest)
    add_subdirectory(tests)
endif()

# Add examples if enabled.
if(VS_LOGGER_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# =============================================================================
# Code Formatting Target
# =============================================================================
find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
    message(STATUS "Found clang-format: ${CLANG_FORMAT_EXE}")
    file(GLOB_RECURSE ALL_CXX_FILES
         "${CMAKE_SOURCE_DIR}/include/*.hpp"
         "${CMAKE_SOURCE_DIR}/src/*.cpp"
         "${CMAKE_SOURCE_DIR}/tests/*.cpp"
         "${CMAKE_SOURCE_DIR}/examples/*.cpp"
    )
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_CXX_FILES}
        COMMENT "Formatting all C++ source files with clang-format."
    )
else()
        message(WARNING "clang-format not found. SourceFiles Formatting will be skipped.")
endif()