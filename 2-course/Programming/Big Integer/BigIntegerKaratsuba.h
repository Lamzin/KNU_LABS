#pragma once


#include <vector>
#include <string>


#include "config.h"
#include "BigInteger.h"


class BigIntegerKaratsuba : public BigInteger{
public:
    BigIntegerKaratsuba(ll Base);
    BigIntegerKaratsuba(const vll &vect, ll Base);
    BigIntegerKaratsuba(const BigInteger &bigInt, ll Base);
    BigIntegerKaratsuba(const std::string &str, ll Base);
    
    virtual void Multiply(const BigIntegerKaratsuba &right_number);
    
    virtual BigIntegerKaratsuba& operator*(const BigIntegerKaratsuba &bigInt) const;

    virtual BigIntegerKaratsuba& operator*(ll x) const;

};