#pragma once

#include <vector>
#include <string>

class BigInteger{
private:
    std::vector<int> number;
    int base, signum;


    void ToBigInteger(const std::string &str);
    bool absoluteCompareLesser(const BigInteger &right_number) const;


    void AddWithoutChecking(const BigInteger &right_number);
    void SubtractWithoutChecking(const BigInteger &right_number, bool compareResult);

public:
    BigInteger(int Base = 256);
    BigInteger(const BigInteger &bigInt, int Base = 256);
    BigInteger(const std::string &str, int Base = 256);
  
  
    int Size() const;
    int Base() const;
    int Signum() const;


    std::string ToString() const;
    const std::vector<int> &ToArray() const;


    void ShiftLeft(int n);
    void ShiftRight(int n);


    BigInteger& operator<<(int n) const;
    BigInteger& operator>>(int n) const;


    void Add(const BigInteger &right_number);
    void Subtract(const BigInteger &right_number);
    void virtual Multiply(const BigInteger &right_number);
    //void virtual Divide(const BigInteger &right_number);


    BigInteger& operator=(const BigInteger &bigInt);
    BigInteger& operator+(const BigInteger &bigInt) const;
    BigInteger& operator-(const BigInteger &bigInt) const;
    virtual BigInteger& operator*(const BigInteger &bigInt);
    //virtual BigInteger& operator/(const BigInteger &bigInt);

};