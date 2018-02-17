#include "catch/catch.hpp"

#include "type_traits.h"

TEST_CASE("Integral constants have value", "[integral]") {
	SECTION("Boolean values") {
		REQUIRE((sstl::integral_constant<bool, true>::value));
		REQUIRE((!sstl::integral_constant<bool, false>::value));
	}

	SECTION("Integral values") {
		REQUIRE((sstl::integral_constant<unsigned char, 8>::value == 8));
		REQUIRE((sstl::integral_constant<int, 127>::value == 127));
	}
}

TEST_CASE("Get the alignment of a type", "[alignment]") {
	REQUIRE((sstl::alignment_of<uint8_t>::value == 1));
	REQUIRE((sstl::alignment_of<uint16_t>::value == 2));
	REQUIRE((sstl::alignment_of<uint32_t>::value == 4));
	REQUIRE((sstl::alignment_of<uint64_t>::value == 8));
}

TEST_CASE("Aligned uninitialized byte storage", "[alignment]") {
	SECTION("Verify the size is correct") {
		REQUIRE(sizeof(sstl::aligned_storage<1, 1>::type) == 1);
		REQUIRE(sizeof(sstl::aligned_storage<4, 1>::type) == 4);
		REQUIRE(sizeof(sstl::aligned_storage<5, 4>::type) == 8);
		REQUIRE(sizeof(sstl::aligned_storage<128, 8>::type) == 128);
	}

	SECTION("Verify the alignement is correct") {
		REQUIRE((sstl::alignment_of<sstl::aligned_storage<1, 1>::type>::value
		         == 1));
		REQUIRE((sstl::alignment_of<sstl::aligned_storage<4, 1>::type>::value
		         == 1));
		REQUIRE((sstl::alignment_of<sstl::aligned_storage<5, 4>::type>::value
		         == 4));
		REQUIRE((sstl::alignment_of<sstl::aligned_storage<128, 8>::type>::value
		         == 8));
	}
}
