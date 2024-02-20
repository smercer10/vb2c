#include "vb2c/lexer.h"
#include "vb2c/token.h"
#include <cctype>
#include <iostream>
#include <string>

Token::Token Lexer::get_token()
{
    skip_whitespace();
    skip_comment();

    Token::Token token;

    using enum Token::Type;

    if (curr_char == '\0')
    {
        token.value = curr_char;
        token.type = eof_;
    }
    else if (curr_char == '\n')
    {
        token.value = curr_char;
        token.type = newline_;
        ++line_num;
        col_num = 1;
    }
    else if (curr_char == '"')
    {
        std::string chars;
        std::string illegal_chars{"\r\n\t\\%"};

        // Get all characters until the next quotation mark
        next_char();
        while (curr_char != '"')
        {
            // Prevents issues with string formatting in emitted C code
            if (illegal_chars.find(curr_char) != std::string::npos)
            {
                abort("Illegal character in string");
            }

            chars += curr_char;
            next_char();
        }

        token.value = chars;
        token.type = string_;
    }
    else if (std::isdigit(curr_char))
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
    }
    // Identifiers can start with a letter or underscore
    else if (std::isalpha(curr_char) || curr_char == '_')
    {
        std::string chars;

        chars += curr_char;

        // Get all consecutive alphanumeric characters and underscores
        while (std::isalnum(peek()) || peek() == '_')
        {
            next_char();
            chars += curr_char;
        }

        // Using type_from_string directly would work right now, but this is more future-proof
        if (Token::is_keyword(Token::type_from_string(chars)))
        {
            token.type = Token::type_from_string(chars);
            token.value = chars;
        }
        else
        {
            token.type = identifier_;
            token.value = chars;
        }
    }
    else if (curr_char == '+')
    {
        token.value = curr_char;
        token.type = plus_;
    }
    else if (curr_char == '-')
    {
        token.value = curr_char;
        token.type = minus_;
    }
    else if (curr_char == '*')
    {
        token.value = curr_char;
        token.type = mult_;
    }
    else if (curr_char == '/')
    {
        token.value = curr_char;
        token.type = div_;
    }
    else if (curr_char == '=')
    {
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
    }
    else if (curr_char == '!')
    {
        if (peek() == '=')
        {
            token.value = "!=";
            token.type = noteq_;
            next_char();
        }
        else
        {
            abort(R"(Expected "!=", got "!)" + std::string(1, peek()) + "\"");
        }
    }
    else if (curr_char == '<')
    {
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
    }
    else if (curr_char == '>')
    {
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
    }
    else
    {
        abort("Unknown token \"" + std::string(1, curr_char) + "\"");
        next_char();
    }

    next_char();

    return token;
}

void Lexer::abort(const std::string& msg) const
{
    std::cerr << "Lexer error: " + msg
        << "\nLn " << line_num << ", Col " << col_num - 1 << "\n";

    std::exit(1);
}

void Lexer::next_char()
{
    ++curr_pos;
    ++col_num;
    curr_char = (curr_pos >= source.length()) ? '\0' : source[curr_pos];
}

char Lexer::peek() const
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
