#ifndef STATIC_STL_MEMORY_H_
#define STATIC_STL_MEMORY_H_

#include "iterator.h"

namespace sstl {

/** Copies elements from the range [first, last] to an uninitialized memory area beginning at d_first. */
template<class InputIt, class ForwardIt>
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first) {
	typedef typename iterator_traits<ForwardIt>::value_type value_type;

	for (; first != last; ++first, ++d_first) {
		new(static_cast<void*>(&*d_first)) value_type(*first);
	}

	return d_first;
}

/** Copies count elements from a range beginning at first to an uninitialized memory area beginning at d_first. */
template<class InputIt, class Size, class ForwardIt>
ForwardIt uninitialized_copy_n(InputIt first, Size count, ForwardIt d_first) {
	typedef typename iterator_traits<ForwardIt>::value_type value_type;

	for (; count; ++first, ++d_first, --count) {
		new(static_cast<void*>(&*d_first)) value_type(*first);
	}

	return d_first;
}

/** Copies the given value to an uninitialized memory area, defined by the range [first, last]. */
template<class ForwardIt, typename T>
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value) {
	typedef typename iterator_traits<ForwardIt>::value_type value_type;

	for (; first != last; ++first) {
		new(static_cast<void*>(&*first)) value_type(value);
	}
}

/** Copies the given value value to the first count elements in an uninitialized memory area beginning at first. */
template<class ForwardIt, class Size, typename T>
ForwardIt uninitialized_fill_n(ForwardIt first, Size count, const T& value) {
	typedef typename iterator_traits<ForwardIt>::value_type value_type;

	for (; count; ++first, --count) {
		new(static_cast<void*>(&*first)) value_type(value);
	}

	return first;
}

/** Constructs objects in the uninitialized storage designated by the range [first, last] by default-initialization. */
template<class ForwardIt>
void uninitialized_default_construct(ForwardIt first, ForwardIt last) {
	typedef typename iterator_traits<ForwardIt>::value_type value_type;

	for (; first != last; ++first) {
		new(static_cast<void*>(&*first)) value_type;
	}
}

/** Constructs n objects in the uninitialized storage starting at first by default-initialization. */
template<class ForwardIt, class Size>
ForwardIt uninitialized_default_construct_n(ForwardIt first, Size n) {
	typedef typename iterator_traits<ForwardIt>::value_type value_type;

	for (; n; ++first, --n) {
		new(static_cast<void*>(&*first)) value_type;
	}

	return first;
}

/** Constructs objects in the uninitialized storage designated by the range [first, last] by value-initialization. */
template<class ForwardIt>
void uninitialized_value_construct(ForwardIt first, ForwardIt last) {
	typedef typename iterator_traits<ForwardIt>::value_type value_type;

	for (; first != last; ++first) {
		new(static_cast<void*>(&*first)) value_type();
	}
}

/** Constructs n objects in the uninitialized storage starting at first by value-initialization. */
template<class ForwardIt, class Size>
ForwardIt uninitialized_value_construct_n(ForwardIt first, Size n) {
	typedef typename iterator_traits<ForwardIt>::value_type value_type;

	for (; n; ++first, --n) {
		new(static_cast<void*>(&*first)) value_type();
	}

	return first;
}

/** Calls the destructor of the object pointed to by p, as if by p->~T(). */
template<typename T>
void destroy_at(T* p) {
	p->~T();
}

/** Destroys the objects in the range [first, last]. */
template<class ForwardIt>
void destroy(ForwardIt first, ForwardIt last) {
	for (; first != last; ++first) { destroy_at(&*first); }
}

/** Destroys the n objects in the range starting at first. */
template<class ForwardIt, class Size>
ForwardIt destroy_n(ForwardIt first, Size n) {
	for (; n; ++first, --n) { destroy_at(&*first); }

	return first;
}

} /* namespace sstl */

#endif /* STATIC_STL_MEMORY_H_ */
