#pragma once
#include <string>
#include "tb2c/token.h"

class Lexer
{
public:
    Lexer(std::string tb_code)
        : source{tb_code + '\n'},
          curr_char{'\0'},
          curr_pos{-1},
          line_num{1},
          col_num{1}
    {
        next_char();
    }

    Token get_token();
    void abort(std::string message);
    void next_char();
    char peek();

private:
    const std::string source;
    char curr_char;
    int curr_pos;
    int line_num;
    int col_num;

    void skip_whitespace();
    void skip_comment();
};
