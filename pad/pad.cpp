#include "pad.hpp"
#include "parser.hpp"
#include "process.hpp"
#include "tokenizer.hpp"

extern "C" {
void pad_quote(const char *input, pad_result_fn callback, void *context) {
  pad::Process(input, callback, context, pad::tokenizer::Tokenize,
               pad::parser::Parse);
}
}
