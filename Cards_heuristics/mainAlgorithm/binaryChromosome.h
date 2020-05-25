/**
 * @file binaryChromosome.h
 * @brief Plik klasy chromosomu.
 * 
 */
#ifndef BINARY_CHROMOSOME_H
#define BINARY_CHROMOSOME_H

#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <memory>
#include <limits.h>

#include "randomPoint.h"

/**
 * @brief Klasa chromosomu
 * 
 */
class BinaryChromosome
{
	enum class Symbol;
	using Container = std::vector<Symbol>;

	/**
	 * @brief Zbiór przechowywanych wartości genów
	 * 
	 */
	Container chromosome;

	/**
	 * @brief Obiekt generatora liczb losowych
	 * 
	 */
	RandomPoint randClass;

	/**
	 * @brief Dobroć chromosomu.
	 * Tym lepsza im wartość jest mniejsza.
	 * 
	 */
	int rating;

	/**
	 * @brief 
	 * 
	 * @param groupA 
	 * @param groupB 
	 * @param groupAIdeal 
	 * @param groupBIdeal 
	 * @return int 
	 */
	int bindTwoGroupRating(const int& groupA, const int& groupB, const int& groupAIdeal, const int& groupBIdeal);

	/**
	 * @brief Wyliczenie możliwych przypisań karty
	 * 
	 */
	enum class Symbol {
		groupA,
		groupB,
		undefined
	};

	#ifdef COUNT_METHOD_CALL
	static unsigned int constructor_call;
	static unsigned int destructor_call;
	static unsigned int constructor_copy_call;
	static unsigned int constructor_rewriting_call;

	static unsigned int method_swap_call;
	static unsigned int method_copy_call;
	static unsigned int method_mutation_call;
	static unsigned int method_evaluate_call;
	static unsigned int method_setRandValues_call;
	static unsigned int method_getSum_call;
	static unsigned int method_comparison_call;
	static unsigned int method_Crossing_call;
	static unsigned int method_singlePointCrossing_call;
	static unsigned int method_multiplePointCrossing_call;
	static unsigned int method_Crossing_call;
	static unsigned int method_uniformCrossing_call;
	static unsigned int method_startHeuristic_call;
	#endif

public:
	/**
	 * @brief Stwórz nowy obiekt Binary Chromosome
	 * 
	 * @param int ilość genów
	 * @param randVal możliwość zainicjowania genów losową wartością
	 */
	BinaryChromosome(const unsigned int& size, bool randVal = true);

	/**
	 * @brief Usuń obiekt Binary Chromosome
	 * 
	 */
	~BinaryChromosome();

	/**
	 * @brief Stwórz nowy obiekt Binary Chromosome kopiując inny
	 * 
	 * @param other obiekt do skopiowania
	 */
	BinaryChromosome(const BinaryChromosome& other);

	/**
	 * @brief Stwórz nowy obiekt Binary Chromosome przenosząc inny
	 * 
	 * @param other obiekt do przeniesienia
	 */
	BinaryChromosome(BinaryChromosome&& other) noexcept;

	/**
	 * @brief przenoszący operator przypisania
	 * 
	 * @param other obiekt do przeniesienia
	 * @return BinaryChromosome& wynik przeniesienia
	 */
	BinaryChromosome& operator=(BinaryChromosome&& other) noexcept;

	/**
	 * @brief kopiujący operator przypisania
	 * 
	 * @param other obiekt do skopiowania
	 * @return BinaryChromosome& wynik kopiowania
	 */
	BinaryChromosome& operator=(const BinaryChromosome& other);

	/**
	 * @brief Kopiowanie ciągu genów z innego chromosomu na podane miejsce tego.
	 * 
	 * @param startPosOther pozycja pierwszego genu do skopiowania
	 * @param endPosOther pozycja za ostatnim genem do skopiowania
	 * @param from chromosom, którego geny będą kopiowane
	 * @param startPosThis pierwsza pozycja, na którą skopiowane zostaną geny
	 * @param endPosThis pozycja za ostatnią, na którą skopiowane zostaną geny
	 */
	void copy(const unsigned int& startPosOther, const unsigned int& endPosOther, const BinaryChromosome& from, const unsigned int& startPosThis, const unsigned int& endPosThis);
	
	/**
	 * @brief Kopiowanie ciągu genów z innego chromosomu na analogiczne miejsce tego.
	 * 
	 * @param startPosOther pozycja pierwszego genu do skopiowania
	 * @param endPosOther pozycja za ostatnim genem do skopiowania
	 * @param from chromosom, którego geny będą kopiowane
	 */
	void copy(const unsigned int& startPosOther, const unsigned int& endPosOther, const BinaryChromosome& from);

	/**
	 * @brief Stworzenie unique_ptr wskazującego na ten obiekt
	 * 
	 * @return std::unique_ptr<BinaryChromosome> unique_ptr wskazujący na ten obiekt
	 */
	std::unique_ptr<BinaryChromosome> copy();

	/**
	 * @brief Zamień ciągi genów między chromosomami.
	 * 
	 * @param startPosOther pozycja pierwszego genu innego chromosomu do zamiany
	 * @param endPosOther pozycja za ostatnim genem innego chromosomu do zamiany
	 * @param from chromosom, z którym zamieniane będą geny
	 * @param startPosThis pozycja pierwszego genu tego chromosomu do zamiany
	 * @param endPosThis pozycja za ostatnim genem tego chromosomu do zamiany
	 */
	void swap(const unsigned int& startPosOther, const unsigned int& endPosOther, BinaryChromosome& from, const unsigned int& startPosThis, const unsigned int& endPosThis);
	
	/**
	 * @brief Zamień ciągi genów na analogicznych pozycjach między chromosomami.
	 * 
	 * @param startPosOther pozycja pierwszego genu do zamiany
	 * @param endPosOther pozycja za ostatnim genem do zamiany
	 * @param from chromosom, z którym zamieniane będą geny
	 */
	void swap(const unsigned int& startPosOther, const unsigned int& endPosOther, BinaryChromosome& from);

	/**
	 * @brief Mutowanie chromosomu.
	 * Inwersja możliwa dla każdego genu.
	 * 
	 * @param probability licznik prawdopodobieństwa mutacji genu
	 * @param maxProbVal mianownik prawdopodobieństwa mutacji genu
	 */
	void mutation(const unsigned int& probability, const unsigned int& maxProbVal = 1000);

	/**
	 * @brief Oblicz wartość dobroci chromosomu.
	 * 
	 * @param groupAIdeal docelowa wartość pierszego stosu
	 * @param groupBIdeal docelowa wartość drugiego stosu
	 */
	void evaluate(const int& groupAIdeal, const int& groupBIdeal);

	/**
	 * @brief Pobierz wartość Rating.
	 * Im mniejsza tym lepiej.
	 * 
	 * @return int wartość dobroci
	 */
	int getRating() const;

	/**
	 * @brief Pobierz ilość genów.
	 * 
	 * @return unsigned int ilość genów
	 */
	unsigned int size() const;

	/**
	 * @brief Zainicjuj geny losowymi wartościami
	 * 
	 */
	void setRandValues();

	/**
	 * @brief Zwróć aktualne sumy wartości na stosach
	 * 
	 * @return std::pair<int, int> sumy wartości na stosach
	 */
	std::pair<int, int> getSum() const;

	/**
	 * @brief Wypisanie przypisań genów.
	 * 
	 * @param os strumień, na który zostaną wypisane przypisania
	 * @param chrom chromosom, którego przypisania zostaną wypisane
	 * @return std::ostream& wskazanie na podany strumień
	 */
	friend std::ostream& operator<< (std::ostream& os, const BinaryChromosome& chrom);

	/**
	 * @brief Operator porównania chromosomów na podstawie przypisania genów
	 * 
	 * @param one pierwszy chromosom do porównania
	 * @param two drugi chromosom do porównania
	 * @return true chromosomy są takie same
	 * @return false chromosomy się różnią
	 */
	friend bool operator==(const BinaryChromosome& one, const BinaryChromosome& two);

	/**
	 * @brief Operator porównania chromosomów na podstawie przypisania genów
	 * 
	 * @param one pierwszy chromosom do porównania
	 * @param two drugi chromosom do porównania
	 * @return true chromosomy się różnią
	 * @return false chromosomy są takie same
	 */
	friend bool operator!=(const BinaryChromosome& one, const BinaryChromosome& two);

	/**
	 * @brief Krzyżowanie jednopunktowe.
	 * 
	 * @param other drugi chromosom do krzyżowania
	 */
	void singlePointCrossing(BinaryChromosome& other);

	/**
	 * @brief Krzyżowanie wielopunktowe
	 * 
	 * @param other drugi chromosom do krzyżowania
	 * @param numberOfPoints ilość punktów krzyżowania
	 */
	void multiplePointCrossing(BinaryChromosome& other, const unsigned int& numberOfPoints);

	/**
	 * @brief Krzyżowanie równomierne
	 * 
	 * @param other drugi chromosom do krzyżowania
	 */
	void uniformCrossing(BinaryChromosome& other);

	/**
	 * @brief Rozwiązanie zachłanne.
	 * Ustawia stan chromosomu na rozwiązanie głównego problemu osiągnięte algorytmem zachłannym dla zadanych wartości docelowych.
	 * 
	 * @param groupAIdeal docelowa wartość dla pierwszego stosu
	 * @param groupBIdeal docelowa wartość dla drugiego stosu
	 */
	void startHeuristic(const int& groupAIdeal, const int& groupBIdeal);


	#ifdef COUNT_METHOD_CALL
	static unsigned int get_constructor_call();
	static unsigned int get_destructor_call();
	static unsigned int get_constructor_copy_call();
	static unsigned int get_constructor_rewriting_call();

	static unsigned int get_method_swap_call();
	static unsigned int get_method_copy_call();
	static unsigned int get_method_mutation_call();
	static unsigned int get_method_evaluate_call();
	static unsigned int get_method_setRandValues_call();
	static unsigned int get_method_getSum_call();
	static unsigned int get_method_comparison_call();
	static unsigned int get_method_Crossing_call();
	static unsigned int get_method_singlePointCrossing_call();
	static unsigned int get_method_multiplePointCrossing_call();
	static unsigned int get_method_Crossing_call();
	static unsigned int get_method_uniformCrossing_call();
	static unsigned int get_method_startHeuristic_call();


	static void method_couter_call_clear();
	#endif	

};


#endif
