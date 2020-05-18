#ifndef TEST_NORMAL_H
#define TEST_NORMAL_H

#include "testInterface.h"
#include "testCardsHeuristic.h"

#include <fstream>
#include <iostream>
#include <sstream>

class TestNormal: public TestCardsHeuristic{
	const static char* keyword[1];

public:
	TestNormal(const unsigned int& maxNumberOfIterations);
	virtual ~TestNormal();
	TestNormal(const TestNormal& other);

	virtual void runTest(const std::string& path) override;
	virtual int runTestSilent(const std::string& path) override;

	virtual void runTestHeuristic(const std::string& path) override;
	virtual int runTestHeuristicSilent(const std::string& path) override;

	virtual TestNormal* clone() const override;

	virtual bool isKeyword(const std::string& word) const override; 
};


#endif