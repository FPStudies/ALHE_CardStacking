#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <memory>

#include "binaryChromosome.h"
#include "randomPoint.h"

class Population
{
	friend class MatingPool;
	using Individual = BinaryChromosome;
	using Container = std::vector<std::shared_ptr<Individual>>;


private:

	Container population;
	RandomPoint mutationProb;
	RandomPoint randomChromosome; // 1 / Container.size(); to choose individual

public:
	Population();
	~Population();
	Population(const Population& other);
	Population(Population&& other);
	Population& operator=(Population&& other);

	void runMutationInPopulation();

	/*
	Creates a new individual
	*/
	Population::Individual singlePointCrossing(Population::Individual& other);
	Population::Individual multiplePointCrossing(Population::Individual& other);
	Population::Individual uniformCrossing(Population::Individual& other);

	void setMutationProb(const unsigned int& popSize);
	void setPopulationSize();
};


#endif
