#include <string>
#include <vector>
#include <set>
#include "expression.h"
#include "parser.h"

using namespace std;

Parser::Parser(string _s){
    error = false;
    s = _s;
    Parse();
}

vector<Expression*> Parser::getExpression(){
    return expression;
}

bool Parser::getError(){
    return error;
}

void Parser::Parse(){
    vector <pair<string, Expression*> > strExpression;
    strExpression.push_back(make_pair("(", new BracketOpen()));
    strExpression.push_back(make_pair(")", new BracketClose()));
    strExpression.push_back(make_pair("+", new Addition()));
    strExpression.push_back(make_pair("-", new Subtraction()));
    strExpression.push_back(make_pair("*", new Multiplication()));
    strExpression.push_back(make_pair("/", new Division()));
    strExpression.push_back(make_pair("exp", new Exponent()));
    
    set <char> Delim;
    Delim.insert('\n');
    Delim.insert('\t');
    Delim.insert(' ');

    Expression* previousExpression = new BracketOpen();// NOT only the number!

    bool findOperation;
    for (int i = 0; i < s.length(); i++){
        findOperation = false;
        if (Delim.find(s[i]) != Delim.end()) continue;

        try{
            std::size_t err;
            double numb = stod(s.substr(i), &err);
            
            if (previousExpression->isNumber()){
                if (s[i] == '+'){
                    expression.push_back(new Addition());
                }
                else if (s[i] == '-'){
                    numb *= -1;
                    expression.push_back(new Subtraction());
                }
            }
            expression.push_back(new Number(numb));
            previousExpression = new Number(numb);
            i += err - 1;
            continue;
        }
        catch(...){
            
        }

        if (s[i] == '-' && (expression.size() == 0 || expression[expression.size()-1]->isBracketOpen())){
            expression.push_back(new UnaryMinus());
            continue;
        }

        for (int j = 0; j < strExpression.size(); j++){
            if (s.find(strExpression[j].first, i) == i){
                i += strExpression[j].first.length() - 1;
                expression.push_back(strExpression[j].second);
                previousExpression = strExpression[j].second;
                findOperation = true;
                break;
            }
        }
        if (findOperation) continue;

        error = true;
        break;
    }

}