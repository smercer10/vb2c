#pragma once
#include <string>

// Enumerators are suffixed with an underscore to avoid conflicts with C++ keywords
enum class TokenType
{
    // Special tokens
    eof_,
    newline_,
    number_,
    identifier_,
    string_,
    // Keywords
    label_,
    goto_,
    print_,
    input_,
    let_,
    if_,
    then_,
    endif_,
    while_,
    repeat_,
    endwhile_,
    // Operators
    eq_,
    plus_,
    minus_,
    mult_,
    div_,
    eqeq_,
    noteq_,
    lt_,
    lteq_,
    gt_,
    gteq_,
};

class Token
{
public:
    TokenType type;
    std::string value;

    std::string type_as_string();
    static TokenType type_from_string(std::string str);
    static bool is_keyword(TokenType type);
    static bool is_comparison_operator(TokenType type);
};
