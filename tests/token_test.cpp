#include "vb2c/token.h"
#include <gtest/gtest.h>

TEST(TokenTest, TypeAsString)
{
    using enum TokenType;

    Token token;

    token.type = eof_;
    EXPECT_EQ(token.type_as_string(), "EOF");

    token.type = newline_;
    EXPECT_EQ(token.type_as_string(), "newline");

    token.type = number_;
    EXPECT_EQ(token.type_as_string(), "number");

    token.type = identifier_;
    EXPECT_EQ(token.type_as_string(), "identifier");

    token.type = string_;
    EXPECT_EQ(token.type_as_string(), "string");

    token.type = label_;
    EXPECT_EQ(token.type_as_string(), "LABEL");

    token.type = goto_;
    EXPECT_EQ(token.type_as_string(), "GOTO");

    token.type = print_;
    EXPECT_EQ(token.type_as_string(), "PRINT");

    token.type = input_;
    EXPECT_EQ(token.type_as_string(), "INPUT");

    token.type = let_;
    EXPECT_EQ(token.type_as_string(), "LET");

    token.type = if_;
    EXPECT_EQ(token.type_as_string(), "IF");

    token.type = then_;
    EXPECT_EQ(token.type_as_string(), "THEN");

    token.type = endif_;
    EXPECT_EQ(token.type_as_string(), "ENDIF");

    token.type = while_;
    EXPECT_EQ(token.type_as_string(), "WHILE");

    token.type = repeat_;
    EXPECT_EQ(token.type_as_string(), "REPEAT");

    token.type = endwhile_;
    EXPECT_EQ(token.type_as_string(), "ENDWHILE");

    token.type = eq_;
    EXPECT_EQ(token.type_as_string(), "=");

    token.type = plus_;
    EXPECT_EQ(token.type_as_string(), "+");

    token.type = minus_;
    EXPECT_EQ(token.type_as_string(), "-");

    token.type = mult_;
    EXPECT_EQ(token.type_as_string(), "*");

    token.type = div_;
    EXPECT_EQ(token.type_as_string(), "/");

    token.type = eqeq_;
    EXPECT_EQ(token.type_as_string(), "==");

    token.type = noteq_;
    EXPECT_EQ(token.type_as_string(), "!=");

    token.type = lt_;
    EXPECT_EQ(token.type_as_string(), "<");

    token.type = lteq_;
    EXPECT_EQ(token.type_as_string(), "<=");

    token.type = gt_;
    EXPECT_EQ(token.type_as_string(), ">");

    token.type = gteq_;
    EXPECT_EQ(token.type_as_string(), ">=");

    token.type = static_cast<TokenType>(-1);
    EXPECT_EQ(token.type_as_string(), "unknown");
}

TEST(TokenTest, TypeFromString)
{
    using enum TokenType;

    EXPECT_EQ(Token::type_from_string("LABEL"), label_);
    EXPECT_EQ(Token::type_from_string("GOTO"), goto_);
    EXPECT_EQ(Token::type_from_string("PRINT"), print_);
    EXPECT_EQ(Token::type_from_string("INPUT"), input_);
    EXPECT_EQ(Token::type_from_string("LET"), let_);
    EXPECT_EQ(Token::type_from_string("IF"), if_);
    EXPECT_EQ(Token::type_from_string("THEN"), then_);
    EXPECT_EQ(Token::type_from_string("ENDIF"), endif_);
    EXPECT_EQ(Token::type_from_string("WHILE"), while_);
    EXPECT_EQ(Token::type_from_string("REPEAT"), repeat_);
    EXPECT_EQ(Token::type_from_string("ENDWHILE"), endwhile_);
    EXPECT_EQ(Token::type_from_string("LABeL"), identifier_);
    EXPECT_EQ(Token::type_from_string("THAN"), identifier_);
    EXPECT_EQ(Token::type_from_string("ENDWHILEE"), identifier_);
}

TEST(TokenTest, IsKeyword)
{
    using enum TokenType;

    EXPECT_TRUE(Token::is_keyword(label_));
    EXPECT_TRUE(Token::is_keyword(goto_));
    EXPECT_TRUE(Token::is_keyword(print_));
    EXPECT_TRUE(Token::is_keyword(input_));
    EXPECT_TRUE(Token::is_keyword(let_));
    EXPECT_TRUE(Token::is_keyword(if_));
    EXPECT_TRUE(Token::is_keyword(then_));
    EXPECT_TRUE(Token::is_keyword(endif_));
    EXPECT_TRUE(Token::is_keyword(while_));
    EXPECT_TRUE(Token::is_keyword(repeat_));
    EXPECT_TRUE(Token::is_keyword(endwhile_));
    EXPECT_FALSE(Token::is_keyword(identifier_));
    EXPECT_FALSE(Token::is_keyword(mult_));
    EXPECT_FALSE(Token::is_keyword(static_cast<TokenType>(-1)));
}

TEST(TokenTest, IsComparisonOperator)
{
    using enum TokenType;

    EXPECT_TRUE(Token::is_comparison_operator(eqeq_));
    EXPECT_TRUE(Token::is_comparison_operator(noteq_));
    EXPECT_TRUE(Token::is_comparison_operator(lt_));
    EXPECT_TRUE(Token::is_comparison_operator(lteq_));
    EXPECT_TRUE(Token::is_comparison_operator(gt_));
    EXPECT_TRUE(Token::is_comparison_operator(gteq_));
    EXPECT_FALSE(Token::is_comparison_operator(div_));
    EXPECT_FALSE(Token::is_comparison_operator(label_));
    EXPECT_FALSE(Token::is_comparison_operator(static_cast<TokenType>(-1)));
}
