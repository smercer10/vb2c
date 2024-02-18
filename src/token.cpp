#include "tb2c/token.h"

std::string Token::type_as_string()
{
    using enum TokenType;

    switch (type)
    {
    case eof_:
        return "eof";
    case newline_:
        return "newline";
    case number_:
        return "number";
    case identifier_:
        return "identifier";
    case string_:
        return "string";
    case label_:
        return "label";
    case goto_:
        return "goto";
    case print_:
        return "print";
    case input_:
        return "input";
    case let_:
        return "let";
    case if_:
        return "if";
    case then_:
        return "then";
    case endif_:
        return "endif";
    case while_:
        return "while";
    case repeat_:
        return "repeat";
    case endwhile_:
        return "endwhile";
    case eq_:
        return "eq";
    case plus_:
        return "plus";
    case minus_:
        return "minus";
    case mult_:
        return "mult";
    case div_:
        return "div";
    case eqeq_:
        return "eqeq";
    case noteq_:
        return "noteq";
    case lt_:
        return "lt";
    case lteq_:
        return "lteq";
    case gt_:
        return "gt";
    case gteq_:
        return "gteq";
    default:
        return "unknown";
    }
}

TokenType Token::type_from_string(std::string s)
{
    using enum TokenType;

    // Only care about keywords
    if (s == "LABEL")
        return label_;
    if (s == "GOTO")
        return goto_;
    if (s == "PRINT")
        return print_;
    if (s == "INPUT")
        return input_;
    if (s == "LET")
        return let_;
    if (s == "IF")
        return if_;
    if (s == "THEN")
        return then_;
    if (s == "ENDIF")
        return endif_;
    if (s == "WHILE")
        return while_;
    if (s == "REPEAT")
        return repeat_;
    if (s == "ENDWHILE")
        return endwhile_;

    return eof_;
}

bool Token::is_keyword(TokenType type)
{
    using enum TokenType;

    switch (type)
    {
    case label_:
    case goto_:
    case print_:
    case input_:
    case let_:
    case if_:
    case then_:
    case endif_:
    case while_:
    case repeat_:
    case endwhile_:
        return true;
    default:
        return false;
    }
}
