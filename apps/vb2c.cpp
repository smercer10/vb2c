#include "vb2c/lexer.h"
#include "vb2c/parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    std::ifstream source_file("../../source.vbas");

    if (!source_file.is_open())
    {
        std::cerr << "Failed to open source file.\n";

        return 1;
    }

    std::stringstream buffer;
    buffer << source_file.rdbuf();
    std::string source = buffer.str();

    lexer lexer(source);
    emitter emitter("output");
    parser parser(lexer, emitter);

    parser.program();
    emitter.write_file();

    std::cout << "Compilation completed with no errors.\n";

    return 0;
}
