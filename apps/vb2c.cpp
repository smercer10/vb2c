#include "vb2c/lexer.h"
#include "vb2c/parser.h"
#include "vb2c/token.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    std::ifstream source_file("../../source.vbas");

    if (!source_file.is_open())
    {
        std::cerr << "Failed to open source file.\n";
        return EXIT_FAILURE;
    }

    std::stringstream buffer;
    buffer << source_file.rdbuf();
    std::string source = buffer.str();

    Lexer lexer(source);
    Parser parser(lexer);

    parser.parse();

    std::cout << "Parsing complete.\n";

    return EXIT_SUCCESS;
}
