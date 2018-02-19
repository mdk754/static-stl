#include "catch/catch.hpp"

#include "algorithm.h"
#include "memory.h"
#include "type_traits.h"

struct Foo {
	Foo() : value(48) {}
	explicit Foo(int v) : value(v) {}
	~Foo() { value = 96; }

	bool operator==(const Foo& rhs) { return value == rhs.value; }

	volatile int value;
};

TEST_CASE("Copy elements into uninitialized memory", "[uninitialized]") {
	const size_t count = 4;

	sstl::aligned_storage<sizeof(Foo), sstl::alignment_of<Foo>::value>::type
	memory[count];

	Foo* dest = reinterpret_cast<Foo*>(memory);

	SECTION("Copy range of elements") {
		Foo source[count];
		source[0].value = 2;
		source[1].value = 4;
		source[2].value = 8;
		source[3].value = 16;

		sstl::uninitialized_copy(source, source + count, dest);

		REQUIRE(sstl::equal(dest, dest + count, source));
	}

	SECTION("Copy n elements") {
		Foo source[count];
		source[0].value = 2;
		source[1].value = 4;
		source[2].value = 8;
		source[3].value = 16;

		sstl::uninitialized_copy_n(source, count, dest);

		REQUIRE(sstl::equal(dest, dest + count, source));
	}
}

TEST_CASE("Fill uninitialized memory with value", "[uninitialized]") {
	const size_t count = 4;

	sstl::aligned_storage<sizeof(Foo), sstl::alignment_of<Foo>::value>::type
	memory[count];

	Foo* dest = reinterpret_cast<Foo*>(memory);

	SECTION("Fill range of elements") {
		Foo source[count];

		sstl::fill(source, source + count, Foo(16));

		sstl::uninitialized_fill(dest, dest + count, Foo(16));

		REQUIRE(sstl::equal(dest, dest + count, source));
	}

	SECTION("Fill n elements") {
		Foo source[count];

		sstl::fill(source, source + count, Foo(16));

		sstl::uninitialized_fill_n(dest, count, Foo(16));

		REQUIRE(sstl::equal(dest, dest + count, source));
	}
}

TEST_CASE("Default construct in uninitialized memory", "[uninitialized]") {
	const size_t count = 4;

	sstl::aligned_storage<sizeof(Foo), sstl::alignment_of<Foo>::value>::type
	memory[count];

	Foo* dest = reinterpret_cast<Foo*>(memory);

	SECTION("Construct range of elements") {
		Foo expect[count];

		sstl::uninitialized_default_construct(dest, dest + count);

		REQUIRE(sstl::equal(dest, dest + count, expect));
	}

	SECTION("Construct n elements") {
		Foo expect[count];

		sstl::uninitialized_default_construct_n(dest, count);

		REQUIRE(sstl::equal(dest, dest + count, expect));
	}
}

TEST_CASE("Value construct in uninitialized memory", "[uninitialized]") {
	const size_t count = 4;

	sstl::aligned_storage<sizeof(int), sstl::alignment_of<int>::value>::type
	memory[count];

	int* dest = reinterpret_cast<int*>(memory);

	SECTION("Construct range of elements") {
		int expect[count] = {0};

		sstl::uninitialized_value_construct(dest, dest + count);

		REQUIRE(sstl::equal(dest, dest + count, expect));
	}

	SECTION("Construct n elements") {
		int expect[count] = {0};

		sstl::uninitialized_value_construct_n(dest, count);

		REQUIRE(sstl::equal(dest, dest + count, expect));
	}
}

TEST_CASE("Destroy elements", "[uninitialized]") {
	const size_t count = 4;

	sstl::aligned_storage<sizeof(Foo), sstl::alignment_of<Foo>::value>::type
	memory[count];

	Foo* dest = reinterpret_cast<Foo*>(memory);

	sstl::uninitialized_default_construct_n(dest, count);

	SECTION("Destroy item at pointer") {
		sstl::destroy_at(dest);

		REQUIRE(dest[0].value == 96);
	}

	SECTION("Destroy range") {
		Foo expect[count];
		sstl::fill_n(expect, count, Foo(96));

		sstl::destroy(dest, dest + count);

		REQUIRE(sstl::equal(dest, dest + count, expect));
	}

	SECTION("Destroy n elements") {
		Foo expect[count];
		sstl::fill_n(expect, count, Foo(96));

		sstl::destroy_n(dest, count);

		REQUIRE(sstl::equal(dest, dest + count, expect));
	}
}
