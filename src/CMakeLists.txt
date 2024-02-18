add_library(tb2c_lib lexer.cpp token.cpp)

target_compile_features(tb2c_lib PUBLIC cxx_std_20)

target_include_directories(tb2c_lib PUBLIC ../include)
