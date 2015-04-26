#pragma once

class Point;

class Figure{
private:
	Point point[4];
	Point A, B, C, D;

public:
	Figure(Point &a, Point &b, Point &c, Point &d);

	bool isTrapeze();
};
