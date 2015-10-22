#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>


#include "BigInteger.h"
#include "BigIntegerKaratsuba.h"
#include "BigIntegerToomCook.h"


using namespace std;


BigInteger BigIntegerMultiplySpeedTestBase(const BigInteger &left, const BigInteger &right){
    double time_begin = clock();

    auto result = left * right;
    
    cerr << "\nBase:\n";
    cerr << left.Size() << " * " << right.Size();
    cerr << " -> time = " << ((double)clock() - time_begin) / CLOCKS_PER_SEC << endl;

    return result;
}


BigIntegerKaratsuba BigIntegerMultiplySpeedTestKaratsuba(const BigIntegerKaratsuba &left, const BigIntegerKaratsuba &right){
    double time_begin = clock();

    auto result = left;
    result.Multiply(right);

    cerr << "\nKaratsuba:\n";
    cerr << left.Size() << " * " << right.Size();
    cerr << " -> time = " << ((double) clock() - time_begin) / CLOCKS_PER_SEC << endl;
    
    return result;
}


BigIntegerToomCook BigIntegerMultiplySpeedTestToomCook(const BigIntegerToomCook &left, const BigIntegerToomCook &right){
    double time_begin = clock();

    auto result = left;
    result.Multiply(right);

    cerr << "\nToomCook:\n";
    cerr << left.Size() << " * " << right.Size();
    cerr << " -> time = " << ((double) clock() - time_begin) / CLOCKS_PER_SEC << endl;
 
    return result;
}

int main(){

    //string a, b;

    //cin >> a >> b;
    //a = string(100000, '1');
    //b = string(50000, '2');
    //a = "1234";
    //b = "2341";
    vector<int> a;
    vector<int> b;

    for (int i = 0; i < 100000; i++) a.push_back(456644);
    for (int i = 0; i < 50000; i++) b.push_back(45004);



    BigInteger A(a);
    BigInteger B(b);

    BigIntegerKaratsuba AA(a);
    BigIntegerKaratsuba BB(b);

    BigIntegerToomCook AAA(a);
    BigIntegerToomCook BBB(b);

    cerr << "Multilpy is coming...\n";

    auto resA = BigIntegerMultiplySpeedTestBase(A, B);
    auto resAA = BigIntegerMultiplySpeedTestKaratsuba(AA, BB);
    //auto resA = resAA;
    auto resAAA = BigIntegerMultiplySpeedTestToomCook(AAA, BBB);

    cout << "AA - A = " << (resAA - resA).Size() << endl;
    cout << "AAA - A = " << (resAAA - resA).Size() << endl;

    //cout << resA.ToString() << endl;
    //cout << resAA.ToString() << endl;
    //cout << resAAA.ToString() << endl;


    cin.get();
    cin.get();

}