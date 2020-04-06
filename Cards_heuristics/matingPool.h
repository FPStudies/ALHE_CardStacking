#ifndef MATING_POOL_H
#define MATING_POOL_H

#include <memory>
#include <algorithm>

#include "population.h"

class MatingPool
{
	enum class CrossoverType;

	Population population_;
	/*
	Population afterTournament;
	Population individualsToCrossover;
	Population afterCrossover;
	Population newResidents;*/

	unsigned int populationSize;
	unsigned int populationSizeAfterTournament;
	unsigned int numberOfCrossovers_;
	unsigned int mutationProb;
	unsigned int maxProbValue;
	int groupAVal;
	int groupBVal;

	bool populationCreated;
	bool duringSimulation;
	bool foundOptimal;

	const static unsigned int numberOfGenes = 10;

	/*
	If there is someone with optimal solution.
	*/
	std::shared_ptr<Population::Individual> best;

	std::shared_ptr<Population::Individual> kingOfPopulation;


	/*
	Choosing Individuals that will be used in crossover.
	*/
	Population tournament(const Population& oldGeneration, const unsigned int& sizeOfNewPop);

	Population crossover(const Population& selectedPopulation, CrossoverType type, const unsigned int& numberOfPointCross);

	void mutation(Population& population);

	void populationEvaluation(Population& population, const int& groupAIdeal, const int& groupBIdeal);

	Population selectFromTwoGenerations(const Population& oldGeneration, const Population& newGeneration);

	std::shared_ptr<Population::Individual> findBestPointer();

	std::shared_ptr<Population::Individual> findBestPointerCopy();

	std::shared_ptr<Population::Individual> findWorstPointer();

	/*
	Choosing from selectedPopulation.
	It is important that this return copy of individual.
	*/
	std::pair<std::shared_ptr<Population::Individual>, std::shared_ptr<Population::Individual>> chooseTwoToCrossover(const Population& selectedPopulation);

	double raitingFunction(const int& rating);

public:
	MatingPool();
	~MatingPool();
	MatingPool(const MatingPool& other) = delete;
	MatingPool(MatingPool&& other) noexcept;
	MatingPool& operator=(MatingPool&& other) noexcept;

	void createFirstPopulation();

	void setPopulationSize(const unsigned int& popSize);
	void setMutationProbability(const unsigned int& random, const unsigned int& max);
	void setNumberOfCrossovers(const unsigned int& value);
	void setPopulationSizeAfterTounament(const int& value);

	void setGroupAValue(const int& value);
	void setGroupBValue(const int& value);

	bool isDataValid();

	void runOneGeneration(CrossoverType type, const unsigned int& numberOfPointCross = 1);

	Population::Individual findBest();

	enum class CrossoverType {
		multiplePoint,
		uniform,
		singlePoint
	};

	friend std::ostream& operator<< (std::ostream& os, const MatingPool& pool);
};


#endif