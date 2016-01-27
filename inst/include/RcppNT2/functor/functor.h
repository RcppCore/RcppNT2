#ifndef RCPP_NT2_FUNCTOR_FUNCTOR_H
#define RCPP_NT2_FUNCTOR_FUNCTOR_H

// Auto-generated functors for functions provided by NT2.
// See 'gen/nt2-functors.R' for more details.

namespace RcppNT2 {
namespace functor {

struct sum {
template <typename T>
inline auto operator()(T&& t) -> decltype(sum(std::forward<T>(t)))
{
    return sum(std::forward<T>(t));
}
};

struct size {
template <typename T>
inline auto operator()(T&& t) -> decltype(std::forward<T>(t).size())
{
    return std::forward<T>(t).size();
}
};

struct plus {
template <typename T, typename U>
inline auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) + std::forward<U>(u))
{
    return std::forward<T>(t) + std::forward<U>(u);
}
};

struct minus {
template <typename T, typename U>
inline auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) - std::forward<U>(u))
{
    return std::forward<T>(t) - std::forward<U>(u);
}
};

struct times {
template <typename T, typename U>
inline auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) * std::forward<U>(u))
{
    return std::forward<T>(t) * std::forward<U>(u);
}
};

struct divide {
template <typename T, typename U>
inline auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) / std::forward<U>(u))
{
    return std::forward<T>(t) / std::forward<U>(u);
}
};


} // namespace functor
} // namespace RcppNT2

#endif /* RCPP_NT2_FUNCTOR_FUNCTOR_H */
