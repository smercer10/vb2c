#pragma once
#include <string>

enum class TokenType
{
    // Enumerators are capitalized to avoid conflict with C++ keywords

    // Special tokens
    EOFILE, // Can't use EOF because it's a macro in cstdio
    NL,
    NUM,
    ID,
    STR,
    // Tiny BASIC Keywords
    LABEL,
    GOTO,
    PRINT,
    INPUT,
    LET,
    IF,
    THEN,
    ENDIF,
    WHILE,
    REPEAT,
    ENDWHILE,
    // Operators
    EQ,
    PLUS,
    MINUS,
    MULT,
    DIV,
    EQEQ,
    NOTEQ,
    LT,
    LTEQ,
    GT,
    GTEQ,
};

class Token
{
public:
    std::string text;
    TokenType type;

    std::string get_type_as_string();
};
