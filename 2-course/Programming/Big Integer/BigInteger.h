#pragma once


#include <vector>
#include <string>


#include "config.h"


class BigInteger{
protected:
    vll number;
    ll base, signum;


    void ToBigInteger(const std::string &str);
    bool absoluteCompareLesser(const BigInteger &right_number) const;


    void AddWithoutChecking(const BigInteger &right_number);
    void SubtractWithoutChecking(const BigInteger &right_number, bool compareResult);

public:
    BigInteger(ll Base);
    BigInteger(const vll &vect, ll Base);
    BigInteger(const BigInteger &bigInt, ll Base);
    BigInteger(const std::string &str, ll Base);
  
  
    ll Size() const;
    ll Base() const;
    ll Signum() const;
    void SignumChange();
    void SignumAbs();


    std::string ToString() const;
    const vll &ToArray() const;


    void ShiftLeft(ll n);
    void ShiftRight(ll n);
    void ModuleByBase(ll n);

    BigInteger& operator<<(ll n) const;
    BigInteger& operator>>(ll n) const;


    void Add(const BigInteger &right_number);
    void Subtract(const BigInteger &right_number);
    virtual void Multiply(const BigInteger &right_number);
    //void virtual Divide(const BigInteger &right_number);


    BigInteger& operator=(const BigInteger &bigInt);
    BigInteger& operator+(const BigInteger &bigInt) const;
    BigInteger& operator-(const BigInteger &bigInt) const;
    virtual BigInteger& operator*(const BigInteger &bigInt) const;
    //virtual BigInteger& operator/(const BigInteger &bigInt);


    void MultiplyInt(ll x);
    void DivideInt(ll x);
    virtual BigInteger& operator*(ll x) const;
    virtual BigInteger& operator/(ll x) const;

};