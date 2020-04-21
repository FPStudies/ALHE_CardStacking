#ifndef BINARY_CHROMOSOME_CPP
#define BINARY_CHROMOSOME_CPP

#include "binaryChromosome.h"


#ifdef COUNT_METHOD_CALL
	unsigned int BinaryChromosome::constructor = 0;
	unsigned int BinaryChromosome::destructor = 0;
	unsigned int BinaryChromosome::constructor_copy = 0;
	unsigned int BinaryChromosome::constructor_rewriting = 0;

	unsigned int BinaryChromosome::method_swap_call = 0;
	unsigned int BinaryChromosome::method_copy_call = 0;
	unsigned int BinaryChromosome::method_mutation_call = 0;
	unsigned int BinaryChromosome::method_evaluate_call = 0;
	unsigned int BinaryChromosome::method_setRandValues_call = 0;
	unsigned int BinaryChromosome::method_getSum_call = 0;
	unsigned int BinaryChromosome::method_comparison_call = 0;
	unsigned int BinaryChromosome::method_Crossing_call = 0;
	unsigned int BinaryChromosome::method_singlePointCrossing_call = 0;
	unsigned int BinaryChromosome::method_multiplePointCrossing_call = 0;
	unsigned int BinaryChromosome::method_Crossing_call = 0;
	unsigned int BinaryChromosome::method_uniformCrossing_call = 0;
	unsigned int BinaryChromosome::method_startHeuristic_call = 0;
#endif



BinaryChromosome::BinaryChromosome(const unsigned int& size, bool randVal)
	:chromosome(), randClass(size), rating(INT_MAX)
{
	#ifdef COUNT_METHOD_CALL
	++constructor;
	#endif
	
	if (randVal) {
		chromosome.resize(size);
		setRandValues();
	}
	else chromosome.resize(size, Symbol::undefined);
}

BinaryChromosome::~BinaryChromosome()
{
	#ifdef COUNT_METHOD_CALL
	++destructor;
	#endif

BinaryChromosome::BinaryChromosome(const BinaryChromosome& other)
	:chromosome(other.chromosome), randClass(other.randClass), rating(other.rating)
{
	#ifdef COUNT_METHOD_CALL
	++constructor_copy;
	#endif
}

BinaryChromosome::BinaryChromosome(BinaryChromosome&& other) noexcept
	: chromosome(std::move(other.chromosome)), randClass(std::move(other.randClass)), rating(std::move(other.rating))
{}

BinaryChromosome& BinaryChromosome::operator=(BinaryChromosome&& other) noexcept
{
	chromosome = std::move(other.chromosome);
	randClass = std::move(other.randClass);
	rating = std::move(other.rating);
	return *this;
}

BinaryChromosome& BinaryChromosome::operator=(const BinaryChromosome& other)
{
	#ifdef COUNT_METHOD_CALL
	++constructor_rewriting;
	#endif
	
	chromosome = other.chromosome;
	randClass = other.randClass;
	rating = other.rating;
	return *this;
}

void BinaryChromosome::copy(const unsigned int& startPosOther, const unsigned int& endPosOther, const BinaryChromosome& from, const unsigned int& startPosThis, const unsigned int& endPosThis)
{
	#ifdef COUNT_METHOD_CALL
	++method_copy_call;
	#endif
	
	if (endPosOther - startPosOther != endPosThis - startPosThis)
		throw std::invalid_argument("Range of the iterators do not match.");


	auto thisIterBegin = chromosome.begin() + startPosThis;
	auto otherIterBegin = from.chromosome.begin() + startPosOther;

	auto thisIterEnd = chromosome.begin() + endPosThis;

	for (; thisIterBegin != thisIterEnd; ++thisIterBegin, ++otherIterBegin) {
		*thisIterBegin = *otherIterBegin;
	}	
}

void BinaryChromosome::copy(const unsigned int& startPosOther, const unsigned int& endPosOther, const BinaryChromosome& from)
{
	this->copy(startPosOther, endPosOther, from, startPosOther, endPosOther);
}

std::unique_ptr<BinaryChromosome> BinaryChromosome::copy()
{
	return std::make_unique<BinaryChromosome>(*this);
}

void BinaryChromosome::swap(const unsigned int& startPosOther, const unsigned int& endPosOther, BinaryChromosome& from, const unsigned int& startPosThis, const unsigned int& endPosThis)
{
	#ifdef COUNT_METHOD_CALL
	++method_swap_call;
	#endif
	
	if (endPosOther - startPosOther != endPosThis - startPosThis)
		throw std::invalid_argument("Range of the iterators do not match.");


	auto thisIterBegin = chromosome.begin() + startPosThis;
	auto otherIterBegin = from.chromosome.begin() + startPosOther;

	auto thisIterEnd = chromosome.begin() + endPosThis;

	Symbol tmp;

	for (; thisIterBegin != thisIterEnd; ++thisIterBegin, ++otherIterBegin) {
		tmp = *otherIterBegin;		
		*otherIterBegin = *thisIterBegin;
		*thisIterBegin = tmp;
	}
}

void BinaryChromosome::swap(const unsigned int& startPosOther, const unsigned int& endPosOther, BinaryChromosome& from)
{
	this->swap(startPosOther, endPosOther, from, startPosOther, endPosOther);
}

void BinaryChromosome::mutation(const unsigned int& probability, const unsigned int& maxProbVal)
{
	#ifdef COUNT_METHOD_CALL
	++method_mutation_call;
	#endif
	
	for (auto it = chromosome.begin(); it != chromosome.end(); ++it) {

		if (RandomPoint::getRand(probability, maxProbVal)) {
			if (*it == Symbol::groupA) *it = Symbol::groupB;
			else if(*it == Symbol::groupB) *it = Symbol::groupA;
		}
		
	}
}

int BinaryChromosome::bindTwoGroupRating(const int& groupA, const int& groupB, const int& groupAIdeal, const int& groupBIdeal)
{
	return std::abs(groupA - groupAIdeal) + std::abs(groupB - groupBIdeal);
}

void BinaryChromosome::evaluate(const int& groupAIdeal, const int& groupBIdeal)
{
	#ifdef COUNT_METHOD_CALL
	++method_evaluate_call;
	#endif
	
	int sumGroupA = 0, sumGroupB = 0;
	unsigned int pos = 1;


	for (auto it = chromosome.begin(); it != chromosome.end(); ++it, ++pos) {
		if (*it == Symbol::groupA) sumGroupA += pos;
		else if (*it == Symbol::groupB) sumGroupB += pos;
		else throw std::invalid_argument("All of the genes in chromosome must be defined.");
	}

	rating = bindTwoGroupRating(sumGroupA, sumGroupB, groupAIdeal, groupBIdeal);
}

int BinaryChromosome::getRating() const
{
	return rating;
}

unsigned int BinaryChromosome::size() const
{
	return chromosome.size();
}

void BinaryChromosome::setRandValues()
{
	#ifdef COUNT_METHOD_CALL
	++method_setRandValues_call;
	#endif
	
	for (auto it = chromosome.begin(); it != chromosome.end(); ++it) {
		if (rand() % 2 == 0) *it = Symbol::groupA;
		else *it = Symbol::groupB;
	}
}

std::pair<int, int> BinaryChromosome::getSum() const
{
	#ifdef COUNT_METHOD_CALL
	++method_getSum_call;
	#endif

	int sumA = 0, sumB = 0, i = 1;
	for (auto it = chromosome.cbegin(); it != chromosome.cend(); ++it, ++i) {
		if (*it == Symbol::groupA) sumA += i;
		else if(*it == Symbol::groupB) sumB += i;
	}
	return std::pair<int, int>(sumA, sumB);
}

std::ostream& operator<< (std::ostream& os, const BinaryChromosome& chrom) {
	for (auto it = chrom.chromosome.cbegin(); it != chrom.chromosome.cend(); ++it) {
		if (*it == BinaryChromosome::Symbol::groupA) os << "A";
		else if (*it == BinaryChromosome::Symbol::groupB) os << "B";
		else if (*it == BinaryChromosome::Symbol::undefined) os << "U";
	}
	os << ": " << chrom.getSum().first << " " << chrom.getSum().second;

	return os;
}

bool operator==(const BinaryChromosome& one, const BinaryChromosome& two)
{
	#ifdef COUNT_METHOD_CALL
	++method_comparison_call;
	#endif
	
	if (one.chromosome.size() != two.chromosome.size()) return false;
	for (auto itOne = one.chromosome.cbegin(), itTwo = two.chromosome.cbegin(); itOne != one.chromosome.cend(); ++itOne, ++itTwo) {
		if (*itOne != *itTwo) return false;
	}
	return true;
}

bool operator!=(const BinaryChromosome& one, const BinaryChromosome& two)
{
	return !(one == two);
}

void BinaryChromosome::singlePointCrossing(BinaryChromosome& other)
{
	#ifdef COUNT_METHOD_CALL
	++method_singlePointCrossing_call;
	#endif


	#ifdef DEBUG
	if (this->chromosome.size() != other.chromosome.size() || this->chromosome.size() < 1)
		throw std::runtime_error("Chromosomes must have the same size or have at least two genes.");
	#endif
	
	unsigned int crossPoint = (rand() % this->chromosome.size());
	crossPoint = (crossPoint != this->chromosome.size() - 1 ? crossPoint + 1: crossPoint);
	
	this->swap(0, crossPoint, other);
}

void BinaryChromosome::multiplePointCrossing(BinaryChromosome& other, const unsigned int& numberOfPoints)
{	
	#ifdef COUNT_METHOD_CALL
	++method_multiplePointCrossing_call;
	#endif
	
	#ifdef DEBUG
	if (this->chromosome.size() != other.chromosome.size() || this->chromosome.size() < 1)
		throw std::runtime_error("Chromosomes must have the same size or have at least two genes.");
	#endif
	std::list<unsigned int> points;

	for (unsigned int i = 0; i < numberOfPoints; ++i) {
		unsigned int crossPoint = rand() % this->chromosome.size();
		crossPoint = (crossPoint != this->chromosome.size() - 1 ? crossPoint + 1 : crossPoint - 1);

		points.push_back(crossPoint);

	}

	points.sort();

	for (auto it = points.cbegin(), itPrev = it++; it != points.cend(); ++it, ++itPrev) {
		this->swap(*(itPrev), *(it), other);
	}
}

void BinaryChromosome::uniformCrossing(BinaryChromosome& other)
{
	#ifdef COUNT_METHOD_CALL
	++method_uniformCrossing_call;
	#endif
	
	#ifdef DEBUG
	if (this->chromosome.size() != other.chromosome.size() || this->chromosome.size() < 1)
		throw std::runtime_error("Chromosomes must have the same size or have at least two genes.");
	#endif
	Symbol tmp;
	auto itThis = chromosome.begin();
	auto itOther = other.chromosome.begin();

	for (; itThis != chromosome.end() || itOther != other.chromosome.end(); ++itThis, ++itOther) {
		if (rand() % 2 == 0) {
			tmp = *itOther;
			*itOther = *itThis;
			*itThis = tmp;
		}
	}
}

void BinaryChromosome::startHeuristic(const int& groupAIdeal, const int& groupBIdeal)
{
	#ifdef COUNT_METHOD_CALL
	++method_startHeuristic_call;
	#endif
	
	auto it = --chromosome.end();
	int grA = groupAIdeal;
	int grB = groupBIdeal;
	unsigned int cards = 10;

	for (int i = chromosome.size() - 1; i >= 0; --i, --it, --cards) {
		if (grA >= grB) {
			*it = Symbol::groupA;
			grA -= cards;
		}
		else {
			*it = Symbol::groupB;
			grB -= cards;
		}

		if (it == chromosome.begin()) break;
	}
}



#ifdef COUNT_METHOD_CALL
	static unsigned int BinaryChromosome::get_constructor() { return constructor; }
	static unsigned int BinaryChromosome::get_destructor() { return destructor; }
	static unsigned int BinaryChromosome::get_constructor_copy() { return constructor_copy; }
	static unsigned int BinaryChromosome::get_constructor_rewriting() { return constructor_rewriting; }

	static unsigned int BinaryChromosome::get_method_swap_call() { return method_swap_call; }
	static unsigned int BinaryChromosome::get_method_copy_call() { return method_copy_call; }
	static unsigned int BinaryChromosome::get_method_mutation_call() { return method_mutation_call; }
	static unsigned int BinaryChromosome::get_method_evaluate_call() { return method_evaluate_call; }
	static unsigned int BinaryChromosome::get_method_setRandValues_call() { return method_setRandValues_call; }
	static unsigned int BinaryChromosome::get_method_getSum_call() { return method_getSum_call; }
	static unsigned int BinaryChromosome::get_method_comparison_call() { return method_comparison_call; }
	static unsigned int BinaryChromosome::get_method_Crossing_call() { return method_Crossing_call; }
	static unsigned int BinaryChromosome::get_method_singlePointCrossing_call() { return method_singlePointCrossing_call; }
	static unsigned int BinaryChromosome::get_method_multiplePointCrossing_call() { return method_multiplePointCrossing_call; }
	static unsigned int BinaryChromosome::get_method_Crossing_call() { return method_Crossing_call; }
	static unsigned int BinaryChromosome::get_method_uniformCrossing_call() { return method_uniformCrossing_call; }
	static unsigned int BinaryChromosome::get_method_startHeuristic_call() { return method_startHeuristic_call; }
#endif








#endif