#pragma once

#include <vector>


#include "Integer.h"


class rhoPollard{
private:
    Integer factor(Integer n);

public:
    rhoPollard();

    std::vector<Integer> factorization(Integer x);

};