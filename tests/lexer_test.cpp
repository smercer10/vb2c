#include <gtest/gtest.h>
#include "tb2c/lexer.h"

TEST(Lexer, Peek)
{
    Lexer lexer("tb2c");
    EXPECT_EQ(lexer.peek(), 'b');

    lexer.next_char();
    EXPECT_EQ(lexer.peek(), '2');

    lexer.next_char();
    EXPECT_EQ(lexer.peek(), 'c');

    lexer.next_char();
    EXPECT_EQ(lexer.peek(), '\n');

    lexer.next_char();
    EXPECT_EQ(lexer.peek(), '\0');
}
