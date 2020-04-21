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
	
	#ifdef COUNT_METHOD_CALL
	static unsigned int constructor_call;
	static unsigned int destructor_call;
	static unsigned int constructor_copy_call;
	static unsigned int constructor_rewriting_call;

	static unsigned int method_operatorAdd_call;

	static unsigned int method_runMutationInPopulation_call;
	static unsigned int method_generatePopulation_call;
	static unsigned int method_evaluate_call;
	#endif
	

public:
	Population();
	Population(const Individual& individual);
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


	#ifdef COUNT_METHOD_CALL
	static unsigned int get_constructor_call();
	static unsigned int get_destructor_call();
	static unsigned int get_constructor_copy_call();
	static unsigned int get_constructor_rewriting_call();

	static unsigned int get_method_operatorAdd_call();

	static unsigned int get_method_runMutationInPopulation_call();
	static unsigned int get_method_generatePopulation_call();
	static unsigned int get_method_evaluate_call();
	#endif

};


#endif
