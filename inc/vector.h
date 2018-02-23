#ifndef STATIC_STL_VECTOR_H_
#define STATIC_STL_VECTOR_H_

#include "array.h"
#include "memory.h"
#include "type_traits.h"

namespace sstl {

/** Sequence container that emulates dynamic size arrays with fixed capacity. */
template<typename T, size_t N = 0>
class vector;

/** Common zero-size base class for all vectors. */
template<typename T>
class vector<T> {
	typedef vector<T, 8> child;

  public:
	typedef T                                value_type;
	typedef value_type*                      pointer;
	typedef const value_type*                const_pointer;
	typedef value_type&                      reference;
	typedef const value_type&                const_reference;
	typedef size_t                           size_type;
	typedef ptrdiff_t                        difference_type;
	typedef pointer                          iterator;
	typedef const_pointer                    const_iterator;
	typedef sstl::reverse_iterator<iterator>       reverse_iterator;
	typedef sstl::reverse_iterator<const_iterator> const_reverse_iterator;

	/** Copy assignment operator. */
	vector& operator=(const vector& rhs) {
		assign(rhs.begin(), rhs.end());
		return *this;
	}
	/** Copy assignment operator for compatible vector. */
	template<typename T2>
	vector& operator=(const vector<T2>& rhs) {
		assign(rhs.begin(), rhs.end());
		return *this;
	}

	/** Random access operator. */
	reference operator[](size_type pos) { return begin()[pos]; }
	const_reference operator[](size_type pos) const { return begin()[pos]; }

	/** Replaces the contents with count copies of value val. */
	void assign(size_type count, const_reference val) {
		resize(count);
		fill_n(begin(), size_, val);
	}
	/** Replaces the contents with copies of those in the range [first, last]. */
	template<class InputIt>
	void assign(InputIt first, InputIt last) {
		typedef typename is_integral<InputIt>::type integral;
		assign_range_dispatch(first, last, integral());
	}

	/** Returns a reference to the element at specified location pos, with bounds checking. */
	reference at(size_type pos) { return begin()[pos % max_size()]; }
	const_reference at(size_type pos) const { return begin()[pos % max_size()]; }

	/** Returns a reference to the first element in the container. */
	reference front() { return *begin(); }
	const_reference front() const { return *begin(); }

	/** Returns reference to the last element in the container. */
	reference back() { return end()[-1]; }
	const_reference back() const { return end()[-1]; }

	/** Returns pointer to the underlying array serving as element storage. */
	pointer data() { return pointer(static_cast<child*>(this)->data_.data()); }
	const_pointer data() const {
		return const_pointer(static_cast<const child*>(this)->data_.data());
	}

	/** Returns an iterator to the first element of the container. */
	iterator begin() { return iterator(static_cast<child*>(this)->data_.begin()); }
	const_iterator begin() const {
		return const_iterator(static_cast<const child*>(this)->data_.begin());
	}
	const_iterator cbegin() const { return begin(); }

	/** Returns an iterator to the element following the last element of the container. */
	iterator end() { return begin() + size_; }
	const_iterator end() const { return begin() + size_; }
	const_iterator cend() const { return end(); }

	/** Returns a reverse iterator to the first element of the reversed container. */
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	const_reverse_iterator crbegin() const { return rbegin(); }

	/** Returns a reverse iterator to the element following the last element of the reversed container. */
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	const_reverse_iterator crend() const { return rend(); }

	/** Checks whether the container has no elements. */
	bool empty() const { return size_ == 0; }
	/** Returns the number of elements in the container. */
	size_type size() const { return size_; }
	/** Returns the maximum possible number of elements. */
	size_type max_size() const {
		return static_cast<const child*>(this)->data_.size();
	}
	/** Returns the number of elements that the container has currently allocated space for. */
	size_type capacity() const { return max_size(); }

	/** Removes all elements from the container. */
	void clear() { resize(0); }

	/** Inserts val before pos. */
	iterator insert(const_iterator pos, const_reference val) {
		if (size_ < max_size()) {
			resize(size_ + 1);
			const difference_type d = distance(cbegin(), pos);
			rotate(rbegin(), rbegin() + 1, reverse_iterator(begin() + d));
			*iterator(pos) = val;
		}

		return iterator(pos);
	}
	iterator insert(const_iterator pos, size_type count, const_reference val) {
		if (size_ < max_size()) {
			count = min(count, max_size() - size_);
			resize(size_ + count);
			const difference_type d = distance(cbegin(), pos);
			rotate(rbegin(), rbegin() + count, reverse_iterator(begin() + d));
			fill_n(iterator(pos), count, val);
		}

		return iterator(pos);
	}
	template<class InputIt>
	iterator insert(const_iterator pos, InputIt first, InputIt last) {
		typedef typename is_integral<InputIt>::type integral;
		return insert_range_dispatch(pos, first, last, integral());
	}

	/** Removes specified elements from the container. */
	iterator erase(const_iterator pos) {
		iterator it = iterator(pos);
		rotate(it, it + 1, end());
		resize(size_ - 1);
		return it;
	}
	iterator erase(const_iterator first, const_iterator last) {
		iterator start = iterator(first);
		iterator finish = iterator(last);
		rotate(start, finish, end());
		resize(size_ - distance(start, finish));
		return start;
	}

	/** Appends the given element value to the end of the container. */
	void push_back(const T& value) {
		if (size_ < max_size()) {
			uninitialized_fill_n(end(), 1, value);
			++size_;
		}
	}

	/** Removes the last element of the container. */
	void pop_back() { resize(size_ - 1); }

	/** Resizes the container to contain count elements. */
	void resize(size_type count) {
		if (count <= size_) {
			destroy(begin() + count, end());
			size_ = count;
		} else {
			count = min(count, max_size());
			uninitialized_value_construct(end(), begin() + count);
			size_ = count;
		}
	}
	void resize(size_type count, const value_type& value) {
		if (count <= size_) {
			destroy(begin() + count, end());
			size_ = count;
		} else {
			count = min(count, max_size());
			uninitialized_fill(end(), begin() + count, value);
			size_ = count;
		}
	}

  protected:
	explicit vector(size_type size) : size_(size) {}
	~vector() {}

	size_type size_;

  private:
	template<class Int>
	void assign_range_dispatch(Int count, Int val, true_type) {
		assign(size_type(count), const_reference(val));
	}
	template<class InputIt>
	void assign_range_dispatch(InputIt first, InputIt last, false_type) {
		resize(distance(first, last));
		copy_n(first, size_, begin());
	}

	template<class InputIt>
	iterator insert_range_dispatch(const_iterator pos, InputIt first, InputIt last,
	                               true_type) {
		return insert(pos, size_type(first), value_type(last));
	}
	template<class InputIt>
	iterator insert_range_dispatch(const_iterator pos, InputIt first, InputIt last,
	                               false_type) {
		if (size_ < max_size()) {
			difference_type count = min(distance(first, last),
			                            difference_type(max_size() - size_));
			resize(size_ + count);
			const difference_type d = distance(cbegin(), pos);
			rotate(rbegin(), rbegin() + count, reverse_iterator(begin() + d));
			copy_n(first, count, iterator(pos));
		}

		return iterator(pos);
	}
};

/** Child class with size-specific storage for the underlying array. */
template<typename T, size_t N>
class vector : public vector<T> {
	friend class vector<T>;
	typedef vector<T> base;

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
	vector() : base(0) {}
	/** Copy constructor. */
	vector(const vector& other) : base(other.size()) {
		uninitialized_copy_n(other.begin(), base::size_, base::begin());
	}
	/** Copy adapter constructor. */
	template<typename T2>
	vector(const vector<T2>& other) : base(min(other.size(), N)) {
		uninitialized_copy_n(other.begin(), base::size_, base::begin());
	}
	/** Constructs the vector with count default initialized elements. */
	explicit vector(size_type count) : base(min(count, N)) {
		uninitialized_value_construct_n(base::begin(), base::size_);
	}
	/** Constructs the vector with count elements having value val. */
	vector(size_type count, const_reference val) : base(min(count, N)) {
		uninitialized_fill_n(base::begin(), base::size_, val);
	}
	/** Constructs the vector with values from range [first, last]. */
	template<class InputIt>
	vector(InputIt first, InputIt last) : base(0) {
		typedef typename is_integral<InputIt>::type integral;
		construct_range_dispatch(first, last, integral());
	}

	~vector() { destroy(base::begin(), base::end()); }

	/** Copy assignment operator. */
	vector& operator=(const vector& rhs) {
		base::assign(rhs.begin(), rhs.end());
		return *this;
	}
	/** Copy assignment operator for compatible vector. */
	template<typename T2>
	vector& operator=(const vector<T2>& rhs) {
		base::assign(rhs.begin(), rhs.end());
		return *this;
	}

  private:
	template<class Int>
	void construct_range_dispatch(Int count, Int val, true_type) {
		base::size_ = min(size_type(count), N);
		uninitialized_fill_n(base::begin(), base::size_, value_type(val));
	}
	template<class InputIt>
	void construct_range_dispatch(InputIt first, InputIt last, false_type) {
		base::size_ = min(size_type(distance(first, last)), N);
		uninitialized_copy_n(first, base::size_, base::begin());
	}

	typedef typename
	aligned_storage<sizeof(T), alignment_of<T>::value>::type element;

	array<element, N> data_;
};

template<typename T>
inline bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
	return lhs.size() == rhs.size() &&
	       equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template<typename T>
inline bool operator<(const vector<T>& lhs, const vector<T>& rhs) {
	return lexicographical_compare(lhs.cbegin(), lhs.cend(),
	                               rhs.cbegin(), rhs.cend());
}

} /* namespace sstl */

#endif /* STATIC_STL_VECTOR_H_ */
