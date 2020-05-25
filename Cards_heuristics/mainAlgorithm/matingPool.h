/**
 * @file matingPool.h
 * @brief Plik klasy puli rozrodczej
 * 
 */
#ifndef MATING_POOL_H
#define MATING_POOL_H

#include <memory>
#include <algorithm>

#include "population.h"

/**
 * @brief Klasa puli rozrodczej
 * 
 */
class MatingPool
{
public:
	/**
	 * @brief Wyliczenie typów krzyżowania
	 * 
	 */
	enum class CrossoverType;

private:
	/**
	 * @brief Populacja
	 * 
	 */
	Population population_;

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
	 * @brief Ilość osobników, które zostaną poddane krzyżowaniu
	 * 
	 */
	unsigned int numberOfCrossovers_;

	/**
	 * @brief Licznik prawdopodobieństwa mutacji genu
	 * 
	 */
	unsigned int mutationProb;

	/**
	 * @brief Mianownik prawdopodobieństwa mutacji genu
	 * 
	 */
	unsigned int maxProbValue;

	/**
	 * @brief Docelowa wartość dla pierwszego stosu
	 * 
	 */
	int groupAVal;

	/**
	 * @brief Docelowa wartość dla drugiego stosu
	 * 
	 */
	int groupBVal;

	/**
	 * @brief Flaga istnienia populacji
	 * 
	 */
	bool populationCreated;

	/**
	 * @brief Flaga generowania nowego pokolenia.
	 * Blokuje modyfikacje parametrów algorytmu do zakończenia tego procesu.
	 * 
	 */
	bool duringSimulation;

	/**
	 * @brief Flaga znalezienia rozwiązania optymalnego
	 * 
	 */
	bool foundOptimal;

	/**
	 * @brief Ilość genów w chromosomach populacji
	 * 
	 */
	const static unsigned int numberOfGenes;

	/**
	 * @brief Wskazanie na chromosom rozwiązania optymalnego
	 * 
	 */
	std::shared_ptr<Population::Individual> best;

	/**
	 * @brief Selekcja kołem ruletki
	 * 
	 * @param oldGeneration populacja przed selekcją
	 * @param sizeOfNewPop docelowa wielkość populacji po selekcji
	 * @return Population populacja po selekcji
	 */
	Population rouletteWheel(const Population& oldGeneration, const unsigned int& sizeOfNewPop);

	/**
	 * @brief Krzyżowanie osobników
	 * 
	 * @param selectedPopulation populacja, której osobniki będą krzyżowane
	 * @param type typ krzyżowania
	 * @param int ilość punktów krzyżowania wielopunktowego
	 * @return Population populacja po krzyżowaniach
	 */
	Population crossover(const Population& selectedPopulation, CrossoverType type, const unsigned int& numberOfPointCross = 3);

	/**
	 * @brief Mutowanie osobników
	 * 
	 * @param population populacja, której osobniki będą mutowane
	 */
	void mutation(Population& population);

	/**
	 * @brief Obliczenie dobroci osobników populacji
	 * 
	 * @param population populacja
	 * @param groupAIdeal docelowa wartość pierwszego stosu
	 * @param groupBIdeal docelowa wartość drugiego stosu
	 */
	void populationEvaluation(Population& population, const int& groupAIdeal, const int& groupBIdeal);

	/**
	 * @brief Dokonaj selekcji z dwóch pokoleń
	 * 
	 * @param oldGeneration stare pokolenie
	 * @param newGeneration nowe pokolenie
	 * @return Population populacja powstała z selekcji
	 */
	Population selectFromTwoGenerations(const Population& oldGeneration, const Population& newGeneration);

	/**
	 * @brief Znajdź najlepszego osobnika populacji
	 * 
	 * @return std::shared_ptr<Population::Individual> wskazanie na najlepszego osobnika populacji
	 */
	std::shared_ptr<Population::Individual> findBestPointer();

	/**
	 * @brief Znajdź najlepszego osobnika populacji
	 * 
	 * @return std::shared_ptr<Population::Individual> kopia wskazania na najlepszego osobnika populacji
	 */
	std::shared_ptr<Population::Individual> findBestPointerCopy();

	/**
	 * @brief Znajdź najgorszego osobnika populacji
	 * 
	 * @return std::shared_ptr<Population::Individual> wskazanie na najgorszego osobnika populacji
	 */
	std::shared_ptr<Population::Individual> findWorstPointer();

	/**
	 * @brief Wybierz osobniki do krzyżowania
	 * 
	 * @param selectedPopulation populacja, z której wybierane będą osobniki
	 * @return std::pair<std::shared_ptr<Population::Individual>, std::shared_ptr<Population::Individual>> para osobników
	 */
	std::pair<std::shared_ptr<Population::Individual>, std::shared_ptr<Population::Individual>> chooseTwoToCrossover(const Population& selectedPopulation);

	/**
	 * @brief Funkcja zależności prawdopodobieństwa wyboru osobnika w selekcji od jego dobroci
	 * 
	 * @param rating dobroć osobnika
	 * @return double prawdopodobieństwo
	 */
	double raitingFunction(const int& rating);

public:

	/**
	 * @brief Stwórz nowy obiekt Mating Pool
	 * 
	 */
	MatingPool();

	/**
	 * @brief Usuń obiekt Mating Pool
	 * 
	 */
	~MatingPool();

	MatingPool(const MatingPool& other) = delete;

	/**
	 * @brief Stwórz nowy obiekt Mating Pool przenosząc inny
	 * 
	 * @param other obiekt do przeniesienia
	 */
	MatingPool(MatingPool&& other) noexcept;

	MatingPool& operator=(MatingPool&& other) noexcept;

	/**
	 * @brief Stwórz pierwsze pokolenie
	 * 
	 */
	void createFirstPopulation();

	/**
	 * @brief Ustaw wartość Population Size
	 * 
	 * @param popSize nowa wartość wielkości populacji
	 */
	void setPopulationSize(const unsigned int& popSize);

	/**
	 * @brief Ustaw wartość Mutation Probability
	 * 
	 * @param random licznik prawdopodobieństwa
	 * @param max mianownik prawdopodobieństwa
	 */
	void setMutationProbability(const unsigned int& random, const unsigned int& max);

	/**
	 * @brief Ustaw wartość Number Of Crossovers
	 * 
	 * @param int nowa ilość osobników, które zostaną poddane krzyżowaniu
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
	 * @param value nowa wartość docelowa dla pierwszego stosu
	 */
	void setGroupAValue(const int& value);

	/**
	 * @brief Ustaw wartość Group B Value
	 * 
	 * @param value nowa wartość docelowa dla drugiego stosu
	 */
	void setGroupBValue(const int& value);

	/**
	 * @brief Sprawdzenie czy ustawione parametry algorytmu są poprawne
	 * 
	 * @return true parametry są poprawne
	 * @return false parametry nie są poprawne
	 */
	bool isDataValid();

	/**
	 * @brief Stwórz kolejne pokolenie
	 * 
	 * @param type typ krzyżowania
	 * @param numberOfPointCross ilość punktów dla krzyżowania wielopunktowego
	 */
	void runOneGeneration(CrossoverType type, const unsigned int& numberOfPointCross = 1);

	/**
	 * @brief Rozwiąż zadanie algorytmem zachłannym
	 * 
	 * @return BinaryChromosome chromosom reprezentujący rozwiązanie
	 */
	BinaryChromosome runHeuristic();

	/**
	 * @brief Znajdź najlepszego osobnika populacji
	 * 
	 * @return Population::Individual najlepszy osobnik populacji
	 */
	Population::Individual findBest();

	/**
	 * @brief Czy znaleziono rozwiązanie optymalne
	 * 
	 * @return true znaleziono
	 * @return false nie znaleziono
	 */
	bool isBestFound();

	/**
	 * @brief Zwróć znalezione rozwiązanie optymalne
	 * 
	 * @return Population::Individual osobnik reprezentujący rozwiązanie optymalne
	 */
	Population::Individual returnBest();

	enum class CrossoverType {
		multiplePoint,
		uniform,
		singlePoint
	};

	/**
	 * @brief Wypisanie populacji do strumienia
	 * 
	 * @param os strumień
	 * @param pool pula rozrodcza z populacją
	 * @return std::ostream& ten sam strumień
	 */
	friend std::ostream& operator<< (std::ostream& os, const MatingPool& pool);
};


#endif