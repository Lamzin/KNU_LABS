#pragma once


#include <vector>
#include <string>


#include "BigInteger.h"


class BigIntegerToomCook : public BigInteger{
public:
    BigIntegerToomCook(int Base = 16384);
    BigIntegerToomCook(const std::vector<int> &vect, int Base = 16384);
    BigIntegerToomCook(const BigInteger &bigInt, int Base = 16384);
    BigIntegerToomCook(const std::string &str, int Base = 16384);

    virtual void Multiply(const BigIntegerToomCook &right_number);

    virtual BigIntegerToomCook& operator*(const BigIntegerToomCook &bigInt) const;

    virtual BigIntegerToomCook& operator*(int x) const;
};