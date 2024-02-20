#pragma once
#include "vb2c/token.h"
#include <string>

class Lexer
{
public:
    explicit Lexer(const std::string& source_code)
        : source{source_code + '\n'},
          curr_char{'\0'},
          curr_pos{-1},
          line_num{1},
          col_num{1}
    {
        next_char();
    }

    Token::Token get_token();

private:
    const std::string source;
    char curr_char;
    int curr_pos;
    int line_num;
    int col_num;

    void abort(const std::string& msg) const;
    void next_char();
    [[nodiscard]] char peek() const;
    void skip_whitespace();
    void skip_comment();
};
