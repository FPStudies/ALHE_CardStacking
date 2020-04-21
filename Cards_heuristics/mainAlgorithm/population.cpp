#ifndef POPULATION_CPP
#define POPULATION_CPP

#include "population.h"


#ifdef COUNT_METHOD_CALL
	unsigned int Population::constructor_call = 0;
	unsigned int Population::destructor_call = 0;
	unsigned int Population::constructor_copy_call = 0;
	unsigned int Population::constructor_rewriting_call = 0;

	unsigned int Population::method_operatorAdd_call = 0;

	unsigned int Population::method_runMutationInPopulation_call = 0;
	unsigned int Population::method_generatePopulation_call = 0;
	unsigned int Population::method_evaluate_call = 0;
#endif


Population::Population()
	:population()
{
	#ifdef COUNT_METHOD_CALL
	++constructor_call;
	#endif
}

Population::~Population()
{
	#ifdef COUNT_METHOD_CALL
	++destructor_call;
	#endif
}

Population::Population(const Population& other)
	:population(other.population)
{
	#ifdef COUNT_METHOD_CALL
	++constructor_copy_call;
	#endif
}

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
	#ifdef COUNT_METHOD_CALL
	++constructor_rewriting_call;
	#endif

	population = other.population;
	return *this;
}

Population& Population::operator+=(const Population& other)
{
	#ifdef COUNT_METHOD_CALL
	++method_operatorAdd_call;
	#endif
	
	this->population.insert(this->population.begin(), other.population.begin(), other.population.end());
	return *this;
}

void Population::runMutationInPopulation(const unsigned int& mutationProb, const unsigned int& maxMutationValue)
{
	#ifdef COUNT_METHOD_CALL
	++method_runMutationInPopulation_call;
	#endif
	
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
	#ifdef COUNT_METHOD_CALL
	++method_generatePopulation_call;
	#endif
	
	for (auto it = population.begin(); it != population.end(); ++it) {
		*it = std::make_shared<Individual>(numberOfGenes);
	}
}

void Population::evaluate(const int& groupAIdeal, const int& groupBIdeal)
{
	#ifdef COUNT_METHOD_CALL
	++method_evaluate_call;
	#endif
	
	for (auto it = population.begin(); it != population.end(); ++it) {
		(*it)->evaluate(groupAIdeal, groupBIdeal);
	}
}


std::ostream& operator<<(std::ostream& os, const Population& pop)
{
	int i = 0;
	for (auto it = pop.population.begin(); it != pop.population.end(); ++it, ++i) {
		os << i << ": " << **it << "\n";
	}

	return os;
}


#ifdef COUNT_METHOD_CALL
	static unsigned int Population::get_constructor_call() { return constructor_call; }
	static unsigned int Population::get_destructor_call() { return destructor_call; }
	static unsigned int Population::get_constructor_copy_call() { return constructor_copy_call; }
	static unsigned int Population::get_constructor_rewriting_call() { return constructor_rewriting_call; }

	static unsigned int Population::get_method_operatorAdd_call(){ return method_operatorAdd_call; }

	static unsigned int Population::get_method_runMutationInPopulation_call() { return method_runMutationInPopulation_call; }
	static unsigned int Population::get_method_generatePopulation_call() { return method_generatePopulation_call; }
	static unsigned int Population::get_method_evaluate_call() { return method_evaluate_call; }
#endif




#endif
