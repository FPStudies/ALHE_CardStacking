/**
 * @file testCardsHeuristic.h
 * @brief Plik bazowej klasy testowania
 * 
 */

#ifndef TEST_CARDS_HEURISTIC_H
#define TEST_CARDS_HEURISTIC_H

#include "testInterface.h"
#include "../mainAlgorithm/matingPool.h"
#include "../userInterface/commandInterpreter.h"

#include <fstream>
#include <iostream>
#include <sstream>

/**
 * @brief Bazowa klasa testowania
 * 
 */
class TestCardsHeuristic: public TestInterface, public CommandInterpreter{
protected:
	/**
	 * @brief Maksymalna ilość wygenerowanych pokoleń
	 * 
	 */
    unsigned int maxNumberOfIterations_;

	/**
	 * @brief Docelowa wartość dla pierwszego stosu
	 * 
	 */
	int groupAValue;

	/**
	 * @brief Docelowa wartość dla drugiego stosu
	 * 
	 */
	int groupBValue;

	/**
	 * @brief Licznik prawdopodobieństwa mutacji
	 * 
	 */
	unsigned int mutationRand;

	/**
	 * @brief Mianownik prawdopodobieństwa mutacji
	 * 
	 */
	unsigned int mutationMax;

	/**
	 * @brief Ilość osobników krzyżowanych w każdym pokoleniu
	 * 
	 */
	unsigned int crossoverNumber;

	/**
	 * @brief Wielkość populacji
	 * 
	 */
	unsigned int populationSize;

	/**
	 * @brief Wielkość populacji po selekcji
	 * 
	 */
	unsigned int populationSizeAfterSelection;

	/**
	 * @brief Ilość punktów krzyżowania wielopunktowego
	 * 
	 */
	unsigned int crossoverPoints;

	/**
	 * @brief Typ krzyżowania
	 * 
	 */
	MatingPool::CrossoverType crossType;

	/**
	 * @brief Czy ustawiono typ krzyżowania
	 * 
	 */
	bool isCrossTypeSet;

	/**
	 * @brief Ścieżka do pliku z wynikami testów
	 * 
	 */
	std::string pathToOutputFile;

	/**
	 * @brief Ustaw wartości puli rozrodczej
	 * 
	 * @param pool pula rozrodcza
	 */
	void setPoolValues(MatingPool& pool);

    const static char* command[10];

    const static char* crossoverMode[3];

public:
	/**
	 * @brief Stwórz nowy obiekt Test Cards Heuristic
	 * 
	 * @param maxNumberOfIterations maksymalna ilość wygenerowanych pokoleń
	 */
    TestCardsHeuristic(const unsigned int& maxNumberOfIterations);

	/**
	 * @brief Usuń obiekt Test Cards Heuristic
	 * 
	 */
	virtual ~TestCardsHeuristic();

	/**
	 * @brief Stwórz nowy obiekt Test Cards Heuristic kopiując inny
	 * 
	 * @param other obiekt do skopiowania
	 */
	TestCardsHeuristic(const TestCardsHeuristic& other);

	/**
	 * @brief Uruchom odpowiedni test metody genetycznej
	 * 
	 * @param keyword nazwa trybu działania
	 * @param path ścieżka do pliku z poleceniami
	 */
    virtual int runTest(const std::string& keyword, const std::string& path) = 0;

	/**
	 * @brief Uruchom test metody genetycznej
	 * 
	 * @param path ścieżka do pliku z poleceniami
	 */
	virtual void runTestBasic(const std::string& path) = 0;

	/**
	 * @brief Uruchom test metody genetycznej z minimalnym wypisem do strumienia
	 * 
	 * @param path ścieżka do pliku z poleceniami
	 * @return int reprezentacja wyniku
	 */
	virtual int runTestSilent(const std::string& path) = 0;

	/**
	 * @brief Uruchom test metody zachłannej
	 * 
	 * @param path ścieżka do pliku z poleceniami
	 */
	virtual void runTestHeuristic(const std::string& path) = 0;

	/**
	 * @brief Uruchom test metody zachłannej minimalnym wypisem do strumienia
	 * 
	 * @param path ścieżka do pliku z poleceniami
	 * @return int reprezentacja wyniku
	 */
	virtual int runTestHeuristicSilent(const std::string& path) = 0;

	/**
	 * @brief Kopiowanie obiektu klasy TestCardsHeuristic
	 * 
	 * @return TestCardsHeuristic* wskazanie na kopię
	 */
	virtual TestCardsHeuristic* clone() const = 0;

	/**
	 * @brief Sprawdzenie czy parametry algorytmu są prawidłowe
	 * 
	 * @return true są poprawne
	 * @return false nie są poprawne
	 */
	virtual bool isDataValid() const override;

	/**
	 * @brief Wykonaj podaną komendę programu
	 * 
	 * @param keyword tryb działania programu
	 * @param flags kolejne flagi wykonania
	 * @param dataToFlags argumenty flag wykonania
	 * @return true bład
	 * @return false powodzenie
	 */
    virtual bool runCommand(const std::string& keyword, const std::vector<std::string>& flags, const std::vector<std::vector<std::string>>& dataToFlags) override;

	/**
	 * @brief Sprawdź czy string jest trybem działania programu
	 * 
	 * @param word string
	 * @return true jest
	 * @return false nie jest
	 */
	virtual bool isKeyword(const std::string& word) const = 0;

	/**
	 * @brief Sprawdź czy string jest flagą
	 * 
	 * @param command string
	 * @return true jest
	 * @return false nie jest
	 */
	virtual bool isCommand(const std::string& command) const override;

	/**
	 * @brief Ustaw wartość Population Size
	 * 
	 * @param int nowa wielkość populacji
	 */
    void setPopulationSize(const unsigned int& popSize);

	/**
	 * @brief Ustaw wartość Mutation Probability
	 * 
	 * @param int nowy licznik prawdopodobieństwa
	 * @param int nowy mianownik prawdopodobieństwa
	 */
	void setMutationProbability(const unsigned int& random, const unsigned int& max);

	/**
	 * @brief Ustaw wartość Number Of Crossovers
	 * 
	 * @param int nowa ilość krzyżowanych osobników
	 */
	void setNumberOfCrossovers(const unsigned int& value);

	/**
	 * @brief Ustaw wartość Population Size After Selection
	 * 
	 * @param value nowa wielkość populacji po selekcji
	 */
	void setPopulationSizeAfterSelection(const int& value);

	/**
	 * @brief Ustaw wartość Group A Value
	 * 
	 * @param value nowa docelowa wartość dla pierwszego stosu
	 */
	void setGroupAValue(const int& value);

	/**
	 * @brief Ustaw wartość Group B Value
	 * 
	 * @param value nowa docelowa wartość dla drugiego stosu
	 */
	void setGroupBValue(const int& value);

	/**
	 * @brief Ustaw wartość Output File
	 * 
	 * @param path nowa ścieżka do pliku z wynikami
	 */
	void setOutputFile(const std::string& path);

	/**
	 * @brief Ustaw wartość Crossover Points
	 * 
	 * @param int nowa ilość punktów krzyżowania wielopunktowego
	 */
	void setCrossoverPoints(const unsigned int& value);

	/**
	 * @brief Ustaw wartość Crossover Type
	 * 
	 * @param type nowy typ krzyżowania
	 */
	void setCrossoverType(MatingPool::CrossoverType type);
};

#endif