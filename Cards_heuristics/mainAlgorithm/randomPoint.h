#ifndef RAND_CLASS_H
#define RAND_CLASS_H

/**	@file randomPoint.h
*	@brief Plik klasy generatora liczb losowych.
*/

#include <utility>
#include <ctime>
#include <stdlib.h>

/** Klasa generatora liczb losowych */
class RandomPoint
{
	using TypeRand = int;	/**< Typ losowanych wartoœci*/
	TypeRand begin, end;	/**< Granice generowanych wartoœci*/
	TypeRand range;			/**< D³ugoœæ zakresu generowanych wartoœci*/

public:
	/** Konstruktor z przypisaniem zakresu jako 0-size*/
	RandomPoint(const TypeRand size);
	/** Konstruktor z przypisaniem zakresu jako beginRange-endRange*/
	RandomPoint(const TypeRand beginRange, const TypeRand endRange);
	~RandomPoint();
	RandomPoint(const RandomPoint& other);
	RandomPoint(RandomPoint&& other) noexcept;
	RandomPoint& operator=(RandomPoint&& other) noexcept;
	RandomPoint& operator=(const RandomPoint& other);

	/** Losowanie z zakresem domkniêtym*/
	TypeRand getClose() const;
	/** Losowanie z zakresem domkniêtym*/
	const TypeRand const_getClose() const;
	/** Losowanie z zakresem otwartym*/
	TypeRand getOpen() const;
	/** Losowanie z zakresem otwartym*/
	const TypeRand const_getOpen() const;

	/** Zmiana cech generatora w oparciu o nowe granice zakresu*/
	void setNew(const TypeRand beginRange, const TypeRand endRange);
	/** Zmiana cech generatora w oparciu o now¹ d³ugoœæ zakresu*/
	void setNew(const TypeRand size);

	/** Losowanie z zakresem domkniêtym na podstawie podanych granic zakresu*/
	static TypeRand getClose(const TypeRand& beginRange, const TypeRand& endRange);
	/** Losowanie z zakresem otwartym na podstawie podanych granic zakresu*/
	static TypeRand getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	/** */
	static const TypeRand const_getClose(const TypeRand& beginRange, const TypeRand& endRange);
	/** */
	static const TypeRand const_getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	/** Losowanie wartoœci z zakresu 0-max i porównanie z podanym prawdopodobieñswem
	*	@param probablility - prawdopodobnieœtwo w promilach.
	*	@return true - wulosowano wartoœæ <= probability
	*	@return false - wulosowano wartoœæ > probability
	*/
	static bool getRand(const TypeRand& probablility, const TypeRand& max);

	/** Ustawienie ziarna w oparciu o zegar*/
	static void newSeed();
	/** Ustawienie ziarna na zadan¹ wartoœæ*/
	static void newSeed(const int seed);
};


#endif
