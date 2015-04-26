#include "point.h"
#include "line.h"
#include "figure.h"

Figure::Figure(Point &a, Point &b, Point &c, Point &d) : A(a), B(b), C(c), D(d){}

bool Figure::isTrapeze(){
	Line 	AB(A, B),
                AC(A, C),
                AD(A, D),
                BC(B, C),
                BD(B, D),
                CD(C, D);

	if (!AB.isValid() || 
		!AC.isValid() || 
		!AD.isValid() || 
		!BC.isValid() || 
		!BD.isValid() || 
		!CD.isValid()) return false; 

	return 	(AB.isParallel(CD) && !BC.isParallel(AD) 
			||
                        BC.isParallel(AD) && !AB.isParallel(CD))
                        && !AC.isOneSide(this->B, this->D) 
			&& !BD.isOneSide(this->A, this->C);
}
