#include "tb2c/lexer.h"
#include "tb2c/token.h"
#include <iostream>
#include <cstdlib>
#include <cctype>

Token Lexer::get_token()
{
    skip_whitespace();

    Token token;

    using enum TokenType;

    switch (curr_char)
    {
    case '\0':
        token.text = curr_char;
        token.type = EOFILE;
        break;
    case '\n':
        token.text = curr_char;
        token.type = NL;
        ++line_num;
        col_num = 1;
        break;
    case '+':
        token.text = curr_char;
        token.type = PLUS;
        break;
    case '-':
        token.text = curr_char;
        token.type = MINUS;
        break;
    case '*':
        token.text = curr_char;
        token.type = MULT;
        break;
    case '/':
        token.text = curr_char;
        token.type = DIV;
        break;
    case '=':
        if (peek() == '=')
        {
            token.text = "==";
            token.type = EQEQ;
            next_char();
        }
        else
        {
            token.text = curr_char;
            token.type = EQ;
        }
        break;
    case '!':
        if (peek() == '=')
        {
            token.text = "!=";
            token.type = NOTEQ;
            next_char();
        }
        else
        {
            abort("Expected \"!=\", got \"!" + std::string(1, peek()) + "\"");
        }
        break;
    default:
        abort("Unknown token \"" + std::string(1, curr_char) + "\"");
        next_char();
    }

    next_char();

    return token;
}

void Lexer::abort(std::string message)
{
    std::cerr << "Lexer error: " + message
              << "\nLn " << line_num << ", Col " << col_num - 1 << "\n";

    std::exit(EXIT_FAILURE);
}

void Lexer::next_char()
{
    ++curr_pos;
    ++col_num;
    curr_char = (curr_pos >= source.length()) ? '\0' : source[curr_pos];
}

char Lexer::peek()
{
    return (curr_pos + 1 >= source.length()) ? '\0' : source[curr_pos + 1];
}

void Lexer::skip_whitespace()
{
    while (curr_char == ' ' || curr_char == '\t' || curr_char == '\r')
    {
        next_char();
    }
}
