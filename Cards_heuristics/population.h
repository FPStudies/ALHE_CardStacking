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

	Container population;
	/*unsigned int mutationProb;
	unsigned int maxMutationValue;
	unsigned int numberOfGenes;*/
	

public:
	Population();
	~Population();
	Population(const Population& other);
	Population(Population&& other) noexcept;
	Population& operator=(Population&& other) noexcept;
	Population& operator=(const Population& other);
	Population& operator+=(const Population& other);

	void runMutationInPopulation(const unsigned int& mutationProb, const unsigned int& maxMutationValue);

	void setPopulationSize(const unsigned int& size);

	void generatePopulation(const unsigned int& numberOfGenes);

	void evaluate(const int& groupAIdeal, const int& groupBIdeal);

	friend std::ostream& operator<< (std::ostream& os, const Population& pop);
};


#endif
