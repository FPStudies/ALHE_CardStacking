#ifndef TEST_V1_H
#define TEST_V1_H

#include "testInterface.h"
#include "../matingPool.h"

#include <fstream>
#include <chrono>

class TestV1: public TestInterface{
	unsigned int maxNumberOfIterations_;

	void setPoolValues(MatingPool& pool);

public:
	TestV1(const unsigned int& maxNumberOfIterations);
	~TestV1();
	TestV1(const TestV1& other);

	void runTest(const std::string& path);
	std::unique_ptr<TestInterface> copy();
};


#endif