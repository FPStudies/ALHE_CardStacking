
#include <iostream>
#include "matingPool.h"
#include "randomPoint.h"
#include "tests/testNormal.h"
#include "userInterface/commandDivider.h"

using namespace std;

int main(int argc, char**argv) {
	cout << "Hello" << endl;

	unsigned int groupA = 13, groupB = 42;

	MatingPool generation;
	RandomPoint::newSeed();

	TestNormal tmp(100);
	CommandDivider commands;

	/*tmp.setCrossoverPoints(3);
	tmp.setCrossoverType("multiplePoint");
	tmp.setGroupAValue(groupA);
	tmp.setGroupBValue(groupB);
	tmp.setMutationProbability(10, 1000);
	tmp.setNumberOfCrossovers(10);
	tmp.setOutputFile("output/test.txt");
	tmp.setPopulationSize(20);
	tmp.setPopulationSizeAfterTounament(10);*/

	commands.addInterpreter(tmp);
	if(commands.loadCommandsFromFile("scripts/test.txt")) std::cout << "Operation failed";

	/*
	Error
	the return value is always the same.
	*/
	/*generation.setGroupAValue(groupA);
	generation.setGroupBValue(groupB);
	generation.setMutationProbability(10, 1000);
	generation.setPopulationSize(20);
	generation.setPopulationSizeAfterTounament(10);
	generation.setNumberOfCrossovers(10);

	if (generation.isDataValid()) std::cout << "Data is valid\n";
	else std::cout << "Data is invalid\n";

	generation.createFirstPopulation();
	cout << "Random init:\n" << generation.findBest() << "\n";

	for (int i = 0; i < 1; ++i) {
		generation.runOneGeneration(MatingPool::CrossoverType::uniform);
	}
	
	cout << "Done" << endl;
	auto temp = generation.findBest();
	cout << temp << endl;
	//cout << generation << endl;



	for (int i = 0; i < 20; ++i) {
		generation.runOneGeneration(MatingPool::CrossoverType::uniform); // tu wywala
	}

	cout << "Done V2" << endl;
	temp = generation.findBest();
	cout << temp <<  endl;
	//cout << generation << endl;


	cout << "\nHeuristic\n";
	BinaryChromosome chromosome(10, false);
	chromosome.startHeuristic(groupA, groupB);
	cout << chromosome << "\n";*/
	
}