#include "vb2c/lexer.h"
#include <gtest/gtest.h>

TEST(LexerTest, Arithmetic)
{
    using enum TokenType;

    Lexer lexer("18 +   2.9-3  *4578 /   5.0");

    Token token{lexer.get_token()};
    ASSERT_EQ(token.type, number_);
    ASSERT_EQ(token.value, "18");

    token = lexer.get_token();
    ASSERT_EQ(token.type, plus_);
    ASSERT_EQ(token.value, "+");

    token = lexer.get_token();
    ASSERT_EQ(token.type, number_);
    ASSERT_EQ(token.value, "2.9");

    token = lexer.get_token();
    ASSERT_EQ(token.type, minus_);
    ASSERT_EQ(token.value, "-");

    token = lexer.get_token();
    ASSERT_EQ(token.type, number_);
    ASSERT_EQ(token.value, "3");

    token = lexer.get_token();
    ASSERT_EQ(token.type, mult_);
    ASSERT_EQ(token.value, "*");

    token = lexer.get_token();
    ASSERT_EQ(token.type, number_);
    ASSERT_EQ(token.value, "4578");

    token = lexer.get_token();
    ASSERT_EQ(token.type, div_);
    ASSERT_EQ(token.value, "/");

    token = lexer.get_token();
    ASSERT_EQ(token.type, number_);
    ASSERT_EQ(token.value, "5.0");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, eof_);
    ASSERT_EQ(token.value[0], '\0');
}

TEST(LexerTest, IfStatement)
{
    using enum TokenType;

    Lexer lexer("#  Check if a is equal to b   \n"
                " IF lemon==   GREEN_APPLE  THEN\n"
                "   PRINT    \"lemon is equal to GREEN_APPLE\"\n"
                "   GOTO   40\n"
                "ENDIF  ");

    Token token{lexer.get_token()};
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, if_);
    ASSERT_EQ(token.value, "IF");

    token = lexer.get_token();
    ASSERT_EQ(token.type, identifier_);
    ASSERT_EQ(token.value, "lemon");

    token = lexer.get_token();
    ASSERT_EQ(token.type, eqeq_);
    ASSERT_EQ(token.value, "==");

    token = lexer.get_token();
    ASSERT_EQ(token.type, identifier_);
    ASSERT_EQ(token.value, "GREEN_APPLE");

    token = lexer.get_token();
    ASSERT_EQ(token.type, then_);
    ASSERT_EQ(token.value, "THEN");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, print_);
    ASSERT_EQ(token.value, "PRINT");

    token = lexer.get_token();
    ASSERT_EQ(token.type, string_);
    ASSERT_EQ(token.value, "lemon is equal to GREEN_APPLE");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, goto_);
    ASSERT_EQ(token.value, "GOTO");

    token = lexer.get_token();
    ASSERT_EQ(token.type, number_);
    ASSERT_EQ(token.value, "40");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, endif_);
    ASSERT_EQ(token.value, "ENDIF");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, eof_);
    ASSERT_EQ(token.value[0], '\0');
}

TEST(LexerTest, WhileLoop)
{
    using enum TokenType;

    Lexer lexer(" INPUT i  \n"
                "WHILE  i   <10\n"
                "   PRINT i  \n  "
                "   LET i=   i +  1\n"
                "  ENDWHILE");

    Token token{lexer.get_token()};
    ASSERT_EQ(token.type, input_);
    ASSERT_EQ(token.value, "INPUT");

    token = lexer.get_token();
    ASSERT_EQ(token.type, identifier_);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, while_);
    ASSERT_EQ(token.value, "WHILE");

    token = lexer.get_token();
    ASSERT_EQ(token.type, identifier_);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, lt_);
    ASSERT_EQ(token.value, "<");

    token = lexer.get_token();
    ASSERT_EQ(token.type, number_);
    ASSERT_EQ(token.value, "10");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, print_);
    ASSERT_EQ(token.value, "PRINT");

    token = lexer.get_token();
    ASSERT_EQ(token.type, identifier_);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, let_);
    ASSERT_EQ(token.value, "LET");

    token = lexer.get_token();
    ASSERT_EQ(token.type, identifier_);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, eq_);
    ASSERT_EQ(token.value, "=");

    token = lexer.get_token();
    ASSERT_EQ(token.type, identifier_);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, plus_);
    ASSERT_EQ(token.value, "+");

    token = lexer.get_token();
    ASSERT_EQ(token.type, number_);
    ASSERT_EQ(token.value, "1");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, endwhile_);
    ASSERT_EQ(token.value, "ENDWHILE");

    token = lexer.get_token();
    ASSERT_EQ(token.type, newline_);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, eof_);
    ASSERT_EQ(token.value[0], '\0');
}
