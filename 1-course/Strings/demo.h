/**********************************************************/
/*  File name: demo.h                                     */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 00:41:46 04/26/15                               */
/*                                                        */
/**********************************************************/

#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace demo{

	void PrintTask(string ss);
	void PrintStr(char *name, string ss);

	void PrintStr(char *name, char *ss, int sz, int len);
	void PrintStrComment(string ss);

	void C_copy();
	void C_cat();
	void C_base_find(char *a, char *b);
	void C_find();
	void C_compare();
	void C_len();

	void CPP_init();
	void CPP_copy();
	void CPP_append();
	void CPP_base_find(string &a, string &b);
	void CPP_find();
	void CPP_compare();
	void CPP_len();
	void CPP_replace3();
}
