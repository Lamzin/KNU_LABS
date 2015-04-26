/**********************************************************************************/
/*  File name: main.cpp                                                           */
/*                                                                                */
/*  Author: Lamzin Oleh                                                           */
/*          olehtomas@gmail.com                                                   */
/*                                                                                */
/*  Time: 00:41:46 04/26/15                                                       */
/*                                                                                */
/*  Lab: Lab#3 - Strings                                                          */
/*  URL = "http://unicyb.kiev.ua/~tkarnaukh/Programming/Semestr2/Lab%203.pdf"     */
/*                                                                                */
/**********************************************************************************/

#include "demo.h"

using namespace std;

void PrintCommandMenu();

int main(){
	cout << "Lab3: Strings\n";
	cout << "Author: Lamzin Oleh, K12";
	cout << "Demonstration using C strings and C++ strings.\n";

	int command = 0;
	
	while(command != -1){
		PrintCommandMenu();
		cout << "command = ";
		cin >> command;

		switch(command){
			case 2:
				demo::C_copy(); 		break;
			case 3:
				demo::C_cat();  		break;
			case 4:
				demo::C_find(); 		break;
			case 5:
				demo::C_compare();  		break;
			case 6:
				demo::C_len();  		break;
			case 7:
				demo::CPP_init();  		break;
			case 8:
				demo::CPP_copy();  		break;
			case 9:
				demo::CPP_append();  		break;
			case 10:
				demo::CPP_find();  		break;
			case 11:
				demo::CPP_compare();  		break;
			case 12:
				demo::CPP_len();  		break;
			case 13:
				demo::CPP_replace3(); 		break;

			case -1:
				cout << "Good buy!\n"; 		break;
			default:
				cout << "command not found\n";
		}
		cin.get();
		cin.get();
	}
}

void PrintCommandMenu(){
	cout << "Command Menu:\n";
	cout << "    -1 : exit\n";
	cout << "    2  : C_copy\n";
	cout << "    3  : C_cat\n";
	cout << "    4  : C_find\n";
	cout << "    5  : C_compare\n";
	cout << "    6  : C_len\n";
	cout << "    7  : CPP_init\n";
	cout << "    8  : CPP_copy\n";
	cout << "    9  : CPP_append\n";
	cout << "    10 : CPP_find\n";
	cout << "    11 : CPP_compare\n";
	cout << "    12 : CPP_len\n";
	cout << "    13 : CPP_replace3\n";
}
