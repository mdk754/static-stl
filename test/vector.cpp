#include "catch/catch.hpp"

#include "vector.h"

TEST_CASE("Construct a vector", "[constructor]") {
	SECTION("Default construct") {
		sstl::vector<char, 3> a;

		REQUIRE(a.size() == 0);
		REQUIRE(a.capacity() == 3);
	}

	SECTION("Value initialize") {
		SECTION("Size fits") {
			sstl::vector<int, 3> a(2, 55);

			REQUIRE(a.size() == 2);
			REQUIRE(a.capacity() == 3);
			REQUIRE(a.at(0) == 55);
			REQUIRE(a.at(1) == 55);
		}

		SECTION("Size too large") {
			sstl::vector<int, 3> a(4, 55);

			REQUIRE(a.size() == 3);
			REQUIRE(a.capacity() == 3);
			REQUIRE(a.at(0) == 55);
			REQUIRE(a.at(1) == 55);
			REQUIRE(a.at(2) == 55);
		}

		SECTION("From a range") {
			const size_t count = 3;
			int array[count] = {0, 1, 2};

			sstl::vector<int, count> a(&array[0], &array[count]);

			REQUIRE(a.size() == count);
			REQUIRE(a.capacity() == count);
			REQUIRE(a.at(0) == 0);
			REQUIRE(a.at(1) == 1);
			REQUIRE(a.at(2) == 2);
		}
	}

	SECTION("Copy construct") {
		sstl::vector<unsigned char, 3> a(3, 8);

		SECTION("From an equivalent vector") {
			sstl::vector<unsigned char, 3> b(a);

			REQUIRE(b.size() == a.size());
			REQUIRE(b.capacity() == 3);
			REQUIRE(b.at(0) == a.at(0));
			REQUIRE(b.at(1) == a.at(1));
			REQUIRE(b.at(2) == a.at(2));
		}

		SECTION("From a smaller vector") {
			sstl::vector<unsigned char, 5> b(a);

			REQUIRE(b.size() == a.size());
			REQUIRE(b.capacity() == 5);
			REQUIRE(b.at(0) == a.at(0));
			REQUIRE(b.at(1) == a.at(1));
			REQUIRE(b.at(2) == a.at(2));
		}

		SECTION("From a larger vector") {
			sstl::vector<unsigned char, 2> b(a);

			REQUIRE(b.size() == 2);
			REQUIRE(b.capacity() == 2);
			REQUIRE(b.at(0) == a.at(0));
			REQUIRE(b.at(1) == a.at(1));
		}

		SECTION("From a compatible type") {
			sstl::vector<unsigned, 4> b(a);

			REQUIRE(b.size() == a.size());
			REQUIRE(b.capacity() == 4);
			REQUIRE(b.at(0) == a.at(0));
			REQUIRE(b.at(1) == a.at(1));
			REQUIRE(b.at(2) == a.at(2));
		}
	}
}

TEST_CASE("Assign a vector", "[assignment]") {
	sstl::vector<char, 3> a(3, 8);

	SECTION("From an equivalent vector") {
		sstl::vector<char, 3> b(1, 16);

		b = a;

		REQUIRE(b.size() == a.size());
		REQUIRE(b.capacity() == 3);
		REQUIRE(b.at(0) == a.at(0));
		REQUIRE(b.at(1) == a.at(1));
		REQUIRE(b.at(2) == a.at(2));
	}

	SECTION("From a smaller vector") {
		sstl::vector<char, 5> b(5, 32);

		b = a;

		REQUIRE(b.size() == a.size());
		REQUIRE(b.capacity() == 5);
		REQUIRE(b.at(0) == a.at(0));
		REQUIRE(b.at(1) == a.at(1));
		REQUIRE(b.at(2) == a.at(2));
	}

	SECTION("From a larger vector") {
		sstl::vector<char, 2> b(2, 48);

		b = a;

		REQUIRE(b.size() == 2);
		REQUIRE(b.capacity() == 2);
		REQUIRE(b.at(0) == a.at(0));
		REQUIRE(b.at(1) == a.at(1));
	}

	SECTION("From a compatible type") {
		sstl::vector<int, 4> b(4, 64);

		b = a;

		REQUIRE(b.size() == a.size());
		REQUIRE(b.capacity() == 4);
		REQUIRE(b.at(0) == a.at(0));
		REQUIRE(b.at(1) == a.at(1));
		REQUIRE(b.at(2) == a.at(2));
	}
}

TEST_CASE("Index into a vector", "[access]") {
	const size_t count = 3;
	sstl::vector<int, count> a(count, 16);

	SECTION("Using random access operator") {
		REQUIRE(a[0] == 16);
		REQUIRE(a[1] == 16);
		REQUIRE(a[2] == 16);
	}

	SECTION("Using bounds checked method") {
		SECTION("Within bounds") {
			REQUIRE(a.at(0) == 16);
			REQUIRE(a.at(1) == 16);
			REQUIRE(a.at(2) == 16);
		}

		SECTION("Stack overflow") {
			int overflow = a.data()[count];
			a.at(count) = ~overflow;

			REQUIRE(a.at(count) == ~overflow);
			REQUIRE(a.data()[count] == overflow);
		}
	}

	SECTION("Using front and back") {
		a.front() = 12;
		a.back() = 24;

		REQUIRE(a[0] == 12);
		REQUIRE(a[a.size() - 1] == 24);
	}

	SECTION("Using underlying pointer") {
		a.front() = 12;
		a.back() = 24;

		REQUIRE(a.data()[0] == 12);
		REQUIRE(a.data()[a.size() - 1] == 24);
	}
}

TEST_CASE("Iterate over a vector", "[iterator]") {
	typedef sstl::vector<int, 3> vector;
	vector a(3, 4);

	SECTION("Forward direction") {
		for (vector::iterator it = a.begin(); it != a.end(); ++it) {
			*it = 16;
		}

		REQUIRE(a[0] == 16);
		REQUIRE(a[1] == 16);
		REQUIRE(a[2] == 16);
	}

	SECTION("Reverse direction") {
		int i = 0;

		for (vector::reverse_iterator it = a.rbegin();
		        it != a.rend(); ++it, ++i) {
			*it = i;
		}

		REQUIRE(a[0] == 2);
		REQUIRE(a[1] == 1);
		REQUIRE(a[2] == 0);
	}

	SECTION("With const-qualified array") {
		const vector b(3, 16);

		size_t count = 0;

		for (vector::const_iterator it = b.begin(); it != b.end(); ++it) {
			if (*it == 16) { ++count; }
		}

		REQUIRE(count == 3);
	}
}

TEST_CASE("Check the size and capacity of a vector", "[capacity]") {
	sstl::vector<int, 8> a(2, 16);

	REQUIRE(!a.empty());
	REQUIRE(a.size() == 2);
	REQUIRE(a.max_size() == 8);
	REQUIRE(a.capacity() == 8);
}

TEST_CASE("Clear a vector of its contents", "[capacity]") {
	sstl::vector<int, 5> a(5, 128);

	REQUIRE(a.size() == 5);

	a.clear();

	REQUIRE(a.size() == 0);
}

TEST_CASE("Insert values into a vector", "[modifiers]") {
	sstl::vector<char, 16> a(4, 'a');

	SECTION("At the front") {
		a.insert(a.begin(), 'b');

		REQUIRE(a.front() == 'b');
	}

	SECTION("At the back") {
		a.insert(a.end(), 'c');

		REQUIRE(a.back() == 'c');
	}

	SECTION("In the middle") {
		a.insert(a.begin() + 2, 'd');

		REQUIRE(a[2] == 'd');
	}

	SECTION("Many at a time") {
		a.insert(a.begin() + 1, 2, 'e');

		REQUIRE(a[0] == 'a');
		REQUIRE(a[1] == 'e');
		REQUIRE(a[2] == 'e');
		REQUIRE(a[3] == 'a');
	}

	SECTION("With a range") {
		char b[4] = {'b', 'c', 'd', 'e'};

		a.insert(a.begin() + 1, b, b + 4);

		REQUIRE(a[0] == 'a');
		REQUIRE(a[1] == 'b');
		REQUIRE(a[2] == 'c');
		REQUIRE(a[3] == 'd');
		REQUIRE(a[4] == 'e');
	}
}

TEST_CASE("Remove values from a vector", "[modifiers]") {
	sstl::vector<int, 16> a(8, 'a');

	SECTION("Erase the first element") {
		a.insert(a.begin(), 'b');

		REQUIRE(a.size() == 9);
		REQUIRE(a.front() == 'b');

		a.erase(a.begin());

		REQUIRE(a.size() == 8);
		REQUIRE(a.front() == 'a');
	}

	SECTION("Erase a middle element") {
		a.insert(a.begin() + 3, 'b');

		REQUIRE(a.size() == 9);
		REQUIRE(a[3] == 'b');

		a.erase(a.begin() + 3);

		REQUIRE(a.size() == 8);
		REQUIRE(a[3] == 'a');
	}

	SECTION("Erase the last element") {
		a.insert(a.end(), 'b');

		REQUIRE(a.size() == 9);
		REQUIRE(a.back() == 'b');

		a.erase(a.end() - 1);

		REQUIRE(a.size() == 8);
		REQUIRE(a.back() == 'a');
	}

	SECTION("Erase a range of elements") {
		a.insert(a.begin(), 'b');

		a.erase(a.begin() + 1, a.end());

		REQUIRE(a.size() == 1);
		REQUIRE(a.back() == 'b');
	}
}

TEST_CASE("Push and pop values on the vector", "[modifiers]") {
	sstl::vector<int, 8> a;

	a.push_back(256);
	a.push_back(32);

	REQUIRE(a.size() == 2);
	REQUIRE(a[0] == 256);
	REQUIRE(a[1] == 32);

	a.pop_back();
	a.pop_back();

	REQUIRE(a.size() == 0);
}

TEST_CASE("Vector can be resized", "[modifiers]") {
	sstl::vector<int, 4> a(2, 16);

	SECTION("Resizing smaller decreases size") {
		a.resize(1);

		REQUIRE(a.size() == 1);
	}

	SECTION("Resizing bigger increases size") {
		SECTION("With default values") {
			a.resize(3);

			REQUIRE(a.size() == 3);
			REQUIRE(a[2] == 0);
		}

		SECTION("With initialized values") {
			a.resize(3, 32);

			REQUIRE(a.size() == 3);
			REQUIRE(a[2] == 32);
		}
	}
}

TEST_CASE("Test vectors for equality", "[comparison]") {
	sstl::vector<char, 3> a(3, 16);

	SECTION("With an equal size vector") {
		SECTION("With same contents") {
			sstl::vector<char, 3> b(3, 16);

			REQUIRE(a == b);
		}

		SECTION("With differing contents") {
			sstl::vector<char, 3> b(3, 32);

			REQUIRE(a != b);
		}
	}

	SECTION("With a smaller size vector") {
		sstl::vector<char, 2> b(2, 16);

		REQUIRE(a != b);
	}

	SECTION("With a larger size vector") {
		sstl::vector<char, 5> b(5, 16);

		REQUIRE(a != b);
	}
}

TEST_CASE("Compare vectors lexicographically", "[comparison]") {
	sstl::vector<int, 4> a(4, 16);

	SECTION("With an equal size vector") {
		SECTION("With lower value") {
			sstl::vector<int, 4> b(4, 8);

			REQUIRE(a > b);
			REQUIRE(a >= b);
			REQUIRE(b < a);
			REQUIRE(b <= a);
		}

		SECTION("With higher value") {
			sstl::vector<int, 4> b(4, 32);

			REQUIRE(a < b);
			REQUIRE(a <= b);
			REQUIRE(b > a);
			REQUIRE(b >= a);
		}

		SECTION("With equal value") {
			sstl::vector<int, 4> b(4, 16);

			REQUIRE(a <= b);
			REQUIRE(a >= b);
		}
	}

	SECTION("With a smaller size vector") {
		sstl::vector<int, 2> b(2, 16);

		REQUIRE(b < a);
	}

	SECTION("With a larger size vector") {
		sstl::vector<int, 8> b(8, 16);

		REQUIRE(a < b);
	}
}
