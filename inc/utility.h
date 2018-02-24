#ifndef STATIC_STL_UTILITY_H_
#define STATIC_STL_UTILITY_H_

namespace sstl {

namespace rel_ops {

/** Implements operator!= in terms of operator==. */
template<class T>
bool operator!=(const T& lhs, const T& rhs) { return !(lhs == rhs); }

/** Implements operator> in terms of operator<. */
template<class T>
bool operator>(const T& lhs, const T& rhs) { return rhs < lhs; }

/** Implements operator<= in terms of operator<. */
template<class T>
bool operator<=(const T& lhs, const T& rhs) { return !(rhs < lhs); }

/** Implements operator>= in terms of operator<. */
template<class T>
bool operator>=(const T& lhs, const T& rhs) { return !(lhs < rhs); }

} /* namespace rel_ops */

} /* namespace sstl */

#endif /* STATIC_STL_UTILITY_H_ */
