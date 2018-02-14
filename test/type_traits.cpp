#include "test.h"

#include "type_traits.h"

namespace type_traits {

struct integral_const : public test {
	integral_const() : test("integral_constant<> values") {}

	bool run() {
		if (sstl::integral_constant<bool, false>::value) { return false; }

		if (sstl::integral_constant<int, 32>::value != 32) { return false; }

		if (sstl::integral_constant<char, 64>::value != 64) { return false; }

		return true;
	}
};

integral_const t1;

struct alignment : public test {
	alignment() : test("alignment_of<> types") {}

	bool run() {
		if (sstl::alignment_of<uint8_t>::value != 1) { return false; }

		if (sstl::alignment_of<uint16_t>::value != 2) { return false; }

		if (sstl::alignment_of<uint32_t>::value != 4) { return false; }

		if (sstl::alignment_of<uint64_t>::value != 8) { return false; }

		return true;
	}
};

alignment t2;

struct aligned_storage_type : public test {
	aligned_storage_type() : test("aligned_storage<> container") {}

	bool run() {
		if (sizeof(sstl::aligned_storage<5, 4>::type) != 8) { return false; }

		if (sizeof(sstl::aligned_storage<15, 8>::type) != 16) { return false; }

		return true;
	}
};

aligned_storage_type t3;

} /* namespace type_traits */
