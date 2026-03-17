#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <process.hpp>
#include <tokenizer.hpp>

using pad::tokenizer::Token;
using testing::_;
using testing::Return;

class MockProcessor {
public:
  MOCK_METHOD(std::vector<Token>, Tokenize, (std::string_view));
  MOCK_METHOD(std::string, Parse, (const std::vector<Token> &));
};

TEST(PadProcess, FormatsInputSeparatorParsed) {
  MockProcessor mock;
  EXPECT_CALL(mock, Tokenize(std::string_view("hello")))
      .WillOnce(Return(std::vector<Token>{}));
  EXPECT_CALL(mock, Parse(_)).WillOnce(Return("world"));

  std::string output;
  pad::Process(
      "hello",
      [](const char *data, size_t len, void *ctx) {
        *static_cast<std::string *>(ctx) = std::string(data, len);
      },
      &output,
      [&](std::string_view s) { return mock.Tokenize(s); },
      [&](const auto &t) { return mock.Parse(t); });

  EXPECT_EQ(output, "hello\t=\tworld");
}

TEST(PadProcess, EmptyInputProducesEmptySides) {
  MockProcessor mock;
  EXPECT_CALL(mock, Tokenize(std::string_view("")))
      .WillOnce(Return(std::vector<Token>{}));
  EXPECT_CALL(mock, Parse(_)).WillOnce(Return(""));

  std::string output;
  pad::Process(
      "",
      [](const char *data, size_t len, void *ctx) {
        *static_cast<std::string *>(ctx) = std::string(data, len);
      },
      &output,
      [&](std::string_view s) { return mock.Tokenize(s); },
      [&](const auto &t) { return mock.Parse(t); });

  EXPECT_EQ(output, "\t=\t");
}

TEST(PadProcess, PassesTokenizeResultToParse) {
  MockProcessor mock;
  Token fake_token("x", 0);
  std::vector<Token> fake_tokens{fake_token};

  EXPECT_CALL(mock, Tokenize(_)).WillOnce(Return(fake_tokens));
  EXPECT_CALL(mock, Parse(fake_tokens)).WillOnce(Return("x"));

  std::string output;
  pad::Process(
      "x",
      [](const char *data, size_t len, void *ctx) {
        *static_cast<std::string *>(ctx) = std::string(data, len);
      },
      &output,
      [&](std::string_view s) { return mock.Tokenize(s); },
      [&](const auto &t) { return mock.Parse(t); });

  EXPECT_EQ(output, "x\t=\tx");
}
