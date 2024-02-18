#include "tb2c/lexer.h"
#include "tb2c/token.h"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>

Token Lexer::get_token()
{
    skip_whitespace();
    skip_comment();

    Token token;

    using enum TokenType;

    switch (curr_char)
    {
    case '"':
    {
        std::string text;
        std::string illegal_chars{"\r\n\t\\%"}; // Avoid issues with emitted C code

        next_char();
        while (curr_char != '"')
        {
            if (illegal_chars.find(curr_char) != std::string::npos)
            {
                abort("Illegal character in string");
            }

            text += curr_char;
            next_char();
        }

        token.text = text;
        token.type = STR;
        break;
    }
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
    case '<':
        if (peek() == '=')
        {
            token.text = "<=";
            token.type = LTEQ;
            next_char();
        }
        else
        {
            token.text = curr_char;
            token.type = LT;
        }
        break;
    case '>':
        if (peek() == '=')
        {
            token.text = ">=";
            token.type = GTEQ;
            next_char();
        }
        else
        {
            token.text = curr_char;
            token.type = GT;
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

void Lexer::skip_comment()
{
    if (curr_char == '#')
    {
        while (curr_char != '\n')
        {
            next_char();
        }
    }
}
