#include "vb2c/token.h"
#include <string>

std::string Token::Token::type_as_string() const
{
    using enum Type;

    switch (type)
    {
    case eof_:
        return "EOF";
    case newline_:
        return "newline";
    case number_:
        return "number";
    case identifier_:
        return "identifier";
    case string_:
        return "string";
    case label_:
        return "LABEL";
    case goto_:
        return "GOTO";
    case print_:
        return "PRINT";
    case input_:
        return "INPUT";
    case let_:
        return "LET";
    case if_:
        return "IF";
    case then_:
        return "THEN";
    case endif_:
        return "ENDIF";
    case while_:
        return "WHILE";
    case repeat_:
        return "REPEAT";
    case endwhile_:
        return "ENDWHILE";
    case eq_:
        return "=";
    case plus_:
        return "+";
    case minus_:
        return "-";
    case mult_:
        return "*";
    case div_:
        return "/";
    case eqeq_:
        return "==";
    case noteq_:
        return "!=";
    case lt_:
        return "<";
    case lteq_:
        return "<=";
    case gt_:
        return ">";
    case gteq_:
        return ">=";
    default:
        return "unknown";
    }
}

Token::Type Token::type_from_string(const std::string& str)
{
    using enum Type;

    // We only care about keywords for now
    if (str == "LABEL")
        return label_;
    if (str == "GOTO")
        return goto_;
    if (str == "PRINT")
        return print_;
    if (str == "INPUT")
        return input_;
    if (str == "LET")
        return let_;
    if (str == "IF")
        return if_;
    if (str == "THEN")
        return then_;
    if (str == "ENDIF")
        return endif_;
    if (str == "WHILE")
        return while_;
    if (str == "REPEAT")
        return repeat_;
    if (str == "ENDWHILE")
        return endwhile_;

    return identifier_;
}

bool Token::is_keyword(const Type type)
{
    using enum Type;

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

bool Token::is_comparison_operator(const Type type)
{
    using enum Type;

    switch (type)
    {
    case eqeq_:
    case noteq_:
    case lt_:
    case lteq_:
    case gt_:
    case gteq_:
        return true;
    default:
        return false;
    }
}
