#pragma once


#include <vector>
#include <string>


#include "config.h"
#include "BigInteger.h"


class BigIntegerToomCook : public BigInteger{
public:
    BigIntegerToomCook(int Base);
    BigIntegerToomCook(const std::vector<int> &vect, int Base);
    BigIntegerToomCook(const BigInteger &bigInt, int Base);
    BigIntegerToomCook(const std::string &str, int Base);

    virtual void Multiply(const BigIntegerToomCook &right_number);

    virtual BigIntegerToomCook& operator*(const BigIntegerToomCook &bigInt) const;

    virtual BigIntegerToomCook& operator*(int x) const;
};