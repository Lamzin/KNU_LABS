#pragma once


#include <vector>
#include <string>


#include "config.h"


class BigInteger{
protected:
    std::vector<int> number;
    int base, signum;


    void ToBigInteger(const std::string &str);
    bool absoluteCompareLesser(const BigInteger &right_number) const;


    void AddWithoutChecking(const BigInteger &right_number);
    void SubtractWithoutChecking(const BigInteger &right_number, bool compareResult);

public:
    BigInteger(int Base);
    BigInteger(const std::vector<int> &vect, int Base);
    BigInteger(const BigInteger &bigInt, int Base);
    BigInteger(const std::string &str, int Base);
  
  
    int Size() const;
    int Base() const;
    int Signum() const;
    void SignumChange();
    void SignumAbs();


    std::string ToString() const;
    const std::vector<int> &ToArray() const;


    void ShiftLeft(int n);
    void ShiftRight(int n);
    void ModuleByBase(int n);

    BigInteger& operator<<(int n) const;
    BigInteger& operator>>(int n) const;


    void Add(const BigInteger &right_number);
    void Subtract(const BigInteger &right_number);
    virtual void Multiply(const BigInteger &right_number);
    //void virtual Divide(const BigInteger &right_number);


    BigInteger& operator=(const BigInteger &bigInt);
    BigInteger& operator+(const BigInteger &bigInt) const;
    BigInteger& operator-(const BigInteger &bigInt) const;
    virtual BigInteger& operator*(const BigInteger &bigInt) const;
    //virtual BigInteger& operator/(const BigInteger &bigInt);


    void MultiplyInt(int x);
    void DivideInt(int x);
    virtual BigInteger& operator*(int x) const;
    virtual BigInteger& operator/(int x) const;

};