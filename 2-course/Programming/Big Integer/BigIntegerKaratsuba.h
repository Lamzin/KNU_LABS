#pragma once


#include <vector>
#include <string>


#include "config.h"
#include "BigInteger.h"


class BigIntegerKaratsuba : public BigInteger{
public:
    BigIntegerKaratsuba(int Base);
    BigIntegerKaratsuba(const std::vector<int> &vect, int Base);
    BigIntegerKaratsuba(const BigInteger &bigInt, int Base);
    BigIntegerKaratsuba(const std::string &str, int Base);
    
    virtual void Multiply(const BigIntegerKaratsuba &right_number);
    
    virtual BigIntegerKaratsuba& operator*(const BigIntegerKaratsuba &bigInt) const;

    virtual BigIntegerKaratsuba& operator*(int x) const;

};