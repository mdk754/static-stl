#include "catch/catch.hpp"

#include "algorithm.h"

struct Foo { int value; };

TEST_CASE("Swap two types with one another", "[swap]") {
	SECTION("Using fundamental type") {
		int a = 16;
		int b = 256;

		sstl::swap(a, b);

		REQUIRE(a == 256);
		REQUIRE(b == 16);
	}

	SECTION("Using pointer type") {
		int a = 16;
		int b = 256;

		int* pa = &a;
		int* pb = &b;

		sstl::swap(pa, pb);

		REQUIRE(a == 16);
		REQUIRE(*pa == 256);
		REQUIRE(b == 256);
		REQUIRE(*pb == 16);
	}

	SECTION("Using user-defined type") {
		Foo a, b;

		a.value = 8;
		b.value = 128;

		sstl::swap(a, b);

		REQUIRE(a.value == 128);
		REQUIRE(b.value == 8);
	}
}

TEST_CASE("Swap two types via iterators", "[swap]") {
	SECTION("Single swap via iterator") {
		int a = 32;
		int b = 64;

		sstl::iter_swap(&a, &b);

		REQUIRE(a == 64);
		REQUIRE(b == 32);
	}

	SECTION("Swap range via iterator") {
		const size_t count = 4;

		unsigned a[count] = {0, 1, 2, 3};
		unsigned b[count] = {3, 2, 1, 0};

		sstl::swap_ranges(&a[0], &a[count], &b[0]);

		REQUIRE(a[0] == 3);
		REQUIRE(a[1] == 2);
		REQUIRE(a[2] == 1);
		REQUIRE(a[3] == 0);

		REQUIRE(b[0] == 0);
		REQUIRE(b[1] == 1);
		REQUIRE(b[2] == 2);
		REQUIRE(b[3] == 3);
	}
}

TEST_CASE("Fill array with values", "[fill]") {
	const size_t count = 3;
	int a[count] = {0};

	SECTION("Fill range using iterators") {
		sstl::fill(&a[0], &a[count], 32);

		REQUIRE(a[0] == 32);
		REQUIRE(a[1] == 32);
		REQUIRE(a[2] == 32);
	}

	SECTION("Fill range with count items") {
		sstl::fill_n(&a[0], count, 64);

		REQUIRE(a[0] == 64);
		REQUIRE(a[1] == 64);
		REQUIRE(a[2] == 64);
	}
}

TEST_CASE("Copy array to another", "[copy]") {
	const size_t count = 3;
	int a[count] = {2, 2, 2};

	SECTION("Copy range using iterators") {
		int b[count] = {0};

		sstl::copy(&a[0], &a[count], &b[0]);

		REQUIRE(b[0] == 2);
		REQUIRE(b[1] == 2);
		REQUIRE(b[2] == 2);
	}

	SECTION("Copy range with count items") {
		int b[count] = {0};

		sstl::copy_n(&a[0], count, b);

		REQUIRE(b[0] == 2);
		REQUIRE(b[1] == 2);
		REQUIRE(b[2] == 2);
	}
}

TEST_CASE("Check the minimum value", "[comparison]") {
	int a = 7;

	SECTION("When the values are equal") {
		int b = 7;

		REQUIRE(sstl::min(a, b) == 7);
	}

	SECTION("When the first value is lower") {
		int b = 9;

		REQUIRE(sstl::min(a, b) == 7);
	}

	SECTION("When the second value is lower") {
		int b = 3;

		REQUIRE(sstl::min(a, b) == 3);
	}
}

TEST_CASE("Check the maximum value", "[comparison]") {
	int a = 7;

	SECTION("When the values are equal") {
		int b = 7;

		REQUIRE(sstl::max(a, b) == 7);
	}

	SECTION("When the first value is lower") {
		int b = 9;

		REQUIRE(sstl::max(a, b) == 9);
	}

	SECTION("When the second value is lower") {
		int b = 3;

		REQUIRE(sstl::max(a, b) == 7);
	}
}

TEST_CASE("Check for equality", "[comparison]") {
	const size_t count = 3;
	int a[count] = {0, 1, 2};

	SECTION("When the values are equal") {
		int b[count] = {0, 1, 2};

		REQUIRE(sstl::equal(&a[0], &a[count], &b[0]));
	}

	SECTION("When the values are not equal") {
		int b[count] = {0};

		REQUIRE(!sstl::equal(&a[0], &a[count], &b[0]));
	}
}

TEST_CASE("Lexicographically compare values", "[comparison]") {
	const size_t count = 5;
	int a[count] = {0, 1, 2, 3, 4};

	SECTION("First mismatching element defines which is less than") {
		SECTION("First array less than") {
			int b[count] = {0, 7, 2, 3, 4};

			REQUIRE(sstl::lexicographical_compare(&a[0], &a[count],
			                                      &b[0], &b[count]));
		}

		SECTION("Second array less than") {
			int b[count] = {0, 1, 0, 3, 4};

			REQUIRE(!sstl::lexicographical_compare(&a[0], &a[count],
			                                       &b[0], &b[count]));
		}
	}

	SECTION("If one range is a prefix of the other, the shorter is less than") {
		REQUIRE(sstl::lexicographical_compare(&a[0], &a[2],
		                                      &a[0], &a[count]));
		REQUIRE(!sstl::lexicographical_compare(&a[0], &a[count],
		                                       &a[0], &a[1]));
	}

	SECTION("If two ranges have the same elements and length, they are equal") {
		REQUIRE(!sstl::lexicographical_compare(&a[0], &a[count],
		                                       &a[0], &a[count]));
	}

	SECTION("An empty range is less than any non-empty range") {
		REQUIRE(sstl::lexicographical_compare(&a[0], &a[0],
		                                      &a[0], &a[count]));
		REQUIRE(!sstl::lexicographical_compare(&a[0], &a[count],
		                                       &a[0], &a[0]));
	}

	SECTION("Two empty ranges are equal") {
		REQUIRE(!sstl::lexicographical_compare(a, a, &a[3], &a[3]));
		REQUIRE(!sstl::lexicographical_compare(&a[3], &a[3], a, a));
	}
}

TEST_CASE("Reverse an array", "[reverse]") {
	SECTION("With an even number of elements") {
		const size_t count = 4;
		int start[count] = {0, 1, 2, 3};
		int finish[count] = {3, 2, 1, 0};

		sstl::reverse(start, &start[count]);

		REQUIRE(start[0] == finish[0]);
		REQUIRE(start[1] == finish[1]);
		REQUIRE(start[2] == finish[2]);
		REQUIRE(start[3] == finish[3]);
	}

	SECTION("With an odd number of elements") {
		const size_t count = 3;
		int start[count] = {0, 1, 2};
		int finish[count] = {2, 1, 0};

		sstl::reverse(start, &start[count]);

		REQUIRE(start[0] == finish[0]);
		REQUIRE(start[1] == finish[1]);
		REQUIRE(start[2] == finish[2]);
	}
}

TEST_CASE("Rotate an array", "[rotate]") {
	const size_t count = 4;
	int start[count] = {0, 1, 2, 3};

	SECTION("Left rotate") {
		int finish[count] = {1, 2, 3, 0};

		sstl::rotate(&start[0], &start[1], &start[count]);

		REQUIRE(start[0] == finish[0]);
		REQUIRE(start[1] == finish[1]);
		REQUIRE(start[2] == finish[2]);
		REQUIRE(start[3] == finish[3]);
	}

	SECTION("Right rotate") {
		int finish[count] = {3, 0, 1, 2};

		sstl::rotate(
		    sstl::reverse_iterator<int*>(&start[count]),
		    sstl::reverse_iterator<int*>(&start[count - 1]),
		    sstl::reverse_iterator<int*>(&start[0])
		);

		REQUIRE(start[0] == finish[0]);
		REQUIRE(start[1] == finish[1]);
		REQUIRE(start[2] == finish[2]);
		REQUIRE(start[3] == finish[3]);
	}
}
