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
    return ch == '.' || (ch >= '0' && ch <= '9');
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

vector<node> torpn::str_to_rpn(string s){
    vector<node> rpn;
    vector<char> op;
    double sign = 1.0f;

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
        string operand;
        if (i - 2 >= 0  && s[i - 2] == '(' 
            && 
            (s[i - 1] == '-' || s[i - 1] == '+')) operand += '-';
        while(i < s.length() && isNum(s[i])) operand += s[i++];
        --i;

        std::size_t error;
        double numb = std::stod(operand, &error);
        rpn.push_back(node(numb));
    }

    return rpn;
}

string calc::prepare(string s){
    s = "(" + s + ")";
    std::size_t found = s.find("exp");
    while(found != std::string::npos){
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
            ch == '(' || ch == ')' || ch == ' ' || 
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

double calc::calculate(istream &out){
    string s;
    getline(out, s);
    return calculate(s);
}

double calc::calculate(string str){
    string prep = prepare(str);
    if(!isExpression(prep)){
        cout << "(ERROR: Invalid expression) ";
        return 0.0f;
    }

    vector<node> rpn = torpn::str_to_rpn(prep); 
    vector<double> value_stack;

    for(int i = 0; i < rpn.size(); i++){
        if (rpn[i].isop){
            double result;
            if (rpn[i].operation == '#'){
                double operand = value_stack.back(); value_stack.pop_back();
                result = exp(operand);
            }
            else{
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
    return value_stack[0];
}
