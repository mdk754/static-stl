#include "test.h"

#include <iostream>

std::vector<test*>& test::tests() {
	static std::vector<test*> tests;
	return tests;
}

int main() {
	std::cout << "Starting test framework with " <<
	          test::tests().size() << " test(s) ...\n\n\n";

	size_t count = 0;
	size_t passed_tests = 0;
	size_t failed_tests = 0;

	for (auto it : test::tests()) {
		std::cout << "  Running test #" << ++count  << ": " << it->name << " ... ";
		bool passed = it->run();

		if (passed) {
			++passed_tests;
			std::cout << "\u2713\n";
		} else {
			++failed_tests;
			std::cout << "\u2717\n";
		}
	}

	std::cout << "\n\n"
	          << "Total passes: " << passed_tests << "\n"
	          << "Total failures: " << failed_tests << "\n";
}
