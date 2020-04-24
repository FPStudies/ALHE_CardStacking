#ifndef TEST_MULTIPLE_POINT_CPP
#define TEST_MULTIPLE_POINT_CPP

#include "testNormal.h"

const char* TestNormal::command[10] = {"A", "B", "mrand", "mmax", "cnumb", "popsize", "popsizetourn", "crosspoints", "crosstype", "path"};

const char* TestNormal::crossoverMode[3] = {"singlePoint", "multiplePoint", "uniform"};

const char* TestNormal::keyword[1] = {"testNormal"};


void TestNormal::setPoolValues(MatingPool& pool)
{
	pool.setGroupAValue(groupAValue);
	pool.setGroupBValue(groupBValue);
	pool.setMutationProbability(mutationRand, mutationMax);
	pool.setNumberOfCrossovers(crossoverNumber);
	pool.setPopulationSize(populationSize);
	pool.setPopulationSizeAfterTounament(populationSizeAfterTournament);
}

TestNormal::TestNormal(const unsigned int& maxNumberOfIterations)
	:maxNumberOfIterations_(maxNumberOfIterations),
	groupAValue(INT_MAX),
	groupBValue(INT_MAX),
	mutationRand(UINT_MAX), 
	mutationMax(UINT_MAX),
	crossoverNumber(UINT_MAX),
	populationSize(UINT_MAX),
	populationSizeAfterTournament(UINT_MAX),
	crossoverPoints(UINT_MAX),
	crossType(MatingPool::CrossoverType::uniform),
	isCrossTypeSet(false)
{}

TestNormal::~TestNormal()
{}

TestNormal::TestNormal(const TestNormal& other)
	:maxNumberOfIterations_(other.maxNumberOfIterations_),
	groupAValue(other.groupAValue),
	groupBValue(other.groupBValue),
	mutationRand(other.mutationRand), 
	mutationMax(other.mutationMax),
	crossoverNumber(other.crossoverNumber),
	populationSize(other.populationSize),
	populationSizeAfterTournament(other.populationSizeAfterTournament),
	crossoverPoints(other.crossoverPoints),
	crossType(other.crossType),
	isCrossTypeSet(other.isCrossTypeSet)
{}

void TestNormal::runTest(const std::string& path)
{
	std::ofstream file;
	std::ostream* out;
	bool fileOpened = false;

	file.open(path);
	if(!file) out = &std::cout;
	else{
		fileOpened = true;
		out = &file;
	}

	*out << "\n\n\n********* Started normal test" << std::endl;
	
	MatingPool pool;
	setPoolValues(pool);

	if(!isDataValid()) *out << "Data is not set properly\n";

	pool.createFirstPopulation();

	for (unsigned int i = 0; i < maxNumberOfIterations_ && !pool.isBestFound(); ++i) {
		pool.runOneGeneration(crossType, crossoverPoints);
		if(pool.isBestFound()) break;
	}

	*out << "The best pair is:\n\t" << pool.findBest() << "\n";

	*out << "********* Ended normal test" << std::endl;

	if(fileOpened) file.close();
}

TestNormal* TestNormal::clone() const
{
	return new TestNormal(*this);
}

bool TestNormal::isDataValid() const {
	if(groupAValue == INT_MAX || groupBValue == INT_MAX || mutationRand == UINT_MAX || mutationMax == UINT_MAX || !isCrossTypeSet || \
	crossoverNumber == UINT_MAX || populationSize == UINT_MAX || populationSizeAfterTournament == UINT_MAX || crossoverPoints == UINT_MAX)
	{
		return false;
	}

	return true;
}


void TestNormal::setPopulationSize(const unsigned int& popSize) {populationSize = popSize; }
void TestNormal::setMutationProbability(const unsigned int& random, const unsigned int& max) {mutationRand = random; mutationMax = max; }
void TestNormal::setNumberOfCrossovers(const unsigned int& value) {crossoverNumber = value; }
void TestNormal::setPopulationSizeAfterTounament(const int& value) {populationSizeAfterTournament = value; }

void TestNormal::setGroupAValue(const int& value) {groupAValue = value; }
void TestNormal::setGroupBValue(const int& value) {groupBValue = value; }

void TestNormal::setOutputFile(const std::string& path) {pathToOutputFile = path; }

void TestNormal::setCrossoverPoints(const unsigned int& value) {crossoverPoints = value; }
void TestNormal::setCrossoverType(MatingPool::CrossoverType type) {crossType = type; isCrossTypeSet = true; }



bool TestNormal::isKeyword(const std::string& word) const {

	for(unsigned int i = 0; i < sizeof(keyword) / sizeof(keyword[0]); ++i){
		if(keyword[i] == word) return true;
	}
	return false;
}

bool TestNormal::isCommand(const std::string& com) const {
	for(unsigned int i = 0; i < sizeof(command) / sizeof(command[0]); ++i){
		if(command[i] == com) return true;
	}

	return false;
}

bool TestNormal::expectedStringAfterCommand(const std::string& com, const std::string& string) const {
	unsigned int pos = 0;
	std::stringstream ss(string);
	std::string valuatedString, tmp;
	int valInt;
	unsigned int valUInt;

	for(; pos < sizeof(command) / sizeof(command[0]); ++pos){
		if(command[pos] == com) break;
	}

	ss >> valuatedString;

	if(pos < 2 && std::stringstream(valuatedString) >> valInt){
		ss >> std::skipws;
		if(!ss.eof()) return false;
	}
	else if(pos >= 2 && pos < 8 && std::stringstream(valuatedString) >> valUInt){
		ss >> std::skipws;
		if(!ss.eof()) return false;
	}
	else if(pos == 8 && std::stringstream(valuatedString) >> tmp){
		ss >> std::skipws;
		if(!ss.eof()) return false;

		for(unsigned int k = 0; k < sizeof(crossoverMode) / sizeof(crossoverMode[0]); ++k){
			if(crossoverMode[k] == tmp) return true;
		}
		return false;
	}
	else if(pos == 9 && std::stringstream(valuatedString) >> tmp){
		ss >> std::skipws;
		if(!ss.eof()) return false;
	}

	return true;
}

bool TestNormal::runCommand(const std::string& keyword, const std::vector<std::string>& flags, const std::vector<std::vector<std::string>>& dataToFlags) {
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
							std::stringstream(str) >> populationSizeAfterTournament;
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

	runTest(pathToOutputFile);

	return false;
}



#endif


