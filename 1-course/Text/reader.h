/**********************************************************/
/*  File name: reader.h                                   */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 18:15:00 05/14/15                               */
/*                                                        */
/**********************************************************/
#pragma once
#include <string>
#include "Vector.h"
#include "database.h"

using namespace std;

class reader{
private:
    static int students, number_of_records, total_score;
    static int cur_score5, cur_score100;
    static string cur_name, cur_subject;

    static Vector<string> split(string &s);
    static bool toint(string &s, int &n);
    static bool is_own_title(string s);

    static bool check_header(string &str);
    static bool check_line(string &str);
    static bool check_footer(string &str);

public:
    static bool load_data(database *data, string input_file);
};
