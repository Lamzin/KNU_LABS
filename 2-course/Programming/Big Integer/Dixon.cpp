#include "Dixon.h"
#include "myMath.h"

Dixon::Dixon(){
    //Base.push_back(Integer("2", BASE_INTEGER));
    //Base.push_back(Integer("3", BASE_INTEGER));
    //Base.push_back(Integer("5", BASE_INTEGER));
    //Base.push_back(Integer("7", BASE_INTEGER));
    //Base.push_back(Integer("11", BASE_INTEGER));
    //Base.push_back(Integer("13", BASE_INTEGER));
    //Base.push_back(Integer("17", BASE_INTEGER));
    //Base.push_back(Integer("19", BASE_INTEGER));
    //Base.push_back(Integer("23", BASE_INTEGER));
    //Base.push_back(Integer("29", BASE_INTEGER));
    //Base.push_back(Integer("31", BASE_INTEGER));
    //Base.push_back(Integer("37", BASE_INTEGER));
    //Base.push_back(Integer("41", BASE_INTEGER));
    //Base.push_back(Integer("43", BASE_INTEGER));
    //Base.push_back(Integer("47", BASE_INTEGER));
    
    //Base.push_back(Integer(53, BASE_INTEGER));
    //Base.push_back(Integer(59, BASE_INTEGER));
    //Base.push_back(Integer(61, BASE_INTEGER));
    //Base.push_back(Integer(67, BASE_INTEGER));
    //Base.push_back(Integer(71, BASE_INTEGER));
    //Base.push_back(Integer(73, BASE_INTEGER));
    //Base.push_back(Integer(79, BASE_INTEGER));
    //Base.push_back(Integer(83, BASE_INTEGER));
    //Base.push_back(Integer(89, BASE_INTEGER));
    //Base.push_back(Integer(97, BASE_INTEGER));
    //Base.push_back(Integer(101, BASE_INTEGER));
    //Base.push_back(Integer(103, BASE_INTEGER));
    //Base.push_back(Integer(107, BASE_INTEGER));
    //Base.push_back(Integer(109, BASE_INTEGER));
    //Base.push_back(Integer(113, BASE_INTEGER));   
    //Base.push_back(Integer(127, BASE_INTEGER));
    //Base.push_back(Integer(131, BASE_INTEGER));
    //Base.push_back(Integer(137, BASE_INTEGER));
    //Base.push_back(Integer(139, BASE_INTEGER));
    //Base.push_back(Integer(149, BASE_INTEGER));
    //Base.push_back(Integer(151, BASE_INTEGER));

    //n = Base.size();
}



//Integer Dixon::factor(Integer x){
//    auto xx = sqrt(x);
//    Integer one("1", BASE_INTEGER);
//
//    if (xx * xx == x) return xx;
//
//    for (; xx < x; xx.Add(one)){
//
//        auto d = gcd(xx, x);
//        if (one < d) return d;
//        auto xxx = (xx * xx) % x;
//
//        if (isSqrt(xxx)){
//            auto yyy = sqrt(xxx);
//            auto delta = xxx;
//            delta.Subtract(yyy);
//            delta = delta % x;
//            auto d = gcd(delta, x);
//
//            if (one < d) return d;
//        }
//    }
//
//    return x;
//}



Integer Dixon::factor(Integer x){
    auto sqrt_x = sqrt(x);
    if (sqrt_x * sqrt_x == x) return sqrt_x;
    
    Integer one("1", BASE_INTEGER), sqrt4_x = sqrt(sqrt_x), cur = sqrt4_x, cur_pow2 = cur * cur;

    while (cur < sqrt_x){

        auto d = gcd(cur_pow2, x);
        if (one < d) return d;
        auto xxx = (cur_pow2 * cur_pow2) % x;
    
        if (isSqrt(xxx)){
            auto yyy = sqrt(xxx);
            auto delta = xxx;
            delta.Subtract(yyy);
            delta = delta % x;
            auto d = gcd(delta, x);
    
            if (one < d) return d;
        }

        cur_pow2.Add(cur * 2);
        cur_pow2.Add(one);
        cur.Add(one);
    }
    
    return x;
}


std::vector<Integer> Dixon::factorization(Integer x){
    std::vector<Integer> answer, que;

    que.push_back(x);

    for (int i = 0; i < que.size(); i++){
        auto divisor = factor(que[i]);
        
        if (divisor == que[i]) answer.push_back(que[i]);
        else{
            que.push_back(divisor);
            que.push_back(que[i] / divisor);
        }
    }

    return answer;
}



//bool Dixon::isSmoothNumber(Integer x){
//    std::vector<int> pow(n, 0);
//    auto xx = x;
//
//    for (int i = 0; i < n; i++){
//        while (xx % Base[i] == 0){
//            pow[i]++;
//            xx = xx / Base[i];
//        }
//    }
//
//    if (xx == 1){
//        numbers.push_back(x);
//        powers.push_back(pow);
//        return true;
//    }
//    else return false;
//}



//Integer Dixon::factor(Integer x){
//    auto xx = sqrt(x);
//    Integer one("1", BASE_INTEGER);
//
//    if (xx * xx == x) return xx;
//
//    for (;xx < x; xx.Add(one)){
//
//        auto d = gcd(xx, x);
//        if (one < d) return d;
//        auto xxx = (xx * xx) % x;
//
//        if (isSqrt(xxx)){
//            auto yyy = sqrt(xxx);
//            auto delta = xxx;
//            delta.Subtract(yyy);
//            delta = delta % x;
//            auto d = gcd(delta, x);
//
//            if (one < d) return d;
//        }
//    }
//
//    return x;
//    
//    //Integer sqx = sqrt(x), one("1", BASE_INTEGER);
//    //if (sqx * sqx == x) return sqx;
//    //
//    //start:
//    //numbers.clear();
//    //for (; numbers.size() != Base.size() + 1 && sqx * sqx < x; sqx.Add(one))
//    //    isSmoothNumber((sqx * sqx) % x);
//
//    //auto xx = numbers[0];
//    //for (int i = 1; i < numbers.size(); i++){
//    //    xx.Multiply(numbers[i]);
//    //    xx = xx % x;
//    //}
//
//    //Integer yy("1", BASE_INTEGER);
//    //for (int i = 0; i < Base.size(); i++){
//    //    int cnt = 0;
//    //    for (int j = 0; j < powers.size(); j++) cnt += powers[i][j];
//    //    cnt /= 2;
//
//    //    for (int j = 0; j < cnt; j++) yy = yy * Base[i];
//    //    yy = yy % x;
//    //}
//
//    //auto delta = xx;
//    //delta.Subtract(yy);
//    //delta = delta % x;
//    ////if (delta == 0) goto start;
//
//    //return gcd(delta, x);
//}
//
//
//std::vector<Integer> Dixon::factorization(Integer x){
//    std::vector<Integer> answer;
//
//    auto divisor = factor(x);
//    if (divisor == x){
//        answer.push_back(x);
//    }
//    else{
//        Dixon left, right;
//        auto left_arr = left.factorization(divisor);
//        auto right_arr = left.factorization(x / divisor);
//            
//        for (auto it = left_arr.begin(); it != left_arr.end(); it++) answer.push_back(*it);
//        for (auto it = right_arr.begin(); it != right_arr.end(); it++) answer.push_back(*it);
//    }
//
//    return answer;
//}