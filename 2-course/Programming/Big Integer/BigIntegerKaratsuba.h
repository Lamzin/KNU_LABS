#pragma once


#include <vector>
#include <string>


#include "BigInteger.h"


class BigIntegerKaratsuba : public BigInteger{
public:
    BigIntegerKaratsuba(int Base = 16384);
    BigIntegerKaratsuba(const std::vector<int> &vect, int Base = 16384);
    BigIntegerKaratsuba(const BigInteger &bigInt, int Base = 16384);
    BigIntegerKaratsuba(const std::string &str, int Base = 16384);
    
    virtual void Multiply(const BigIntegerKaratsuba &right_number);
    
    virtual BigIntegerKaratsuba& operator*(const BigIntegerKaratsuba &bigInt) const;

    virtual BigIntegerKaratsuba& operator*(int x) const;

};