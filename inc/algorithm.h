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

} /* namespace sstl */

#endif /* STATIC_STL_ALGORITHM_H_ */
