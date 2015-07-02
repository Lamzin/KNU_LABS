#include <iostream>
#include <fstream>
#include <string>
#include "reader.h"

using namespace std;

Reader::Reader(){
    getline(cin, s);
    read = true;
    error = false;    
}

Reader::Reader(ifstream &_in){
    read = false;
    error = false;
    in = &_in;
    if (!error) Read();
}

Reader::Reader(string file){
    read = false;
    in = new ifstream(file);
    error = !in->is_open();
    if (!error) Read();
}

void Reader::Read(){
    if (error || read) return;

    string tmp;
    while(*in){
        getline(*in, tmp);
        if (*in){
            s += tmp;
        }
    }
    in->close();

    read = true;
}

string Reader::getStr(){
    return s;
}

bool Reader::getError(){
    return error;
}
