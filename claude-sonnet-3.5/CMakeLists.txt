cmake_minimum_required(VERSION 3.28)
project(claude-sonnet-3.5)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Include current directory
include_directories(.)

# Add the gtest subdirectory (assuming you cloned the repo into a 'googletest' folder)
add_subdirectory(googletest)

# Link gtest and gtest_main libraries
enable_testing()

# Add your source files for the task2 project
add_executable(claude-sonnet-3.5
        main.cpp
        Polynomial.cpp
        Polynomial.h
)

# Link gtest and pthread (required for gtest)
target_link_libraries(claude-sonnet-3.5 gtest gtest_main pthread)

# Add a test target for running tests
add_test(NAME PolynomialTest COMMAND claude-sonnet-3.5)

