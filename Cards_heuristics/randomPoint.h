#ifndef RAND_CLASS_H
#define RAND_CLASS_H

#include <utility>
#include <ctime>
#include <stdlib.h>

class RandomPoint
{
	using TypeRand = int;
	TypeRand begin, end;
	TypeRand range;

public:
	RandomPoint(const TypeRand size);
	RandomPoint(const TypeRand beginRange, const TypeRand endRange);
	~RandomPoint();
	RandomPoint(const RandomPoint& other);
	RandomPoint(RandomPoint&& other) noexcept;
	RandomPoint& operator=(RandomPoint&& other) noexcept;
	RandomPoint& operator=(const RandomPoint& other);

	TypeRand getClose() const;
	const TypeRand const_getClose() const;
	TypeRand getOpen() const;
	const TypeRand const_getOpen() const;

	void setNew(const TypeRand beginRange, const TypeRand endRange);
	void setNew(const TypeRand size);

	static TypeRand getClose(const TypeRand& beginRange, const TypeRand& endRange);
	static TypeRand getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	static const TypeRand const_getClose(const TypeRand& beginRange, const TypeRand& endRange);
	static const TypeRand const_getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	/*
	Probablility in per mille.
	*/
	static bool getRand(const TypeRand& probablility, const TypeRand& max);

	static void newSeed();
	static void newSeed(const int seed);
};


#endif
