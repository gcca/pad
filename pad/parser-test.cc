#include <gtest/gtest.h>
#include <parser.hpp>

using pad::parser::NodeId;
using pad::parser::Parse;
using pad::tokenizer::Token;
using pad::tokenizer::Tokenize;

TEST(NodeId, EvalReturnsCopy) {
  Token token("hello", 0);
  NodeId node(token);

  auto result = node.Eval();
  EXPECT_EQ(result->ToString(), "hello");
}

TEST(NodeId, ToStringFromToken) {
  Token token("world", 5);
  NodeId node(token);

  EXPECT_EQ(node.ToString(), "world");
  EXPECT_EQ(std::to_string(node), "world");
}

TEST(Parser, NaiveParse) {
  auto tokens = Tokenize("hello world");
  auto result = Parse(tokens);
  EXPECT_EQ(result, "hello world");
}

TEST(Parser, NaiveParseWithNumbers) {
  auto tokens = Tokenize("$-123.45 ok");
  auto result = Parse(tokens);
  EXPECT_EQ(result, "$ -123.45 ok");
}
