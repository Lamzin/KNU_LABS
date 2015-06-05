/**********************************************************/
/*  File name: calc.h                                     */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 06:19:46 05/21/15                               */
/*                                                        */
/**********************************************************/
#pragma once

#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct node{
    bool isop;
    char operation;
    double number;

    node(char ch);
    node(double num);
};

class torpn{
private:
    bool isDelim(char ch);
    bool isOperation(char ch);
    bool isNum(char ch);
    bool isUnary(char ch);
    int priority(char op);

public:
    vector<node> str_to_rpn(string s, bool &err);
};

class calc{
private:
    bool isExpression(string s);
    bool inAlphabet(char ch); 
    bool inSpecialSymbols(char ch);
    string prepare(string s, bool &err);

public:
    double calculate(string str, bool &err);
    double calculate(istream &out, bool &err);
};
