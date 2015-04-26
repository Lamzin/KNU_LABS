#pragma once

class Point{

private: 
    double x,y;

public: 
    Point(double x1=0, double y1=0);

    bool read();  //true if OK
    void write() const;

    double getX() const;
    double getY() const;

    bool operator ==(const Point&) const;
    bool operator >(const Point&) const; //lexicographically
    bool operator <(const Point&) const;
    bool operator >=(const Point&) const;
    bool operator <=(const Point&) const;

    const Point& operator ||(const Point&) const; // max
    const Point& operator &&(const Point&) const; // min
 };

double dist(const Point&, const Point&);
