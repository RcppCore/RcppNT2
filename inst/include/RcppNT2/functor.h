#ifndef RCPP_NT2_FUNCTORS_H
#define RCPP_NT2_FUNCTORS_H

// Auto-generated functors for functions provided by NT2.
// See 'gen/nt2-functors.R' for more details.

namespace RcppNT2 {
namespace functor {

struct sum {
template <typename T>
inline T operator()(const T& data) {
    return sum(data);
}
};

struct plus {
template <typename T>
inline T operator()(const T& lhs, const T& rhs) {
    return lhs + rhs;
}
};

struct minus {
template <typename T>
inline T operator()(const T& lhs, const T& rhs) {
    return lhs - rhs;
}
};

struct times {
template <typename T>
inline T operator()(const T& lhs, const T& rhs) {
    return lhs * rhs;
}
};

struct divide {
template <typename T>
inline T operator()(const T& lhs, const T& rhs) {
    return lhs / rhs;
}
};


} // namespace functor
} // namespace RcppNT2

#endif /* RCPP_NT2_FUNCTORS_H */
