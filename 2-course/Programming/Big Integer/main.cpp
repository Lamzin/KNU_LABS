#include <iostream>
#include <string>

#include "BigInteger.h"


using namespace std;

int main(){

    string a, b;

    cin >> a >> b;

    BigInteger A(a);
    BigInteger B(b);
    A.Subtract(B);
    //BigInteger C = A - B;


    cout << endl << A.ToString() << endl;

    cin.get();
    cin.get();


}