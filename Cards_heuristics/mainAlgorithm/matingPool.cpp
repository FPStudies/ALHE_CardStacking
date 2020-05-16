#ifndef MATING_POOL_CPP
#define MATING_POOL_CPP

#include "matingPool.h"

const unsigned int MatingPool::numberOfGenes = 10;

MatingPool::MatingPool()
	: population_(), 
	populationSize(0), 
	populationSizeAfterTournament(0),
	numberOfCrossovers_(0),
	mutationProb(0),
	maxProbValue(1000),
	groupAVal(0),
	groupBVal(0),
	populationCreated(false), 
	duringSimulation(false),
	foundOptimal(false),
	best(std::make_shared<Population::Individual>(4, false))
{}

MatingPool::~MatingPool()
{}


MatingPool::MatingPool(MatingPool&& other) noexcept
	:population_(std::move(other.population_)),
	populationSize(std::move(other.populationSize)),
	populationSizeAfterTournament(std::move(other.populationSizeAfterTournament)),
	numberOfCrossovers_(std::move(other.numberOfCrossovers_)),
	mutationProb(std::move(other.mutationProb)),
	maxProbValue(std::move(other.maxProbValue)),
	groupAVal(std::move(other.groupAVal)),
	groupBVal(std::move(other.groupBVal)),
	populationCreated(std::move(other.populationCreated)),
	duringSimulation(std::move(other.duringSimulation)),
	foundOptimal(other.foundOptimal),
	best(std::move(other.best))
{}

MatingPool& MatingPool::operator=(MatingPool&& other) noexcept
{
	population_ = std::move(other.population_);
	populationSize = std::move(other.populationSize);
	populationSizeAfterTournament = std::move(other.populationSizeAfterTournament);
	numberOfCrossovers_ = std::move(other.numberOfCrossovers_);
	mutationProb = std::move(other.mutationProb);
	maxProbValue = std::move(other.maxProbValue);
	groupAVal = std::move(other.groupAVal);
	groupBVal = std::move(other.groupBVal);
	populationCreated = std::move(other.populationCreated);
	duringSimulation = std::move(other.duringSimulation);
	foundOptimal = other.foundOptimal;
	best = std::move(other.best);
	return *this;
}

void MatingPool::setPopulationSize(const unsigned int& popSize)
{
	if(duringSimulation) return;
	populationSize = popSize;
	population_.setPopulationSize(popSize);
}

void MatingPool::setMutationProbability(const unsigned int& random, const unsigned int& max)
{
	if (duringSimulation) return;
	mutationProb = random;
	maxProbValue = max;
}

void MatingPool::setNumberOfCrossovers(const unsigned int& value)
{
	if (duringSimulation) return;
	numberOfCrossovers_ = value;
}

void MatingPool::setGroupAValue(const int& value)
{
	if (duringSimulation) return;
	groupAVal = value;
}

void MatingPool::setGroupBValue(const int& value)
{
	if (duringSimulation) return;
	groupBVal = value;
}

bool MatingPool::isDataValid()
{
	if (populationSize > 1 && populationSizeAfterTournament <= populationSize && populationSizeAfterTournament > 1) {
		if (numberOfCrossovers_ <= populationSizeAfterTournament && numberOfCrossovers_ > 1)
			if (mutationProb <= maxProbValue) return true;
	}

	return false;
}

void MatingPool::setPopulationSizeAfterTounament(const int& value)
{
	if (duringSimulation) return;
	populationSizeAfterTournament = value;
}

void MatingPool::createFirstPopulation()
{
	if (populationCreated || duringSimulation) return;
	population_.generatePopulation(numberOfGenes);
	populationEvaluation(population_, groupAVal, groupBVal);
	populationCreated = true;
}

void MatingPool::runOneGeneration(CrossoverType type, const unsigned int& numberOfPointCross)
{
	if (foundOptimal || !populationCreated) return;
	duringSimulation = true;

	std::shared_ptr<Population::Individual> pointerToBest = findBestPointer();
	std::shared_ptr<Population::Individual> copiedBest = pointerToBest->copy();

	Population toCrossover = std::move(rouletteWheel(population_, populationSizeAfterTournament)); // tu wywala
	if (foundOptimal) {
		population_ = std::move(toCrossover);
		return;
	}
	
	Population afterCrossover = std::move(crossover(toCrossover, type, numberOfPointCross));

	mutation(afterCrossover);
	populationEvaluation(afterCrossover, groupAVal, groupBVal);

	population_ = std::move(selectFromTwoGenerations(population_, afterCrossover));
	if (foundOptimal) {
		return;
	}

	std::shared_ptr<Population::Individual> newPointerToBest = findBestPointer();
	if (newPointerToBest != pointerToBest || *copiedBest != *newPointerToBest) {
		std::shared_ptr<Population::Individual> worst = findWorstPointer();
		*worst = *copiedBest;
	}

	duringSimulation = false;
}

Population::Individual MatingPool::findBest()
{
	if (foundOptimal) {
		return *best;
	}
	if (!populationCreated || duringSimulation) return Population::Individual(2, false);
	
	int min = INT_MAX;
	Population::Individual ret(4, false);

	for (auto it = population_.population.begin(); it != population_.population.end(); ++it) {
		if ((*it)->getRating() < min) {
			min = (*it)->getRating();
			ret = **it;
		}
	}

	return std::move(ret);
}

bool MatingPool::isBestFound()
{
	return foundOptimal;
}

Population::Individual MatingPool::returnBest()
{
	if (foundOptimal) return *best;
	return Population::Individual(2, false);
}


void MatingPool::populationEvaluation(Population& population, const int& groupAIdeal, const int& groupBIdeal)
{
	population.evaluate(groupAIdeal, groupBIdeal);
}

Population MatingPool::crossover(const Population& selectedPopulation, CrossoverType type, const unsigned int& numberOfPointCross)
{
	Population returnPopulation;
	for (unsigned int i = 0; i < numberOfCrossovers_ / 2; ++i) {
		auto ret = chooseTwoToCrossover(selectedPopulation);

		switch (type) {
		case CrossoverType::uniform:
			ret.first->uniformCrossing(*ret.second);
			break;
		case CrossoverType::singlePoint:
			ret.first->singlePointCrossing(*ret.second);
			break;
		case CrossoverType::multiplePoint:
			ret.first->multiplePointCrossing(*ret.second, numberOfPointCross);
			break;
		}

		returnPopulation.population.push_back(ret.first);
		returnPopulation.population.push_back(ret.second);
	}

	return std::move(returnPopulation);
}

void MatingPool::mutation(Population& population)
{
	for (auto it = population.population.begin(); it != population.population.end(); ++it) {
		(*it)->mutation(mutationProb, maxProbValue);
	}
}

double MatingPool::raitingFunction(const int& rating)
{
	return std::exp2(1 * RAND_MAX / rating);
}

Population MatingPool::rouletteWheel(const Population& oldGeneration, const unsigned int& sizeOfNewPop)
{
	Population newPop;
	unsigned int selected = 0;

	auto it = oldGeneration.population.begin();

	while (selected != sizeOfNewPop) {
		
		if (it == oldGeneration.population.end()) it = oldGeneration.population.begin();
		int rating = (*it)->getRating(); // tutaj wywala
		if (rating == 0) { // must be, because raitingFunction(0) is infinite
			best = *it;
			foundOptimal = true;
			return Population();
		}

		if (raitingFunction(rating) >= rand()) {
			newPop.population.push_back(*it);
			++selected;
		}

		++it;
	}
	return std::move(newPop);
}

Population MatingPool::selectFromTwoGenerations(const Population& oldGeneration, const Population& newGeneration)
{
	Population tmp = oldGeneration;
	tmp += newGeneration;

	return std::move(rouletteWheel(tmp, populationSize));
}

std::pair<std::shared_ptr<Population::Individual>, std::shared_ptr<Population::Individual>> MatingPool::chooseTwoToCrossover(const Population& selectedPopulation)
{
	//bool notFound = true;
	int random = rand() % selectedPopulation.population.size();
	//auto it = selectedPopulation.population.begin() + random;
	std::shared_ptr<Population::Individual> one = nullptr, two = nullptr;

	/*while (notFound) {
		if (it == selectedPopulation.population.end()) it = selectedPopulation.population.begin();

		int rating = (*it)->getRating();
		if (rating == 0) {
			best = *it;
			foundOptimal = true;
			return std::pair<std::shared_ptr<Population::Individual>, std::shared_ptr<Population::Individual>>();
		}

		if (raitingFunction(rating) >= rand()) {
			if(one == nullptr) one = (*it)->copy();
			else {
				two = (*it)->copy();
				notFound = false;
			}
		}

		++it;
	}*/
	
	auto it1 = selectedPopulation.population.begin() + (random % selectedPopulation.population.size());
	auto it2 = selectedPopulation.population.begin() + (random % selectedPopulation.population.size());
	if(it1 == it2) {
		++it2;
		if (it2 == selectedPopulation.population.end()) it2 = selectedPopulation.population.begin();
	}

	one = (*it1)->copy();
	two = (*it2)->copy();

	return std::pair<std::shared_ptr<Population::Individual>, std::shared_ptr<Population::Individual>>(one, two);
}

std::shared_ptr<Population::Individual> MatingPool::findBestPointer()
{
	if (foundOptimal) {
		return best->copy();
	}
	if (!populationCreated) return nullptr;

	int min = INT_MAX;
	std::shared_ptr<Population::Individual> ret = nullptr;

	for (auto it = population_.population.begin(); it != population_.population.end(); ++it) {
		if ((*it)->getRating() < min) {
			min = (*it)->getRating();
			ret = *it;
		}
	}

	return ret;
}

std::shared_ptr<Population::Individual> MatingPool::findBestPointerCopy()
{
	return findBestPointer()->copy();
}

std::shared_ptr<Population::Individual> MatingPool::findWorstPointer()
{
	if (!populationCreated) return nullptr;

	int max = INT_MIN;
	std::shared_ptr<Population::Individual> ret = nullptr;

	for (auto it = population_.population.begin(); it != population_.population.end(); ++it) {
		if ((*it)->getRating() > max) {
			max = (*it)->getRating();
			ret = *it;
		}
	}
	return ret;
}

std::ostream& operator<<(std::ostream& os, const MatingPool& pool)
{
	os << pool.population_;
	return os;
}


#endif