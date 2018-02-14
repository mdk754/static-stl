#ifndef STATIC_STL_UTILITY_H_
#define STATIC_STL_UTILITY_H_

namespace sstl {

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

} /* namespace sstl */

#endif /* STATIC_STL_UTILITY_H_ */
