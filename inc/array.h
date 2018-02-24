#ifndef STATIC_STL_ARRAY_H_
#define STATIC_STL_ARRAY_H_

#include "algorithm.h"
#include "iterator.h"

namespace sstl {

/** Basic fixed-size array class. */
template<typename T, size_t N = 0>
class array;

/** Common zero-size base class for all fixed-size arrays. */
template<typename T>
class array<T> {
	typedef array<T, 8> child;

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

	/** Copy assignment operator. */
	array& operator=(const array& rhs) {
		fill(copy_n(rhs.begin(),
		            min(rhs.size(), size()),
		            begin()), end(), value_type());
		return *this;
	}
	/** Copy assignment operator for compatible array. */
	template<typename T2>
	array& operator=(const array<T2>& rhs) {
		fill(copy_n(rhs.begin(),
		            min(rhs.size(), size()),
		            begin()), end(), value_type());
		return *this;
	}

	/** Random access operator. */
	reference operator[](size_type pos) { return begin()[pos]; }
	const_reference operator[](size_type pos) const { return begin()[pos]; }

	/** Access element at pos with bounds checking. */
	reference at(size_type pos) { return begin()[pos % size()]; }
	const_reference at(size_type pos) const { return begin()[pos % size()]; }

	/** Access the first element. */
	reference front() { return *begin(); }
	const_reference front() const { return *begin(); }

	/** Access the last element. */
	reference back() { return end()[-1]; }
	const_reference back() const { return end()[-1]; }

	/** Access the underlying array pointer. */
	pointer data() { return static_cast<child*>(this)->data_; }
	const_pointer data() const { return static_cast<const child*>(this)->data_; }

	/** Returns an iterator to the first element in the array. */
	iterator begin() { return data(); }
	const_iterator begin() const { return data(); }
	const_iterator cbegin() const { return data(); }

	/** Returns an iterator to the invalid element immediately following the array. */
	iterator end() { return begin() + size(); }
	const_iterator end() const { return begin() + size(); }
	const_iterator cend() const { return begin() + size(); }

	/** Returns a reverse iterator to the first element of the reversed container. */
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	const_reverse_iterator crbegin() const { return rbegin(); }

	/** Returns a reverse iterator to the element following the last element of the reversed container. */
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	const_reverse_iterator crend() const { return rend(); }

	/** Checks whether the container has no elements. */
	bool empty() const { return false; }
	/** Returns the number of elements in the container. */
	size_type size() const { return static_cast<const child*>(this)->capacity_; }
	/** Returns the maximum possible number of elements. */
	size_type max_size() const { return size(); }

  protected:
	array() {}
	~array() {}
};

/** Child class with size-specific storage for the underlying array. */
template<typename T, size_t N>
class array : public array<T> {
	friend class array<T>;
	typedef array<T> base;

  public:
	typedef typename base::pointer                pointer;
	typedef typename base::const_pointer          const_pointer;
	typedef typename base::value_type             value_type;
	typedef typename base::reference              reference;
	typedef typename base::const_reference        const_reference;
	typedef typename base::size_type              size_type;
	typedef typename base::difference_type        difference_type;
	typedef typename base::iterator               iterator;
	typedef typename base::const_iterator         const_iterator;
	typedef typename base::reverse_iterator       reverse_iterator;
	typedef typename base::const_reverse_iterator const_reverse_iterator;

	/** Default constructor. */
	array() : capacity_(N) { fill_n(data_, N, value_type()); }
	/** Copy constructor. */
	array(const array& other) : capacity_(N) { copy_n(other.begin(), N, data_); }
	/** Construct from a compatible array. */
	template<typename T2>
	array(const array<T2>& other) : capacity_(N) {
		fill(copy_n(other.begin(), min(other.size(), N), data_),
		     base::end(),
		     value_type());
	}
	/** Initialized constructor. */
	explicit array(const_reference val) : capacity_(N) { fill_n(data_, N, val); }

	/** Copy assignment operator. */
	array& operator=(const array& rhs) {
		copy_n(rhs.begin(), N, data_);
		return *this;
	}
	/** Copy assignment operator for compatible array. */
	template<typename T2>
	array& operator=(const array<T2>& rhs) {
		fill(copy_n(rhs.begin(), min(rhs.size(), N), data_),
		     base::end(),
		     value_type());
		return *this;
	}

  private:
	size_type capacity_;
	value_type data_[N];
};

template<typename T>
inline bool operator==(const array<T>& lhs, const array<T>& rhs) {
	return lhs.size() == rhs.size() &&
	       equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template<typename T>
inline bool operator!=(const array<T>& lhs, const array<T>& rhs) {
	return !(lhs == rhs);
}

template<typename T>
inline bool operator<(const array<T>& lhs, const array<T>& rhs) {
	return lexicographical_compare(lhs.cbegin(), lhs.cend(),
	                               rhs.cbegin(), rhs.cend());
}

template<typename T>
inline bool operator>(const array<T>& lhs, const array<T>& rhs) {
	return rhs < lhs;
}

template<typename T>
inline bool operator<=(const array<T>& lhs, const array<T>& rhs) {
	return !(rhs < lhs);
}

template<typename T>
inline bool operator>=(const array<T>& lhs, const array<T>& rhs) {
	return !(lhs < rhs);
}

} /* namespace sstl */

#endif /* STATIC_STL_ARRAY_H_ */
