/**********************************************************/
/*  File name: calc.cpp                                   */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 06:19:46 05/21/15                               */
/*                                                        */
/**********************************************************/
#include <math.h>
#include <vector>
#include "calc.h"

#include <iostream>
using namespace std;

#define what_is(x) cerr << #x << " = " << (x) << endl;

node::node(char ch) : isop(true), operation(ch), number(0.0f){}
node::node(double num) : isop(false), operation('$'), number(num){}

bool torpn::isDelim(char ch){
    return ch == ' ';
}

bool torpn::isOperation(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '#';
}

bool torpn::isNum(char ch){
    return ch == '.' || ch == 'e' || (ch >= '0' && ch <= '9');
}

bool torpn::isUnary(char ch){
    return ch == '+' || ch == '-';
}

int torpn::priority(char op){
    return
        op == '#' ? 3 :
        op == '+' || op == '-' ? 1 :
        op == '*' || op == '/' ? 2 :
        -1;
}

vector<node> torpn::str_to_rpn(string s, bool &err){
    err = true;

    vector<node> rpn;
    vector<char> op;
    double sign = 1.0f;
    bool prev_numb = false;

    for(int i = 0; i < s.length(); i++){
        if (isDelim(s[i])) continue;
        if (s[i] == '('){
            op.push_back('(');
            continue;
        }
        if (s[i] == ')'){
            while(op.size()){
                char top = op.back(); op.pop_back();
                if (top == '(') break;
                rpn.push_back(node(top));
            }
            continue;
        }
        if (isUnary(s[i]) && s[i - 1] == '('){
            continue;
        }
        if (isOperation(s[i])){
            while(op.size() && priority(op.back()) >= priority(s[i])){
                rpn.push_back(node(op.back()));
                op.pop_back();
            }
            op.push_back(s[i]);
            continue;
        }

        std::size_t error;
        double numb = std::stod(s.substr(i), &error);
        if (    i - 2 >= 0 && 
                s[i - 2] == '(' && 
                s[i - 1] == '-') numb *= -1;

        i += error - 1;

        rpn.push_back(node(numb));
    }

    err = false;
    return rpn;
}

string calc::prepare(string s, bool &err){
    s = "(" + s + ")";
    std::size_t found = s.find("exp");
    while(found != std::string::npos){
        if (found + 3 >= s.length() || s[found + 3] != '(') err = true;
        s.replace(found, 3, "#");
        found = s.find("exp");
    }
    found = s.find(" ");
    while(found != std::string::npos){
        s.replace(found, 1, "");                
        found = s.find(" ");
    }
    found = s.find("-#");
    while(found != std::string::npos){
        s.replace(found, 2, "-1*#");                
        found = s.find("-#");
    }
    found = s.find("(-(");
    while(found != std::string::npos){
        s.replace(found, 3, "(0-(");                
        found = s.find("(-(");
    }

    return s;
}

bool calc::inAlphabet(char ch){
    return  ch == '+' || ch == '-' || 
            ch == '*' || ch == '/' || 
            ch == '#' || ch == '.' || 
            ch == '(' || ch == ')' || 
            ch == ' ' || ch == 'e' || ch == '\t' || 
            (ch >= '0' && ch <= '9');
}

bool calc::inSpecialSymbols(char ch){ // This symbol can*t to be near!
    return  ch == '+' || ch == '-' || 
            ch == '*' || ch == '/' || 
            ch == '.';
}

bool calc::isExpression(string s){
    int nested = 0;
    for (int i = 0; i<s.length(); i++){
        if (!inAlphabet(s[i])) return false;
        if (i && inSpecialSymbols(s[i]) && inSpecialSymbols(s[i - 1])) return false;
        if (i && s[i] == '#' && (s[i - 1] == '.' || s[i - 1] == '#')) return false;
        if (s[i] == '(') nested++;
        if (s[i] == ')') nested--;
        if (nested < 0) return false;
    }
    if (nested != 0) return false;
    return true;
}

double calc::calculate(istream &out, bool &err){
    string s;
    getline(out, s);
    return calculate(s, err);
}

double calc::calculate(string str, bool &err){
    err = false;

    string prep = prepare(str, err);
    if (err) return 0.0f;
    if(!isExpression(prep)){
        err = true;
        return 0.0f;
    }

    torpn torpn_obj;
    vector<node> rpn = torpn_obj.str_to_rpn(prep, err);
    if (err) return 0.0f;
    vector<double> value_stack;

    for(int i = 0; i < rpn.size(); i++){
        if (rpn[i].isop){
            double result;
            if (rpn[i].operation == '#'){// # == exp
                if (value_stack.size() < 1){
                    err = true;
                    return 0.0f;
                }
                double operand = value_stack.back(); value_stack.pop_back();
                result = exp(operand);
            }
            else{
                if (value_stack.size() < 2){
                    err = true;
                    return 0.0f;
                }
                double r = value_stack.back(); value_stack.pop_back();
                double l = value_stack.back(); value_stack.pop_back();
                switch(rpn[i].operation){
                    case '+':
                        result = l + r; break;
                    case '-':
                        result = l - r; break;
                    case '*':
                        result = l * r; break;
                    case '/':
                        result = l / r; break;
                }
            }
            value_stack.push_back(result);
        }
        else value_stack.push_back(rpn[i].number);
    }

    if (value_stack.size() != 1) return 0.0f;

    err = false;
    return value_stack[0];
}
