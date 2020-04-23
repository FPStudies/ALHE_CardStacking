#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <memory>
#include <chrono>
#include <vector>

#include "../mainAlgorithm/matingPool.h"
#include "testInterface.h"


class Tests 
{
	std::vector<std::unique_ptr<TestInterface>> tests;

public:
	Tests();
	~Tests();
	Tests(const Tests& other) = delete;

	/*
	Path to folder where results should be saved.
	*/
	void runTests(const std::string& path);

	/*
	Copy and add test.
	*/
	void addTest(TestInterface& test);
};


#endif