#pragma once

#include <vector>
#include <map>

typedef unsigned long long ui64;
typedef unsigned int ui32;
typedef double f64;
typedef std::vector<ui32> vui32;

struct Histogram
{
	std::map<int, ui32> statistic;
	ui64 count;
	f64 coefficient, left, right;

	Histogram(f64 _left, f64 _right, f64 _coef) : left(_left), right(_right), coefficient(_coef){
		count = 0;
	}

	void add(f64 numb){
		if (numb > right || numb < left) return;

		numb = numb * coefficient;
		if (numb < 0.0f) numb -= 1.0f;// because [-1.2] = -2 

		count++;
		statistic[static_cast<int>(numb)]++;
	}

};