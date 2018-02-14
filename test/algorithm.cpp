#include "test.h"

#include "algorithm.h"

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

struct fill_int : public test {
	fill_int() : test("fill() with integers") {}

	bool run() {
		size_t count = 7;

		int a[count] = {0};

		sstl::fill(a, &a[count], 20);

		for (unsigned i = 0; i < count; ++i) {
			if (a[i] != 20) { return false; }
		}

		return true;
	}
};

fill_int t5;

struct fill_n_int : public test {
	fill_n_int() : test("fill_n() with integers") {}

	bool run() {
		size_t count = 7;
		size_t filled = count - 2;

		int a[count] = {0};

		sstl::fill_n(a, filled, 20);

		for (unsigned i = 0; i < filled; ++i) {
			if (a[i] != 20) { return false; }
		}

		for (unsigned i = filled; i < count; ++i) {
			if (a[i] != 0) { return false; }
		}

		return true;
	}
};

fill_n_int t6;

struct copy_int : public test {
	copy_int() : test("copy() with integers") {}

	bool run() {
		size_t count = 7;

		int a[count] = {0};
		int b[count] = {0};

		for (unsigned i = 0; i < count; ++i) {
			a[i] = 9;
		}

		sstl::copy(a, &a[count], b);

		for (unsigned i = 0; i < count; ++i) {
			if (b[i] != 9) { return false; }
		}

		return true;
	}
};

copy_int t7;

struct copy_n_int : public test {
	copy_n_int() : test("copy_n() with integers") {}

	bool run() {
		size_t count = 7;
		size_t filled = count - 2;

		int a[count] = {0};
		int b[count] = {0};

		for (unsigned i = 0; i < count; ++i) {
			a[i] = 9;
		}

		sstl::copy_n(a, filled, b);

		for (unsigned i = 0; i < filled; ++i) {
			if (b[i] != 9) { return false; }
		}

		for (unsigned i = filled; i < count; ++i) {
			if (b[i] != 0) { return false; }
		}

		return true;
	}
};

copy_n_int t8;

struct min_int_unique : public test {
	min_int_unique() : test("min() with unique integers") {}

	bool run() {
		int a = 7;
		int b = 13;

		return sstl::min(a, b) == 7;
	}
};

min_int_unique t9;

struct min_int_equal : public test {
	min_int_equal() : test("min() with equal integers") {}

	bool run() {
		int a = 7;
		int b = 7;

		return sstl::min(a, b) == 7;
	}
};

min_int_equal t10;

struct max_int_unique : public test {
	max_int_unique() : test("max() with unique integers") {}

	bool run() {
		int a = 7;
		int b = 13;

		return sstl::max(a, b) == 13;
	}
};

max_int_unique t11;

struct max_int_equal : public test {
	max_int_equal() : test("max() with equal integers") {}

	bool run() {
		int a = 7;
		int b = 7;

		return sstl::max(a, b) == 7;
	}
};

max_int_equal t12;

struct equality : public test {
	equality() : test("equal() with integers") {}

	bool run() {
		int a[5] = { 1, 2, 3, 4, 5 };
		int b[5] = { 1, 2, 3, 4, 5 };

		if (!sstl::equal(&a[0], &a[5], &b[0])) { return false; }

		b[3] = 0;

		if (sstl::equal(&a[0], &a[5], &b[0])) { return false; }

		return true;
	}
};

equality t16;

struct lexicographical_comparison : public test {
	lexicographical_comparison() :
		test("lexicographical_compare() with integers") {}

	bool run() {
		int a[5] = { 1, 2, 3, 4, 5 };

		{
			int b[5] = { 1, 1, 3, 4, 5 };

			if (sstl::lexicographical_compare(&a[0], &a[5], &b[0], &b[5])) {
				return false;
			}

			if (!sstl::lexicographical_compare(&b[0], &b[5], &a[0], &a[5])) {
				return false;
			}
		}

		if (sstl::lexicographical_compare(&a[0], &a[5], &a[0], &a[3])) {
			return false;
		}

		if (sstl::lexicographical_compare(&a[0], &a[5], &a[0], &a[5])) {
			return false;
		}

		if (!sstl::lexicographical_compare(&a[0], &a[0], &a[0], &a[3])) {
			return false;
		}

		if (sstl::lexicographical_compare(&a[0], &a[0], &a[3], &a[3])) {
			return false;
		}

		return true;
	}
};

lexicographical_comparison t17;

} /* namespace algorithm */
