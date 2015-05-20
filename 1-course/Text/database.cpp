/**********************************************************/
/*  File name: database.cpp                               */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 18:15:00 05/14/15                               */
/*                                                        */
/**********************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
#include "database.h"
#include "reader.h"

using namespace std;

subject::subject() : name(""), score100(0), score5(0){}
subject::subject(string _name, int _score100, int _score5) 
        : 
        name(_name), 
        score100(_score100), 
        score5(_score5){}

void subject::print(ostream &out){
    out << "        (subj) " << name << " (score100) " << score100 << ", (score5) " << score5 << endl;
}

student::student(){
    name = "";
    total_score = 0;    
}

student::student(string _name, subject subj){
    name = _name;
    result.push_back(subj);
    total_score = subj.score100;
}

void student::push(subject subj){
    result.push_back(subj);
    total_score += subj.score100;
}

void student::print(ostream &out){
    out << "    (student) " << name << " (total_score) " << total_score << endl;
    for(int i = 0; i < result.size(); i++){
        result[i].print(out);
    }
}

database::database() : full(false){}

void database::load(string file_name){
    if (full){
        cerr << "Error! Data is full!" << endl;
        return;
    }
    full = reader::load_data(this, file_name);
}

void database::print(ostream &out){
    out << "(All results)" << endl;
    for (int i = 0; i<data.size(); i++){
        data[i].print(out);
    }
}

void database::print_top(ostream &out){
    if (!full) return;
    
    pair<int, int> *vpii = new pair<int, int>[data.size()];
    
    for(int i = 0; i<data.size(); i++){
        vpii[i] = make_pair(data[i].total_score, i);
    }   

    sort(vpii, vpii + data.size());
    out << "(TOP)" << endl;
    for (int i = 0; i<min(5, (int)data.size()); i++){
        data[vpii[data.size() - 1 - i].second].print(out);
    }
}
