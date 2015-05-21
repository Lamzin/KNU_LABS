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
    static bool isDelim(char ch);
    static bool isOperation(char ch);
    static bool isNum(char ch);
    static bool isUnary(char ch);
    static int priority(char op);

public:
    static vector<node> str_to_rpn(string s);
};

class calc{
private:
    bool isExpression(string s);
    bool inAlphabet(char ch); 
    bool inSpecialSymbols(char ch);
    string prepare(string s);

public:
    double calculate(string str);
    double calculate(istream &out);
};
