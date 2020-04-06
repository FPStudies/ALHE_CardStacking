
#include <iostream>
#include "matingPool.h"
#include "randomPoint.h"

using namespace std;

int main(int argc, char**argv) {
	cout << "Hello" << endl;

	unsigned int groupA = 13, groupB = 42;

	MatingPool generation;
	RandomPoint::newSeed();

	/*
	Error
	the return value is always the same.
	*/
	generation.setGroupAValue(groupA);
	generation.setGroupBValue(groupB);
	generation.setMutationProbability(10, 1000);
	generation.setPopulationSize(50);
	generation.setPopulationSizeAfterTounament(20);
	generation.setNumberOfCrossovers(20);

	if (generation.isDataValid()) std::cout << "Data is valid\n";
	else std::cout << "Data is invalid\n";

	generation.createFirstPopulation();

	for (int i = 0; i < 1; ++i) {
		generation.runOneGeneration(MatingPool::CrossoverType::singlePoint);
	}
	
	cout << "Done" << endl;
	auto temp = generation.findBest();
	cout << temp.getSum().first << " " << temp.getSum().second << " " << temp << endl;
	//cout << generation << endl;



	for (int i = 0; i < 20; ++i) {
		generation.runOneGeneration(MatingPool::CrossoverType::singlePoint); // tu wywala
	}
/*
	cout << "Done V2" << endl;
	temp = generation.findBest();
	cout << temp.getSum().first << " " << temp.getSum().second << " " << temp <<  endl;
	//cout << generation << endl;


	cout << "\nHeuristic\n";
	BinaryChromosome chromosome(10, false);
	chromosome.startHeuristic(groupA, groupB);
	cout << chromosome << "  value: " << chromosome.getSum().first << " // " << chromosome.getSum().second << "\n";
	*/
}