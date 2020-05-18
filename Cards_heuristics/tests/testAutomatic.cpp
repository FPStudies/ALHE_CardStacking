#ifndef TEST_AUTO_CPP
#define TEST_AUTO_CPP

#include "testAutomatic.h"

const char* TestAuto::keyword[1] = { "TestAuto" };

TestAuto::TestAuto(const unsigned int& maxNumberOfIterations)
	:TestCardsHeuristic(maxNumberOfIterations)
{}

TestAuto::~TestAuto()
{}

TestAuto::TestAuto(const TestAuto& other)
	:TestCardsHeuristic(other)
{}

void TestAuto::runTest(const std::string& path) {
	std::ofstream file;
	std::ostream* out;
	bool fileOpened = false;

	file.open(path);
	if (!file) out = &std::cout;
	else {
		fileOpened = true;
		out = &file;
	}

	*out << "\n\n\n********* Started time test" << std::endl;

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

	*out << "The best pair is:\n\t" << pool.findBest() << "\n";
	*out << "Test last:\t" << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << "\n";

	*out << "********* Ended time test" << std::endl;

	if (fileOpened) file.close();
}

TestAuto* TestAuto::clone() const
{
	return new TestAuto(*this);
}

bool TestAuto::isKeyword(const std::string& word) const {

	for (unsigned int i = 0; i < sizeof(keyword) / sizeof(keyword[0]); ++i) {
		if (keyword[i] == word) return true;
	}
	return false;
}

#endif