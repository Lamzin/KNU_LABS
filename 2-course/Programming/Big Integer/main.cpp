#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>


#include "BigInteger.h"
#include "BigIntegerKaratsuba.h"
#include "BigIntegerToomCook.h"
#include "BigIntegerStrassen.h"
#include "BigIntegerSchonhage.h"
#include "Integer.h"


#include "myMath.h"
#include "Dixon.h"
#include "rhoPollard.h"

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


BigIntegerStrassen BigIntegerMultiplySpeedSchongahe(const BigIntegerStrassen &left, const BigIntegerStrassen &right){
    double time_begin = clock();

    auto result = left;
    result.Multiply(right);

    cerr << "\nSchongahe:\n";
    cerr << left.Size() << " * " << right.Size();
    cerr << " -> time = " << ((double) clock() - time_begin) / CLOCKS_PER_SEC << endl;

    return result;
}


void print_factorization(Integer x, vector<Integer> fact){
    cerr << x.ToString() << ": ";
    for (int i = 0; i < fact.size(); i++) cerr << fact[i].ToString() << ", ";
    cerr << endl;
}

void dixon_method(){
    string a, b;
    a = "89755";//619 29 5
    a = "44564564564564564";
    //a = "44564564";
    //a = "445645654";
    Integer A(a, BASE_INTEGER);

    Dixon Dix;
    print_factorization(A, Dix.factorization(A));
}


void polard_method(){
    string a, b;
    a = "89755";//619 29 5
    a = "279841";//23*23*23*23
    a = "44564564564564564";

    Integer A(a, BASE_INTEGER);

    rhoPollard polard;
    print_factorization(A, polard.factorization(A));

}


int main(){

    //dixon_method();

    polard_method();


    //string a, b;
    //a = "1234";
    //b = "2341";
    //a = string(5000, '3');
    //b = string(5000, '2');
    //
    //vll a;
    //vll aa;
    //vll b;
    //vll bb;
    //int len_a = 100000;
    //int len_b = 100000;
    //
    //for (int i = 0; i < len_a; i++) a.push_back(664 * 32768 + 4654);
    //for (int i = 0; i < len_a; i++) aa.push_back(4654), aa.push_back(664);

    //for (int i = 0; i < len_b; i++) b.push_back(228 * 32768 + 1488);
    //for (int i = 0; i < len_b; i++) bb.push_back(1488), bb.push_back(228);


    //BigInteger A(a, BASE);
    //BigInteger B(b, BASE);

    //BigIntegerKaratsuba AA(a, BASE_KARATSUBA);
    //BigIntegerKaratsuba BB(b, BASE_KARATSUBA);

    //BigIntegerToomCook AAA(a, BASE_TOOM_COOK);
    //BigIntegerToomCook BBB(b, BASE_TOOM_COOK);

    //BigIntegerStrassen AAAA(aa, BASE_STRASSEN);
    //BigIntegerStrassen BBBB(bb, BASE_STRASSEN);

    //BigIntegerStrassen AAAAA(aa, BASE_SCHONGAHE);
    //BigIntegerStrassen BBBBB(bb, BASE_SCHONGAHE);


    //cerr << "Multilpy is coming...\n";

    ////auto resA = BigIntegerMultiplySpeedTestBase(A, B);
    //auto resAA = BigIntegerMultiplySpeedTestKaratsuba(AA, BB);
    ////auto resA = resAA;
    //auto resAAA = BigIntegerMultiplySpeedTestToomCook(AAA, BBB);
    //auto resAAAA = BigIntegerMultiplySpeedStrassen(AAAA, BBBB);
    //auto resAAAAA = BigIntegerMultiplySpeedSchongahe(AAAAA, BBBBB);



    //cout << "AA - A = " << resAA.ToString().compare(resA.ToString()) << endl;
    //cout << "AAA - A = " << resAAA.ToString().compare(resA.ToString()) << endl;
    //cout << "AAAA - A = " << resAAAA.ToString().compare(resA.ToString()) << endl;
    //cout << "AAAAA - A = " << resAAAAA.ToString().compare(resA.ToString()) << endl;
    /*cout << "AA - A = " << (resAA - resA).Size() << endl;
    cout << "AAA - A = " << (resAAA - resA).Size() << endl;
    cout << "AAAA - A = " << (resAAAA - resA).Size() << endl;
    cout << "AAAAA - A = " << (resAAAAA - resA).Size() << endl;*/


    //cout << resA.ToString() << endl << endl;
    //cout << resAA.ToString() << endl << endl;
    //cout << resAAA.ToString() << endl << endl;
    //cout << resAAAA.ToString() << endl << endl;
    //cout << resAAAAA.ToString() << endl << endl;


    cin.get();
    cin.get();

}