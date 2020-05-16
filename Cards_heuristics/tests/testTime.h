#ifndef TEST_TIME_H
#define TEST_TIME_H

#include "testCardsHeuristic.h"

#include <chrono>

class TestTime: public TestCardsHeuristic{
    const static char* keyword[1];

public:
    TestTime(const unsigned int& maxNumberOfIterations);
	virtual ~TestTime();
	TestTime(const TestTime& other);

	virtual void runTest(const std::string& path) override;
	virtual TestTime* clone() const override;

	virtual bool isKeyword(const std::string& word) const override; 

};


#endif