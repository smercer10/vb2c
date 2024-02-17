#include "tb2c/lexer.h"
#include <iostream>

void Lexer::abort()
{
    std::cout << "Something went wrong!\n";
}

void Lexer::next_char()
{
    ++curr_pos;
    curr_char = (curr_pos >= source.length()) ? '\0' : source[curr_pos];
}

char Lexer::peek()
{
    return (curr_pos + 1 >= source.length()) ? '\0' : source[curr_pos + 1];
}
