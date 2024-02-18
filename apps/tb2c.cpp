#include <iostream>
#include "tb2c/lexer.h"
#include "tb2c/token.h"
#include <cstdlib>

int main()
{
    Lexer lexer("- */     +/");

    Token token = lexer.get_token();

    while (token.type != TokenType::EOFILE)
    {
        std::cout << token.get_type_as_string() << "\n";
        token = lexer.get_token();
    }

    return EXIT_SUCCESS;
}
