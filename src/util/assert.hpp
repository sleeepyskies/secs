#pragma once

#include "slog.hpp"
#define SECS_ASSERT(cond, msg)                                                                                          \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            err("Assertion failed: {}", msg);                                                                          \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (0)
