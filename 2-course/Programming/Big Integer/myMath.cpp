#include <time.h>

#include "myMath.h"


Integer sqrt(Integer n){
    Integer Left("0", BASE_INTEGER), Right = n, Middle("0", BASE_INTEGER);

    while (Left < Right){
        Middle = Left;
        Middle.Add(Right);
        Middle.DivideInt(2);

        if (Middle * Middle < n){
            Left = Middle;
            Left.Add(Integer("1", BASE_INTEGER));
        }
        else Right = Middle;
    }

    return Right;
}


bool isSqrt(Integer x){
    Integer sq = sqrt(x);
    return sq * sq == x;
}


Integer gcd(Integer a, Integer b){
    while (b.Size()){
        a = a % b;
        std::swap(a, b);
    }
    return a;
}


Integer rand(Integer n){
    srand(time(NULL));

    auto arr = n.ToArray();

    for (int i = 0; i < arr.size(); i++){
        ll next_value = (rand() * RAND_MAX + rand()) % BASE_INTEGER;
        arr[i] = next_value;
    }

    Integer res = Integer(arr, BASE_INTEGER) % n;
    if (res.Size() == 0) res.Add(Integer("1", BASE_INTEGER));

    return res;
}