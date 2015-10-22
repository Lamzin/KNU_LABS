#pragma once


#include <vector>
#include <string>


#include "config.h"
#include "BigInteger.h"


class BigIntegerToomCook : public BigInteger{
public:
    BigIntegerToomCook(ll Base);
    BigIntegerToomCook(const vll &vect, ll Base);
    BigIntegerToomCook(const BigInteger &bigInt, ll Base);
    BigIntegerToomCook(const std::string &str, ll Base);

    virtual void Multiply(const BigIntegerToomCook &right_number);

    virtual BigIntegerToomCook& operator*(const BigIntegerToomCook &bigInt) const;

    virtual BigIntegerToomCook& operator*(ll x) const;
};