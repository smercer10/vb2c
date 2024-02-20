#pragma once
#include "vb2c/lexer.h"
#include "vb2c/token.h"
#include <string>
#include <unordered_set>

class Parser
{
public:
    explicit Parser(Lexer& lexer)
        : lexer{lexer}
    {
        Token::Token init;
        init.type = Token::Type::eof_;
        init.value = "";

        current_token = init;
        peek_token = init;
        next_token();
        next_token();
    }

    void parse();

private:
    Lexer& lexer;
    Token::Token current_token;
    Token::Token peek_token;
    std::unordered_set<std::string> identifiers;
    std::unordered_set<std::string> declared_labels;
    std::unordered_set<std::string> requested_labels;

    void statement();
    void comparison();
    void expression();
    void term();
    void unary();
    void primary();
    void newline();
    static void abort(const std::string& msg);
    bool check_token(Token::Type type) const;
    bool check_peek(Token::Type type) const;
    void match(Token::Type type);
    void next_token();
};
