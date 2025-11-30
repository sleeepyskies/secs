#pragma once

/// @brief Checks the given condition and crashes the program if false and prints the debug message.
#define SecsAssert(cond, fmt, ...)                                                                \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            std::abort();                                                                          \
        }                                                                                          \
} while (0)
