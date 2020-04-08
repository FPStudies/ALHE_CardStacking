#ifndef POPULATION_CPP
#define POPULATION_CPP

#include "population.h"

Population::Population()
	:population()
{}

Population::~Population()
{}

Population::Population(const Population& other)
	:population(other.population)
{}

Population::Population(Population&& other) noexcept
	:population(std::move(other.population))
{}

Population& Population::operator=(Population&& other) noexcept
{
	population = std::move(other.population);
	return *this;
}

Population& Population::operator=(const Population& other)
{
	population = other.population;
	return *this;
}

Population& Population::operator+=(const Population& other)
{
	this->population.insert(this->population.begin(), other.population.begin(), other.population.end());
	return *this;
}

void Population::runMutationInPopulation(const unsigned int& mutationProb, const unsigned int& maxMutationValue)
{
	for (auto it = population.begin(); it != population.end(); ++it) {
		(*it)->mutation(mutationProb, maxMutationValue);
	}
}

void Population::setPopulationSize(const unsigned int& size)
{
	population.resize(size);
}

void Population::generatePopulation(const unsigned int& numberOfGenes)
{
	for (auto it = population.begin(); it != population.end(); ++it) {
		*it = std::make_shared<Individual>(numberOfGenes);
	}
}

void Population::evaluate(const int& groupAIdeal, const int& groupBIdeal)
{
	for (auto it = population.begin(); it != population.end(); ++it) {
		(*it)->evaluate(groupAIdeal, groupBIdeal);
	}
}


#endif

std::ostream& operator<<(std::ostream& os, const Population& pop)
{
	int i = 0;
	for (auto it = pop.population.begin(); it != pop.population.end(); ++it, ++i) {
		os << i << ": " << **it << "\n";
	}

	return os;
}
