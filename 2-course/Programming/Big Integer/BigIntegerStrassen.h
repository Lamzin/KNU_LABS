#pragma once


#include <vector>
#include <string>
#include <complex>

#include "config.h"
#include "BigInteger.h"


class BigIntegerStrassen : public BigInteger{
private:
    void FastFourierTransform(std::vector<std::complex<long double>> &vect, bool invert);

public:
    BigIntegerStrassen(int Base);
    BigIntegerStrassen(const std::vector<int> &vect, int Base);
    BigIntegerStrassen(const BigInteger &bigInt, int Base);
    BigIntegerStrassen(const std::string &str, int Base);
    
    virtual void Multiply(const BigIntegerStrassen &right_number);

    virtual BigIntegerStrassen& operator*(const BigIntegerStrassen &bigInt) const;
};