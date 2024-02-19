#pragma once
#include "vb2c/lexer.h"
#include "vb2c/token.h"
#include <string>

class Parser
{
public:
    Parser(Lexer &lexer)
        : lexer{lexer}
    {
        Token init;
        init.type = TokenType::eof_;
        init.value = "";

        current_token = init;
        peek_token = init;
        next_token();
        next_token();
    }

    void parse();

private:
    Lexer &lexer;
    Token current_token;
    Token peek_token;

    void statement();
    void comparison();
    void expression();
    void term();
    void unary();
    void primary();
    void newline();
    void abort(std::string msg);
    bool check_token(TokenType type);
    bool check_peek(TokenType type);
    void match(TokenType type);
    void next_token();
};
