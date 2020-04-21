#ifndef RAND_CLASS_CPP
#define RAND_CLASS_CPP

#include "randomPoint.h"

RandomPoint::RandomPoint(const TypeRand size)
	:begin(0), end(size), range(size)
{}

RandomPoint::RandomPoint(const TypeRand beginRange, const TypeRand endRange)
	:begin(beginRange), end(endRange), range(endRange - beginRange)
{}

RandomPoint::~RandomPoint()
{}

RandomPoint::RandomPoint(const RandomPoint& other)
	:begin(other.begin), end(other.end), range(other.range)
{}

RandomPoint::RandomPoint(RandomPoint&& other) noexcept
	:begin(std::move(other.begin)), end(std::move(other.end)), range(std::move(other.range))
{}

RandomPoint& RandomPoint::operator=(RandomPoint&& other) noexcept
{
	begin = std::move(other.begin);
	end = std::move(other.end);
	range = std::move(other.range);
	return *this;
}

RandomPoint& RandomPoint::operator=(const RandomPoint& other)
{
	begin = other.begin;
	end = other.end;
	range = other.range;
	return *this;
}

RandomPoint::TypeRand RandomPoint::getClose() const
{
	return (rand() % (range + 1)) + begin;
}

const RandomPoint::TypeRand RandomPoint::const_getClose() const
{
	return getClose();
}

RandomPoint::TypeRand RandomPoint::getOpen() const
{
	return (rand() % (range - 1)) + begin + 1;
}

const RandomPoint::TypeRand RandomPoint::const_getOpen() const
{
	return getOpen();
}

void RandomPoint::setNew(const TypeRand beginRange, const TypeRand endRange)
{
	begin = beginRange;
	end = endRange;
	range = begin - end;
}

void RandomPoint::setNew(const TypeRand size)
{
	begin = 0;
	end = size;
	range = begin - end;
}

RandomPoint::TypeRand RandomPoint::getClose(const TypeRand& beginRange, const TypeRand& endRange)
{
	TypeRand rg = endRange - beginRange + 1;
	return (rand() % rg) + beginRange;
}

RandomPoint::TypeRand RandomPoint::getOpen(const TypeRand& beginRange, const TypeRand& endRange)
{
	TypeRand rg = endRange - beginRange - 1;
	return (rand() % rg) + beginRange + 1;
}

const RandomPoint::TypeRand RandomPoint::const_getClose(const TypeRand& beginRange, const TypeRand& endRange)
{
	return getClose(beginRange, endRange);
}

const RandomPoint::TypeRand RandomPoint::const_getOpen(const TypeRand& beginRange, const TypeRand& endRange)
{
	return getOpen(beginRange, endRange);
}

bool RandomPoint::getRand(const TypeRand& probablility, const TypeRand& max)
{
	return getOpen(0, max) <= probablility ? true : false;
}

void RandomPoint::newSeed()
{
	srand(static_cast<unsigned int>(time(nullptr)));
}

void RandomPoint::newSeed(const int seed)
{
	srand(seed);
}


#endif