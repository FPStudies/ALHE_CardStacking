/**
 * @file main.cpp
 * @brief Plik głównej funkcji programu.
 * 
 */
#include <iostream>
#include "mainAlgorithm/matingPool.h"
#include "mainAlgorithm/randomPoint.h"
#include "tests/testNormal.h"
#include "tests/testTime.h"
#include "userInterface/commandDivider.h"

using namespace std;

/**
 * @brief Główna funkcja programu. 
 * Wywołuje moduły odpowiedzialne za wczytanie danych i rozwiązanie zadania.
 */
int main(int argc, char**argv) {
	if (argc != 2)
		{
			cout<< "Please provide the path to the file with commands.\n";
			return -1;
		}

	MatingPool generation;
	RandomPoint::newSeed();

	TestNormal normal(200);
	TestTime time(200);

	CommandDivider commands;

	commands.addInterpreter(normal);
	commands.addInterpreter(time);
	if(commands.loadCommandsFromFile(argv[2])) std::cout << "Operation failed";

	return 0;
}