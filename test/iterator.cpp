#include "catch/catch.hpp"

#include "iterator.h"

TEST_CASE("Get the distance between two iterators", "[comparison]") {
	const size_t count = 3;
	int a[count];

	REQUIRE(sstl::distance(a, a) == 0);
	REQUIRE(sstl::distance(&a[0], &a[count]) == count);
	REQUIRE(sstl::distance(sstl::reverse_iterator<int*>(&a[count]),
	                       sstl::reverse_iterator<int*>(&a[0])) == count);
}
