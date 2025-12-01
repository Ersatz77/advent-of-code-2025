cmake_minimum_required(VERSION 4.2)

# ------------------------------------------------------------------------------
# Setup project
# ------------------------------------------------------------------------------

project(advent_of_code_2025
    LANGUAGES CXX
    VERSION 1.0.0
)

# Check for in-source builds
include("cmake/ban_in_source_builds.cmake")

# Turn off compiler specific extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# Create target for specifying the C++ standard and compiler specific options
# ------------------------------------------------------------------------------
add_library(project_options INTERFACE)
target_compile_features(project_options
    INTERFACE
        cxx_std_23
)

# Enable multi-processor compilation on MSVC
if(MSVC)
    target_compile_options(project_options
        INTERFACE
            /MP
    )
endif()


# ------------------------------------------------------------------------------
# Create target for compiler warnings
# ------------------------------------------------------------------------------
include("cmake/compiler_warnings.cmake")
add_library(project_warnings INTERFACE)

option(project_warnings_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
set_project_warnings(project_warnings
    "${project_warnings_WARNINGS_AS_ERRORS}"
    ""
    ""
    ""
)

# ------------------------------------------------------------------------------
# Manage dependencies
# https://github.com/cpm-cmake/CPM.cmake
# ------------------------------------------------------------------------------
file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.0/CPM.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake"
    EXPECTED_HASH SHA256=2020B4FC42DBA44817983E06342E682ECFC3D2F484A581F11CC5731FBE4DCE8A
)
include("${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake")

CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY "fmtlib/fmt"
    GIT_TAG "12.1.0"
)
CPMAddPackage(
    NAME ctre
    GITHUB_REPOSITORY "hanickadot/compile-time-regular-expressions"
    GIT_TAG "v3.10.0"
)

# ------------------------------------------------------------------------------
# Create executable
# ------------------------------------------------------------------------------
add_executable(aoc_2025_app)

target_sources(aoc_2025_app
    PRIVATE
        "src/main.cpp" "src/utility/day.h" "src/utility/day.cpp" "src/utility/utility.h" "src/utility/io.h" "src/utility/io.cpp" "src/utility/math.h" "src/utility/math.cpp" "src/utility/string.h" "src/utility/string.cpp" "src/utility/vec.h" "src/solutions/all.h" "src/solutions/day_1/day_1.h" "src/solutions/day_1/day_1.cpp" "src/solutions/day_2/day_2.h" "src/solutions/day_2/day_2.cpp"
)

target_include_directories(aoc_2025_app
    PRIVATE
        "src/"
)

target_link_libraries(aoc_2025_app
    PRIVATE
        project_options
        project_warnings
        fmt::fmt
        ctre::ctre
)

# ------------------------------------------------------------------------------
# Install options
# ------------------------------------------------------------------------------
install(
    TARGETS
        aoc_2025_app
)
