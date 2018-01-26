#ifndef STATIC_STL_ITERATOR_H_
#define STATIC_STL_ITERATOR_H_

#include <cstddef>

namespace sstl {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/** Type trait class that provides uniform interface to the properties of Iterator types. */
template<class Iterator>
struct iterator_traits {
	typedef typename Iterator::iterator_category iterator_category;
	typedef typename Iterator::value_type        value_type;
	typedef typename Iterator::pointer           pointer;
	typedef typename Iterator::reference         reference;
	typedef typename Iterator::difference_type   difference_type;
};

template<typename T>
struct iterator_traits<T*> {
	typedef random_access_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef T*                         pointer;
	typedef T&                         reference;
	typedef ptrdiff_t                  difference_type;
};

template<typename T>
struct iterator_traits<const T*> {
	typedef random_access_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef const T*                   pointer;
	typedef const T&                   reference;
	typedef ptrdiff_t                  difference_type;
};

template<class Iterator>
class reverse_iterator {
  public:
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type        value_type;
	typedef typename iterator_traits<Iterator>::pointer           pointer;
	typedef typename iterator_traits<Iterator>::reference         reference;
	typedef typename iterator_traits<Iterator>::difference_type   difference_type;

	/** Default constructor. */
	reverse_iterator() : it_() {}
	/** Copy constructor. */
	reverse_iterator(const reverse_iterator& other) : it_(other.it_) {}
	/** Copy adapter constructor. */
	template<typename U>
	reverse_iterator(const reverse_iterator<U>& other) : it_(other.it_) {}
	/** Construct from an Iterator. */
	explicit reverse_iterator(Iterator it) : it_(it) {}

	/** Copy assignment operator. */
	template<class U>
	reverse_iterator& operator=(const reverse_iterator<U>& other) {
		it_ = other.it_;
		return *this;
	}
	/** Returns a reference to the element previous to current. */
	reference operator*() const { Iterator tmp(it_); return *--tmp; }
	/** Returns a pointer to the element previous to current. */
	pointer operator->() const { return &(operator*()); }
	/** Returns a reference to the element at specified relative location. */
	reference operator[](difference_type n) const { return it_[-n - 1]; }
	/** Pre-increments the iterator, applied in reverse. */
	reverse_iterator& operator++() { --it_; return *this; }
	/** Post-increments the iterator, applied in reverse. */
	reverse_iterator operator++(int) { reverse_iterator tmp(*this); --it_; return *tmp; }
	/** Pre-decrements the iterator, applied in reverse. */
	reverse_iterator& operator--() { ++it_; return *this; }
	/** Post-decrements the iterator, applied in reverse. */
	reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++it_; return *tmp; }
	/** Returns an iterator which is advanced by n positions. */
	reverse_iterator operator+(difference_type n) const { return reverse_iterator(it_ - n); }
	/** Returns an iterator which is advanced by -n positions. */
	reverse_iterator operator-(difference_type n) const { return reverse_iterator(it_ + n); }
	/** Advances the iterator by n positions. */
	reverse_iterator& operator+=(difference_type n) { return it_ -= n; }
	/** Advances the iterator by -n positions. */
	reverse_iterator& operator-=(difference_type n) { return it_ += n; }

	/** Returns the underlying base iterator. */
	Iterator base() const { return it_; }

  protected:
	Iterator it_;
};

template<class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() == rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() < rhs.base();
}

} /* namespace sstl */

#endif /* STATIC_STL_ITERATOR_H_ */
