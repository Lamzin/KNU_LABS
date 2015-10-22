#pragma once


#include <vector>
#include <string>
#include <complex>

#include "config.h"
#include "BigInteger.h"


class BigIntegerStrassen : public BigInteger{
private:
    void FastFourierTransform(vcomp &vect, bool invert);

public:
    BigIntegerStrassen(ll Base);
    BigIntegerStrassen(const vll &vect, ll Base);
    BigIntegerStrassen(const BigInteger &bigInt, ll Base);
    BigIntegerStrassen(const std::string &str, ll Base);
    
    virtual void Multiply(const BigIntegerStrassen &right_number);

    virtual BigIntegerStrassen& operator*(const BigIntegerStrassen &bigInt) const;
};