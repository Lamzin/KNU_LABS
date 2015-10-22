#pragma once


#include <vector>
#include <string>
#include <complex>


#include "config.h"
#include "BigInteger.h"


class BigIntegerSchonhage : public BigInteger{
private:
    ll reverse_element(ll n, ll mod);
    void FastFourierTransform(vll &vect, bool invert);

public:
    BigIntegerSchonhage(ll Base);
    BigIntegerSchonhage(const vll &vect, ll Base);
    BigIntegerSchonhage(const BigInteger &bigInt, ll Base);
    BigIntegerSchonhage(const std::string &str, ll Base);

    virtual void Multiply(const BigIntegerSchonhage &right_number);

    virtual BigIntegerSchonhage & operator*(const BigIntegerSchonhage &bigInt) const;

    virtual BigIntegerSchonhage & operator*(ll x) const;

};