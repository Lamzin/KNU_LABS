/**********************************************************/
/*  File name: demo.cpp                                   */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 00:41:46 04/26/15                               */
/*                                                        */
/**********************************************************/


/*	Beautiful is better than ugly.
    Explicit is better than implicit.
    Simple is better than complex.
    Complex is better than complicated.
    Flat is better than nested.
    Sparse is better than dense.
    Readability counts.
    Special cases aren't special enough to break the rules.
    Although practicality beats purity.
    Errors should never pass silently.
    Unless explicitly silenced.
    In the face of ambiguity, refuse the temptation to guess.
    There should be one-- and preferably only one --obvious way to do it.
    Although that way may not be obvious at first unless you're Dutch.
    Now is better than never.
    Although never is often better than *right* now.
    If the implementation is hard to explain, it's a bad idea.
    If the implementation is easy to explain, it may be a good idea.
    Namespaces are one honking great idea -- let's do more of those!
*/

#include <string>
#include <math.h>
#include <stdio.h>
#include "string.h"
#include "demo.h" 

using namespace std;

namespace demo{
	void PrintTask(string ss){
		cout << "***********************************\n";
		cout << "Task:\n" << ss << "\n\n";
	}

	void PrintStr(char *name, string ss){
		cout << "(C++: " << name << ") ";
		cout << "\"" << ss << "\"; ";
		cout << "size = " << ss.length() << "; ";
		cout << "len = " << ss.length() << ";";
		cout << endl;
	}

	void PrintStr(char *name, char *ss, int sz, int len){
		cout << "(C: " << name << ") ";
		cout << "\"" << ss << "\"; ";
		cout << "size = " << sz << "; ";
		cout << "len = " << len << ";";
		cout << endl;
	}

	void PrintStrComment(string ss){
		cout << "Comment: " << ss << "\n";
	}

	void C_copy(){
		//Task2
		PrintTask("Demonstrate safe copying of C strings.");

		char a[] = "Beautiful is better than ugly.";
		char b[] = "Explicit is better than implicit.";
		string comment = "try copy b to a\n";

		PrintStr("a", a, sizeof(a), strlen(a));
		PrintStr("b", b, sizeof(b), strlen(b));
		PrintStrComment(comment);

		if (sizeof(a) > strlen(b)){
			strcpy(a, b);
			comment = "success!\n";
		}
		else comment = "fail: sizeof(a) <= strlen(b)\n";

		PrintStrComment("Result:");
		PrintStr("a", a, sizeof(a), strlen(a));
		PrintStr("b", b, sizeof(b), strlen(b));
		PrintStrComment(comment);
	}

	void C_cat(){
		//Task3
		PrintTask("Demonstrate safe concatenating of C strings.");

		char a[100] = "Simple is better than complex.";
		char b[] = " Complex is better than complicated.";
		string comment = "try a = a + b\n";

		PrintStr("a", a, sizeof(a), strlen(a));
		PrintStr("b", b, sizeof(b), strlen(b));
		PrintStrComment(comment);

		if (sizeof(a) > strlen(a) + strlen(b)){
			strcat(a, b);
			comment = "success!\n";
		}
		else comment = "fail: sizeof(a) <= strlen(a) + strlen(a)\n";

		PrintStrComment("Result:");
		PrintStr("a", a, sizeof(a), strlen(a));
		PrintStr("b", b, sizeof(b), strlen(b));
		PrintStrComment(comment);
	}

	void C_base_find(char *a, char *b){
		for (int i = 0, find = 0; i < (int)strlen(a) - (int)strlen(b); i++){
			find = 1;
			for (int j = 0; j < (int)strlen(b); j++)
				if (a[i + j] != b[j]){
					find = 0;
					break;
				}
			if (find) cout << i << " ";
		}
	}

	void C_find(){
		//task4
		PrintTask("Demonstrate search one C string in another C string.");
		PrintStrComment("search b in a, print index");

		char a[] = "Now is better than never.";
		char b[] = "better";
		PrintStr("a", a, sizeof(a), strlen(a));
		PrintStr("b", b, sizeof(b), strlen(b));
		PrintStrComment("result: ");
		C_base_find(a, b);
		PrintStrComment("\n");


		char aa[] = "abacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacaba";
		char bb[] = "aba";
		PrintStr("aa", aa, sizeof(aa), strlen(aa));
		PrintStr("bb", bb, sizeof(bb), strlen(bb));
		PrintStrComment("result: ");
		C_base_find(aa, bb);
		PrintStrComment("\n");

		char aaa[] = "If the implementation is hard to explain, it's a bad idea.";
		char bbb[] = "If the implementation is easy to explain, it may be a good idea.";
		PrintStr("aaa", aaa, sizeof(aaa), strlen(aaa));
		PrintStr("bbb", bbb, sizeof(bbb), strlen(bbb));
		PrintStrComment("result: ");
		C_base_find(aaa, bbb);
		PrintStrComment("\n");
	}

	void C_compare(){
		//Task5
		PrintTask("Demonstrate compare two C strings.");

		char a[1000];
		char b[1000];
		string comment;
		gets(a);
		PrintStrComment("a = ");
		gets(a);
		PrintStrComment("b = ");
		gets(b);

		PrintStr("a", a, sizeof(a), strlen(a));
		PrintStr("b", b, sizeof(b), strlen(b));

		int result = strcmp(a, b);
		if (result > 0) comment = "a > b";
		else if (result == 0) comment = "a == b";
		else comment = "a < b";

		PrintStrComment(comment);
	}

	void C_len(){
		//Task6
		PrintTask("Demonstrate length of C strings.");

		char a[] = "Flat is better than nested.";
		char b[] = "";
		string comment;

		PrintStr("a", a, sizeof(a), strlen(a));
		PrintStr("b", b, sizeof(b), strlen(b));
	}

	void CPP_init(){
		//Task7
		PrintTask("Demonstrate initialization of C++ string.");

		char a[] = "Sparse is better than dense.";
		string b(a);
		string comment = "(C++) b init (C) a\n";
		PrintStr("a", a, sizeof(a), strlen(a));
		PrintStr("b", b);
		PrintStrComment(comment);

		string x = "Readability counts.";
		string y(x);
		comment = "(C++) b init (C++) a";
		PrintStr("x", x);
		PrintStr("y", y);
		PrintStrComment(comment);
	}

	void CPP_copy(){
		//Task8
		PrintTask("Demonstrate copying C++ string to C++ string.");

		string a = "Special cases aren't special enough to break the rules.";
		string b = "Although practicality beats purity.";
		string comment = "(C++) b copy to (C++) a\n";

		PrintStr("a", a);
		PrintStr("b", b);
		PrintStrComment(comment);

		a = b;

		PrintStr("a", a);
		PrintStr("b", b);
		PrintStrComment("success!");
	}

	void CPP_append(){
		//Task9
		PrintTask("Demonstrate appending one C++ string to another C++ string.");

		string a = "Errors should never pass silently.";
		string b = "Unless explicitly silenced.";
		string comment = "(C++) b append to (C++) a\n";

		PrintStr("a", a);
		PrintStr("b", b);
		PrintStrComment(comment);

		a.append(b);

		PrintStr("a", a);
		PrintStr("b", b);
		PrintStrComment("success!");	
	}

	void CPP_base_find(string &a, string &b){
		for (int i = 0, find = 0; i < (int)a.length() - (int)b.length(); i++){
			find = 1;
			for (int j = 0; j < (int)b.length(); j++){
				if (a[i + j] != b[j]){
					find = 0;
					break;
				}
			}
			if (find) cout << i << " ";
		}
	}

	void CPP_find(){
		//Task10
		PrintTask("Demonstrate search one C++ string in another C++ string.");
		PrintStrComment("search b in a, print index");

		string a = "Now is better than never.";
		string b = "better";
		PrintStr("a", a);
		PrintStr("b", b);
		PrintStrComment("result: ");
		CPP_base_find(a, b);
		PrintStrComment("\n");

		string aa = "abacabadabacabaeabacabadabacabafabacabadabacabaeabacabadabacaba";
		string bb = "aba";
		PrintStr("aa", aa);
		PrintStr("bb", bb);
		PrintStrComment("result: ");
		CPP_base_find(aa, bb);
		PrintStrComment("\n");

		string aaa = "If the implementation is hard to explain, it's a bad idea.";
		string bbb = "If the implementation is easy to explain, it may be a good idea.";
		PrintStr("aaa", aaa);
		PrintStr("bbb", bbb);
		PrintStrComment("result: ");
		CPP_base_find(aaa, bbb);
		PrintStrComment("\n");
	}

	void CPP_compare(){
		//Task11
		PrintTask("Demonstrate comparing of two C++ strings.");

		string a, b, comment;
		getline(cin, a);
		PrintStrComment("a = ");
		getline(cin, a);

		PrintStrComment("b = ");
		getline(cin, b);

		PrintStr("a", a);
		PrintStr("b", b);

		int result = a.compare(b);
		if (result > 0) comment = "a > b";
		else if (result == 0) comment = "a == b";
		else comment = "a < b";

		PrintStrComment(comment);
	}

	void CPP_len(){
		//Task12
		PrintTask("Demonstrate length of C++ string.");

		string a = "In the face of ambiguity, refuse the temptation to guess.";
		string b = "There should be one-- and preferably only one --obvious way to do it.";
		string comment;

		PrintStr("a", a);
		PrintStr("b", b);
	}

	void CPP_replace3(){
		//Task13
		PrintTask("Demonstrate safe replacing s[3] to char.");

		string a = "Although that way may not be obvious at first unless you're Dutch.";
		string b = "xyz";
		char ch;

		PrintStrComment("char = ");
		cin >> ch;
		string tt; getline(cin, tt);

		PrintStrComment("try ch insert to a and to b");
		PrintStr("a", a);
		PrintStr("b", b);

		if (a.length() > 3){
			a[3] = ch;
			PrintStrComment("a : success!");
		} else PrintStrComment("a : fail: a.length() <= 3");

		if (b.length() > 3){
			b[3] = ch;
			PrintStrComment("b : success!");
		} else PrintStrComment("b : fail: b.length() <= 3");

		PrintStr("a", a);
		PrintStr("b", b);
	}
}
