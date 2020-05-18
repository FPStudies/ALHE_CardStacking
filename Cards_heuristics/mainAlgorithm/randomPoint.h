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
	using TypeRand = int;	/**< Typ losowanych warto�ci*/
	TypeRand begin, end;	/**< Granice generowanych warto�ci*/
	TypeRand range;			/**< D�ugo�� zakresu generowanych warto�ci*/

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

	/** Losowanie z zakresem domkni�tym*/
	TypeRand getClose() const;
	/** Losowanie z zakresem domkni�tym*/
	const TypeRand const_getClose() const;
	/** Losowanie z zakresem otwartym*/
	TypeRand getOpen() const;
	/** Losowanie z zakresem otwartym*/
	const TypeRand const_getOpen() const;

	/** Zmiana cech generatora w oparciu o nowe granice zakresu*/
	void setNew(const TypeRand beginRange, const TypeRand endRange);
	/** Zmiana cech generatora w oparciu o now� d�ugo�� zakresu*/
	void setNew(const TypeRand size);

	/** Losowanie z zakresem domkni�tym na podstawie podanych granic zakresu*/
	static TypeRand getClose(const TypeRand& beginRange, const TypeRand& endRange);
	/** Losowanie z zakresem otwartym na podstawie podanych granic zakresu*/
	static TypeRand getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	/** */
	static const TypeRand const_getClose(const TypeRand& beginRange, const TypeRand& endRange);
	/** */
	static const TypeRand const_getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	/** Losowanie warto�ci z zakresu 0-max i por�wnanie z podanym prawdopodobie�swem
	*	@param probablility - prawdopodobnie�two w promilach.
	*	@return true - wulosowano warto�� <= probability
	*	@return false - wulosowano warto�� > probability
	*/
	static bool getRand(const TypeRand& probablility, const TypeRand& max);

	/** Ustawienie ziarna w oparciu o zegar*/
	static void newSeed();
	/** Ustawienie ziarna na zadan� warto��*/
	static void newSeed(const int seed);
};


#endif
