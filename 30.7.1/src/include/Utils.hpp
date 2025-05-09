#pragma once
#include <chrono>
#include <iostream>
inline auto now()
{
    return std::chrono::high_resolution_clock::now();
}
inline double elapsed_seconds(
    const decltype(now()) &start,
    const decltype(now()) &end)
{
    return std::chrono::duration<double>(end - start).count();
}
