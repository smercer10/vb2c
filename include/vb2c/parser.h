#pragma once
#include "vb2c/lexer.h"
#include "vb2c/token.h"
#include "vb2c/emitter.h"
#include <string>
#include <unordered_set>

class parser
{
public:
    explicit parser(lexer& lexer, emitter& emitter)
        : lexer_{lexer},
          emitter_{emitter},
          has_print_statement_{false},
          has_input_statement_{false}
    {
        token::token init;
        init.type = token::tkn_type::tkn_eof;
        init.value = "";

        current_token_ = init;
        peek_token_ = init;
        next_token();
        next_token();
    }

    // Grammar: {statement}
    void program();

private:
    lexer& lexer_;
    emitter& emitter_;
    token::token current_token_;
    token::token peek_token_;
    bool has_print_statement_;
    bool has_input_statement_;
    std::unordered_set<std::string> declared_identifiers_;
    std::unordered_set<std::string> declared_labels_;
    std::unordered_set<std::string> requested_labels_;

    // Grammar: print_statement | if_statement | while_statement | label_statement |
    //          goto_statement | input_statement | let_statement
    void statement();

    // Grammar: PRINT (string | expression)
    void print_statement();

    // Grammar: IF comparison THEN newline {statement} ENDIF
    void if_statement();

    // Grammar: WHILE comparison REPEAT newline {statement} ENDWHILE
    void while_statement();

    // Grammar: LABEL identifier
    void label_statement();

    // Grammar: GOTO identifier
    void goto_statement();

    // Grammar: INPUT identifier
    void input_statement();

    // Grammar: LET identifier = expression
    void let_statement();

    // Grammar: expression (== | != | < | <= | > | >=) expression
    void comparison();

    // Grammar: expression {(+ | -) expression}
    void expression();

    // Grammar: unary {(* | /) unary}
    void term();

    // Grammar: [+ | -] primary
    void unary();

    // Grammar: number | identifier
    void primary();

    // Grammar: {newline}
    void newline();

    static void abort(const std::string& msg);

    // Aborts if it doesn't match
    void match_current_token(token::tkn_type type);

    bool check_current_token(token::tkn_type type) const;
    bool check_peek_token(token::tkn_type type) const;
    void next_token();
};
