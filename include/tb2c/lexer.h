#pragma once
#include "tb2c/token.h"
#include <string>

class Lexer
{
public:
    Lexer(std::string source_code)
        : source{source_code + '\n'},
          curr_char{'\0'},
          curr_pos{-1},
          line_num{1},
          col_num{1}
    {
        next_char();
    }

    Token get_token();

private:
    const std::string source;
    char curr_char;
    int curr_pos;
    int line_num;
    int col_num;

    void abort(std::string msg);
    void next_char();
    char peek();
    void skip_whitespace();
    void skip_comment();
};
