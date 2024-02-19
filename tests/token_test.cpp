#include <gtest/gtest.h>
#include <tb2c/token.h>

TEST(TokenTest, TypeAsString)
{
    using enum TokenType;

    Token token;

    token.type = eof_;
    EXPECT_EQ(token.type_as_string(), "eof");

    token.type = newline_;
    EXPECT_EQ(token.type_as_string(), "newline");

    token.type = number_;
    EXPECT_EQ(token.type_as_string(), "number");

    token.type = identifier_;
    EXPECT_EQ(token.type_as_string(), "identifier");

    token.type = string_;
    EXPECT_EQ(token.type_as_string(), "string");

    token.type = label_;
    EXPECT_EQ(token.type_as_string(), "label");

    token.type = goto_;
    EXPECT_EQ(token.type_as_string(), "goto");

    token.type = print_;
    EXPECT_EQ(token.type_as_string(), "print");

    token.type = input_;
    EXPECT_EQ(token.type_as_string(), "input");

    token.type = let_;
    EXPECT_EQ(token.type_as_string(), "let");

    token.type = if_;
    EXPECT_EQ(token.type_as_string(), "if");

    token.type = then_;
    EXPECT_EQ(token.type_as_string(), "then");

    token.type = endif_;
    EXPECT_EQ(token.type_as_string(), "endif");

    token.type = while_;
    EXPECT_EQ(token.type_as_string(), "while");

    token.type = repeat_;
    EXPECT_EQ(token.type_as_string(), "repeat");

    token.type = endwhile_;
    EXPECT_EQ(token.type_as_string(), "endwhile");

    token.type = eq_;
    EXPECT_EQ(token.type_as_string(), "eq");

    token.type = plus_;
    EXPECT_EQ(token.type_as_string(), "plus");

    token.type = minus_;
    EXPECT_EQ(token.type_as_string(), "minus");

    token.type = mult_;
    EXPECT_EQ(token.type_as_string(), "mult");

    token.type = div_;
    EXPECT_EQ(token.type_as_string(), "div");

    token.type = eqeq_;
    EXPECT_EQ(token.type_as_string(), "eqeq");

    token.type = noteq_;
    EXPECT_EQ(token.type_as_string(), "noteq");

    token.type = lt_;
    EXPECT_EQ(token.type_as_string(), "lt");

    token.type = lteq_;
    EXPECT_EQ(token.type_as_string(), "lteq");

    token.type = gt_;
    EXPECT_EQ(token.type_as_string(), "gt");

    token.type = gteq_;
    EXPECT_EQ(token.type_as_string(), "gteq");

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
    EXPECT_FALSE(Token::is_keyword(identifier_));
    EXPECT_FALSE(Token::is_keyword(static_cast<TokenType>(-1)));
}
