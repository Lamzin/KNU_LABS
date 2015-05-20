/**********************************************************/
/*  File name: Vector.h                                   */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 18:15:00 05/14/15                               */
/*                                                        */
/**********************************************************/
#pragma once

#include <iostream>
using namespace std;

template <class T>
class Vector{
private:
    int array_size;
    T *array;

public:
    Vector(){
        array_size = 0;
        array = NULL;
    }
    Vector(int sz){
        array_size = sz;
        array = new T(array_size);
    }
    Vector(const Vector<T> &v){
        array_size = v.size();
        array = array_size ? new T[array_size] : NULL;
        for(int i = 0; i < array_size; i++) array[i] = v[i];
    }
    Vector & operator=(const Vector<T> &v){
        array_size = v.size();
        delete [] array;
        array = new T[array_size];
        for(int i = 0; i < array_size; i++) array[i] = v[i];
        return *this;
    }
    ~Vector(){
        delete[] array;
    }
    T& operator [](int index) const{
        return array[index];
    }
    int size() const{
        return array_size;
    }
    void push_back(T data){
        T *p = new T[array_size + 1];
        for (int i = 0; i < array_size; i++) p[i] =  array[i];
        p[array_size++] = data;
        delete [] array;
        array = p;
    }
};
