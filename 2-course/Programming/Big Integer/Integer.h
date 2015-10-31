#pragma once


#include <vector>
#include <string>


#include "config.h"
#include "BigInteger.h"
#include "BigIntegerKaratsuba.h"


class Integer : public BigIntegerKaratsuba{
private:
    static bool cmp_equal(const Integer &left, const Integer &right);


public:
    Integer(ll Base);
    Integer(const vll &vect, ll Base);
    Integer(const BigInteger &bigInt, ll Base);
    Integer(const std::string &str, ll Base);

    virtual void Multiply(const Integer &right_number);

    virtual Integer& operator*(const Integer &bigInt) const;

    virtual Integer& operator*(ll x) const;

    

    std::pair<Integer, int> multiplicative_inverse() const;
    
    void virtual Divide(const Integer &right_number);
    virtual Integer& operator/(const Integer &right_number) const;
    virtual Integer& operator%(const Integer &right_number) const;
    virtual Integer& operator%(const int &right_number) const;
    virtual bool operator<(const Integer &right_number) const;
    virtual bool operator==(const Integer &right_number) const;
    virtual bool operator==(const ll &right_number) const;
};