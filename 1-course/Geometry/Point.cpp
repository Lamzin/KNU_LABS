#include <iostream>
#include <cmath>
#include "point.h"

using namespace std;

const double DBL_EPSILON = 0.000001f;

Point::Point(double x1, double y1){
    x = x1;
    y = y1;
}

bool Point::read(){
	double xx, yy;
	cout << "\nx = ";
	cin >> xx;
	cout << "y = ";
	cin >> yy;
	if (cin.good()){
		this->x = xx;
		this->y = yy;
		return true;
	}
	return false;
}

void Point::write() const {
	cout << "(" << this->x << ", " << this->y << ")\n";
}

double Point::getX() const {
	return this->x;
}

double Point::getY() const {
	return this->y;
}

bool Point::operator ==(const Point &p) const {
	return abs(this->getX() - p.getX()) < DBL_EPSILON && 
               abs(this->getY() - p.getY()) < DBL_EPSILON;
}
