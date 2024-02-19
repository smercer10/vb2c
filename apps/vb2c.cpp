#include "vb2c/lexer.h"
#include "vb2c/parser.h"
#include "vb2c/token.h"
#include <cstdlib>
#include <iostream>

int main()
{
    std::string source = "LET foo = bar * 3 + 2"
                         "IF foo > 0 THEN      "
                         "  PRINT \"yes!\"     "
                         "ENDIF                ";

    Lexer lexer(source);
    Parser parser(lexer);

    parser.parse();

    std::cout << "Parsing complete.\n";

    return EXIT_SUCCESS;
}
