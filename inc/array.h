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
	typedef array<T, 1> child;

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
		            static_cast<child*>(this)->data_), end(), T());
		return *this;
	}
	/** Copy assignment operator for compatible array. */
	template<typename T2>
	array& operator=(const array<T2>& rhs) {
		fill(copy_n(rhs.begin(),
		            min(rhs.size(), size()),
		            static_cast<child*>(this)->data_), end(), T());
		return *this;
	}

	/** Random access operator. */
	reference operator[](size_type pos) {
		return static_cast<child*>(this)->data_[pos];
	}
	const_reference operator[](size_type pos) const {
		return static_cast<const child*>(this)->data_[pos];
	}

	/** Access element at pos with bounds checking. */
	reference at(size_type pos) {
		return static_cast<child*>(this)->data_[pos % capacity_];
	}
	const_reference at(size_type pos) const {
		return static_cast<const child*>(this)->data_[pos % capacity_];
	}

	/** Access the first element. */
	reference front() { return static_cast<child*>(this)->data_[0]; }
	const_reference front() const {
		return static_cast<const child*>(this)->data_[0];
	}

	/** Access the last element. */
	reference back() { return static_cast<child*>(this)->data_[capacity_ - 1]; }
	const_reference back() const {
		return static_cast<const child*>(this)->data_[capacity_ - 1];
	}

	/** Access the underlying array pointer. */
	pointer data() { return static_cast<child*>(this)->data_; }
	const_pointer data() const { return static_cast<const child*>(this)->data_; }

	/** Returns an iterator to the first element in the array. */
	iterator begin() { return static_cast<child*>(this)->data_; }
	const_iterator begin() const { return static_cast<const child*>(this)->data_; }
	const_iterator cbegin() const { return static_cast<const child*>(this)->data_; }

	/** Returns an iterator to the invalid element immediately following the array. */
	iterator end() { return begin() + capacity_; }
	const_iterator end() const { return begin() + capacity_; }
	const_iterator cend() const { return begin() + capacity_; }

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
	size_type size() const { return capacity_; }
	/** Returns the maximum possible number of elements. */
	size_type max_size() const { return capacity_; }

  protected:
	array(size_type cap) : capacity_(cap) {}
	~array() {}

  private:
	size_type capacity_;
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
	array() : base(N) { fill_n(data_, N, T()); }
	/** Copy constructor. */
	array(const array& other) : base(N) { copy_n(other.begin(), N, data_); }
	/** Construct from a compatible array. */
	template<typename T2>
	array(const array<T2>& other) : base(N) {
		fill(copy_n(other.begin(), min(other.size(), N), data_), base::end(), T());
	}
	/** Initialized constructor. */
	explicit array(const_reference val) : base(N) { fill_n(data_, N, val); }

	/** Copy assignment operator. */
	array& operator=(const array& rhs) {
		copy_n(rhs.begin(), N, data_);
		return *this;
	}
	/** Copy assignment operator for compatible array. */
	template<typename T2>
	array& operator=(const array<T2>& rhs) {
		fill(copy_n(rhs.begin(), min(rhs.size(), N), data_), base::end(), T());
		return *this;
	}

  private:
	T data_[N];
};

} /* namespace sstl */

#endif /* STATIC_STL_ARRAY_H_ */
