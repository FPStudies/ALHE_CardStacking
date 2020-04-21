#ifndef BINARY_CHROMOSOME_H
#define BINARY_CHROMOSOME_H

#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <memory>
#include <limits.h>

#include "randomPoint.h"

class BinaryChromosome
{
	enum class Symbol;
	using Container = std::vector<Symbol>;

	Container chromosome;
	RandomPoint randClass;
	int rating;

	int bindTwoGroupRating(const int& groupA, const int& groupB, const int& groupAIdeal, const int& groupBIdeal);

	enum class Symbol {
		groupA,
		groupB,
		undefined
	};

	#ifdef COUNT_METHOD_CALL
	static unsigned int constructor_call;
	static unsigned int destructor_call;
	static unsigned int constructor_copy_call;
	static unsigned int constructor_rewriting_call;

	static unsigned int method_swap_call;
	static unsigned int method_copy_call;
	static unsigned int method_mutation_call;
	static unsigned int method_evaluate_call;
	static unsigned int method_setRandValues_call;
	static unsigned int method_getSum_call;
	static unsigned int method_comparison_call;
	static unsigned int method_Crossing_call;
	static unsigned int method_singlePointCrossing_call;
	static unsigned int method_multiplePointCrossing_call;
	static unsigned int method_Crossing_call;
	static unsigned int method_uniformCrossing_call;
	static unsigned int method_startHeuristic_call;
	#endif

public:

	BinaryChromosome(const unsigned int& size, bool randVal = true);
	~BinaryChromosome();
	BinaryChromosome(const BinaryChromosome& other);
	BinaryChromosome(BinaryChromosome&& other) noexcept;
	BinaryChromosome& operator=(BinaryChromosome&& other) noexcept;
	BinaryChromosome& operator=(const BinaryChromosome& other);


	/*
	Copy given chromosome segments to this chromosome.
	*/
	void copy(const unsigned int& startPosOther, const unsigned int& endPosOther, const BinaryChromosome& from, const unsigned int& startPosThis, const unsigned int& endPosThis);
	void copy(const unsigned int& startPosOther, const unsigned int& endPosOther, const BinaryChromosome& from);

	std::unique_ptr<BinaryChromosome> copy();

	/*
	Swap given chromosome segments to this chromosome.
	*/
	void swap(const unsigned int& startPosOther, const unsigned int& endPosOther, BinaryChromosome& from, const unsigned int& startPosThis, const unsigned int& endPosThis);
	void swap(const unsigned int& startPosOther, const unsigned int& endPosOther, BinaryChromosome& from);

	/*
	All of the genes in chromosome have this probability to mutate.
	*/
	void mutation(const unsigned int& probability, const unsigned int& maxProbVal);

	/*
	Calculate how good this chromosome is.
	May be changed in other kind of task.
	*/
	void evaluate(const int& groupAIdeal, const int& groupBIdeal);

	/*
	The fewer the better.
	*/
	int getRating() const;

	unsigned int size() const;

	void setRandValues();

	std::pair<int, int> getSum() const;

	friend std::ostream& operator<< (std::ostream& os, const BinaryChromosome& chrom);
	friend bool operator==(const BinaryChromosome& one, const BinaryChromosome& two);
	friend bool operator!=(const BinaryChromosome& one, const BinaryChromosome& two);


	void singlePointCrossing(BinaryChromosome& other);
	void multiplePointCrossing(BinaryChromosome& other, const unsigned int& numberOfPoints);
	void uniformCrossing(BinaryChromosome& other);


	void startHeuristic(const int& groupAIdeal, const int& groupBIdeal);


	#ifdef COUNT_METHOD_CALL
	static unsigned int get_constructor_call();
	static unsigned int get_destructor_call();
	static unsigned int get_constructor_copy_call();
	static unsigned int get_constructor_rewriting_call();

	static unsigned int get_method_swap_call();
	static unsigned int get_method_copy_call();
	static unsigned int get_method_mutation_call();
	static unsigned int get_method_evaluate_call();
	static unsigned int get_method_setRandValues_call();
	static unsigned int get_method_getSum_call();
	static unsigned int get_method_comparison_call();
	static unsigned int get_method_Crossing_call();
	static unsigned int get_method_singlePointCrossing_call();
	static unsigned int get_method_multiplePointCrossing_call();
	static unsigned int get_method_Crossing_call();
	static unsigned int get_method_uniformCrossing_call();
	static unsigned int get_method_startHeuristic_call();


	static void method_couter_call_clear();
	#endif	

};


#endif
