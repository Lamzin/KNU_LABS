/********************************************************************************/
/*  File name: main.cpp                                                         */
/*                                                                              */
/*  Lab Calculator, Variant A                                                   */
/*  URL = http://cyb.univ.kiev.ua/~tkarnaukh/Programming/Semestr2/Lab%205.pdf   */
/*                                                                              */
/*  Author: Lamzin Oleh                                                         */
/*          olehtomas@gmail.com                                                 */
/*                                                                              */
/*  Time: 06:19:46 05/21/15                                                     */
/*                                                                              */
/********************************************************************************/
//g++ -std=c++11 main.cpp calc.cpp 

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include "calc.h"

using namespace std;

void user();
void file(char *name);
void testing();
void print_help();
void print_info();

double my_abs(double x){
    return ((x) > 0.0) ? (x) : -(x);  
} 

int main(int argc, char **argv){
    print_info();

    if (argc < 2){
        cerr << "I don't what to do...";
        print_help();
        return 0;
    }

    if (strcmp(argv[1],"-h") == 0){
        print_help();
        return 0;
    }

    if (strcmp(argv[1],"-u") == 0){
        user();
        return 0;
    }

    if (strcmp(argv[1],"-f") == 0){
        if (argc < 3){
            cerr << "Invalid command, enter file name in command line.";
            return 0;
        }
        file(argv[2]);
        return 0;
    }

    if (strcmp(argv[1],"-t") == 0){
        testing();
        return 0;
    }

    cerr << "Invalid command.\n";
    return 0;
}

void user(){
    calc calculator;
    cout << "Enter expression: ";
    cout << "Result: " << calculator.calculate(cin) << endl;
}

void file(char *name){
    fstream file(name, ios::in);
    if (!file.is_open()){
        cerr << "File not open!\n";
        return;
    }

    calc calculator;
    cout << "Result: " << calculator.calculate(file) << endl;
    file.close();
}

void testing(){
    calc calculator;
    vector<pair<string, double> > tests;
    int AC_count = 0;

    tests.push_back(make_pair("-5.5-2*(12+56/12.32*12.2+exp(2.2))", -158.459117907));
    tests.push_back(make_pair("123/12.123*exp(-2/228+3/exp(1))", 30.3242060857));
    tests.push_back(make_pair("-exp(4)/exp(3)", -2.71828182459));
    tests.push_back(make_pair("1+2+3+4+5+6+7+8+9", 45));
    tests.push_back(make_pair("( -( -( -( -( -( -(-1) ) ) ) ) ) )", -1));
    tests.push_back(make_pair("exp( exp(1/2 * (3 - 2) ) )", 5.2003257647899));
    tests.push_back(make_pair("13+46*56+456/6-456/4978*12.123+15", 2678.889496183));
    tests.push_back(make_pair("-(435+21*(2/exp(3)))+16/exp(1/exp(3))", -421.8681449850));
    tests.push_back(make_pair("1*2*3*4*5*6*7*8*9*10", 3628800));
    tests.push_back(make_pair("2 + 2", 4));
    //https://www.wolframalpha.com/ - calculate it!

    cout << "Test result:\n";
    for (int i = 0; i<tests.size(); i++){
        double res = calculator.calculate(tests[i].first);
        cout << "    " << tests[i].first << endl;
        cout << "    Expected result: " << tests[i].second << endl;
        cout << "    Result: " << res << endl;
        cout << "    " << (my_abs(res - tests[i].second) < 0.000001 ? "OK" : "WA") << endl;       
        AC_count += my_abs(res - tests[i].second) < 0.000001;
    }
    cout << "AC: " << AC_count << " / " << tests.size() << endl;
}

void print_help(){
    cout << "\nHelp:\n"
         << "    -h: help\n" 
         << "    -u: user's expression\n"
         << "    -f file_name: expression in the file\n"
         << "    -t: auto testing\n";
}

void print_info(){
    cout << "Lamzin Oleh, K12 - Lab Calculator, variant A.\n\n"
         << "Task: realize expression calculator with constants.\n"
         << "    depending on the command-line arguments the program should:\n"
         << "        -u : to ask the user the expression and calculate its\n"
         << "        -f file_name: to calculate recorded in a file expression, user enters the file name\n"
         << "        -t : to execute automatic testing and display the result\n\n"

         << "BNF:\n"
         << "terminals:  '+', '-', '*', '/', '(', ')', 'x', 'exp' // x - double\n"
         << "nonterminals: <expression>, <term>, <factor>\n"
         << "products:\n"
         << "    <expression> → <expression> + <term>\n"
         << "    <expression> → <expression> - <term>\n"
         << "    <expression> → <term>\n"
         << "    <term> → <term> * <factor>\n"
         << "    <term> → <term> / <factor>\n"
         << "    <term> → exp(<factor>)\n"
         << "    <term> → <factor>\n"
         << "    <factor> → (<expression>)\n"
         << "    <factor> → x,\n"
         << "the initial nonterminal <expression>.\n\n\n";
         //URL ="https://en.wikipedia.org/wiki/Context-free_grammar"
}
