#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "vb2c/lexer.h"
#include "vb2c/parser.h"

int main(int argc, char *argv[])
{
    std::string source_path;
    std::string output_path;

    // Get file paths from command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "s:o:")) != -1)
    {
        switch (opt)
        {
        case 's':
            source_path = optarg;
            break;
        case 'o':
            output_path = optarg;
            break;
        default:
            std::cerr << "Invalid option.\n\n"
                      << "Usage: vb2c -s <source file path> [-o <output filepath>]\n";
            return 1;
        }
    }

    if (source_path.empty())
    {
        std::cerr << "Source file path is required.\n\n"
                  << "Usage: vb2c -s <source file path> [-o <output file path>]\n";
        return 1;
    }

    // Source file must exist
    std::ifstream source_file(source_path);
    if (!source_file.is_open())
    {
        std::cerr << "Failed to open source file.\n";
        return 1;
    }

    // Default output file is out.c
    if (output_path.empty())
    {
        output_path = "out.c";
    }

    std::stringstream buffer;
    buffer << source_file.rdbuf();
    std::string source = buffer.str();

    lexer lexer(source);
    emitter emitter(output_path);
    parser parser(lexer, emitter);

    parser.program();
    emitter.write_file();

    std::cout << "Compilation finished with no errors.\n";

    return 0;
}
