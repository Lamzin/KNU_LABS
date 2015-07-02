#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "expression.h"

using namespace std;

class Calculator{
protected:
    string str;
    vector <Expression*> rpn, infixNotation;
    double result;

    bool error, read, calculate;

    void BuildAll();
public:
    Calculator();
    Calculator(string s);

    void Read();
    void Read(string fileName);
    void Read(ifstream &_in);

    void Calculate();
    double getResult();
    bool getError();

    void print();
};