#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>


#include "BigInteger.h"
#include "BigIntegerKaratsuba.h"
#include "BigIntegerToomCook.h"
#include "BigIntegerStrassen.h"


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


BigIntegerStrassen BigIntegerMultiplySpeedStrassen(const BigIntegerStrassen &left, const BigIntegerStrassen &right){
    double time_begin = clock();

    auto result = left;
    result.Multiply(right);

    cerr << "\nStrassen:\n";
    cerr << left.Size() << " * " << right.Size();
    cerr << " -> time = " << ((double) clock() - time_begin) / CLOCKS_PER_SEC << endl;

    return result;
}

int main(){

    //string a, b;
    //a = "1234";
    //b = "2341";
    //a = string(5000, '1');
    //b = string(330, '2');
    //
    vector<int> a;
    vector<int> b;
    for (int i = 0; i < 500000; i++) a.push_back(456644);
    for (int i = 0; i < 300000; i++) b.push_back(45004);



    BigInteger A(a, BASE);
    BigInteger B(b, BASE);

    BigIntegerKaratsuba AA(a, BASE_KARATSUBA);
    BigIntegerKaratsuba BB(b, BASE_KARATSUBA);

    BigIntegerToomCook AAA(a, BASE_TOOM_COOK);
    BigIntegerToomCook BBB(b, BASE_TOOM_COOK);

    BigIntegerStrassen AAAA(a, BASE_STRASSEN);
    BigIntegerStrassen BBBB(b, BASE_STRASSEN);


    cerr << "Multilpy is coming...\n";

    //auto resA = BigIntegerMultiplySpeedTestBase(A, B);
    auto resAA = BigIntegerMultiplySpeedTestKaratsuba(AA, BB);
    auto resA = resAA;
    //auto resAAA = BigIntegerMultiplySpeedTestToomCook(AAA, BBB);
    auto resAAAA = BigIntegerMultiplySpeedStrassen(AAAA, BBBB);

   /* cout << "AA - A = " << resAA.ToString().compare(resA.ToString()) << endl;
    cout << "AAA - A = " << resAAA.ToString().compare(resA.ToString()) << endl;
    cout << "AAAA - A = " << resAAAA.ToString().compare(resA.ToString()) << endl;*/
    cout << "AA - A = " << (resAA - resA).Size() << endl;
    //cout << "AAA - A = " << (resAAA - resA).Size() << endl;
    cout << "AAAA - A = " << (resAAAA - resA).Size() << endl;


    //cout << resA.ToString() << endl << endl;
    //cout << resAA.ToString() << endl << endl;
    //cout << resAAA.ToString() << endl << endl;
    //cout << resAAAA.ToString() << endl << endl;


    cin.get();
    cin.get();

}