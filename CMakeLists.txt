cmake_minimum_required(VERSION 3.14...3.29)

project(
    tb2c
    VERSION 1.0
    DESCRIPTION "A Tiny BASIC to C compiler. "
    LANGUAGES CXX)

include(FetchContent)

enable_testing()

add_subdirectory(apps)

add_subdirectory(src)

add_subdirectory(tests)
