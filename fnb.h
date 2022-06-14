#pragma once

#include <chrono>

template <
    typename result_t	= std::chrono::milliseconds,
    typename clock_t	= std::chrono::steady_clock,
    typename duration_t = std::chrono::milliseconds
>
inline auto since(const std::chrono::time_point<clock_t, duration_t> &start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

template <
    typename duration_t = std::chrono::milliseconds,
    typename R = void(*), typename ... Params
>
auto bench(R(*func)(Params...), Params ... params)
{
    using namespace std::chrono;
    steady_clock::time_point start = steady_clock::now();
    if constexpr (std::is_void_v<decltype(func(params...))>)
    {
        func(params...);
        return since<duration_t>(start);
    }
    else if constexpr (!std::is_void_v<decltype(func(params...))>)
    {
        auto r = func(params...);
        return since<duration_t>(start);
    }
}
