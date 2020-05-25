/**
 * @file randomPoint.h
 * @brief Plik klasy generatora liczb losowych.
 * 
 */
#ifndef RAND_CLASS_H
#define RAND_CLASS_H

#include <utility>
#include <ctime>
#include <stdlib.h>

/**
 * @brief Klasa generatora liczb losowych
 * 
 */
class RandomPoint
{
	/**
	 * @brief Typ losowanych wartości
	 * 
	 */
	using TypeRand = int;

	/**
	 * @brief Granice generowanych wartości
	 * 
	 */
	TypeRand begin, end;

	/**
	 * @brief Długość zakresu generowanych wartości
	 * 
	 */
	TypeRand range;

public:
	/**
	 * @brief Stwórz nowy obiekt Random Point ustawiając zakres jako 0-size
	 * 
	 * @param size koniec zakresu generowanych wartości
	 */
	RandomPoint(const TypeRand size);

	/**
	 * @brief Stwórz nowy obiekt Random Point ustawiając zakres jako beginRange-endRange
	 * 
	 * @param beginRange początek zakresu generowanych wartości
	 * @param endRange koniec zakresu generowanych wartości
	 */
	RandomPoint(const TypeRand beginRange, const TypeRand endRange);

	/**
	 * @brief Usuń obiekt Random Point
	 * 
	 */
	~RandomPoint();

	/**
	 * @brief Stwórz nowy obiekt Random Point kopiując inny
	 * 
	 * @param other obiekt do skopiowania
	 */
	RandomPoint(const RandomPoint& other);

	/**
	 * @brief Stwórz nowy obiekt Random Point przenosząc inny
	 * 
	 * @param other obiekt do przeniesienia
	 */
	RandomPoint(RandomPoint&& other) noexcept;

	/**
	 * @brief Przenoszący operator przypisania
	 * 
	 * @param other obiekt do przeniesienia
	 * @return RandomPoint& wynik przeniesienia
	 */
	RandomPoint& operator=(RandomPoint&& other) noexcept;

	/**
	 * @brief Kopiujący operator przypisania
	 * 
	 * @param other obiekt do skopiowania
	 * @return RandomPoint& wynik kopiowania
	 */
	RandomPoint& operator=(const RandomPoint& other);

	/**
	 * @brief Losowanie z zakresem domkniętym
	 * 
	 * @return TypeRand wynik losowania
	 */
	TypeRand getClose() const;

	/**
	 * @brief Losowanie z zakresem domkniętym
	 * 
	 * @return const TypeRand stały wynik losowania
	 */
	const TypeRand const_getClose() const;

	/**
	 * @brief Losowanie z zakresem otwartym
	 * 
	 * @return TypeRand wynik losowania
	 */
	TypeRand getOpen() const;

	/**
	 * @brief Losowanie z zakresem otwartym
	 * 
	 * @return const TypeRand stały wynik losowania
	 */
	const TypeRand const_getOpen() const;

	/**
	 * @brief Ustaw wartość granic generowania
	 * 
	 * @param beginRange początek zakresu
	 * @param endRange koniec zakresu
	 */
	void setNew(const TypeRand beginRange, const TypeRand endRange);

	/**
	 * @brief Ustaw wartość długości zakresu generowania
	 * 
	 * @param size długość zakresu
	 */
	void setNew(const TypeRand size);

	/**
	 * @brief Losowanie z zakresem domkniętym na podstawie podanych granic zakresu
	 * 
	 * @param beginRange początek zakresu
	 * @param endRange koniec zakresu
	 * @return TypeRand wynik losowania
	 */
	static TypeRand getClose(const TypeRand& beginRange, const TypeRand& endRange);

	/**
	 * @brief Losowanie z zakresem otwartym na podstawie podanych granic zakresu
	 * 
	 * @param beginRange początek zakresu
	 * @param endRange koniec zakresu
	 * @return TypeRand wynik losowania
	 */
	static TypeRand getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	/**
	 * @brief Losowanie z zakresem domkniętym na podstawie podanych granic zakresu
	 * 
	 * @param beginRange początek zakresu
	 * @param endRange koniec zakresu
	 * @return const TypeRand stały wynik losowania
	 */
	static const TypeRand const_getClose(const TypeRand& beginRange, const TypeRand& endRange);

	/**
	 * @brief Losowanie z zakresem otwartym na podstawie podanych granic zakresu
	 * 
	 * @param beginRange początek zakresu
	 * @param endRange koniec zakresu
	 * @return const TypeRand stały wynik losowania
	 */
	static const TypeRand const_getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	/**
	 * @brief Losowanie wartości z zakresu 0-max i porównanie z podanym prawdopodobieńswem
	 * 
	 * @param probablility prawdopodobnieńtwo w promilach
	 * @param max koniec zakresu losowania
	 * @return true wulosowano wartość <= probability
	 * @return false wulosowano wartość > probability
	 */
	static bool getRand(const TypeRand& probablility, const TypeRand& max);

	/**
	 * @brief Ustawienie ziarna w oparciu o zegar
	 * 
	 */
	static void newSeed();

	/**
	 * @brief Ustawienie ziarna na zadaną wartość
	 * 
	 * @param seed nowa wartość ziarna
	 */
	static void newSeed(const int seed);
};


#endif
