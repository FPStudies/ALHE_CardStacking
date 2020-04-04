#ifndef BINARY_CHROMOSOME_H
#define BINARY_CHROMOSOME_H

#include <iostream>
#include <vector>

#include "randomPoint.h"

class BinaryChromosome
{
	enum class Symbol;
	using Container = std::vector<Symbol>;

	Container chromosome;
	RandomPoint randClass;

public:
	enum class Symbol {
		groupA,
		groupB
	};

	BinaryChromosome(const unsigned int& size);
	~BinaryChromosome();
	BinaryChromosome(const BinaryChromosome& other);
	BinaryChromosome(BinaryChromosome&& other);
	BinaryChromosome& operator=(BinaryChromosome&& other);


	/*
	Copy given chromosome segment to this chromosome.
	*/
	void copy(const unsigned int& startPosOther, const unsigned int& endPosOther, const BinaryChromosome& from, const unsigned int& startPosThis, const unsigned int& endPosThis);
	void copy(const unsigned int& startPosOther, const unsigned int& endPosOther, const BinaryChromosome& from);

	/*
	All of the genes in chromosome have this probability to mutate.
	*/
	void mutation(RandomPoint& probability);

	/*
	Calculate how good this chromosome is.
	*/
	void evaluate();

	int getRating();

	unsigned int size() const;

	friend std::ostream& operator<< (std::ostream& os, const BinaryChromosome& chrom) {
		for (BinaryChromosome::Container::const_iterator it = chrom.chromosome.cbegin(); it != chrom.chromosome.cend(); ++it) {
			if (*it == Symbol::groupA) os << "A";
			else if (*it == Symbol::groupB) os << "B";
		}

		return os;
	}

};


#endif