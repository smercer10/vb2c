#include "vb2c/parser.h"
#include "vb2c/token.h"
#include <cstdlib>
#include <iostream>
#include <string>

void Parser::parse()
{
    std::cout << "PROGRAM\n";

    // Skip newlines before the first statement
    while (check_token(TokenType::newline_))
    {
        next_token();
    }

    // Parse all statements until the end of the file
    while (!check_token(TokenType::eof_))
    {
        statement();
    }

    // Check for any requested labels that were not declared
    for (const auto &label : requested_labels)
    {
        if (!declared_labels.contains(label))
        {
            abort("Undefined label \"" + label + "\"");
        }
    }
}

void Parser::statement()
{
    // Grammar: PRINT (string | expression)
    if (check_token(TokenType::print_))
    {
        std::cout << "STATEMENT: PRINT\n";

        next_token();

        if (check_token(TokenType::string_))
        {
            next_token();
        }
        else
        {
            expression();
        }
    }
    // Grammar: IF comparison THEN newline {statement} ENDIF
    else if (check_token(TokenType::if_))
    {
        std::cout << "STATEMENT: IF\n";

        next_token();
        comparison();
        match(TokenType::then_);
        newline();

        while (!check_token(TokenType::endif_))
        {
            statement();
        }

        match(TokenType::endif_);
    }
    // Grammar: WHILE comparison REPEAT newline {statement} ENDWHILE
    else if (check_token(TokenType::while_))
    {
        std::cout << "STATEMENT: WHILE\n";

        next_token();
        comparison();
        match(TokenType::repeat_);
        newline();

        while (!check_token(TokenType::endwhile_))
        {
            statement();
        }

        match(TokenType::endwhile_);
    }
    // Grammar: LABEL identifier
    else if (check_token(TokenType::label_))
    {
        std::cout << "STATEMENT: LABEL\n";

        next_token();

        // A LABEL can only be declared once
        if (declared_labels.contains(current_token.value))
        {
            abort("Duplicate label \"" + current_token.value + "\"");
        }

        declared_labels.insert(current_token.value);

        match(TokenType::identifier_);
    }
    // Grammar: GOTO identifier
    else if (check_token(TokenType::goto_))
    {
        std::cout << "STATEMENT: GOTO\n";

        next_token();

        // GOTO statements can reference labels before they are declared
        requested_labels.insert(current_token.value);

        match(TokenType::identifier_);
    }
    // Grammar: INPUT identifier
    else if (check_token(TokenType::input_))
    {
        std::cout << "STATEMENT: INPUT\n";

        next_token();

        // INPUT statements implicitly (re)declare identifiers
        if (!identifiers.contains(current_token.value))
        {
            identifiers.insert(current_token.value);
        }

        match(TokenType::identifier_);
    }
    // Grammar: LET identifier = expression
    else if (check_token(TokenType::let_))
    {
        std::cout << "STATEMENT: LET\n";

        next_token();

        // Identifiers can be redeclared
        if (!identifiers.contains(current_token.value))
        {
            identifiers.insert(current_token.value);
        }

        match(TokenType::identifier_);
        match(TokenType::eq_);
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

    if (Token::is_comparison_operator(current_token.type))
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

    while (check_token(TokenType::plus_) || check_token(TokenType::minus_))
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

    while (check_token(TokenType::mult_) || check_token(TokenType::div_))
    {
        next_token();
        unary();
    }
}

// Grammar: [+ | -] primary
void Parser::unary()
{
    std::cout << "UNARY\n";

    if (check_token(TokenType::plus_) || check_token(TokenType::minus_))
    {
        next_token();
    }

    primary();
}

// Grammar: number | identifier
void Parser::primary()
{
    if (check_token(TokenType::number_))
    {
        std::cout << "PRIMARY: " << current_token.value << "\n";
        next_token();
    }
    else if (check_token(TokenType::identifier_))
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
    std ::cout << "NEWLINE\n";

    // Require at least one newline
    match(TokenType::newline_);

    // But extra newlines are allowed
    while (check_token(TokenType::newline_))
    {
        next_token();
    }
}

void Parser::abort(std::string msg)
{
    std::cerr << "Parser error: " + msg + "\n";

    std::exit(EXIT_FAILURE);
}

bool Parser::check_token(TokenType type)
{
    return type == current_token.type;
}

bool Parser::check_peek(TokenType type)
{
    return type == peek_token.type;
}

// Match current_token with the given type and advance to the next token
void Parser::match(TokenType type)
{
    if (!check_token(type))
    {
        Token expected;
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
