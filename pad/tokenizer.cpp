#include "tokenizer.hpp"

namespace {

static bool IsDigit(char c) { return c >= '0' && c <= '9'; }

static bool StartsNumber(std::string_view input, std::size_t i) {
  if (i >= input.size())
    return false;
  if (IsDigit(input[i]))
    return true;
  if (input[i] == '-' && i + 1 < input.size() && IsDigit(input[i + 1]))
    return true;
  return false;
}

static std::size_t ConsumeNumber(std::string_view input, std::size_t i) {
  if (i < input.size() && input[i] == '-')
    ++i;
  while (i < input.size() && IsDigit(input[i]))
    ++i;
  if (i < input.size() && input[i] == '.' && i + 1 < input.size() &&
      IsDigit(input[i + 1])) {
    ++i;
    while (i < input.size() && IsDigit(input[i]))
      ++i;
  }
  return i;
}

static bool IsOperator(char c) {
  return c == '+' || c == '*' || c == '/';
}

static bool IsDelimiter(std::string_view input, std::size_t i) {
  char c = input[i];
  if (c == ' ' || c == ')' || c == '(' || IsOperator(c) || c == '-')
    return true;
  return StartsNumber(input, i);
}

} // namespace

namespace pad::tokenizer {

static constexpr std::size_t kMostLikelyTokenSize = 8;

Token::Token(std::string_view text, std::size_t position)
    : text_(text), position_(position) {}

std::string_view Token::text() const { return text_; }

std::size_t Token::position() const { return position_; }

std::vector<Token> Tokenize(std::string_view input) {
  std::vector<Token> tokens;
  tokens.reserve(kMostLikelyTokenSize);

  std::size_t i = 0;

  while (i < input.size()) {
    if (input[i] == ' ') {
      ++i;
      continue;
    }

    if (StartsNumber(input, i)) {
      std::size_t start = i;
      i = ConsumeNumber(input, i);
      tokens.emplace_back(input.substr(start, i - start), start);
    } else if (input[i] == ')' || input[i] == '(') {
      tokens.emplace_back(input.substr(i, 1), i);
      ++i;
    } else if (IsOperator(input[i]) ||
               (input[i] == '-' && !StartsNumber(input, i))) {
      tokens.emplace_back(input.substr(i, 1), i);
      ++i;
    } else {
      std::size_t start = i;
      while (i < input.size() && !IsDelimiter(input, i)) {
        ++i;
      }
      if (i < input.size() && input[i] == '(') {
        ++i;
      }
      tokens.emplace_back(input.substr(start, i - start), start);
    }
  }

  return tokens;
}

} // namespace pad::tokenizer
