#pragma once

class Expression{
public:
    virtual bool isNumber();
    virtual bool isOperation();
    virtual bool isOperationBinary();
    virtual bool isOperationUnary();
    virtual bool isBracketClose();
    virtual bool isBracketOpen();

    virtual int OperationPriority();
    virtual double getNumber();
    virtual double getResult(bool &error, double leftOperand, double rightOperand);
    virtual double getResult(bool &error, double Operand);

    virtual void printInfo() = 0;
};

class Number : public Expression{
protected:
    double numb;
public:
    Number(double _numb);

    double getNumber();
    bool isNumber();

    void printInfo();
};

class BracketOpen : public Expression{
public:
    bool isBracketOpen();

    void printInfo();
};

class BracketClose : public Expression{
public:
    bool isBracketClose();

    void printInfo();
};

class Addition : public Expression{
public:
    bool isOperation();
    bool isOperationBinary();
    
    int OperationPriority();
    double getResult(bool &error, double leftOperand, double rightOperand);

    void printInfo();
};

class Subtraction : public Expression{
public:
    bool isOperation();
    bool isOperationBinary();
    
    int OperationPriority();
    double getResult(bool &error, double leftOperand, double rightOperand);

    void printInfo();
};

class Multiplication : public Expression{
public:
    bool isOperation();
    bool isOperationBinary();
    
    int OperationPriority();
    double getResult(bool &error, double leftOperand, double rightOperand);

    void printInfo();
};

class Division : public Expression{
public:
    bool isOperation();
    bool isOperationBinary();
    
    int OperationPriority();
    double getResult(bool &error, double leftOperand, double rightOperand);

    void printInfo();
};

class Exponent : public Expression{
public:
    bool isOperation();
    bool isOperationUnary();
    
    int OperationPriority();
    double getResult(bool &error, double Operand);

    void printInfo();
};

class UnaryMinus : public Expression{
public:
    bool isOperation();
    bool isOperationUnary();
    
    int OperationPriority();
    double getResult(bool &error, double Operand);

    void printInfo();
};