/**
 * @file population.h
 * @brief Plik klasy populacji
 * 
 */
#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <memory>

#include "binaryChromosome.h"
#include "randomPoint.h"

/**
 * @brief Klasa populacji
 * 
 */
class Population
{
	friend class MatingPool;
	using Individual = BinaryChromosome;
	using Container = std::vector<std::shared_ptr<Individual>>;

	/**
	 * @brief Agregacja osobników
	 * 
	 */
	Container population;
	
	#ifdef COUNT_METHOD_CALL
	static unsigned int constructor_call;
	static unsigned int destructor_call;
	static unsigned int constructor_copy_call;
	static unsigned int constructor_rewriting_call;

	static unsigned int method_operatorAdd_call;

	static unsigned int method_runMutationInPopulation_call;
	static unsigned int method_generatePopulation_call;
	static unsigned int method_evaluate_call;
	#endif
	

public:
	/**
	 * @brief Stwórz nowy obiekt Population
	 * 
	 */
	Population();

	/*
	 * @brief Stwórz nowy obiekt Population
	 * 
	 * @param 
	 */
	//Population(const Individual& individual);

	/**
	 * @brief Usuń obiekt Population
	 * 
	 */
	~Population();

	/**
	 * @brief Stwórz nowy obiekt Population kopiując inny
	 * 
	 * @param other obiekt do skopiowania
	 */
	Population(const Population& other);

	/**
	 * @brief Stwórz nowy obiekt Population przenosząc inny
	 * 
	 * @param other obiekt do przeniesienia
	 */
	Population(Population&& other) noexcept;

	/**
	 * @brief Przenoszący operator przypisania
	 * 
	 * @param other obiekt do przeniesienia
	 * @return Population& wynik przeniesienia
	 */
	Population& operator=(Population&& other) noexcept;

	/**
	 * @brief Kopiujący operator przypisania
	 * 
	 * @param other obiekt do skopiowania
	 * @return Population& wynik kopiowania
	 */
	Population& operator=(const Population& other);

	/**
	 * @brief Łączenie populacji
	 * 
	 * @param other populacja do złączenia
	 * @return Population& wynik łączenia
	 */
	Population& operator+=(const Population& other);

	/**
	 * @brief Dokonaj mutacji w populacji
	 * 
	 * @param mutationProb licznik prawdopodobieństwa mutacji
	 * @param maxMutationValue mianownik prawdopodobieństwa mutacji
	 */
	void runMutationInPopulation(const unsigned int& mutationProb, const unsigned int& maxMutationValue = 1000);

	/**
	 * @brief Ustaw wartość Population Size
	 * 
	 * @param size nowa wielkość populacji
	 */
	void setPopulationSize(const unsigned int& size);

	/**
	 * @brief Stwórz nową populację
	 * 
	 * @param numberOfGenes ilość genów osobników populacji
	 */
	void generatePopulation(const unsigned int& numberOfGenes);

	/**
	 * @brief Oblicz dobroć osobników populacji
	 * 
	 * @param groupAIdeal docelowa wartość dla pierszego stosu
	 * @param groupBIdeal docelowa wartość dla drugiego stosu
	 */
	void evaluate(const int& groupAIdeal, const int& groupBIdeal);

	/**
	 * @brief Wypisz osobniki populacji do strumienia
	 * 
	 * @param os strumień
	 * @param pop populacja
	 * @return std::ostream& ten sam strumień
	 */
	friend std::ostream& operator<< (std::ostream& os, const Population& pop);


	#ifdef COUNT_METHOD_CALL
	static unsigned int get_constructor_call();
	static unsigned int get_destructor_call();
	static unsigned int get_constructor_copy_call();
	static unsigned int get_constructor_rewriting_call();

	static unsigned int get_method_operatorAdd_call();

	static unsigned int get_method_runMutationInPopulation_call();
	static unsigned int get_method_generatePopulation_call();
	static unsigned int get_method_evaluate_call();


	static void method_couter_call_clear();
	#endif

};


#endif
