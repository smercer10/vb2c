#include "vb2c/parser.h"
#include "vb2c/token.h"
#include <cstdlib>
#include <iostream>
#include <string>

void Parser::parse()
{
    std::cout << "PROGRAM\n";

    // Skip newlines before the first statement
    while (check_token(Token::Type::newline_))
    {
        next_token();
    }

    // Parse all statements until the end of the file
    while (!check_token(Token::Type::eof_))
    {
        statement();
    }

    // Check for any requested labels that were not declared
    for (const auto& label : requested_labels)
    {
        if (!declared_labels.contains(label))
        {
            abort("Undefined label \"" + label + "\"");
        }
    }
}

void Parser::statement() // NOLINT
{
    // Grammar: PRINT (string | expression)
    if (check_token(Token::Type::print_))
    {
        std::cout << "STATEMENT: PRINT\n";

        next_token();

        if (check_token(Token::Type::string_))
        {
            next_token();
        }
        else
        {
            expression();
        }
    }
    // Grammar: IF comparison THEN newline {statement} ENDIF
    else if (check_token(Token::Type::if_))
    {
        std::cout << "STATEMENT: IF\n";

        next_token();
        comparison();
        match(Token::Type::then_);
        newline();

        while (!check_token(Token::Type::endif_))
        {
            statement();
        }

        match(Token::Type::endif_);
    }
    // Grammar: WHILE comparison REPEAT newline {statement} ENDWHILE
    else if (check_token(Token::Type::while_))
    {
        std::cout << "STATEMENT: WHILE\n";

        next_token();
        comparison();
        match(Token::Type::repeat_);
        newline();

        while (!check_token(Token::Type::endwhile_))
        {
            statement();
        }

        match(Token::Type::endwhile_);
    }
    // Grammar: LABEL identifier
    else if (check_token(Token::Type::label_))
    {
        std::cout << "STATEMENT: LABEL\n";

        next_token();

        // A LABEL can only be declared once
        if (declared_labels.contains(current_token.value))
        {
            abort("Duplicate label \"" + current_token.value + "\"");
        }

        declared_labels.insert(current_token.value);

        match(Token::Type::identifier_);
    }
    // Grammar: GOTO identifier
    else if (check_token(Token::Type::goto_))
    {
        std::cout << "STATEMENT: GOTO\n";

        next_token();

        // GOTO statements can reference labels before they are declared
        requested_labels.insert(current_token.value);

        match(Token::Type::identifier_);
    }
    // Grammar: INPUT identifier
    else if (check_token(Token::Type::input_))
    {
        std::cout << "STATEMENT: INPUT\n";

        next_token();

        // INPUT statements implicitly (re)declare identifiers
        if (!identifiers.contains(current_token.value))
        {
            identifiers.insert(current_token.value);
        }

        match(Token::Type::identifier_);
    }
    // Grammar: LET identifier = expression
    else if (check_token(Token::Type::let_))
    {
        std::cout << "STATEMENT: LET\n";

        next_token();

        // Identifiers can be redeclared
        if (!identifiers.contains(current_token.value))
        {
            identifiers.insert(current_token.value);
        }

        match(Token::Type::identifier_);
        match(Token::Type::eq_);
        expression();
    }
    else
    {
        abort("Invalid statement at \"" + current_token.value + "\"");
    }

    newline();
}

// Grammar: expression (== | != | < | <= | > | >=) expression
void Parser::comparison()
{
    std::cout << "COMPARISON\n";

    expression();

    if (is_comparison_operator(current_token.type))
    {
        next_token();
        expression();
    }
    else
    {
        abort("Expected comparison operator, got \"" + current_token.value + "\"");
    }
}

// Grammar: expression {(+ | -) expression}
void Parser::expression()
{
    std::cout << "EXPRESSION\n";

    term();

    while (check_token(Token::Type::plus_) || check_token(Token::Type::minus_))
    {
        next_token();
        term();
    }
}

// Grammar: unary {(* | /) unary}
void Parser::term()
{
    std::cout << "TERM\n";

    unary();

    while (check_token(Token::Type::mult_) || check_token(Token::Type::div_))
    {
        next_token();
        unary();
    }
}

// Grammar: [+ | -] primary
void Parser::unary()
{
    std::cout << "UNARY\n";

    if (check_token(Token::Type::plus_) || check_token(Token::Type::minus_))
    {
        next_token();
    }

    primary();
}

// Grammar: number | identifier
void Parser::primary()
{
    if (check_token(Token::Type::number_))
    {
        std::cout << "PRIMARY: " << current_token.value << "\n";
        next_token();
    }
    else if (check_token(Token::Type::identifier_))
    {
        // Variables must be declared before use
        if (!identifiers.contains(current_token.value))
        {
            abort("Variable referenced before assignment \"" + current_token.value + "\"");
        }

        std::cout << "PRIMARY: " << current_token.value << "\n";
        next_token();
    }
    else
    {
        abort("Unexpected token \"" + current_token.value + "\"");
    }
}

void Parser::newline()
{
    std::cout << "NEWLINE\n";

    // Require at least one newline
    match(Token::Type::newline_);

    // But extra newlines are allowed
    while (check_token(Token::Type::newline_))
    {
        next_token();
    }
}

void Parser::abort(const std::string& msg)
{
    std::cerr << "Parser error: " + msg + "\n";

    std::exit(EXIT_FAILURE);
}

bool Parser::check_token(const Token::Type type) const
{
    return type == current_token.type;
}

bool Parser::check_peek(const Token::Type type) const
{
    return type == peek_token.type;
}

void Parser::match(const Token::Type type)
{
    if (!check_token(type))
    {
        Token::Token expected;
        expected.type = type;
        abort("Expected " + expected.type_as_string() + ", got \"" + current_token.value + "\"");
    }
    next_token();
}

void Parser::next_token()
{
    current_token = peek_token;
    peek_token = lexer.get_token();
}
