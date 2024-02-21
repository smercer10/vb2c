#include "vb2c/token.h"
#include <gtest/gtest.h>

TEST(TokenTest, TypeAsString)
{
    using enum token::tkn_type;

    token::token token;

    token.type = tkn_eof;
    EXPECT_EQ(token.type_as_string(), "EOF");

    token.type = tkn_newline;
    EXPECT_EQ(token.type_as_string(), "newline");

    token.type = tkn_number;
    EXPECT_EQ(token.type_as_string(), "number");

    token.type = tkn_identifier;
    EXPECT_EQ(token.type_as_string(), "identifier");

    token.type = tkn_string;
    EXPECT_EQ(token.type_as_string(), "string");

    token.type = tkn_label;
    EXPECT_EQ(token.type_as_string(), "LABEL");

    token.type = tkn_goto;
    EXPECT_EQ(token.type_as_string(), "GOTO");

    token.type = tkn_print;
    EXPECT_EQ(token.type_as_string(), "PRINT");

    token.type = tkn_input;
    EXPECT_EQ(token.type_as_string(), "INPUT");

    token.type = tkn_let;
    EXPECT_EQ(token.type_as_string(), "LET");

    token.type = tkn_if;
    EXPECT_EQ(token.type_as_string(), "IF");

    token.type = tkn_then;
    EXPECT_EQ(token.type_as_string(), "THEN");

    token.type = tkn_endif;
    EXPECT_EQ(token.type_as_string(), "ENDIF");

    token.type = tkn_while;
    EXPECT_EQ(token.type_as_string(), "WHILE");

    token.type = tkn_repeat;
    EXPECT_EQ(token.type_as_string(), "REPEAT");

    token.type = tkn_endwhile;
    EXPECT_EQ(token.type_as_string(), "ENDWHILE");

    token.type = tkn_eq;
    EXPECT_EQ(token.type_as_string(), "=");

    token.type = tkn_plus;
    EXPECT_EQ(token.type_as_string(), "+");

    token.type = tkn_minus;
    EXPECT_EQ(token.type_as_string(), "-");

    token.type = tkn_mult;
    EXPECT_EQ(token.type_as_string(), "*");

    token.type = tkn_div;
    EXPECT_EQ(token.type_as_string(), "/");

    token.type = tkn_eqeq;
    EXPECT_EQ(token.type_as_string(), "==");

    token.type = tkn_noteq;
    EXPECT_EQ(token.type_as_string(), "!=");

    token.type = tkn_lt;
    EXPECT_EQ(token.type_as_string(), "<");

    token.type = tkn_lteq;
    EXPECT_EQ(token.type_as_string(), "<=");

    token.type = tkn_gt;
    EXPECT_EQ(token.type_as_string(), ">");

    token.type = tkn_gteq;
    EXPECT_EQ(token.type_as_string(), ">=");

    token.type = static_cast<token::tkn_type>(-1);
    EXPECT_EQ(token.type_as_string(), "unknown");
}

TEST(TokenTest, TypeFromString)
{
    using enum token::tkn_type;

    EXPECT_EQ(token::type_from_string("LABEL"), tkn_label);
    EXPECT_EQ(token::type_from_string("GOTO"), tkn_goto);
    EXPECT_EQ(token::type_from_string("PRINT"), tkn_print);
    EXPECT_EQ(token::type_from_string("INPUT"), tkn_input);
    EXPECT_EQ(token::type_from_string("LET"), tkn_let);
    EXPECT_EQ(token::type_from_string("IF"), tkn_if);
    EXPECT_EQ(token::type_from_string("THEN"), tkn_then);
    EXPECT_EQ(token::type_from_string("ENDIF"), tkn_endif);
    EXPECT_EQ(token::type_from_string("WHILE"), tkn_while);
    EXPECT_EQ(token::type_from_string("REPEAT"), tkn_repeat);
    EXPECT_EQ(token::type_from_string("ENDWHILE"), tkn_endwhile);
    EXPECT_EQ(token::type_from_string("LABeL"), tkn_identifier);
    EXPECT_EQ(token::type_from_string("THAN"), tkn_identifier);
    EXPECT_EQ(token::type_from_string("ENDWHILEE"), tkn_identifier);
}

TEST(TokenTest, IsKeyword)
{
    using enum token::tkn_type;

    EXPECT_TRUE(token::is_keyword(tkn_label));
    EXPECT_TRUE(token::is_keyword(tkn_goto));
    EXPECT_TRUE(token::is_keyword(tkn_print));
    EXPECT_TRUE(token::is_keyword(tkn_input));
    EXPECT_TRUE(token::is_keyword(tkn_let));
    EXPECT_TRUE(token::is_keyword(tkn_if));
    EXPECT_TRUE(token::is_keyword(tkn_then));
    EXPECT_TRUE(token::is_keyword(tkn_endif));
    EXPECT_TRUE(token::is_keyword(tkn_while));
    EXPECT_TRUE(token::is_keyword(tkn_repeat));
    EXPECT_TRUE(token::is_keyword(tkn_endwhile));
    EXPECT_FALSE(token::is_keyword(tkn_identifier));
    EXPECT_FALSE(token::is_keyword(tkn_mult));
    EXPECT_FALSE(token::is_keyword(static_cast<token::tkn_type>(-1)));
}

TEST(TokenTest, IsComparisonOperator)
{
    using enum token::tkn_type;

    EXPECT_TRUE(token::is_comparison_op(tkn_eqeq));
    EXPECT_TRUE(token::is_comparison_op(tkn_noteq));
    EXPECT_TRUE(token::is_comparison_op(tkn_lt));
    EXPECT_TRUE(token::is_comparison_op(tkn_lteq));
    EXPECT_TRUE(token::is_comparison_op(tkn_gt));
    EXPECT_TRUE(token::is_comparison_op(tkn_gteq));
    EXPECT_FALSE(token::is_comparison_op(tkn_div));
    EXPECT_FALSE(token::is_comparison_op(tkn_label));
    EXPECT_FALSE(token::is_comparison_op(static_cast<token::tkn_type>(-1)));
}
