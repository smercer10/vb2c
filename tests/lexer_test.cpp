#include "vb2c/lexer.h"
#include <gtest/gtest.h>

TEST(LexerTest, Arithmetic)
{
    using enum token::tkn_type;

    lexer lexer("18 +   2.9-3  *4578 /   5.0");

    token::token token{lexer.get_token()};
    ASSERT_EQ(token.type, tkn_number);
    ASSERT_EQ(token.value, "18");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_plus);
    ASSERT_EQ(token.value, "+");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_number);
    ASSERT_EQ(token.value, "2.9");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_minus);
    ASSERT_EQ(token.value, "-");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_number);
    ASSERT_EQ(token.value, "3");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_mult);
    ASSERT_EQ(token.value, "*");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_number);
    ASSERT_EQ(token.value, "4578");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_div);
    ASSERT_EQ(token.value, "/");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_number);
    ASSERT_EQ(token.value, "5.0");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_eof);
    ASSERT_EQ(token.value[0], '\0');
}

TEST(LexerTest, IfStatement)
{
    using enum token::tkn_type;

    lexer lexer("#  Check if a is equal to b   \n"
        " IF lemon==   GREEN_APPLE  THEN\n"
        "   PRINT    \"lemon is equal to GREEN_APPLE\"\n"
        "   GOTO   40\n"
        "ENDIF  ");

    token::token token{lexer.get_token()};
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_if);
    ASSERT_EQ(token.value, "IF");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_identifier);
    ASSERT_EQ(token.value, "lemon");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_eqeq);
    ASSERT_EQ(token.value, "==");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_identifier);
    ASSERT_EQ(token.value, "GREEN_APPLE");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_then);
    ASSERT_EQ(token.value, "THEN");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_print);
    ASSERT_EQ(token.value, "PRINT");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_string);
    ASSERT_EQ(token.value, "lemon is equal to GREEN_APPLE");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_goto);
    ASSERT_EQ(token.value, "GOTO");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_number);
    ASSERT_EQ(token.value, "40");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_endif);
    ASSERT_EQ(token.value, "ENDIF");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_eof);
    ASSERT_EQ(token.value[0], '\0');
}

TEST(LexerTest, WhileLoop)
{
    using enum token::tkn_type;

    lexer lexer(" INPUT i  \n"
        "WHILE  i   <10\n"
        "   PRINT i  \n  "
        "   LET i=   i +  1\n"
        "  ENDWHILE");

    token::token token{lexer.get_token()};
    ASSERT_EQ(token.type, tkn_input);
    ASSERT_EQ(token.value, "INPUT");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_identifier);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_while);
    ASSERT_EQ(token.value, "WHILE");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_identifier);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_lt);
    ASSERT_EQ(token.value, "<");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_number);
    ASSERT_EQ(token.value, "10");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_print);
    ASSERT_EQ(token.value, "PRINT");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_identifier);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_let);
    ASSERT_EQ(token.value, "LET");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_identifier);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_eq);
    ASSERT_EQ(token.value, "=");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_identifier);
    ASSERT_EQ(token.value, "i");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_plus);
    ASSERT_EQ(token.value, "+");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_number);
    ASSERT_EQ(token.value, "1");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_endwhile);
    ASSERT_EQ(token.value, "ENDWHILE");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_newline);
    ASSERT_EQ(token.value, "\n");

    token = lexer.get_token();
    ASSERT_EQ(token.type, tkn_eof);
    ASSERT_EQ(token.value[0], '\0');
}
