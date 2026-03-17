#include <gtest/gtest.h>
#include <tokenizer.hpp>

using pad::tokenizer::Token;
using pad::tokenizer::Tokenize;

TEST(Tokenizer, SplitsBySpaces) {
  auto tokens = Tokenize("hello world foo");
  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].text(), "hello");
  EXPECT_EQ(tokens[0].position(), 0);

  EXPECT_EQ(tokens[1].text(), "world");
  EXPECT_EQ(tokens[1].position(), 6);

  EXPECT_EQ(tokens[2].text(), "foo");
  EXPECT_EQ(tokens[2].position(), 12);
}

TEST(Tokenizer, EmptyInput) {
  auto tokens = Tokenize("");
  EXPECT_TRUE(tokens.empty());
}

TEST(Tokenizer, MultipleSpaces) {
  auto tokens = Tokenize("  a   b  ");
  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].text(), "a");
  EXPECT_EQ(tokens[0].position(), 2);

  EXPECT_EQ(tokens[1].text(), "b");
  EXPECT_EQ(tokens[1].position(), 6);
}

TEST(Tokenizer, SingleWord) {
  auto tokens = Tokenize("hello");
  ASSERT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0].text(), "hello");
  EXPECT_EQ(tokens[0].position(), 0);
}

TEST(Tokenizer, Integer) {
  auto tokens = Tokenize("123");
  ASSERT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0].text(), "123");
  EXPECT_EQ(tokens[0].position(), 0);
}

TEST(Tokenizer, Decimal) {
  auto tokens = Tokenize("123.45");
  ASSERT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0].text(), "123.45");
  EXPECT_EQ(tokens[0].position(), 0);
}

TEST(Tokenizer, NegativeInteger) {
  auto tokens = Tokenize("-123");
  ASSERT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0].text(), "-123");
  EXPECT_EQ(tokens[0].position(), 0);
}

TEST(Tokenizer, NegativeDecimal) {
  auto tokens = Tokenize("-123.45");
  ASSERT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0].text(), "-123.45");
  EXPECT_EQ(tokens[0].position(), 0);
}

TEST(Tokenizer, SymbolBeforeNumber) {
  auto tokens = Tokenize("$-123.45");
  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].text(), "$");
  EXPECT_EQ(tokens[0].position(), 0);

  EXPECT_EQ(tokens[1].text(), "-123.45");
  EXPECT_EQ(tokens[1].position(), 1);
}

TEST(Tokenizer, NumberBeforeSymbol) {
  auto tokens = Tokenize("-123.45$");
  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].text(), "-123.45");
  EXPECT_EQ(tokens[0].position(), 0);

  EXPECT_EQ(tokens[1].text(), "$");
  EXPECT_EQ(tokens[1].position(), 7);
}

TEST(Tokenizer, MixedWithSpaces) {
  auto tokens = Tokenize("total $-123.45 ok");
  ASSERT_EQ(tokens.size(), 4);

  EXPECT_EQ(tokens[0].text(), "total");
  EXPECT_EQ(tokens[0].position(), 0);

  EXPECT_EQ(tokens[1].text(), "$");
  EXPECT_EQ(tokens[1].position(), 6);

  EXPECT_EQ(tokens[2].text(), "-123.45");
  EXPECT_EQ(tokens[2].position(), 7);

  EXPECT_EQ(tokens[3].text(), "ok");
  EXPECT_EQ(tokens[3].position(), 15);
}

TEST(Tokenizer, ClosingParenSeparate) {
  auto tokens = Tokenize("foo)");
  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].text(), "foo");
  EXPECT_EQ(tokens[0].position(), 0);

  EXPECT_EQ(tokens[1].text(), ")");
  EXPECT_EQ(tokens[1].position(), 3);
}

TEST(Tokenizer, ClosingParenAfterNumber) {
  auto tokens = Tokenize("123.45)");
  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].text(), "123.45");
  EXPECT_EQ(tokens[0].position(), 0);

  EXPECT_EQ(tokens[1].text(), ")");
  EXPECT_EQ(tokens[1].position(), 6);
}

TEST(Tokenizer, NestedParens) {
  auto tokens = Tokenize("a(b))");
  ASSERT_EQ(tokens.size(), 4);

  EXPECT_EQ(tokens[0].text(), "a(");
  EXPECT_EQ(tokens[0].position(), 0);

  EXPECT_EQ(tokens[1].text(), "b");
  EXPECT_EQ(tokens[1].position(), 2);

  EXPECT_EQ(tokens[2].text(), ")");
  EXPECT_EQ(tokens[2].position(), 3);

  EXPECT_EQ(tokens[3].text(), ")");
  EXPECT_EQ(tokens[3].position(), 4);
}

TEST(Tokenizer, CompoundExpression) {
  auto tokens = Tokenize("sqrt(54 + 32)/(23 - 1)");
  ASSERT_EQ(tokens.size(), 11);

  EXPECT_EQ(tokens[0].text(), "sqrt(");
  EXPECT_EQ(tokens[0].position(), 0);

  EXPECT_EQ(tokens[1].text(), "54");
  EXPECT_EQ(tokens[1].position(), 5);

  EXPECT_EQ(tokens[2].text(), "+");
  EXPECT_EQ(tokens[2].position(), 8);

  EXPECT_EQ(tokens[3].text(), "32");
  EXPECT_EQ(tokens[3].position(), 10);

  EXPECT_EQ(tokens[4].text(), ")");
  EXPECT_EQ(tokens[4].position(), 12);

  EXPECT_EQ(tokens[5].text(), "/");
  EXPECT_EQ(tokens[5].position(), 13);

  EXPECT_EQ(tokens[6].text(), "(");
  EXPECT_EQ(tokens[6].position(), 14);

  EXPECT_EQ(tokens[7].text(), "23");
  EXPECT_EQ(tokens[7].position(), 15);

  EXPECT_EQ(tokens[8].text(), "-");
  EXPECT_EQ(tokens[8].position(), 18);

  EXPECT_EQ(tokens[9].text(), "1");
  EXPECT_EQ(tokens[9].position(), 20);

  EXPECT_EQ(tokens[10].text(), ")");
  EXPECT_EQ(tokens[10].position(), 21);
}

TEST(Tokenizer, CompoundExpressionWithNegatives) {
  auto tokens = Tokenize("sqrt(-54.90 + -32.08)/(-23.76 - -1.05)");
  ASSERT_EQ(tokens.size(), 11);

  EXPECT_EQ(tokens[0].text(), "sqrt(");
  EXPECT_EQ(tokens[0].position(), 0);

  EXPECT_EQ(tokens[1].text(), "-54.90");
  EXPECT_EQ(tokens[1].position(), 5);

  EXPECT_EQ(tokens[2].text(), "+");
  EXPECT_EQ(tokens[2].position(), 12);

  EXPECT_EQ(tokens[3].text(), "-32.08");
  EXPECT_EQ(tokens[3].position(), 14);

  EXPECT_EQ(tokens[4].text(), ")");
  EXPECT_EQ(tokens[4].position(), 20);

  EXPECT_EQ(tokens[5].text(), "/");
  EXPECT_EQ(tokens[5].position(), 21);

  EXPECT_EQ(tokens[6].text(), "(");
  EXPECT_EQ(tokens[6].position(), 22);

  EXPECT_EQ(tokens[7].text(), "-23.76");
  EXPECT_EQ(tokens[7].position(), 23);

  EXPECT_EQ(tokens[8].text(), "-");
  EXPECT_EQ(tokens[8].position(), 30);

  EXPECT_EQ(tokens[9].text(), "-1.05");
  EXPECT_EQ(tokens[9].position(), 32);

  EXPECT_EQ(tokens[10].text(), ")");
  EXPECT_EQ(tokens[10].position(), 37);
}
