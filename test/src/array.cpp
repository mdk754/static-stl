#include "test.h"

#include "array.h"
#include "utility.h"

namespace array {

struct array_construct : public test {
	array_construct() : test("array<> constructors") {}

	bool run() {
		sstl::array<char, 7> a;
		sstl::array<char, 7> b(42);
		sstl::array<char, 7> c(b);
		sstl::array<char>& c1 = c;
		sstl::array<char, 12> d(c1);
		sstl::array<int, 5> e(d);

		return
		    a[0] == 0 &&
		    b[2] == 42 &&
		    c[4] == 42 &&
		    d[6] == 42 &&
		    d[7] == 0 &&
		    e[0] == 42 &&
		    e[4] == 42;
	}
};

array_construct t1;

struct array_assign : public test {
	array_assign() : test("array<> assignment") {}

	bool run() {
		sstl::array<char, 7> a(5);
		a[1] = 3;
		a[4] = 19;

		sstl::array<char, 7> b(0);
		b = a;

		sstl::array<int, 3> c(0);
		c = a;

		sstl::array<int, 11> d(0);
		d = a;

		return
		    b[0] == 5 &&
		    b[1] == 3 &&
		    b[4] == 19 &&
		    c[0] == 5 &&
		    c[1] == 3 &&
		    d[0] == 5 &&
		    d[1] == 3 &&
		    d[4] == 19 &&
		    d[7] == 0 &&
		    d[10] == 0;
	}
};

array_assign t2;

struct array_at : public test {
	array_at() : test("array<> indexing") {}

	bool run() {
		const size_t count = 13;
		sstl::array<int, count> a;

		for (unsigned i = 0; i < count; ++i) {
			a.data()[i] = ~i;
		}

		for (unsigned i = 0; i < count; ++i) {
			if (a.at(i) != a.data()[i] || a[i] != a.data()[i]) { return false; }
		}

		int overflow = a.data()[count];
		a.at(count) = ~overflow;

		if (a.data()[count] != overflow) { return false; }

		a.front() = 42;
		a.back() = 241;

		return a[0] == 42 && a[count - 1] == 241;
	}
};

array_at t3;

struct array_iterate : public test {
	array_iterate() : test("array<> iterators") {}

	bool run() {
		sstl::array<unsigned, 10> a;

		unsigned i = 0;

		for (auto it = a.begin(); it != a.end(); ++it) {
			*it = i++;
		}

		using namespace sstl::rel_ops;

		for (auto it = a.crbegin(); it != a.crend(); ++it) {
			if (*it != --i) { return false; }
		}

		return true;
	}
};

array_iterate t4;

struct array_capacity : public test {
	array_capacity() : test("array<> size and capacity") {}

	bool run() {
		sstl::array<char, 10> a;

		a[5] = 13;

		if (a.empty() || a.size() != 10 || a.max_size() != 10) { return false; }

		return true;
	}
};

array_capacity t5;

} /* namespace array */
