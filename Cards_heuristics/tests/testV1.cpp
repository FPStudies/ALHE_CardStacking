#ifndef TEST_V1_CPP
#define TEST_V1_CPP

#include "testV1.h"

void TestV1::setPoolValues(MatingPool& pool)
{
	pool.setGroupAValue();
	pool.setGroupBValue();
	pool.setMutationProbability();
	pool.setNumberOfCrossovers();
	pool.setPopulationSize();
	pool.setPopulationSizeAfterTounament();
}

TestV1::TestV1(const unsigned int& maxNumberOfIterations)
	:maxNumberOfIterations_(maxNumberOfIterations)
{}

TestV1::~TestV1()
{}

TestV1::TestV1(const TestV1 & other)
{}

void TestV1::runTest(const std::string& path)
{
	MatingPool pool;
	setPoolValues(pool);

	for (unsigned int i = 0; i < maxNumberOfIterations_ && !pool.isBestFound(); ++i) {
		pool.runOneGeneration();
	}

}

std::unique_ptr<TestInterface> TestV1::copy()
{
	return std::unique_ptr<TestInterface>(*this);
}



#endif


