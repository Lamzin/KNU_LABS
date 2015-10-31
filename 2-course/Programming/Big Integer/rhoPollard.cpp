#pragma once

#include "rhoPollard.h"
#include "myMath.h"

rhoPollard::rhoPollard(){


}


//cormen2 - RUS - page 1007
Integer rhoPollard::factor(Integer n){
    
    Integer x = rand(n);
    Integer y = x, one("1", BASE_INTEGER);

    for (int i = 1, k = 2; i < 100; i++){
        x = x * x;
        x.Subtract(one);
        x = x % n;

        auto delta = y;
        y.Subtract(x);
        auto d = gcd(delta, n);

        if (one < d && d < n) return d;

        if (i == k){
            k *= 2;
            y = x;
        }
    }
            
    return n;
}


std::vector<Integer> rhoPollard::factorization(Integer x){
    
    std::vector<Integer> que, result;
    que.push_back(x);

    for (int i = 0; i < que.size(); i++){
        auto divisor = factor(que[i]);

        if (divisor < que[i]){
            que.push_back(divisor);
            que.push_back(que[i] / divisor);
        }
        else{
            result.push_back(que[i]);
        }
    }

    return result;
}