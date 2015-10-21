#pragma once

#include "BigInteger.h"

class BigIntegerKaratsuba : public BigInteger{
public:
    BigIntegerKaratsuba(int Base = 256);
    BigIntegerKaratsuba(const BigInteger &bigInt, int Base = 256);
    BigIntegerKaratsuba(const std::string &str, int Base = 256);
    
    virtual void Multiply(const BigIntegerKaratsuba &right_number);
    
    virtual BigIntegerKaratsuba& operator*(const BigIntegerKaratsuba &bigInt);
};