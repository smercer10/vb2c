#include "vb2c/lexer.h"
#include "vb2c/token.h"
#include <cctype>
#include <cstdlib>
#include <iostream>

Token Lexer::get_token()
{
    skip_whitespace();
    skip_comment();

    Token token;

    using enum TokenType;

    switch (curr_char)
    {
    case '\0':
        token.value = curr_char;
        token.type = eof_;
        break;
    case '\n':
        token.value = curr_char;
        token.type = newline_;
        ++line_num;
        col_num = 1;
        break;
    case '"':
    {
        std::string chars;
        std::string illegal_chars{"\r\n\t\\%"};

        // Get all characters until the next quotation mark
        next_char();
        while (curr_char != '"')
        {
            // Avoid issues with string formatting in emitted C code
            if (illegal_chars.find(curr_char) != std::string::npos)
            {
                abort("Illegal character in string");
            }

            chars += curr_char;
            next_char();
        }

        token.value = chars;
        token.type = string_;
        break;
    }
    case '0' ... '9':
    {
        std::string chars;

        chars += curr_char;

        // Get all consecutive digits
        while (std::isdigit(peek()))
        {
            next_char();
            chars += curr_char;
        }

        // Check for decimal part
        if (peek() == '.')
        {
            next_char();
            chars += curr_char;

            // Must have at least one digit after the decimal point
            if (!std::isdigit(peek()))
            {
                abort("Expected digit after decimal point");
            }

            // Get all consecutive digits after the decimal point
            while (std::isdigit(peek()))
            {
                next_char();
                chars += curr_char;
            }
        }

        token.value = chars;
        token.type = number_;
        break;
    }
    case 'A' ... 'Z':
    case 'a' ... 'z':
    {
        std::string chars;

        chars += curr_char;

        // Get all consecutive alphanumeric characters and underscores
        while (std::isalnum(peek()) || peek() == '_')
        {
            next_char();
            chars += curr_char;
        }

        // Check if the token is a keyword
        // Using type_from_string directly would work right now, but this is more future-proof
        if (Token::is_keyword(Token::type_from_string(chars)))
        {
            token.type = Token::type_from_string(chars);
            token.value = chars;
        }
        // Otherwise, it's an identifier
        else
        {
            token.type = identifier_;
            token.value = chars;
        }
        break;
    }

    case '+':
        token.value = curr_char;
        token.type = plus_;
        break;
    case '-':
        token.value = curr_char;
        token.type = minus_;
        break;
    case '*':
        token.value = curr_char;
        token.type = mult_;
        break;
    case '/':
        token.value = curr_char;
        token.type = div_;
        break;
    case '=':
        if (peek() == '=')
        {
            token.value = "==";
            token.type = eqeq_;
            next_char();
        }
        else
        {
            token.value = curr_char;
            token.type = eq_;
        }
        break;
    case '!':
        if (peek() == '=')
        {
            token.value = "!=";
            token.type = noteq_;
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
            token.value = "<=";
            token.type = lteq_;
            next_char();
        }
        else
        {
            token.value = curr_char;
            token.type = lt_;
        }
        break;
    case '>':
        if (peek() == '=')
        {
            token.value = ">=";
            token.type = gteq_;
            next_char();
        }
        else
        {
            token.value = curr_char;
            token.type = gt_;
        }
        break;
    default:
        abort("Unknown token \"" + std::string(1, curr_char) + "\"");
        next_char();
    }

    next_char();

    return token;
}

int Lexer::get_line_num()
{
    return line_num;
}

void Lexer::abort(std::string msg)
{
    std::cerr << "Lexer error: " + msg
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
