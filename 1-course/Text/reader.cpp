/**********************************************************/
/*  File name: reader.cpp                                 */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 18:15:00 05/14/15                               */
/*                                                        */
/**********************************************************/
#include <iostream>
#include <fstream>
#include "reader.h"
#include "database.h"
#include "Vector.h"

using namespace std;

int reader::students, reader::number_of_records, reader::total_score;
int reader::cur_score100, reader::cur_score5;
string reader::cur_name, reader::cur_subject;

bool reader::toint(string &s, int &n){
    std::size_t error;
    int var = std::stoi(s, &error);

    if (error != s.length()) return false;
    n = var;
    return true;
}

bool reader::is_own_title(string s){
    for (int i = 0; i<s.length(); i++){
        if (s[i] == ' ') continue;
        if (('a' > s[i] || s[i] > 'z') && ('A' > s[i] || s[i] > 'Z')) return false;
    }
    return true;
}

Vector<string> reader::split(string &str){
    Vector<string> vect_split;
    string tmp="";

    for (int j = 0; j < str.length(); j++){
        if (str[j] == ' ') continue;
        if (str[j] == ';'){
            vect_split.push_back(tmp);
            tmp = "";
        }
        else tmp += str[j];
    }
    vect_split.push_back(tmp);

    return vect_split;
}

bool reader::check_header(string &str){
    Vector<string> vect_split = split(str);
    if (vect_split.size() != 1) return false;

    return toint(vect_split[0], students);
}

bool reader::check_line(string &str){
    Vector<string> vect_split = split(str);
    if (vect_split.size() != 6) return false;

    int tmp_score5, tmp_score100;
    if (       toint(vect_split[4], tmp_score100) 
            && toint(vect_split[5], tmp_score5) 
            && is_own_title(vect_split[0] + " " + vect_split[1] + " " + vect_split[2]) 
            && is_own_title(vect_split[3])){

        cur_score100 = tmp_score100;
        cur_score5   = tmp_score5;
        cur_name = vect_split[0] + " " + vect_split[1] + " " + vect_split[2];
        cur_subject = vect_split[3];
        return true;
    }
    return false;
}

bool reader::check_footer(string &str){
    Vector<string> vect_split = split(str);
    if (vect_split.size() != 2) return false;

    int tmp_total, tmp_number;
    if (toint(vect_split[0], tmp_number) && toint(vect_split[1], tmp_total)){
        number_of_records = tmp_number;
        total_score   = tmp_total;
        return true;
    }
    return false;
}

bool reader::load_data(database *data, string input_file){//return true if load some student result to data
    fstream file(input_file, ios::in);
    if (!file.is_open()){
        cerr << "(ERROR) file opening. File name = \"" + input_file + "\"\n";
        return false;
    }

    string tmp_str;
    Vector<string> vect_str;
    while(file){
        getline(file, tmp_str);
        if (file) vect_str.push_back(tmp_str);
    }
    file.close();
    if (vect_str.size() < 2){
        cerr << "(ERROR) too short input file.\n";
        return false;
    }

    if (!check_header(vect_str[0])){
        cerr << "(ERROR) invalid header.\n";
        return false;
    }
    int summary_score100 = 0;
    for(int i = 1; i < vect_str.size() - 1; i++){
        if (check_line(vect_str[i])){
            int index = 0;
            while(index < data->data.size() && data->data[index].name != cur_name) index++;

            if (index == data->data.size())
                data->data.push_back(student(cur_name, subject(cur_subject, cur_score100, cur_score5)));
            else
                data->data[index].push(subject(cur_subject, cur_score100, cur_score5));

            summary_score100 += cur_score100;
        }
        else{
            cerr << "(ERROR) invalid data, line = " << i + 1 << ".\n";
            return i > 1;
        }
    }
    if (!check_footer(vect_str[vect_str.size() - 1])){
        cerr << "(ERROR) invalid footer.\n";
        return true;
    }

    if (data->data.size() != students || summary_score100 != total_score || number_of_records != vect_str.size() - 2)
        cerr << "(ERROR) invalid input.\n";
    else
        cerr << "(SUCCESS) correct input.\n";
    return true;
}
