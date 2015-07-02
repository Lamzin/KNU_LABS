#pragma once
#include <string>
#include <vector>
#include "expression.h"

using namespace std;

class ReversePolishNotationBuilder{
protected:
    vector<Expression*> rpn, infixNotation;
    bool error;

    void Build();
    bool ValidNested();
    bool TwoNumbersInARow();
public:
    ReversePolishNotationBuilder(vector<Expression*> _infixNotation);

    vector<Expression*> getRPN();
    bool getError();
};