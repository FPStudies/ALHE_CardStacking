#ifndef TEST_INTERFACE_H
#define TEST_INTERFACE_H


#include <iostream>
#include <limits>

class TestInterface
{
public:
	TestInterface() {};
	~TestInterface() {};
	TestInterface(const TestInterface& other) = delete;

	virtual void runTest(const std::string& path) = 0;
	virtual TestInterface* clone() const = 0;
	virtual bool isDataValid() const = 0;
};


#endif