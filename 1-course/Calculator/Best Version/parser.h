#pragma once
#include <string>
#include <vector>
#include "expression.h"

using namespace std;

class Parser{
protected:
    string s;
    vector<Expression*> expression;
    bool error;

    void Parse();

public:
    Parser(string _s);

    vector<Expression*> getExpression();
    bool getError();
};