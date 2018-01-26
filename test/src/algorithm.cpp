#include "test.h"

#include "sstl"

namespace algorithm {

struct swap_int : public test {
	swap_int() : test("swap() with integer") {}

	bool run() {
		int x, x2;
		x = x2 = 13;

		int y, y2;
		y = y2 = 47;

		sstl::swap(x, y);

		return x == y2 && y == x2;
	}
};

swap_int t1;

struct swap_foo : public test {
	swap_foo() : test("swap() with custom type") {}

	bool run() {
		struct Foo {
			int x;
			int y;
		};

		Foo a = { 13, 47 };
		Foo b = { 25, 42 };

		sstl::swap(a, b);

		return
		    a.x == 25 && a.y == 42 &&
		    b.x == 13 && b.y == 47;
	}
};

swap_foo t2;

struct iter_swap_int : public test {
	iter_swap_int() : test("iter_swap() with integer") {}

	bool run() {
		int x, x2;
		x = x2 = 13;

		int y, y2;
		y = y2 = 47;

		sstl::iter_swap(&x, &y);

		return x == y2 && y == x2;
	}
};

iter_swap_int t3;

struct swap_ranges_int : public test {
	swap_ranges_int() : test("swap_ranges() with integers") {}

	bool run() {
		size_t count = 20;

		unsigned a[count];
		unsigned b[count];

		for (unsigned i = 0, j = count; i < count; ++i, --j) {
			a[i] = i;
			b[i] = j;
		}

		sstl::swap_ranges(a, &a[count], b);

		for (unsigned i = 0, j = count; i < count; ++i, --j) {
			if (a[i] != j || b[i] != i) {
				return false;
			}
		}

		return true;
	}
};

swap_ranges_int t4;

} /* namespace algorithm */
