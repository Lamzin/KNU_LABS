/********************************************************************************/
/*  File name: main.cpp                                                         */
/*                                                                              */
/*  Lab Calculator, Variant A                                                   */
/*  URL = http://cyb.univ.kiev.ua/~tkarnaukh/Programming/Semestr2/Lab%205.pdf   */
/*                                                                              */
/*  Author: Lamzin Oleh                                                         */
/*          olehtomas@gmail.com                                                 */
/*                                                                              */
/*  Time: 01:06:11 06/21/15                                                     */
/*                                                                              */
/********************************************************************************/

//time g++ -std=c++11 main.cpp expression.cpp parser.cpp ReversePolishNotationBuilder.cpp reader.cpp calculator.cpp

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <math.h>
#include "calculator.h"

using namespace std;

#define ABS(x) ((x) > 0) ? (x) : -(x)

void User();
void File(char *name);
void Testing();
void PrintHelp();
void PrintInfo();

int main(int argc, char **argv){

    PrintInfo();

    if (argc < 2){
        cerr << "I don't what to do...";
        PrintHelp();
    }
    else if (strcmp(argv[1],"-h") == 0){
        PrintHelp();
    }
    else if (strcmp(argv[1],"-u") == 0){
        User();
    }
    else if (strcmp(argv[1],"-f") == 0){
        if (argc < 3)
            cerr << "Invalid command, enter file name in command line.";
        else
            File(argv[2]);
    }
    else if (strcmp(argv[1],"-t") == 0){
        Testing();
        return 0;
    }
    else
        cerr << "Invalid command.\n";
}

void PrintInfo(){
    cout << "Lamzin Oleh, K12 - Lab Calculator, variant A.\n\n"
         << "Task: realize expression calculator with constants.\n"
         << "    depending on the command-line arguments the program should:\n"
         << "        -u : to ask the user the expression and calculate its\n"
         << "        -f file_name: to calculate recorded in a file expression, user enters the file name\n"
         << "        -t : to execute automatic testing and display the result\n\n"

         << "BNF\n"
         << "    <digit> ::= '0' | '1' | ... | '9'\n"
         << "    <uint> ::= <digit> | <digit><uint>\n"
         << "    <int> ::= ['+' | '-']<uint>\n\n"
         << "    <double_normal> ::= <int>'.'<uint>\n"
         << "    <double_science> ::= <double_normal>'e'<int>\n"
         << "    <double> ::= <double_normal> | <double_science>\n\n"
         << "    <bin_op> ::= '+' | '-' | '*' | '/'\n"
         << "    <expression> ::= <double> | <expression><bin_op><expression> | 'exp('<expression>')' | '('<expression>')'\n\n"
         << "    <input> ::= <expression>\n"
         << "    <output> ::= <double>\n\n";
}

void PrintHelp(){
    cout << "\nHelp:\n"
         << "    -h: help\n" 
         << "    -u: user's expression\n"
         << "    -f file_name: expression in the file\n"
         << "    -t: auto testing\n";
}

void User(){
    Calculator calculator;
    calculator.Read();
    calculator.Calculate();

    double result = calculator.getResult();
    bool error = calculator.getError();

    if (error)
        cout << "$Result: #Error\n";
    else
        cout << "$Result: " << result << endl;
}

void File(char *name){
    Calculator calculator;
    calculator.Read(string(name));
    calculator.Calculate();

    double result = calculator.getResult();
    bool error = calculator.getError();

    if (error)
        cout << "$Result from file: #Error\n";
    else
        cout << "$Result from file: " << result << endl;
}

void Testing(){
    vector<pair<string, pair<double, bool> > > tests;

    //https://www.wolframalpha.com/ - calculate it!
    //WITHOUT ERROR
    tests.push_back(make_pair("-5.5-2*(12+56/12.32*12.2+exp(2.2))", make_pair(-158.459117907, false)));
    tests.push_back(make_pair("123/12.123*exp(-2/228+3/exp(1))", make_pair(30.3242060857, false)));
    tests.push_back(make_pair("-exp(4)/exp(3)", make_pair(-2.71828182459, false)));
    tests.push_back(make_pair("1+2+3+4+5+6+7+8+9", make_pair(45, false)));
    tests.push_back(make_pair("( -( -( -( -( -( -(-1) ) ) ) ) ) )", make_pair(-1, false)));
    tests.push_back(make_pair("exp( exp(1/2 * (3 - 2) ) )", make_pair(5.2003257647899, false)));
    tests.push_back(make_pair("13+46*56+456/6-456/4978*12.123+15", make_pair(2678.889496183, false)));
    tests.push_back(make_pair("-(435+21*(2/exp(3)))+16/exp(1/exp(3))", make_pair(-421.8681449850, false)));
    tests.push_back(make_pair("1*2*3*4*5*6*7*8*9*10", make_pair(3628800, false)));
    tests.push_back(make_pair("2 + 2", make_pair(4, false)));

    //WITH ERROR
    tests.push_back(make_pair("1/0.0", make_pair(0.0, true)));
    tests.push_back(make_pair(") 13.02e-2 + 45 (", make_pair(0.0, true)));
    tests.push_back(make_pair(" ) ( 2 + 2 ) ( ", make_pair(0.0, true)));
    tests.push_back(make_pair("1       2        3", make_pair(0.0, true)));
    tests.push_back(make_pair("1 *  *  *  2", make_pair(0.0, true)));
    tests.push_back(make_pair("1 2 +", make_pair(0.0, true)));
    tests.push_back(make_pair("15 / (120 / 4 - 30)", make_pair(0.0, true)));
    tests.push_back(make_pair("( -3 * ( -8 )", make_pair(0.0, true)));
    tests.push_back(make_pair("1515 (15)", make_pair(0.0, true)));
    tests.push_back(make_pair("5 - 5 ( 555 ) * 555", make_pair(0.0, true)));

    int accepted = 0;

    cout << "$Testing:\n";
    for (int i = 0; i < tests.size(); i++){
        Calculator calculator(tests[i].first);
        calculator.Calculate();

        double result = calculator.getResult();
        bool error = calculator.getError();

        cout.precision(9);
        cout << "#" << i + 1 << endl;
        cout << tests[i].first << endl;
        cout << "expected result:" << endl;
        cout << "    result = " << fixed << tests[i].second.first << endl;
        cout << "    error  = " << tests[i].second.second << endl;
        cout << "result:" << endl;
        cout << "        result = " << fixed << result << endl;
        cout << "        error  = " << error << endl;

        if (error == tests[i].second.second && ABS(result - tests[i].second.first) < 1e-6){
            accepted++;
            cout << "    $OK!" << endl;
        }
        else 
            cout << "    $WA!" << endl;
        cout << "________________________________________________________________________________\n\n";
    }

    cout << endl << "Total AC: " << accepted << " / "  << tests.size() << endl;
}