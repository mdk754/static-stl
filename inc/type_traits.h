#ifndef STATIC_STL_TYPE_TRAITS_H_
#define STATIC_STL_TYPE_TRAITS_H_

#include <stddef.h>
#include <stdint.h>

namespace sstl {

/** Wraps a static constant of specified type. */
template<typename T, T v>
struct integral_constant {
	static const T value = v;

	typedef T                 value_type;
	typedef integral_constant type;

	operator value_type() const { return value; }
	value_type operator()() const { return value; }
};

/** If B is true, enable_if has a public member typedef type, equal to T. */
template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

namespace detail {
template<typename T>
struct alignment_of {
	struct alignment_wrapper {
		char pad;
		T type;
	};
	static const size_t value = sizeof(alignment_wrapper) - sizeof(T);
};
} /* namespace detail */

/** Provides the member constant value equal to the alignment requirement of the type T. */
template<typename T>
struct alignment_of :
	public integral_constant<size_t, detail::alignment_of<T>::value> {};

/** Provides the nested type type, which is a trivial type with the same alignment as Align . */
template<size_t Align>
struct aligned_pod { typedef long double type; };

template<>
struct aligned_pod<1> { typedef uint8_t type; };

template<>
struct aligned_pod<2> { typedef uint16_t type; };

template<>
struct aligned_pod<4> { typedef uint32_t type; };

template<>
struct aligned_pod<8> { typedef uint64_t type; };

/** Provides the nested type type, which is a trivial type of size N with alignment Align. */
template<size_t N, size_t Align>
struct aligned_storage {
	union type {
		unsigned char data_[N];
		typename aligned_pod<Align>::type align_;
	};

  private:
	/** This type gives compilation errors if we can't align on the requested boundary for this platform. */
	typedef typename
	enable_if < (Align <= alignment_of<aligned_pod<0>::type>::value) >::type
	alignment_possible;
};

} /* namespace sstl */

#endif /* STATIC_STL_TYPE_TRAITS_H_ */
