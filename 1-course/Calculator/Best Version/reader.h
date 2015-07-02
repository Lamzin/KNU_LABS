#pragma once
#include <iostream>
#include <string>

using namespace std;

class Reader{
protected:
    ifstream *in;
    string s;
    bool error;
    bool read;

    void Read();
public:
    Reader();
    Reader(ifstream &_in);
    Reader(string file);

    string getStr();
    bool getError();
};