#include "vb2c/parser.h"
#include "vb2c/token.h"
#include <cstdlib>
#include <iostream>
#include <string>

void parser::program()
{
    std::cout << "PROGRAM\n";

    // Skip newlines before the first statement
    while (check_current_token(token::tkn_type::tkn_newline))
    {
        next_token();
    }

    // Parse all statements until the end of the file
    while (!check_current_token(token::tkn_type::tkn_eof))
    {
        statement();
    }

    // Check for any requested labels that were not declared
    for (const auto& label : requested_labels_)
    {
        if (!declared_labels_.contains(label))
        {
            abort("Undefined label \"" + label + "\"");
        }
    }
}

void parser::statement() // NOLINT
{
    if (check_current_token(token::tkn_type::tkn_print))
    {
        std::cout << "STATEMENT: PRINT\n";

        print_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_if))
    {
        std::cout << "STATEMENT: IF\n";

        if_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_while))
    {
        std::cout << "STATEMENT: WHILE\n";

        while_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_label))
    {
        std::cout << "STATEMENT: LABEL\n";

        label_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_goto))
    {
        std::cout << "STATEMENT: GOTO\n";

        goto_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_input))
    {
        std::cout << "STATEMENT: INPUT\n";

        input_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_let))
    {
        std::cout << "STATEMENT: LET\n";

        let_statement();
    }
    else
    {
        abort("Invalid statement at \"" + current_token_.value + "\"");
    }

    newline();
}

void parser::print_statement()
{
    next_token();

    if (check_current_token(token::tkn_type::tkn_string))
    {
        next_token();
    }
    else
    {
        expression();
    }
}

void parser::if_statement() // NOLINT
{
    next_token();
    comparison();
    match_current_token(token::tkn_type::tkn_then);
    newline();

    while (!check_current_token(token::tkn_type::tkn_endif))
    {
        statement();
    }

    match_current_token(token::tkn_type::tkn_endif);
}

void parser::while_statement() // NOLINT
{
    next_token();
    comparison();
    match_current_token(token::tkn_type::tkn_repeat);
    newline();

    while (!check_current_token(token::tkn_type::tkn_endwhile))
    {
        statement();
    }

    match_current_token(token::tkn_type::tkn_endwhile);
}

void parser::label_statement()
{
    next_token();

    // Labels can only be declared once
    if (declared_labels_.contains(current_token_.value))
    {
        abort("Duplicate label \"" + current_token_.value + "\"");
    }

    declared_labels_.insert(current_token_.value);

    match_current_token(token::tkn_type::tkn_identifier);
}

void parser::goto_statement()
{
    next_token();

    // Goto statements can reference labels before they are declared
    requested_labels_.insert(current_token_.value);

    match_current_token(token::tkn_type::tkn_identifier);
}

void parser::input_statement()
{
    next_token();

    // Input statements implicitly (re)declare identifiers
    if (!declared_identifiers_.contains(current_token_.value))
    {
        declared_identifiers_.insert(current_token_.value);
    }

    match_current_token(token::tkn_type::tkn_identifier);
}

void parser::let_statement()
{
    next_token();

    // Identifiers can be redeclared
    if (!declared_identifiers_.contains(current_token_.value))
    {
        declared_identifiers_.insert(current_token_.value);
    }

    match_current_token(token::tkn_type::tkn_identifier);
    match_current_token(token::tkn_type::tkn_eq);
    expression();
}

void parser::comparison()
{
    std::cout << "COMPARISON\n";

    expression();

    if (is_comparison_op(current_token_.type))
    {
        next_token();
        expression();
    }
    else
    {
        abort("Expected comparison operator, got \"" + current_token_.value + "\"");
    }
}

void parser::expression()
{
    std::cout << "EXPRESSION\n";

    term();

    while (check_current_token(token::tkn_type::tkn_plus) || check_current_token(token::tkn_type::tkn_minus))
    {
        next_token();
        term();
    }
}

void parser::term()
{
    std::cout << "TERM\n";

    unary();

    while (check_current_token(token::tkn_type::tkn_mult) || check_current_token(token::tkn_type::tkn_div))
    {
        next_token();
        unary();
    }
}

void parser::unary()
{
    std::cout << "UNARY\n";

    if (check_current_token(token::tkn_type::tkn_plus) || check_current_token(token::tkn_type::tkn_minus))
    {
        next_token();
    }

    primary();
}

void parser::primary()
{
    if (check_current_token(token::tkn_type::tkn_number))
    {
        std::cout << "PRIMARY: " << current_token_.value << "\n";
        next_token();
    }
    else if (check_current_token(token::tkn_type::tkn_identifier))
    {
        // Variables must be declared before use
        if (!declared_identifiers_.contains(current_token_.value))
        {
            abort("Variable referenced before assignment \"" + current_token_.value + "\"");
        }

        std::cout << "PRIMARY: " << current_token_.value << "\n";
        next_token();
    }
    else
    {
        abort("Unexpected token \"" + current_token_.value + "\"");
    }
}

void parser::newline()
{
    std::cout << "NEWLINE\n";

    // Require at least one newline
    match_current_token(token::tkn_type::tkn_newline);

    // But extra newlines are allowed
    while (check_current_token(token::tkn_type::tkn_newline))
    {
        next_token();
    }
}

void parser::abort(const std::string& msg)
{
    std::cerr << "Parser error: " + msg + "\n";

    std::exit(EXIT_FAILURE);
}

void parser::match_current_token(const token::tkn_type type)
{
    if (!check_current_token(type))
    {
        token::token expected;
        expected.type = type;
        abort("Expected " + expected.type_as_string() + ", got \"" + current_token_.value + "\"");
    }
    next_token();
}

bool parser::check_current_token(const token::tkn_type type) const
{
    return type == current_token_.type;
}

bool parser::check_peek_token(const token::tkn_type type) const
{
    return type == peek_token_.type;
}

void parser::next_token()
{
    current_token_ = peek_token_;
    peek_token_ = lexer_.get_token();
}
