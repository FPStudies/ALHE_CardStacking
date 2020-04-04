#ifndef MATING_POOL_H
#define MATING_POOL_H

#include <memory>

#include "population.h"

class MatingPool
{
	Population::Container population;
	/*
	Population::Container afterTournament;
	Population::Container individualsToCrossover;
	Population::Container afterCrossover;
	Population::Container newResidents;*/

	unsigned int populationSize;
	unsigned int poolSize;
	RandomPoint mutationProb;

	bool populationCreated;
	bool duringSimulation;

	/*
	Choosing Individuals that will be used in crossover.
	*/
	Population::Container tournament(Population::Container& oldGeneration);

	Population::Container crossover(Population::Container& selectedPopulation);

	void mutation(Population::Container& population);

	void populationEvaluation(Population::Container& population);

	Population::Container selectFromTwoGenerations(Population::Container& oldGeneration, Population::Container& newGeneration);



	/*
	Choosing from individualsToCrossover
	*/
	std::pair<Population::Individual, Population::Individual> chooseTwoToCrossover() const;

public:
	MatingPool(unsigned int matingPoolSize);
	~MatingPool();
	MatingPool(const MatingPool& other) = delete;
	MatingPool(MatingPool&& other);
	MatingPool& operator=(MatingPool&& other);

	void createFirstPopulation();

	void setPopulationSize(const unsigned int& popSize);
	void setMutationProbability(const RandomPoint& random);
	void setMatingPoolSize(const unsigned int& matPoolSize);

	Population::Container runOneGeneration();
};


#endif