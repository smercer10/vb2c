#pragma once
#include <string>
#include "token.h"

class lexer
{
public:
    explicit lexer(const std::string &source) :
        source_{source + '\n'}, curr_char_{'\0'}, curr_pos_{-1}, line_num_{1}, col_num_{1}
    {
        next_char();
    }

    // Returns the next valid token from the current position in the source
    token::token get_token();

private:
    const std::string source_;
    char curr_char_;
    int curr_pos_;
    int line_num_;
    int col_num_;

    void process_string(token::token &token);
    void process_number(token::token &token);
    void process_identifier(token::token &token);
    void abort(const std::string &msg) const;
    void next_char();
    [[nodiscard]] char peek() const;
    void skip_whitespace();
    void skip_comment();
};
