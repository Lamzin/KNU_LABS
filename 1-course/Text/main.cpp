/******************************************************************************/
/*  File name: main.cpp                                                       */
/*                                                                            */
/*  Lab Text, variant A                                                       */
/*  URL = http://cyb.univ.kiev.ua/~tkarnaukh/Programming/Semestr2/Lab%204.pdf */
/*                                                                            */
/*  Author: Lamzin Oleh                                                       */
/*          olehtomas@gmail.com                                               */
/*                                                                            */
/*  Time: 18:15:00 05/14/15                                                   */
/*                                                                            */
/******************************************************************************/
//g++ -std=c++11 main.cpp database.cpp reader.cpp

#include <iostream>
#include <fstream>
#include <string>
#include "database.h"
#include "reader.h"

using namespace std;

void print_info();

int main(int argc, char **argv){
    ofstream output_stream;
    string input_file, output_file, disp;
    bool result_to_display = true;

    print_info();

    if (argc > 1) input_file = argv[1];
    else{
        cout << "(ENTER) input file: ";
        getline(cin, input_file);
    }

    cout << "Display the results on the Screen, or write to the file?(-d/-f) ";
    getline(cin, disp);
    if (disp != "-d"){
        cout << "(ENTER) output file: ";
        getline(cin, output_file);
        output_stream.open(output_file, ios_base::out);
        result_to_display = false;
    }

    database data;
    data.load(input_file);
    data.print_top((result_to_display) ? cout : output_stream);

    return 0;
}

void print_info(){
    cout << "Lamzin Oleh, K12 - Lab Text variant A.\n\n"
         << "Task: File contains the results of student examinations assembly winter session.\n"
         << "      Find the best 5 students and their result.\n\n"

         << "BNF:\n"
         << "<digit>   ::= '0'|'1'|...|'9'\n"
         << "<number>  ::= ['+'|'-'']<digit>|<digit><number>\n"
         << "<char>    ::= 'a'|'b'|...|'z'|'A'|'B'|...|'Z'\n"
         << "<string>  ::= <char>|<char><string>\n\n"
         << "<input>   ::= <number>\\n{<string>';'<string>';'<string>';'<string>';'<number>';'<number>'\\n'}<number>';'<number>\n\n"
         << "<output>  ::= '(TOP)'\\n{<string>' '<number>\\n{<string>''<number>' '<number>\\n}}\n\n";
}
