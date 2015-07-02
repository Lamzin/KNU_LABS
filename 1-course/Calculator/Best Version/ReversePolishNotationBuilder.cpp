#include <string>
#include <vector>
#include "expression.h"
#include "ReversePolishNotationBuilder.h"

using namespace std;

ReversePolishNotationBuilder::ReversePolishNotationBuilder(vector<Expression*> _infixNotation){
    infixNotation = _infixNotation;

    error = !ValidNested() || TwoNumbersInARow();
    if (!error) Build();
}

vector<Expression*> ReversePolishNotationBuilder::getRPN(){
    return rpn;
}

bool ReversePolishNotationBuilder::getError(){
    return error;
}

bool ReversePolishNotationBuilder::ValidNested(){
    int nested = 0;
    for (int i = 0; i < infixNotation.size(); i++){
        if (infixNotation[i]->isBracketOpen()) nested++;
        else if (infixNotation[i]->isBracketClose()) nested--;
        if (nested < 0) return false; 
    }
    return nested == 0;
}

bool ReversePolishNotationBuilder::TwoNumbersInARow(){
    for (int i = 1; i < infixNotation.size(); i++)
        if (infixNotation[i]->isNumber() && infixNotation[i - 1]->isNumber()){
            return true;
        }
    return false;
}

void ReversePolishNotationBuilder::Build(){
    vector <Expression*> operation;

    for (int i = 0; i < infixNotation.size(); i++){
        if (infixNotation[i]->isBracketOpen()){
            operation.push_back(infixNotation[i]);
        }
        else if (infixNotation[i]->isBracketClose()){
            while(operation.size()){
                Expression* top;
                top = operation.back();
                operation.pop_back();
                if (top->isBracketOpen()){
                    break;
                }
                rpn.push_back(top);
            }
        }
        else if (infixNotation[i]->isOperation()){
            while(  operation.size() 
                    && 
                    operation.back()->OperationPriority() >= infixNotation[i]->OperationPriority())
            {
                rpn.push_back(operation.back());
                operation.pop_back();
            }
            operation.push_back(infixNotation[i]);
        }
        else if (infixNotation[i]->isNumber()){
            rpn.push_back(infixNotation[i]);
        }
    }   

    while(operation.size()){
        rpn.push_back(operation.back());
        operation.pop_back();
    }
}