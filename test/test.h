#ifndef STATIC_STL_TEST_TEST_H_
#define STATIC_STL_TEST_TEST_H_

#include <string>
#include <vector>

struct test {
	test(const std::string& name) : name(name) { tests().push_back(this); }

	virtual bool run() = 0;

	static std::vector<test*>& tests();

	std::string name;
};

#endif /* STATIC_STL_TEST_TEST_H_ */
