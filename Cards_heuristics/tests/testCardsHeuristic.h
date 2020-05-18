#ifndef TEST_CARDS_HEURISTIC_H
#define TEST_CARDS_HEURISTIC_H

#include "testInterface.h"
#include "../mainAlgorithm/matingPool.h"
#include "../userInterface/commandInterpreter.h"

#include <fstream>
#include <iostream>
#include <sstream>

class TestCardsHeuristic: public TestInterface, public CommandInterpreter{
protected:
    unsigned int maxNumberOfIterations_;

	int groupAValue;
	int groupBValue;
	unsigned int mutationRand, mutationMax;
	unsigned int crossoverNumber;
	unsigned int populationSize;
	unsigned int populationSizeAfterTournament;

	unsigned int crossoverPoints;

	MatingPool::CrossoverType crossType;
	bool isCrossTypeSet;

	std::string pathToOutputFile;

	void setPoolValues(MatingPool& pool);

    const static char* command[10];
    const static char* crossoverMode[3];

public:
    TestCardsHeuristic(const unsigned int& maxNumberOfIterations);
	virtual ~TestCardsHeuristic();
	TestCardsHeuristic(const TestCardsHeuristic& other);

    virtual void runTest(const std::string& path) = 0;
	virtual int runTestSilent(const std::string& path) = 0;
	virtual TestCardsHeuristic* clone() const = 0;
	virtual bool isDataValid() const override;

    virtual bool runCommand(const std::string& keyword, const std::vector<std::string>& flags, const std::vector<std::vector<std::string>>& dataToFlags) override; // TODO
	virtual bool isKeyword(const std::string& word) const = 0; 
	virtual bool isCommand(const std::string& command) const override;
	virtual bool expectedStringAfterCommand(const std::string& command, const std::string& string) const override;


    void setPopulationSize(const unsigned int& popSize);
	void setMutationProbability(const unsigned int& random, const unsigned int& max);
	void setNumberOfCrossovers(const unsigned int& value);
	void setPopulationSizeAfterTounament(const int& value);

	void setGroupAValue(const int& value);
	void setGroupBValue(const int& value);

	void setOutputFile(const std::string& path);

	void setCrossoverPoints(const unsigned int& value);
	void setCrossoverType(MatingPool::CrossoverType type);
};

#endif