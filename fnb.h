#pragma once

#include <functional>
#include <type_traits>
#include <chrono>

template <
    typename result_t	= std::chrono::milliseconds,
    typename clock_t	= std::chrono::steady_clock,
    typename duration_t = std::chrono::milliseconds
>
auto since(const std::chrono::time_point<clock_t, duration_t> &start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

template <
    typename Duration = std::chrono::milliseconds,
    typename F, typename... Args
>
auto bench(F &&func, Args &&... args)
{
    using namespace std::chrono;
    steady_clock::time_point start = steady_clock::now();
    if constexpr (std::is_void_v<std::invoke_result_t<F, Args...>> || std::is_trivially_destructible_v<std::invoke_result_t<F, Args...>>) {
        (void)std::invoke(func, std::forward<Args>(args)...);
        return since<Duration>(start);
    }
    else {
        decltype(auto) r = std::invoke(func, std::forward<Args>(args)...);
        return since<Duration>(start);
    }
}
