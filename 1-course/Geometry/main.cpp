//*****************************************************************************
//                                                                            *
//  Lab Geometry, variant A (trapeze)                                         *
//  URL = "http://unicyb.kiev.ua/~tkarnaukh/Programming/Semestr2/Lab%202.pdf" *
//                                                                            *
//                                                                            *
//  Author: Lamzin Oleh, K12                                                  *
//  Date: 03.04.2015                                                          *
//                                                                            *
//*****************************************************************************


#include <iostream>
#include "point.h"
#include "line.h"
#include "figure.h"

using namespace std;

int main(){
	Point A,B,C,D;

	cout << "Lamzin Oleh, K12 - Lab Geometry.\n";
	cout << "Let's check: 4 points of the plane == trapeze?\n\n";

	cout << "Please, enter the coordinates of the points:";
	if (A.read() && B.read() && C.read() && D.read()){
		cout << "\n";
		A.write();
		B.write();
		C.write();
		D.write();

		Figure figure(A,B,C,D);
		cout << (figure.isTrapeze() ? "It is trapeze.\n" : "It is not trapeze.\n");
	}
	else{
		cout << "Sorry, input error! Try again.\n";
	}
	cout << "Good Bye!\n";

	return 0;
}
