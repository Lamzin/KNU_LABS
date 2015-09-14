#pragma once

#include <string>

#include "types.h"


class RandomGenerator{
protected:
	Histogram *histo;
	std::string __doc;
	ui64 modulo;

public:
	RandomGenerator();
	virtual ~RandomGenerator();

	virtual ui32 next();
	virtual f64 next_f64();
	Histogram *get_histogram();
	std::string __doc__();
};



//*********************************************************
//1
class LinearCongruential : public RandomGenerator{
protected:
	ui64 numb0, numb1, a, c;

public:
	LinearCongruential();
	virtual ui32 next();
};



//*********************************************************
//2
class QuadraticCongruential : public RandomGenerator{
protected:
	ui64 numb0, numb1, a, c, d;

public:
	QuadraticCongruential();
	virtual ui32 next();
};



//*********************************************************
//3
class FibonacciMethod : public RandomGenerator{
protected:
	ui64 numb0, numb1, numb2;

public:
	FibonacciMethod();
	virtual ui32 next();
};



//*********************************************************
//4
class InversiveCongruential : public RandomGenerator{
protected:
	ui64 numb0, numb1, a, c;
	ui64 reverse_element(ui64 num);

public:
	InversiveCongruential();
	virtual ui32 next();
};



//*********************************************************
//5
class ShufflingMethod : public RandomGenerator{
protected:
	ui64 numb0;
	RandomGenerator *X, *Y;

public:
	ShufflingMethod();
	virtual ui32 next();
};



//*********************************************************
// #6
class StandardDeviation : public RandomGenerator{
protected:
	RandomGenerator *Gen;
	f64 sum, arr[12];

public:
	StandardDeviation();
	virtual f64 next_f64();
};



//*********************************************************
// #7
class PolarCoordinates : public RandomGenerator{
protected:
	RandomGenerator *Gen;
	f64 V1, V2, numb0, numb1, S;
	bool start;

public:
	PolarCoordinates();
	virtual f64 next_f64();
};



//*********************************************************
// #8 // Knuth 2volume page131
class RatioMethodForNormalDeviates : public RandomGenerator{  
protected:
	RandomGenerator *Gen;
	f64 U, V, numb0;

public:
	RatioMethodForNormalDeviates();
	virtual f64 next_f64();
};



//*********************************************************
// #9 // Knuth 2volume page133 // Exponential Distribution
class LogarithmMethod : public RandomGenerator{
protected:
	RandomGenerator *Gen;
	f64 mu, numb0;

public:
	LogarithmMethod();
	virtual f64 next_f64();
};



//*********************************************************
// #10 // Knuth 2volume page134
class GammaDistribution : public RandomGenerator{
protected:
	RandomGenerator *Gen;
	f64 U, Y, X, a;

	f64 some_value();

public:
	GammaDistribution();
	virtual f64 next_f64();
};
