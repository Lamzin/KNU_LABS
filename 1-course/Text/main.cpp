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

         << "input file BNF:\n"
         << "<students_count>\n"
         << "<first name>; <middle name>; <last name>; <subject>; <score 100> <score 5>\n"
         << "...\n"
         << "<first name>; <middle name>; <last name>; <subject>; <score 100> <score 5>\n"
         << "<number of records>; <total score>\n\n"

         << "output BNF:\n"
         << "(TOP)\n"
         << "(student) <name> (total_score) <total_score>\n"
         << "    (subj) <subject_name> (score100) <score100> (score5) <score5>\n"
         << "    ...\n"
         << "    (subj) <subject_name> (score100) <score100> (score5) <score5>\n"
         << "...\n"
         << "(student) <name> (total_score) <total_score>\n"
         << "    (subj) <subject_name> (score100) <score100> (score5) <score5>\n"
         << "    ...\n"
         << "    (subj) <subject_name> (score100) <score100> (score5) <score5>\n\n";
}
