//Knuth 1977 RUS volume 2 page 314
//Knuth 1997 ENG volume 2 page 295


#include <algorithm>
#include <vector>


#include "BigInteger.h"
#include "BigIntegerKaratsuba.h"


BigIntegerKaratsuba::BigIntegerKaratsuba(int Base) : BigInteger(Base){}


BigIntegerKaratsuba::BigIntegerKaratsuba(const std::vector<int> &vect, int Base) : BigInteger(vect, Base){}


BigIntegerKaratsuba::BigIntegerKaratsuba(const BigInteger &bigInt, int Base) : BigInteger(bigInt, Base){}


BigIntegerKaratsuba::BigIntegerKaratsuba(const std::string &str, int Base) : BigInteger(str, Base){}


void BigIntegerKaratsuba::Multiply(const BigIntegerKaratsuba &right_number){
    int n = std::max(this->Size(), right_number.Size()) / 2;
    int m = std::min(this->Size(), right_number.Size());

    if (m == 0){
        this->number.clear();
        return;
    }
    //if (this->Size() == 1 && right_number.Size() == 1){ // because RUNTIME if (n < 1)
    else if (this->Size() + right_number.Size() < 300 || m < 100){ // because RUNTIME if (n < 1)
        this->BigInteger::Multiply(right_number);
        return;
    }
    

    int signum_result = this->signum * right_number.Signum();

    //*this = (U1*V1 << n) + (U1*V1 << 2 * n) + (U0*V0 << n) + (U0*V0) + ((U1 - U0) * (V0 - V1) << n);
    //Let's execute next steps to save some memory
    BigIntegerKaratsuba U0 = *this, U1 = *this, V0 = right_number, V1 = right_number;
    U0.SignumAbs();
    U1.SignumAbs();
    V0.SignumAbs();
    V1.SignumAbs();
    
    U1.ShiftRight(n);
    U0.ModuleByBase(n);
    V1.ShiftRight(n);
    V0.ModuleByBase(n);

    BigIntegerKaratsuba U1V1, U0V0;
    U1V1 = U1;
    U1V1.Multiply(V1);//U1V1 = U1*V1
    U0V0 = U0;
    U0V0.Multiply(V0);//U0V0 = U0*V0

    U1.Subtract(U0);
    V0.Subtract(V1);
    U1.Multiply(V0);//delta = (U1 - U0) * (V0 - V1)

    *this = U1;
    this->ShiftLeft(n); // delta << n

    U1V1.ShiftLeft(n);
    this->Add(U1V1);
    U1V1.ShiftLeft(n);
    this->Add(U1V1);
    
    this->Add(U0V0);
    U0V0.ShiftLeft(n);
    this->Add(U0V0);

    this->signum = signum_result;

    while (number.size() && number.back() == 0) number.pop_back();
}


BigIntegerKaratsuba& BigIntegerKaratsuba::operator*(const BigIntegerKaratsuba &bigInt) const{
    BigIntegerKaratsuba *result = new BigIntegerKaratsuba(*this);
    result->Multiply(bigInt);
    return *result;
}


BigIntegerKaratsuba& BigIntegerKaratsuba::operator*(int x) const{
    BigIntegerKaratsuba *result = new BigIntegerKaratsuba(*this);
    result->MultiplyInt(x);
    return *result;
}