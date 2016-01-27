#ifndef RCPP_NT2_VARIADIC_TOOLS_H
#define RCPP_NT2_VARIADIC_TOOLS_H

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
  auto&& lhs = min(std::forward<F>(f), std::forward<T>(t));
  auto&& rhs = min(std::forward<F>(f), std::forward<Ts>(ts)...);
  return lhs < rhs ? lhs : rhs;
}

template <typename F, typename T>
inline auto max(F&& f, T&& t) -> decltype(std::forward<T>(t))
{
  return std::forward<T>(t);
}

template <typename F, typename T, typename... Ts>
inline auto max(F&& f, T&& t, Ts&&... ts) -> decltype(std::forward<T>(t))
{
  auto&& lhs = max(std::forward<F>(f), std::forward<T>(t));
  auto&& rhs = max(std::forward<F>(f), std::forward<Ts>(ts)...);
  return lhs < rhs ? rhs : lhs;
}

template <int Size, typename... Ts>
void increment(Ts&&... ts) {}

template <int Size, typename T, typename... Ts>
void increment(T&& t, Ts&&... ts)
{
  std::forward<T>(t) += Size;
  increment<Size>(std::forward<Ts>(ts)...);
}

} // namespace variadic
} // namespace RcppNT2

#endif /* RCPP_NT2_VARIADIC_TOOLS_H */
