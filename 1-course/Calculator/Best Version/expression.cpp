#include <math.h>
#include <iostream>
#include <algorithm>
#include "expression.h"

using namespace std;

bool Expression::isNumber(){
    return false;
}

bool Expression::isOperation(){
    return false;
}

bool Expression::isOperationBinary(){
    return false;
}

bool Expression::isOperationUnary(){
    return false;
}

bool Expression::isBracketClose(){
    return false;
}

bool Expression::isBracketOpen(){
    return false;
}

int Expression::OperationPriority(){
    return 0;
}

double Expression::getNumber(){
    return 0.0f;
}

double Expression::getResult(bool &error, double leftOperand, double rightOperand){
    error = false;
    return 0.0f;
}

double Expression::getResult(bool &error, double Operand){
    error = false;
    return 0.0f;
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

Number::Number(double _numb) : numb(_numb){}

double Number::getNumber(){
    return numb;
}

bool Number::isNumber(){
    return true;
}

void Number::printInfo(){
    cerr << "\"" << numb << "\" ";
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool BracketOpen::isBracketOpen(){
    return true;
}

void BracketOpen::printInfo(){
    cerr << "\"" << "(" << "\" ";
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool BracketClose::isBracketClose(){
    return true;
}

void BracketClose::printInfo(){
    cerr << "\"" << ")" << "\" ";
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool Addition::isOperation(){
    return true;
}

bool Addition::isOperationBinary(){
    return true;
}

int Addition::OperationPriority(){
    return 1;
}

double Addition::getResult(bool &error, double leftOperand, double rightOperand){
    error = false;
    return leftOperand + rightOperand;
}

void Addition::printInfo(){
    cerr << "\"" << "+" << "\" ";
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool Subtraction::isOperation(){
    return true;
}

bool Subtraction::isOperationBinary(){
    return true;
}

int Subtraction::OperationPriority(){
    return 1;
}

double Subtraction::getResult(bool &error, double leftOperand, double rightOperand){
    error = false;
    return leftOperand - rightOperand;
}

void Subtraction::printInfo(){
    cerr << "\"" << "-" << "\" ";
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool Multiplication::isOperation(){
    return true;
}

bool Multiplication::isOperationBinary(){
    return true;
}

int Multiplication::OperationPriority(){
    return 2;
}

double Multiplication::getResult(bool &error, double leftOperand, double rightOperand){
    error = false;
    return leftOperand * rightOperand;
}

void Multiplication::printInfo(){
    cerr << "\"" << "*" << "\" ";
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool Division::isOperation(){
    return true;
}

bool Division::isOperationBinary(){
    return true;
}

int Division::OperationPriority(){
    return 2;
}

double Division::getResult(bool &error, double leftOperand, double rightOperand){
    if (std::abs(rightOperand) < 1e-9){
        error = true;
        return 0.0f;
    }
    error = false;
    return leftOperand / rightOperand;
}

void Division::printInfo(){
    cerr << "\"" << "/" << "\" ";
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool Exponent::isOperation(){
    return true;
}

bool Exponent::isOperationUnary(){
    return true;
}

int Exponent::OperationPriority(){
    return 3;
}

double Exponent::getResult(bool &error, double Operand){
    error = false;
    return exp(Operand);
}

void Exponent::printInfo(){
    cerr << "\"" << "exp" << "\" ";
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

bool UnaryMinus::isOperation(){
    return true;
}

bool UnaryMinus::isOperationUnary(){
    return true;
}

int UnaryMinus::OperationPriority(){
    return 1;
}

double UnaryMinus::getResult(bool &error, double Operand){
    return -Operand;
}

void UnaryMinus::printInfo(){
    cerr << "\"" << "-" << "\" ";
}
