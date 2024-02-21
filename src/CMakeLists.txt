add_library(vb2c_lib lexer.cpp token.cpp parser.cpp emitter.cpp)

target_compile_features(vb2c_lib PUBLIC cxx_std_20)

target_include_directories(vb2c_lib PUBLIC ../include)
