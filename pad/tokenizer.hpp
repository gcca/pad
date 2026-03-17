#pragma once

#include <cstddef>
#include <string_view>
#include <vector>

namespace pad::tokenizer {

class Token {
public:
  Token(std::string_view text, std::size_t position);

  std::string_view text() const;
  std::size_t position() const;

  bool operator==(const Token &other) const = default;

private:
  std::string_view text_;
  std::size_t position_;
};

[[nodiscard]] std::vector<Token> Tokenize(std::string_view input);

} // namespace pad::tokenizer
