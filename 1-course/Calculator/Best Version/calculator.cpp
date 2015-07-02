#include <vector>
#include <string>
#include <iostream>

#include "expression.h"
#include "reader.h"
#include "parser.h"
#include "ReversePolishNotationBuilder.h"
#include "calculator.h"

Calculator::Calculator(){
    error = false;
    read = false;
    calculate = false;
    result = 0.0f;
}

Calculator::Calculator(string s){
    str = s;

    error = false;
    read = true;
    calculate = false;
    result = 0.0f;
}

void Calculator::Read(){
    if (read) return;
    
    Reader reader;
    str = reader.getStr();
    error = reader.getError();
    read = true;
}

void Calculator::Read(string fileName){
    if (read) return;
    
    Reader reader(fileName);
    str = reader.getStr();
    error = reader.getError();
    read = true;
}

void Calculator::Read(ifstream &_in){
    if (read) return;

    Reader reader(_in);
    str = reader.getStr();
    error = reader.getError();
    read = true;
}

double Calculator::getResult(){
    return result;
}

bool Calculator::getError(){
    return error;    
}

#define what_is(x) cerr << #x << ": " << x << endl;
void Calculator::print(){
    what_is(str);
    what_is(result);

    cerr << "infix: ";
    for (int i = 0; i < infixNotation.size(); i++){
        infixNotation[i]->printInfo();
    }

    cerr << "\nrpn: ";
    for (int i = 0; i < rpn.size(); i++){
        rpn[i]->printInfo();
    }
    cerr << endl;

    what_is(error);
    what_is(read);
    what_is(calculate);
}

void Calculator::BuildAll(){
    if (error) return;

    Parser parser(str);
    infixNotation = parser.getExpression();
    error |= parser.getError();
    if (error) return;

    ReversePolishNotationBuilder rpnBuilder(infixNotation);
    rpn = rpnBuilder.getRPN();
    error |= rpnBuilder.getError();
}

void Calculator::Calculate(){
    BuildAll();
    if (error){
        calculate = true;
        return;
    }

    vector <double> valueStack;

    for (int i = 0; i < rpn.size() && !error; i++){
        if (rpn[i]->isOperation()){
            if (rpn[i]->isOperationBinary()){
                if (valueStack.size() < 2){
                    error = true;
                }
                else{
                    double rightOperand = valueStack.back();
                    valueStack.pop_back();
                    double leftOperand = valueStack.back();
                    valueStack.pop_back();

                    double res = rpn[i]->getResult(error, leftOperand, rightOperand);
                    if (!error){
                        valueStack.push_back(res);                                        
                    }
                }
            }
            else if (rpn[i]->isOperationUnary()){ 
                if (valueStack.size() < 1){
                    error = true;
                }
                else{
                    double Operand = valueStack.back();
                    valueStack.pop_back();

                    double res = rpn[i]->getResult(error, Operand);
                    if (!error){
                        valueStack.push_back(res);                                        
                    }
                }
            }
        }
        else if (rpn[i]->isNumber()){
            valueStack.push_back(rpn[i]->getNumber());
        }
    }

    if (!error && valueStack.size() == 1){
        this->result = valueStack[0];
    }
    else {
        error = true;
    }
}