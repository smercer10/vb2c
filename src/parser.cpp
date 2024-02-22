// ReSharper disable CppDFAEndlessLoop
// ReSharper disable CppDFAUnreachableCode
#include "vb2c/parser.h"
#include "vb2c/token.h"
#include <iostream>
#include <string>

void parser::program()
{
    emitter_.emit_header_line("#include <stdlib.h>");
    emitter_.emit_header_line("int main(void){");

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

    // We only need to include stdio.h if we have print or input statements
    if (has_print_statement_ || has_input_statement_)
    {
        emitter_.header_prepend("#include <stdio.h>");
    }

    emitter_.emit_line("return EXIT_SUCCESS;");
    emitter_.emit_line("}");

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
        has_print_statement_ = true;

        print_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_if))
    {
        if_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_while))
    {
        while_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_label))
    {
        label_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_goto))
    {
        goto_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_input))
    {
        has_input_statement_ = true;

        input_statement();
    }
    else if (check_current_token(token::tkn_type::tkn_let))
    {
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
        emitter_.emit_line("printf(\"" + current_token_.value + "\\n\");");
        next_token();
    }
    else
    {
        emitter_.emit(std::string("printf(\"%") + ".2f\\n\",");
        expression();
        emitter_.emit_line(");");
    }
}

void parser::if_statement() // NOLINT
{
    next_token();
    emitter_.emit("if(");

    comparison();

    match_current_token(token::tkn_type::tkn_then);
    newline();
    emitter_.emit_line("){");

    while (!check_current_token(token::tkn_type::tkn_endif))
    {
        statement();
    }

    match_current_token(token::tkn_type::tkn_endif);
    emitter_.emit_line("}");
}

void parser::while_statement() // NOLINT
{
    next_token();
    emitter_.emit("while(");

    comparison();

    match_current_token(token::tkn_type::tkn_repeat);
    newline();
    emitter_.emit_line("){");

    while (!check_current_token(token::tkn_type::tkn_endwhile))
    {
        statement();
    }

    match_current_token(token::tkn_type::tkn_endwhile);
    emitter_.emit_line("}");
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

    emitter_.emit_line(current_token_.value + ":");

    match_current_token(token::tkn_type::tkn_identifier);
}

void parser::goto_statement()
{
    next_token();

    // Goto statements can reference labels before they are declared
    requested_labels_.insert(current_token_.value);

    emitter_.emit_line("goto " + current_token_.value + ";");

    match_current_token(token::tkn_type::tkn_identifier);
}

void parser::input_statement()
{
    next_token();

    // Input statements implicitly (re)declare identifiers
    if (!declared_identifiers_.contains(current_token_.value))
    {
        declared_identifiers_.insert(current_token_.value);
        // Follows old C convention of declaring all variables at the top of the function
        emitter_.emit_header_line("float " + current_token_.value + ";");
    }

    // Boilerplate C code to handle invalid input
    emitter_.emit_line("if(scanf(\"%f\",&" + current_token_.value + ")==EOF){");
    emitter_.emit_line(R"(printf("Error: Invalid input\n");)");
    emitter_.emit_line("exit(EXIT_FAILURE);");
    emitter_.emit_line("}");

    match_current_token(token::tkn_type::tkn_identifier);
}

void parser::let_statement()
{
    next_token();

    // Identifiers can be redeclared
    if (!declared_identifiers_.contains(current_token_.value))
    {
        declared_identifiers_.insert(current_token_.value);
        // Follows old C convention of declaring all variables at the top of the function
        emitter_.emit_header_line("float " + current_token_.value + ";");
    }

    emitter_.emit(current_token_.value + "=");

    match_current_token(token::tkn_type::tkn_identifier);
    match_current_token(token::tkn_type::tkn_eq);

    expression();

    emitter_.emit_line(";");
}

void parser::comparison()
{
    expression();

    if (is_comparison_op(current_token_.type))
    {
        emitter_.emit(current_token_.value);
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
    term();

    while (check_current_token(token::tkn_type::tkn_plus) || check_current_token(token::tkn_type::tkn_minus))
    {
        emitter_.emit(current_token_.value);
        next_token();
        term();
    }
}

void parser::term()
{
    unary();

    while (check_current_token(token::tkn_type::tkn_mult) || check_current_token(token::tkn_type::tkn_div))
    {
        emitter_.emit(current_token_.value);
        next_token();
        unary();
    }
}

void parser::unary()
{
    if (check_current_token(token::tkn_type::tkn_plus) || check_current_token(token::tkn_type::tkn_minus))
    {
        emitter_.emit(current_token_.value);
        next_token();
    }

    primary();
}

void parser::primary()
{
    if (check_current_token(token::tkn_type::tkn_number))
    {
        emitter_.emit(current_token_.value);
        next_token();
    }
    else if (check_current_token(token::tkn_type::tkn_identifier))
    {
        // Variables must be declared before use
        if (!declared_identifiers_.contains(current_token_.value))
        {
            abort("Variable referenced before assignment \"" + current_token_.value + "\"");
        }

        emitter_.emit(current_token_.value);
        next_token();
    }
    else
    {
        abort("Unexpected token \"" + current_token_.value + "\"");
    }
}

void parser::newline()
{
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
