#pragma once

#include "Vector.h"

template<class T>
void Sort(Vector<T> &arr){
    if (arr.size() == 0) return; 
    Sort(arr, 0, arr.size() - 1);
}

template<class T>
void Sort(Vector<T> &arr, int left, int right){
    
    int i = left, j = right;
    T tmp;
    T pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;      
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        Sort(arr, left, j);
    if (i < right)
        Sort(arr, i, right);
}
