#ifndef STATIC_STL_ARRAY_H_
#define STATIC_STL_ARRAY_H_

#include "algorithm.h"
#include "iterator.h"

namespace sstl {

/** Basic fixed-size array class. */
template<typename T, size_t N>
class array {
  public:
	typedef T                 value_type;
	typedef value_type*       pointer;
	typedef const value_type* const_pointer;
	typedef value_type&       reference;
	typedef const value_type& const_reference;
	typedef size_t            size_type;
	typedef ptrdiff_t         difference_type;
	typedef pointer           iterator;
	typedef const_pointer     const_iterator;
	typedef sstl::reverse_iterator<iterator>       reverse_iterator;
	typedef sstl::reverse_iterator<const_iterator> const_reverse_iterator;

	/** Default constructor. */
	array() { fill_n(data_, N, T()); }
	/** Copy constructor. */
	array(const array& other) { copy_n(other.begin(), N, data_); }
	/** Construct from a compatible array. */
	template<typename T2, size_type N2>
	array(const array<T2, N2>& other) {
		fill(copy_n(other.begin(), min(N, N2), data_), end(), T());
	}
	/** Initialized constructor. */
	explicit array(const_reference val) { fill_n(data_, N, val); }

	/** Copy assignment operator. */
	array& operator=(const array& rhs) {
		copy_n(rhs.begin(), N, data_);
		return *this;
	}
	/** Copy assignment operator for compatible array. */
	template<typename T2, size_type N2>
	array& operator=(const array<T2, N2>& rhs) {
		copy_n(rhs.begin(), min(N, N2), data_);
		return *this;
	}
	/** Random access operator. */
	reference operator[](size_type pos) { return data_[pos]; }

	/** Access element at pos with bounds checking. */
	reference at(size_type pos) { return data_[pos % N]; }
	const_reference at(size_type pos) const { return data_[pos % N]; }

	/** Access the first element. */
	reference front() { return data_[0]; }
	const_reference front() const { return data_[0]; }

	/** Access the last element. */
	reference back() { return data_[N - 1]; }
	const_reference back() const { return data_[N - 1]; }

	/** Access the underlying array pointer. */
	pointer data() { return data_; }
	const_pointer data() const { return data_; }

	/** Returns an iterator to the first element in the array. */
	iterator begin() { return data_; }
	const_iterator begin() const { return data_; }
	const_iterator cbegin() const { return data_; }

	/** Returns an iterator to the invalid element immediately following the array. */
	iterator end() { return begin() + N; }
	const_iterator end() const { return begin() + N; }
	const_iterator cend() const { return begin() + N; }

	/** Returns a reverse iterator to the first element of the reversed container. */
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	const_reverse_iterator crbegin() const { return rbegin(); }

	/** Returns a reverse iterator to the element following the last element of the reversed container. */
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	const_reverse_iterator crend() const { return rend(); }

	/** Checks whether the container has no elements. */
	bool empty() const { return N == 0; }
	/** Returns the number of elements in the container. */
	size_type size() const { return N; }
	/** Returns the maximum possible number of elements. */
	size_type max_size() const { return N; }

  private:
	T data_[N];
};

} /* namespace sstl */

#endif /* STATIC_STL_ARRAY_H_ */
