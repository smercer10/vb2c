#include "tb2c/lexer.h"
#include "tb2c/token.h"
#include <cstdlib>
#include <iostream>

int main()
{
    Lexer lexer("IF + -123 foo * THEN /");

    Token token{lexer.get_token()};

    while (token.type != TokenType::eof_)
    {
        std::cerr << token.type_as_string() << "\n";
        token = lexer.get_token();
    }

    return EXIT_SUCCESS;
}
