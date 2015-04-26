#include <iostream>
#include <cmath>

#include "point.h"
#include "line.h"

using namespace std;

const double DBL_EPSILON = 0.000001f;

Line::Line(const Point& A, const Point& B){
    double dx = A.getX() - B.getX(),  dy = A.getY() - B.getY();
    this->a =  dy;
    this->b = -dx;
    this->c = -A.getX() * dy + A.getY() * dx;
    this->normalize();
}

void Line::normalize(){
    if (abs(this->a) < DBL_EPSILON && abs(this->b) < DBL_EPSILON){
            this->a = this->b = this->c = 0;
            this->state = false;
            return;
    }

    if (abs(this->a) < DBL_EPSILON){
            this->a = 0.0f;
            this->c /= this->b;
            this->b = 1.0f;
    }
    else if (abs(this->b) < DBL_EPSILON){
            this->b = 0.0f;
            this->c /= this->a;
            this->a = 1.0f;
    }
    else{
            this->a /= this->b;
            this->c /= this->b;
            this->b = 1.0f;
    }
    this->state = true;
}

void Line::write() const {
    cout << showpos << " " << this->a << "*x " << this->b << "*y " << this->c; 
}

bool Line::isParallel(const Line &line) const {
    return abs(this->a * line.b - this->b * line.a) < DBL_EPSILON;
}

double Line::distanceSigned(const Point &point) const {
    return (this->state) ? (this->a * point.getX() + this->b * point.getY() + this->c) / hypot(this->a, this->b) : 0.0f;
}

bool Line::isOneSide(const Point &A, const Point &B) const {
    double distA = this->distanceSigned(A), distB = this->distanceSigned(B);
    return distA > DBL_EPSILON && distB > DBL_EPSILON || distA < -DBL_EPSILON && distB < -DBL_EPSILON;
}

bool Line::isValid() const{
    return this->state;
}
