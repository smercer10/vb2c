FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_executable(tb2c_test lexer_test.cpp token_test.cpp)

target_link_libraries(tb2c_test tb2c_lib GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(tb2c_test)
