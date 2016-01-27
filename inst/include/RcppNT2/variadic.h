#ifndef RCPP_NT2_VARIADIC_H
#define RCPP_NT2_VARIADIC_H

namespace RcppNT2 {
namespace variadic {

template <typename F, typename... Args>
inline auto apply(F&& f, Args&&... args) -> decltype(std::forward<F>(f)(std::forward<Args>(args)...))
{
  return std::forward<F>(f)(std::forward<Args>(args)...);
}

template <typename F, typename T>
inline auto min(F&& f, T&& t) -> decltype(std::forward<T>(t))
{
  return std::forward<T>(t);
}

template <typename F, typename T, typename... Ts>
inline auto min(F&& f, T&& t, Ts&&... ts) -> decltype(std::forward<T>(t))
{
  return (min(std::forward<F>(f), std::forward<T>(t)) < min(std::forward<F>(f), std::forward<Ts>(ts)...))
    ? min(std::forward<F>(f), std::forward<T>(t))
    : min(std::forward<F>(f), std::forward<Ts>(ts)...);
}

template <int Index, typename... Ts>
std::size_t size(Ts&&... ts)
{
  return std::get<Index>(std::tuple<Ts...>()).size();
}

} // namespace variadic
} // namespace RcppNT2

#endif /* RCPP_NT2_VARIADIC_H */
