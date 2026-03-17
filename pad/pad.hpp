#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*pad_result_fn)(const char *data, size_t len, void *context);

void pad_quote(const char *input, pad_result_fn callback, void *context);

#ifdef __cplusplus
}
#endif
