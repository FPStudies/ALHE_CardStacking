#ifndef TEST_TIME_CPP
#define TEST_TIME_CPP

#include "testTime.h"

const char* TestTime::keyword[1] = {"testTime"};

TestTime::TestTime(const unsigned int& maxNumberOfIterations)
	:TestCardsHeuristic(maxNumberOfIterations)
{}

TestTime::~TestTime()
{}

TestTime::TestTime(const TestTime& other)
	:TestCardsHeuristic(other)
{}

void TestTime::runTest(const std::string& path){
    std::ofstream file;
	std::ostream* out;
	bool fileOpened = false;

	file.open(path, std::ios::app);
	if(!file) out = &std::cout;
	else{
		fileOpened = true;
		out = &file;
	}

	*out << "\n\n\n********* Started time test" << std::endl;
	
	MatingPool pool;
	setPoolValues(pool);

	if(!isDataValid()) *out << "Data is not set properly\n";

    auto startTime = std::chrono::steady_clock::now();

	pool.createFirstPopulation();

	for (unsigned int i = 0; i < maxNumberOfIterations_ && !pool.isBestFound(); ++i) {

		pool.runOneGeneration(crossType, crossoverPoints);

		if(pool.isBestFound()) break;
	}
    auto endTime = std::chrono::steady_clock::now();

	*out << "The best pair is:\n\t" << pool.findBest() << "\n";
    *out << "Test last:\t" << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << "\n";

	*out << "********* Ended time test" << std::endl;

	if(fileOpened) file.close();
}

int TestTime::runTestSilent(const std::string& path) {
	std::ofstream file;
	std::ostream* out;
	bool fileOpened = false;

	file.open(path, std::ios::app);
	if (!file) out = &std::cout;
	else {
		fileOpened = true;
		out = &file;
	}

	MatingPool pool;
	setPoolValues(pool);

	if (!isDataValid()) *out << "Data is not set properly\n";

	auto startTime = std::chrono::steady_clock::now();

	pool.createFirstPopulation();

	for (unsigned int i = 0; i < maxNumberOfIterations_ && !pool.isBestFound(); ++i) {

		pool.runOneGeneration(crossType, crossoverPoints);

		if (pool.isBestFound()) break;
	}
	auto endTime = std::chrono::steady_clock::now();
	auto timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
	*out << timeDuration << "\n";

	if (fileOpened) file.close();

	return static_cast<int>(timeDuration);
}

TestTime* TestTime::clone() const
{
	return new TestTime(*this);
}

bool TestTime::isKeyword(const std::string& word) const {

	for(unsigned int i = 0; i < sizeof(keyword) / sizeof(keyword[0]); ++i){
		if(keyword[i] == word) return true;
	}
	return false;
}

#endif