#pragma once

#include <vector>
#include <map>

#include "config.h"
#include "Integer.h"



class Dixon{
private:
    
    int n;
    //std::vector<Integer> numbers;
    //std::vector<std::vector<int>> powers;
    //std::vector<Integer> Base;
    //std::map<Integer, int> result;

    Integer factor(Integer x);
    //bool isSmoothNumber(Integer x);


public:
    Dixon();

    std::vector<Integer> factorization(Integer x);
};