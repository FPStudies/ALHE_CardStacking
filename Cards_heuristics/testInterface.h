#ifndef TEST_INTERFACE_H
#define TEST_INTERFACE_H


#include <iostream>
#include <memory>

class TestInterface
{
public:
	TestInterface();
	~TestInterface();
	TestInterface(const TestInterface& other) = delete;

	virtual void runTest(const std::string& path) = 0;
	virtual std::unique_ptr<TestInterface> copy() = 0;
};


#endif