#ifndef STATIC_STL_ALGORITHM_H_
#define STATIC_STL_ALGORITHM_H_

#include "iterator.h"

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

/** Returns true if the range [first1, last1] is equal to the range beginning at first2. */
template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
	for (; first1 != last1; ++first1, ++first2) {
		if (!(*first1 == *first2)) {
			return false;
		}
	}

	return true;
}

/** Returns true if the range [first1, last1] is equal to the range beginning at first2, via binary predicate. */
template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
           BinaryPredicate p) {
	for (; first1 != last1; ++first1, ++first2) {
		if (!p(*first1, *first2)) {
			return false;
		}
	}

	return true;
}

/** Checks if the first range [first1, last1] is lexicographically less than the second range [first2, last2]. */
template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2) {
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
		if (*first1 < *first2) { return true; }

		if (*first2 < *first1) { return false; }
	}

	return (first1 == last1) && (first2 != last2);
}

/** Checks if the first range [first1, last1] is lexicographically less than the second range [first2, last2], via comparison functor. */
template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp) {
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
		if (comp(*first1, *first2)) { return true; }

		if (comp(*first2, *first1)) { return false; }
	}

	return (first1 == last1) && (first2 != last2);
}

/** Reverses the order of the elements in the range [first, last]. */
template<class BidirIt>
inline void reverse(BidirIt first, BidirIt last) {
	for (; first != last && first != --last; ++first) { iter_swap(first, last); }
}

/** Performs a left rotation on a range of elements. */
template <class ForwardIt>
ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last) {
	if (first == n_first) { return last; }

	if (n_first == last) { return first; }

	reverse(first, n_first);
	reverse(n_first, last);
	reverse(first, last);

	return first + distance(n_first, last);
}

} /* namespace sstl */

#endif /* STATIC_STL_ALGORITHM_H_ */
