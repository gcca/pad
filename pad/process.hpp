#pragma once

#include "pad.hpp"

#include <string>
#include <string_view>

namespace pad {

static constexpr std::string_view kSeparator = "\t=\t";

template <typename TokenizeFn, typename ParseFn>
void Process(const char *input, pad_result_fn callback, void *context,
             TokenizeFn tokenize, ParseFn parse) {
  std::string_view source(input);
  auto tokens = tokenize(source);
  auto parsed = parse(tokens);

  std::string result;
  result.reserve(source.size() + kSeparator.size() + parsed.size());
  result += source;
  result += kSeparator;
  result += parsed;

  callback(result.c_str(), result.size(), context);
}

} // namespace pad
