#include "catch/catch.hpp"

#include "array.h"

TEST_CASE("Construct an array", "[constructor]") {
	SECTION("Default construct") {
		sstl::array<char, 3> a;

		REQUIRE(a[0] == 0);
		REQUIRE(a[1] == 0);
		REQUIRE(a[2] == 0);
	}

	SECTION("Value initialize") {
		sstl::array<int, 3> a(16);

		REQUIRE(a[0] == 16);
		REQUIRE(a[1] == 16);
		REQUIRE(a[2] == 16);
	}

	SECTION("Copy construct") {
		sstl::array<unsigned char, 3> a(8);

		SECTION("From an equivalent array") {
			sstl::array<unsigned char, 3> b(a);

			REQUIRE(b[0] == a[0]);
			REQUIRE(b[1] == a[1]);
			REQUIRE(b[2] == a[2]);
		}

		SECTION("From a smaller array") {
			sstl::array<unsigned char, 5> b(a);

			REQUIRE(b[0] == a[0]);
			REQUIRE(b[1] == a[1]);
			REQUIRE(b[2] == a[2]);
			REQUIRE(b[3] == 0);
			REQUIRE(b[4] == 0);
		}

		SECTION("From a larger array") {
			sstl::array<unsigned char, 2> b(a);

			REQUIRE(b[0] == a[0]);
			REQUIRE(b[1] == a[1]);
		}

		SECTION("From a compatible type") {
			sstl::array<unsigned, 4> b(a);

			REQUIRE(b[0] == a[0]);
			REQUIRE(b[1] == a[1]);
			REQUIRE(b[2] == a[2]);
			REQUIRE(b[3] == 0);
		}
	}
}

TEST_CASE("Assign an array", "[assignment]") {
	sstl::array<char, 3> a(8);

	SECTION("From an equivalent array") {
		sstl::array<char, 3> b(16);

		b = a;

		REQUIRE(b[0] == a[0]);
		REQUIRE(b[1] == a[1]);
		REQUIRE(b[2] == a[2]);
	}

	SECTION("From a smaller array") {
		sstl::array<char, 5> b(32);

		b = a;

		REQUIRE(b[0] == a[0]);
		REQUIRE(b[1] == a[1]);
		REQUIRE(b[2] == a[2]);
		REQUIRE(b[3] == 0);
		REQUIRE(b[4] == 0);
	}

	SECTION("From a larger array") {
		sstl::array<char, 2> b(48);

		b = a;

		REQUIRE(b[0] == a[0]);
		REQUIRE(b[1] == a[1]);
	}

	SECTION("From a compatible type") {
		sstl::array<int, 4> b(64);

		b = a;

		REQUIRE(b[0] == a[0]);
		REQUIRE(b[1] == a[1]);
		REQUIRE(b[2] == a[2]);
		REQUIRE(b[3] == 0);
	}
}

TEST_CASE("Index into an array", "[access]") {
	const size_t count = 3;
	sstl::array<int, count> a;

	for (size_t i = 0; i < count; ++i) {
		a.data()[i] = ~i;
	}

	SECTION("Using random access operator") {
		REQUIRE(a[0] == ~0);
		REQUIRE(a[1] == ~1);
		REQUIRE(a[2] == ~2);
	}

	SECTION("Using bounds checked method") {
		SECTION("Within bounds") {
			REQUIRE(a.at(0) == ~0);
			REQUIRE(a.at(1) == ~1);
			REQUIRE(a.at(2) == ~2);
		}

		SECTION("Stack overflow") {
			int overflow = a.data()[count];
			a.at(count) = ~overflow;

			REQUIRE(a.at(count) == ~overflow);
			REQUIRE(a.data()[count] == overflow);
		}
	}
}

TEST_CASE("Iterate over an array", "[iterator]") {
	typedef sstl::array<int, 3> array;
	array a(4);

	SECTION("Forward direction") {
		for (array::iterator it = a.begin(); it != a.end(); ++it) {
			*it = 16;
		}

		REQUIRE(a[0] == 16);
		REQUIRE(a[1] == 16);
		REQUIRE(a[2] == 16);
	}

	SECTION("Reverse direction") {
		int i = 0;

		for (array::reverse_iterator it = a.rbegin();
		        it != a.rend(); ++it, ++i) {
			*it = i;
		}

		REQUIRE(a[0] == 2);
		REQUIRE(a[1] == 1);
		REQUIRE(a[2] == 0);
	}

	SECTION("With const-qualified array") {
		const array b(16);

		size_t count = 0;

		for (array::const_iterator it = b.begin(); it != b.end(); ++it) {
			if (*it == 16) { ++count; }
		}

		REQUIRE(count == 3);
	}
}

TEST_CASE("Check the capacity of an array", "[capacity]") {
	sstl::array<int, 8> a;

	REQUIRE(!a.empty());
	REQUIRE(a.size() == 8);
	REQUIRE(a.max_size() == 8);
}

TEST_CASE("Test arrays for equality", "[comparison]") {
	sstl::array<char, 3> a(16);

	SECTION("With an equal size array") {
		SECTION("With same contents") {
			sstl::array<char, 3> b(16);

			REQUIRE(a == b);
		}

		SECTION("With differing contents") {
			sstl::array<char, 3> b(32);

			REQUIRE(a != b);
		}
	}

	SECTION("With a smaller size array") {
		sstl::array<char, 2> b(16);

		REQUIRE(a != b);
	}

	SECTION("With a larger size array") {
		sstl::array<char, 5> b(16);

		REQUIRE(a != b);
	}
}

TEST_CASE("Compare arrays lexicographically", "[comparison]") {
	sstl::array<int, 4> a(16);

	SECTION("With an equal size array") {
		SECTION("With lower value") {
			sstl::array<int, 4> b(8);

			REQUIRE(a > b);
			REQUIRE(a >= b);
			REQUIRE(b < a);
			REQUIRE(b <= a);
		}

		SECTION("With higher value") {
			sstl::array<int, 4> b(32);

			REQUIRE(a < b);
			REQUIRE(a <= b);
			REQUIRE(b > a);
			REQUIRE(b >= a);
		}

		SECTION("With equal value") {
			sstl::array<int, 4> b(16);

			REQUIRE(a <= b);
			REQUIRE(a >= b);
		}
	}

	SECTION("With s smaller size array") {
		sstl::array<int, 2> b(16);

		REQUIRE(b < a);
	}

	SECTION("With s larger size array") {
		sstl::array<int, 8> b(16);

		REQUIRE(a < b);
	}
}
