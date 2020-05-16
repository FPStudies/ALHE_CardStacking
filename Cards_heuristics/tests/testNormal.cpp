#ifndef TEST_NORMAL_CPP
#define TEST_NORMAL_CPP

#include "testNormal.h"

const char* TestNormal::keyword[1] = {"testNormal"};


TestNormal::TestNormal(const unsigned int& maxNumberOfIterations)
	:TestCardsHeuristic(maxNumberOfIterations)
{}

TestNormal::~TestNormal()
{}

TestNormal::TestNormal(const TestNormal& other)
	:TestCardsHeuristic(other)
{}

void TestNormal::runTest(const std::string& path)
{
	std::ofstream file;
	std::ostream* out;
	bool fileOpened = false;

	file.open(path);
	if(!file) out = &std::cout;
	else{
		fileOpened = true;
		out = &file;
	}

	*out << "\n\n\n********* Started normal test" << std::endl;
	
	MatingPool pool;
	setPoolValues(pool);

	if(!isDataValid()) *out << "Data is not set properly\n";

	pool.createFirstPopulation();

	for (unsigned int i = 0; i < maxNumberOfIterations_ && !pool.isBestFound(); ++i) {
		pool.runOneGeneration(crossType, crossoverPoints);
		if(pool.isBestFound()) break;
	}

	*out << "The best pair is:\n\t" << pool.findBest() << "\n";

	*out << "********* Ended normal test" << std::endl;

	if(fileOpened) file.close();
}

TestNormal* TestNormal::clone() const
{
	return new TestNormal(*this);
}

bool TestNormal::isKeyword(const std::string& word) const {

	for(unsigned int i = 0; i < sizeof(keyword) / sizeof(keyword[0]); ++i){
		if(keyword[i] == word) return true;
	}
	return false;
}



#endif


