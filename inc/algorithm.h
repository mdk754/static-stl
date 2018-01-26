#ifndef STATIC_STL_ALGORITHM_H_
#define STATIC_STL_ALGORITHM_H_

namespace sstl {

/** Exchanges the given values. */
template<typename T>
inline void swap(T& a, T& b) {
	T tmp(a);
	a = b;
	b = tmp;
}

/** Swaps the values of the elements the given iterators are pointing to. */
template<class ForwardIt1, class ForwardIt2>
inline void iter_swap(ForwardIt1 a, ForwardIt2 b) {
	swap(*a, *b);
}

/** Exchanges elements between range [first1, last1] and another range starting at first2. */
template<class ForwardIt1, class ForwardIt2>
inline ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1,
                              ForwardIt2 first2) {
	for (; first1 != last1; ++first1, ++first2) { iter_swap(first1, first2); }

	return first2;
}

/** Assigns the given value to the elements in the range [first, last]. */
template<class ForwardIt, typename T>
inline void fill(ForwardIt first, ForwardIt last, const T& val) {
	for (; first != last; ++first) { *first = val; }
}

/** Assigns the given value to the first len elements in the range beginning at first if len > 0. */
template<class OutputIt, class Size, typename T>
inline OutputIt fill_n(OutputIt first, Size len, const T& val) {
	for (; len; --len, ++first) { *first = val; }

	return first;
}

/** Copies the elements in the range, defined by [first, last], to another range beginning at dest. */
template<class InputIt, class OutputIt>
inline void copy(InputIt first, InputIt last, OutputIt dest) {
	for (; first != last; ++first, ++dest) { *dest = *first; }
}

/** Copies exactly len values from the range beginning at first to the range beginning at dest, if len > 0. */
template<class InputIt, class Size, class OutputIt>
inline OutputIt copy_n(InputIt first, Size len, OutputIt dest) {
	for (; len; --len, ++first, ++dest) { *dest = *first; }

	return dest;
}

/** Returns the smaller of the given values. */
template<typename T>
inline const T& min(const T& a, const T& b) {
	return b < a ? b : a;
}

/** Returns the smaller of the given values, via comparison functor. */
template<typename T, class Compare>
inline const T& min(const T& a, const T& b, Compare comp) {
	return comp(b, a) ? b : a;
}

/** Returns the greater of the given values. */
template<typename T>
inline const T& max(const T& a, const T& b) {
	return a < b ? b : a;
}

/** Returns the greater of the given values, via comparison functor. */
template<typename T, class Compare>
inline const T& max(const T& a, const T& b, Compare comp) {
	return comp(a, b) ? b : a;
}

} /* namespace sstl */

#endif /* STATIC_STL_ALGORITHM_H_ */
