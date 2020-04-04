#ifndef RAND_CLASS_H
#define RAND_CLASS_H


class RandomPoint
{
	using TypeRand = int;
	TypeRand begin, end;
	TypeRand range;

public:
	RandomPoint(const TypeRand beginRange, const TypeRand endRange);
	~RandomPoint();
	RandomPoint(const RandomPoint& other);
	RandomPoint(RandomPoint&& other);
	RandomPoint& operator=(RandomPoint&& other);

	TypeRand getClose() const;
	const TypeRand const_getClose() const;
	TypeRand getOpen() const;
	const TypeRand const_getOpen() const;

	static TypeRand getClose(const TypeRand& beginRange, const TypeRand& endRange);
	static TypeRand getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	static const TypeRand const_getClose(const TypeRand& beginRange, const TypeRand& endRange);
	static const TypeRand const_getOpen(const TypeRand& beginRange, const TypeRand& endRange);

	static void newSeed();
	static void newSeed(const int seed);
};


#endif
