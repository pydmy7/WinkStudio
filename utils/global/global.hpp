#ifndef GLOBAL_HPP
#define GLOBAL_HPP

// p.s.
// std::unreachable();  // Since C++23
// __assume(false);  // MSVC
// __builtin_unreachable();  // GCC/Clang
#if defined(__MINGW32__) || defined(__GNUC__) || defined(__clang__)
    #define unreachable() __builtin_unreachable()
#elif defined(_MSC_VER)
    #define unreachable() __assume(false)
#else
    #define unreachable() assert(false)
#endif

namespace global {



}

#endif // GLOBAL_HPP
