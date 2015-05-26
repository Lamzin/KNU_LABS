#pragma once

template<class T>
struct Pair{
    T first, second;

    Pair(T f, T s) : first(f), second(s){}
    Pair(const Pair &p) : first(p.first), second(p.second){}
    Pair(){}

    bool operator <(const Pair &p){
        if (first != p.first) return first < p.first;
        return second < p.second;
    }
    
    bool operator >(const Pair &p){
        if (first != p.first) return first > p.first;
        return second > p.second;
    }

    Pair & operator = (const Pair &p){
        first = p.first;
        second = p.second;
        return *this;
    }
};
