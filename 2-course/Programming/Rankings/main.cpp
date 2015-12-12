#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <map>

using namespace std;


#define what_is(x) cerr << #x << ": " << x << endl;


struct Point{
    double x, y;

    Point() : x(0.0f), y(0.0f){}
    Point(double xx, double yy) : x(xx), y(yy){}

    bool operator < (const Point &p) const{
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
};


struct Line{
    double a, b, c;

    Line() : a(0.0f), b(0.0f), c(0.0f) {}
    Line(double aa, double bb, double cc) : a(aa), b(bb), c(cc) {}
    Line(Point p, Point q){
        a = q.y - p.y;
        b = -q.x + p.x;
        c = - b * p.y - a * p.x;


        if (a < 0.0f) {
            a *= -1.0f;
            b *= -1.0f;
            c *= -1.0f;
        }
    }

};


double dist(Point p, Point q){
    return hypot(p.x - q.x, p.y - q.y);
}


double ABS(double X){
    if (X < 0.0f) return -X;
    return X;
}

double dist(Point p, Line l){
    return (l.a * p.x + l.b * p.y + l.c) / hypot(l.a, l.b);
}

Line paralelTo(Point p, Line l){
    Line ans;
    ans.a = l.a;
    ans.b = l.b;
    ans.c = - l.a * p.x - l.b * p.y;
    return ans;
}


Line perpendicularTo(Point p, Line l){
    Line ans;
    ans.a = l.b;
    ans.b = -l.a;
    ans.c = - ans.a * p.x - ans.b * p.y;
    return ans;
}


Point intersection(Line L1, Line L2){
    Point p;
    
    double d = L1.a * L2.b - L2.a * L1.b;
    if (d != 0.0f) {
        p.x = (L2.c * L1.b - L1.c * L2.b) / d;
        p.y = (L2.a * L1.c - L1.a * L2.c) / d;
    }
    return p;
}


vector<Point> input(){
    fstream in("input.txt", ios::in);
    int n, number;

    in >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        in >> number >> points[i].x >> points[i].y;
    }
    in.close();
    return points;
}


void output(vector<int> vect, string comment){
    fstream out("output.txt", ios::app);

    out << comment << endl;
    for (int i = 0; i < vect.size(); i++){
        out << i + 1 << " " << vect[i] << endl;
    }
    out.close();
}


void outputStatistic(int a, int b){
    fstream out("output.txt", ios::app);

    out << "Matching: " << a << " / " <<  b << endl; 

    out.close();
}


Point turn(Point p, double dx, double dy, double engel, double alpha){
    p.x -= dx;
    p.y -= dy;

    double newX = p.x * cos(engel) + p.y * sin(engel);
    double newY = p.x * sin(engel) - p.y * cos(engel);

    p.x = alpha * newX;
    p.y = newY;
    return p;
}


vector<int> ranking(vector<Point> points) {
    vector<int> rank(points.size());

    if (points.size() < 3) {
        for (int i = 0; i < points.size(); i++){
            rank[i] = i + 1;
        }
        return rank;
    }


    int numb1 = 0, numb2 = 1;
    double d = dist(points[0], points[1]);
    for (int i = 0; i < points.size(); i++){
        for (int j = i + 1; j < points.size(); j++){
            if (d < dist(points[i], points[j])){
                d     = dist(points[i], points[j]);
                numb1 = i;
                numb2 = j;
            }
        }
    }

    Line L(points[numb1], points[numb2]);


    int numbR = 0, numbQ = 0;
    double distR = 0.0f, distQ = 0.0f;
    for (int i = 0; i < points.size(); i++){
        double dd = dist(points[i], L);
        if (dd > distQ) {
            distQ = dd;
            numbQ = i;
        }
        else if (dd < distR){
            distR = dd;
            numbR = i;
        }
    }


    Line L1 = paralelTo(points[numbQ], L), 
         L2 = paralelTo(points[numbR], L);

    Line L3 = perpendicularTo(points[numb1], L1), 
         L4 = perpendicularTo(points[numb2], L1);

    Point P  = intersection(L1, L3),
          P2 = intersection(L1, L4),
          P3 = intersection(L4, L2),
          P4 = intersection(L3, L2);

    double a = ABS(distR) + ABS(distQ), b = d;
    double engel = atan2(L3.b, L3.a), alpha = a / b;
    double dx = P.x, dy = P.y;

    
    for (int i = 0; i < points.size(); i++){
       points[i] = turn(points[i], dx, dy, engel, alpha);
    }


    P = turn(P, dx, dy, engel, alpha);
    P2 = turn(P2, dx, dy, engel, alpha);
    P3 = turn(P3, dx, dy, engel, alpha);
    P4 = turn(P4, dx, dy, engel, alpha);


    Point centr;
    for (int i = 0; i < points.size(); i++) {
        centr.x += points[i].x;
        centr.y += points[i].y;
    }

    centr.x /= (double)points.size();
    centr.y /= (double)points.size();


    vector<pair<double, int> > vect;
    for (int i = 0; i < points.size(); i++){
        vect.push_back(make_pair(dist(points[i], centr), i));
    }


    sort(vect.begin(), vect.end());


    for (int i = 0; i < vect.size(); i++) {
        rank[vect[i].second] = i + 1; 
    }

    return rank;
}



vector<int> methodFirst(vector<Point> points){
    vector<int> rank(points.size());
    map<Point, pair<int, int> > mp;

    for (int i = 0; i < points.size(); i++) {
        mp[points[i]] = make_pair(i, -1);
    }

    int n = points.size();
    for (int i = n; points.size(); i--){
        vector<int> nrank = ranking(points);

        for (int j = 0; j < nrank.size(); j++) 
            if (nrank[j] == i){
                mp[points[j]].second = i;

                points.erase(points.begin() + j);

                break;
            }
    }


    for(map<Point, pair<int, int> >::iterator it = mp.begin(); it != mp.end(); it++) {
        rank[(*it).second.first] = (*it).second.second;
    }


    output(rank, "First method:");
    return rank;
}


vector<int> methodSecond(vector<Point> points){
    vector<int> rank = ranking(points);

    output(rank, "Second method:");
    return rank;
}


int main(){
    vector<Point> points = input();

    vector<int> rank1 = methodFirst(points);
    vector<int> rank2 = methodSecond(points);

    int cnt = 0;
    map<int, int> mp;
    for (int i = 0; i < rank1.size(); i++){
        cnt += rank1[i] == rank2[i];
        if (rank1[i] != rank2[i]){
            if (rank1[i] < 4) mp[i]++;
            if (rank2[i] < 4) mp[i]++;
        }
    }

    for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++){
        if ((*it).second == 2) cnt++;
    }

    outputStatistic(cnt, points.size());

    return 0;
}