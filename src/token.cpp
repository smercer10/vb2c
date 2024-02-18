#include "tb2c/token.h"

std::string Token::get_type_as_string()
{
    using enum TokenType;

    switch (type)
    {
    case EOFILE:
        return "EOFILE";
    case NL:
        return "NL";
    case NUM:
        return "NUM";
    case ID:
        return "ID";
    case STR:
        return "STR";
    case LABEL:
        return "LABEL";
    case GOTO:
        return "GOTO";
    case PRINT:
        return "PRINT";
    case INPUT:
        return "INPUT";
    case LET:
        return "LET";
    case IF:
        return "IF";
    case THEN:
        return "THEN";
    case ENDIF:
        return "ENDIF";
    case WHILE:
        return "WHILE";
    case REPEAT:
        return "REPEAT";
    case ENDWHILE:
        return "ENDWHILE";
    case EQ:
        return "EQ";
    case PLUS:
        return "PLUS";
    case MINUS:
        return "MINUS";
    case MULT:
        return "MULT";
    case DIV:
        return "DIV";
    case EQEQ:
        return "EQEQ";
    case NOTEQ:
        return "NOTEQ";
    case LT:
        return "LT";
    case LTEQ:
        return "LTEQ";
    case GT:
        return "GT";
    case GTEQ:
        return "GTEQ";
    default:
        return "UNKNOWN";
    }
}
