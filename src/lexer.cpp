#include "vb2c/lexer.h"
#include "vb2c/token.h"
#include <cctype>
#include <iostream>
#include <string>

token::token lexer::get_token()
{
    skip_whitespace();
    skip_comment();

    token::token token;

    using enum token::tkn_type;

    if (curr_char_ == '\0')
    {
        token.value = curr_char_;
        token.type = tkn_eof;
    }
    else if (curr_char_ == '\n')
    {
        token.value = curr_char_;
        token.type = tkn_newline;
        ++line_num_;
        col_num_ = 1;
    }
    else if (curr_char_ == '"')
    {
        process_string(token);
    }
    else if (std::isdigit(curr_char_))
    {
        process_number(token);
    }
    // Identifiers can start with a letter or underscore
    else if (std::isalpha(curr_char_) || curr_char_ == '_')
    {
        process_identifier(token);
    }
    else if (curr_char_ == '+')
    {
        token.value = curr_char_;
        token.type = tkn_plus;
    }
    else if (curr_char_ == '-')
    {
        token.value = curr_char_;
        token.type = tkn_minus;
    }
    else if (curr_char_ == '*')
    {
        token.value = curr_char_;
        token.type = tkn_mult;
    }
    else if (curr_char_ == '/')
    {
        token.value = curr_char_;
        token.type = tkn_div;
    }
    else if (curr_char_ == '=')
    {
        if (peek() == '=')
        {
            token.value = "==";
            token.type = tkn_eqeq;
            next_char();
        }
        else
        {
            token.value = curr_char_;
            token.type = tkn_eq;
        }
    }
    else if (curr_char_ == '!')
    {
        if (peek() == '=')
        {
            token.value = "!=";
            token.type = tkn_noteq;
            next_char();
        }
        else
        {
            abort(R"(Expected "!=", got "!)" + std::string(1, peek()) + "\"");
        }
    }
    else if (curr_char_ == '<')
    {
        if (peek() == '=')
        {
            token.value = "<=";
            token.type = tkn_lteq;
            next_char();
        }
        else
        {
            token.value = curr_char_;
            token.type = tkn_lt;
        }
    }
    else if (curr_char_ == '>')
    {
        if (peek() == '=')
        {
            token.value = ">=";
            token.type = tkn_gteq;
            next_char();
        }
        else
        {
            token.value = curr_char_;
            token.type = tkn_gt;
        }
    }
    else
    {
        abort("Unknown token \"" + std::string(1, curr_char_) + "\"");
        next_char();
    }

    next_char();

    return token;
}

void lexer::process_string(token::token& token)
{
    std::string chars;
    const std::string illegal_chars{"\r\n\t\\%"};

    // Get all characters until the next quotation mark
    next_char();
    while (curr_char_ != '"')
    {
        // Prevents issues with string formatting in emitted C code
        if (illegal_chars.find(curr_char_) != std::string::npos)
        {
            abort("Illegal character in string");
        }

        chars += curr_char_;
        next_char();
    }

    token.value = chars;
    token.type = token::tkn_type::tkn_string;
}

void lexer::process_number(token::token& token)
{
    std::string chars;

    chars += curr_char_;

    // Get all consecutive digits
    while (std::isdigit(peek()))
    {
        next_char();
        chars += curr_char_;
    }

    // Check for decimal part
    if (peek() == '.')
    {
        next_char();
        chars += curr_char_;

        // Must have at least one digit after the decimal point
        if (!std::isdigit(peek()))
        {
            abort("Expected digit after decimal point");
        }

        // Get all consecutive digits after the decimal point
        while (std::isdigit(peek()))
        {
            next_char();
            chars += curr_char_;
        }
    }

    token.value = chars;
    token.type = token::tkn_type::tkn_number;
}

void lexer::process_identifier(token::token& token)
{
    std::string chars;

    chars += curr_char_;

    // Get all consecutive alphanumeric characters and underscores
    while (std::isalnum(peek()) || peek() == '_')
    {
        next_char();
        chars += curr_char_;
    }

    // Using type_from_string directly would work right now, but this is more future-proof
    if (token::is_keyword(token::type_from_string(chars)))
    {
        token.type = token::type_from_string(chars);
        token.value = chars;
    }
    else
    {
        token.type = token::tkn_type::tkn_identifier;
        token.value = chars;
    }
}


void lexer::abort(const std::string& msg) const
{
    std::cerr << "Lexer error: " + msg
        << "\nLn " << line_num_ << ", Col " << col_num_ - 1 << "\n";

    std::exit(1);
}

void lexer::next_char()
{
    ++curr_pos_;
    ++col_num_;
    curr_char_ = (curr_pos_ >= source_.length()) ? '\0' : source_[curr_pos_];
}

char lexer::peek() const
{
    return (curr_pos_ + 1 >= source_.length()) ? '\0' : source_[curr_pos_ + 1];
}

void lexer::skip_whitespace()
{
    while (curr_char_ == ' ' || curr_char_ == '\t' || curr_char_ == '\r')
    {
        next_char();
    }
}

void lexer::skip_comment()
{
    if (curr_char_ == '#')
    {
        while (curr_char_ != '\n')
        {
            next_char();
        }
    }
}
