#include <iostream>
#include <string>

#include "BigInteger.h"
#include "BigIntegerKaratsuba.h"


using namespace std;

int main(){

    string a, b;

    cin >> a >> b;

    BigInteger A(a);
    BigInteger B(b);

    auto tmp = A - B;
    cout << "TMP = " << tmp.ToString() << endl;


    BigIntegerKaratsuba AA(a);
    BigIntegerKaratsuba BB(b);


    cout << (A*B).ToString() << endl;
    cout << (AA*BB).ToString() << endl;


    cin.get();
    cin.get();

}