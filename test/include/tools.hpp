#pragma once

inline void busy(unsigned iterations_count = 10'000)
{
    for (volatile unsigned i = 0; i < iterations_count; i = i + 1) {};
}