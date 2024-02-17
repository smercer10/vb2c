#pragma once
#include <string>

class Lexer
{
public:
    Lexer(std::string tb_code)
        : source{tb_code + "\n"},
          curr_char{' '},
          curr_pos{-1}
    {
    }

    std::string get_token();
    void abort();

private:
    const std::string source;
    char curr_char;
    int curr_pos;

    void next_char();
    char peek();
    void skip_whitespace();
    void skip_comment();
};