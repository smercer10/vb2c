FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_executable(vb2c_test lexer_test.cpp token_test.cpp)

target_compile_features(vb2c_test PRIVATE cxx_std_20)

target_link_libraries(vb2c_test vb2c_lib GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(vb2c_test)
