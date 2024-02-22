#include "vb2c/token.h"
#include <string>

std::string token::token::type_as_string() const
{
    using enum tkn_type;

    switch (type)
    {
    case tkn_eof:
        return "EOF";
    case tkn_newline:
        return "newline";
    case tkn_number:
        return "number";
    case tkn_identifier:
        return "identifier";
    case tkn_string:
        return "string";
    case tkn_label:
        return "LABEL";
    case tkn_goto:
        return "GOTO";
    case tkn_print:
        return "PRINT";
    case tkn_input:
        return "INPUT";
    case tkn_let:
        return "LET";
    case tkn_if:
        return "IF";
    case tkn_then:
        return "THEN";
    case tkn_endif:
        return "ENDIF";
    case tkn_while:
        return "WHILE";
    case tkn_repeat:
        return "REPEAT";
    case tkn_endwhile:
        return "ENDWHILE";
    case tkn_eq:
        return "=";
    case tkn_plus:
        return "+";
    case tkn_minus:
        return "-";
    case tkn_mult:
        return "*";
    case tkn_div:
        return "/";
    case tkn_eqeq:
        return "==";
    case tkn_noteq:
        return "!=";
    case tkn_lt:
        return "<";
    case tkn_lteq:
        return "<=";
    case tkn_gt:
        return ">";
    case tkn_gteq:
        return ">=";
    default:
        return "unknown";
    }
}

token::tkn_type token::type_from_string(const std::string &str)
{
    using enum tkn_type;

    // We only care about keywords for now
    if (str == "LABEL")
        return tkn_label;
    if (str == "GOTO")
        return tkn_goto;
    if (str == "PRINT")
        return tkn_print;
    if (str == "INPUT")
        return tkn_input;
    if (str == "LET")
        return tkn_let;
    if (str == "IF")
        return tkn_if;
    if (str == "THEN")
        return tkn_then;
    if (str == "ENDIF")
        return tkn_endif;
    if (str == "WHILE")
        return tkn_while;
    if (str == "REPEAT")
        return tkn_repeat;
    if (str == "ENDWHILE")
        return tkn_endwhile;

    return tkn_identifier;
}

bool token::is_keyword(const tkn_type type)
{
    using enum tkn_type;

    switch (type)
    {
    case tkn_label:
    case tkn_goto:
    case tkn_print:
    case tkn_input:
    case tkn_let:
    case tkn_if:
    case tkn_then:
    case tkn_endif:
    case tkn_while:
    case tkn_repeat:
    case tkn_endwhile:
        return true;
    default:
        return false;
    }
}

bool token::is_comparison_op(const tkn_type type)
{
    using enum tkn_type;

    switch (type)
    {
    case tkn_eqeq:
    case tkn_noteq:
    case tkn_lt:
    case tkn_lteq:
    case tkn_gt:
    case tkn_gteq:
        return true;
    default:
        return false;
    }
}
