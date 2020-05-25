#ifndef TEST_CARDS_HEURISTIC_CPP
#define TEST_CARDS_HEURISTIC_CPP

#include "testCardsHeuristic.h"

/** 
* 	@brief Dostępne komendy (flagi):
*	A - docelowa wartość dla stosu A
*	B - docelowa wartość dla stosu B
*	mrand - licznik prawdopodobieństwa mutacji
*	mmax - mianownik prawdopodobieństwa mutacji
*	cnumb - ilość osobników poddawanych krzyżowaniu w każdym pokoleniu
*	popsize - wielkość populacji
*	popsizetourn - wielkość populacji po selekcji
*	crosspoints - ilość punktów przecięcia dla krzyżowania wielopunktowego
*	crosstype - typ krzyżowania
*	path - ściećka dla pliku wynikowego
*/
const char* TestCardsHeuristic::command[10] = {"A", "B", "mrand", "mmax", "cnumb", "popsize", "popsizetourn", "crosspoints", "crosstype", "path"};

/** 
* 	@brief Dostępne tryby krzyżowania:
*	singlePoint - jednopunktowe
*	multiplePoint - wielopunktowe
*	uniform - równomierne
*/
const char* TestCardsHeuristic::crossoverMode[3] = {"singlePoint", "multiplePoint", "uniform"};

void TestCardsHeuristic::setPoolValues(MatingPool& pool)
{
	pool.setGroupAValue(groupAValue);
	pool.setGroupBValue(groupBValue);
	pool.setMutationProbability(mutationRand, mutationMax);
	pool.setNumberOfCrossovers(crossoverNumber);
	pool.setPopulationSize(populationSize);
	pool.setPopulationSizeAfterSelection(populationSizeAfterSelection);
}

TestCardsHeuristic::TestCardsHeuristic(const unsigned int& maxNumberOfIterations)
	:maxNumberOfIterations_(maxNumberOfIterations),
	groupAValue(INT_MAX),
	groupBValue(INT_MAX),
	mutationRand(UINT_MAX), 
	mutationMax(UINT_MAX),
	crossoverNumber(UINT_MAX),
	populationSize(UINT_MAX),
	populationSizeAfterSelection(UINT_MAX),
	crossoverPoints(UINT_MAX),
	crossType(MatingPool::CrossoverType::uniform),
	isCrossTypeSet(false)
{}

TestCardsHeuristic::~TestCardsHeuristic()
{}

TestCardsHeuristic::TestCardsHeuristic(const TestCardsHeuristic& other)
	:maxNumberOfIterations_(other.maxNumberOfIterations_),
	groupAValue(other.groupAValue),
	groupBValue(other.groupBValue),
	mutationRand(other.mutationRand), 
	mutationMax(other.mutationMax),
	crossoverNumber(other.crossoverNumber),
	populationSize(other.populationSize),
	populationSizeAfterSelection(other.populationSizeAfterSelection),
	crossoverPoints(other.crossoverPoints),
	crossType(other.crossType),
	isCrossTypeSet(other.isCrossTypeSet)
{}

bool TestCardsHeuristic::isDataValid() const {
	if(groupAValue == INT_MAX || groupBValue == INT_MAX || mutationRand == UINT_MAX || mutationMax == UINT_MAX || !isCrossTypeSet || \
	crossoverNumber == UINT_MAX || populationSize == UINT_MAX || populationSizeAfterSelection == UINT_MAX || crossoverPoints == UINT_MAX)
	{
		return false;
	}

	return true;
}

void TestCardsHeuristic::setPopulationSize(const unsigned int& popSize) {populationSize = popSize; }
void TestCardsHeuristic::setMutationProbability(const unsigned int& random, const unsigned int& max) {mutationRand = random; mutationMax = max; }
void TestCardsHeuristic::setNumberOfCrossovers(const unsigned int& value) {crossoverNumber = value; }
void TestCardsHeuristic::setPopulationSizeAfterSelection(const int& value) {populationSizeAfterSelection = value; }

void TestCardsHeuristic::setGroupAValue(const int& value) {groupAValue = value; }
void TestCardsHeuristic::setGroupBValue(const int& value) {groupBValue = value; }

void TestCardsHeuristic::setOutputFile(const std::string& path) {pathToOutputFile = path; }

void TestCardsHeuristic::setCrossoverPoints(const unsigned int& value) {crossoverPoints = value; }
void TestCardsHeuristic::setCrossoverType(MatingPool::CrossoverType type) {crossType = type; isCrossTypeSet = true; }


bool TestCardsHeuristic::isCommand(const std::string& com) const {
	for(unsigned int i = 0; i < sizeof(command) / sizeof(command[0]); ++i){
		if(command[i] == com) return true;
	}

	return false;
}

bool TestCardsHeuristic::runCommand(const std::string& keyword, const std::vector<std::string>& flags, const std::vector<std::vector<std::string>>& dataToFlags) {
	if(flags.size() != dataToFlags.size()) return true;
	
	for(auto& fl : flags){
		for(unsigned int i = 0; i < sizeof(command) / sizeof(command[0]); ++i){
			if(command[i] == fl){
				for(unsigned int p = 0; p < dataToFlags[i].size(); ++p){
					std::stringstream ss(dataToFlags[i][p]);
					std::string str, crossMode;
					ss >> str;
			
					switch (i){
						case 0:
							std::stringstream(str) >> groupAValue;
							break;
						case 1:
							std::stringstream(str) >> groupBValue;
							break;
						case 2:
							std::stringstream(str) >> mutationRand;
							break;
						case 3:
							std::stringstream(str) >> mutationMax;
							break;
						case 4:
							std::stringstream(str) >> crossoverNumber;
							break;
						case 5:
							std::stringstream(str) >> populationSize;
							break;
						case 6:
							std::stringstream(str) >> populationSizeAfterSelection;
							break;
						case 7:
							std::stringstream(str) >> crossoverPoints;
							break;
						case 8:
							std::stringstream(str) >> crossMode;
							for(unsigned int k = 0; k < sizeof(crossoverMode) / sizeof(crossoverMode[0]); ++k){
								if(crossoverMode[k] == crossMode) {
									switch (k){
										case 0:
											setCrossoverType(MatingPool::CrossoverType::singlePoint);
											break;
										case 1:
											setCrossoverType(MatingPool::CrossoverType::multiplePoint);
											break;
										case 2:
											setCrossoverType(MatingPool::CrossoverType::uniform);
											break;
										default:
											return true;
									}
								}
							}
							break;
						case 9:
							std::stringstream(str) >> pathToOutputFile;
							break;
						default:
							return true;
					}
				}
			}
		}
	}

	runTest(keyword, pathToOutputFile);

	return false;
}



#endif