/**********************************************************/
/*  File name: database.cpp                               */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 18:15:00 05/14/15                               */
/*                                                        */
/**********************************************************/
#pragma once
#include <string>
#include <fstream>
#include "Vector.h"

using namespace std;

class subject{
public:
    string name;
    int score100;
    int score5;

    subject();
    subject(string, int, int);

    void print(ostream &out);
};

class student{
public:
    string name;
    Vector<subject> result;
    int total_score;

    student();
    student(string, subject);

    void push(subject);
    void print(ostream &out);
};

class database{
public:
    Vector<student> data;
    bool full;

    database();
    void print(ostream &out);
    void print_top(ostream &out);
    void load(string file_name);
};
