//http://www.mit.edu/afs.new/athena/astaff/source/src-9.0/third/gmp/doc/multiplication
//http ://www.cryptalarm.it/ca/uploads/file/iterativeToomCookForVeryUnbalancedMultiplication.pdf


#include <algorithm>


#include "BigInteger.h"
#include "BigIntegerToomCook.h"


BigIntegerToomCook::BigIntegerToomCook(int Base) : BigInteger(Base){}


BigIntegerToomCook::BigIntegerToomCook(const std::vector<int> &vect, int Base) : BigInteger(vect, Base){}


BigIntegerToomCook::BigIntegerToomCook(const BigInteger &bigInt, int Base) : BigInteger(bigInt, Base){}


BigIntegerToomCook::BigIntegerToomCook(const std::string &str, int Base) : BigInteger(str, Base){}


void BigIntegerToomCook::Multiply(const BigIntegerToomCook &right_number){
    int n = std::max(this->Size(), right_number.Size()) / 3;
    int m = std::min(this->Size(), right_number.Size());

    if (m == 0){
        number.clear();
        signum = 1;
        return;
    }
    else if (this->Size() + right_number.Size() < 300 || m < 100){
        this->BigInteger::Multiply(right_number);
        return;
    }


    BigIntegerToomCook X2(BASE_TOOM_COOK), X1(BASE_TOOM_COOK), X0(BASE_TOOM_COOK), 
        Y2(BASE_TOOM_COOK), Y1(BASE_TOOM_COOK), Y0(BASE_TOOM_COOK), buffer(BASE_TOOM_COOK);
    buffer = *this;
    X0 = buffer;
    X0.ModuleByBase(n);
    buffer.ShiftRight(n);
    X1 = buffer;
    X1.ModuleByBase(n);
    X2 = buffer;
    X2.ShiftRight(n);

    buffer = right_number;
    Y0 = buffer;
    Y0.ModuleByBase(n);
    buffer.ShiftRight(n);
    Y1 = buffer;
    Y1.ModuleByBase(n);
    Y2 = buffer;
    Y2.ShiftRight(n);

    BigIntegerToomCook W0(BASE_TOOM_COOK), W1(BASE_TOOM_COOK), W2(BASE_TOOM_COOK), 
        W3(BASE_TOOM_COOK), W4(BASE_TOOM_COOK);

    //W0 = X0 * Y0;
    W0 = X0;
    W0.Multiply(Y0);


    //W1 = (X2 + X1 + X0) * (Y2 + Y1 + Y0);
    buffer = X2; buffer.Add(X1); buffer.Add(X0); W1 = buffer;
    buffer = Y2; buffer.Add(Y1); buffer.Add(Y0); W1.Multiply(buffer);
    //

    //W2 = (X2 * 4 + X1 * 2 + X0) * (Y2 * 4 + Y1 * 2 + Y0);
    buffer = X2; buffer.MultiplyInt(2);
    buffer.Add(X1); buffer.MultiplyInt(2);
    buffer.Add(X0); W2 = buffer;

    buffer = Y2; buffer.MultiplyInt(2);
    buffer.Add(Y1); buffer.MultiplyInt(2);
    buffer.Add(Y0); W2.Multiply(buffer);
    //

    //W3 = (X2 * 9 + X1 * 3 + X0) * (Y2 * 9 + Y1 * 3 + Y0);
    buffer = X2; buffer.MultiplyInt(3);
    buffer.Add(X1); buffer.MultiplyInt(3);
    buffer.Add(X0); W3 = buffer;

    buffer = Y2; buffer.MultiplyInt(3);
    buffer.Add(Y1); buffer.MultiplyInt(3);
    buffer.Add(Y0); W3.Multiply(buffer);
    //
    
    //W4 = (X2 * 16 + X1 * 4 + X0) * (Y2 * 16 + Y1 * 4 + Y0);
    buffer = X2; buffer.MultiplyInt(4);
    buffer.Add(X1); buffer.MultiplyInt(4);
    buffer.Add(X0); W4 = buffer;

    buffer = Y2; buffer.MultiplyInt(4);
    buffer.Add(Y1); buffer.MultiplyInt(4);
    buffer.Add(Y0); W4.Multiply(buffer);
    //


    //Solving linear system:
    //    0    0    0    0    1 | W0
    //    1    1    1    1    1 | W1
    //   16    8    4    2    1 | W2
    //   81   27    9    3    1 | W3
    //  256   64   16    4    1 | W4
    W4.Subtract(W3);
    W3.Subtract(W2);
    W2.Subtract(W1);
    W1.Subtract(W0);

    //    0    0    0    0    1 | W0
    //    1    1    1    1    0 | W1
    //   15    7    3    1    0 | W2
    //   65   19    5    1    0 | W3
    //  175   37    7    1    0 | W4
    W4.Subtract(W3);
    W3.Subtract(W2);
    W2.Subtract(W1);

    //    0    0    0    0    1 | W0
    //    1    1    1    1    0 | W1
    //   14    6    2    0    0 | W2
    //   50   12    2    0    0 | W3
    //  110   18    2    0    0 | W4
    W4.Subtract(W3);
    W3.Subtract(W2);
    W4.DivideInt(2);
    W3.DivideInt(2);
    W2.DivideInt(2);

    //    0    0    0    0    1 | W0
    //    1    1    1    1    0 | W1
    //    7    3    1    0    0 | W2
    //   18    3    0    0    0 | W3
    //   30    3    0    0    0 | W4
    W4.Subtract(W3);
    W4.DivideInt(3);
    W3.DivideInt(3);

    //    0    0    0    0    1 | W0
    //    1    1    1    1    0 | W1
    //    7    3    1    0    0 | W2
    //    6    1    0    0    0 | W3
    //    4    0    0    0    0 | W4
    W4.DivideInt(4);

    //    0    0    0    0    1 | W0
    //    1    1    1    1    0 | W1
    //    7    3    1    0    0 | W2
    //    6    1    0    0    0 | W3
    //    1    0    0    0    0 | W4
    
    
    //W3 ready:
    W3.Subtract(W4 * 6);

    //W2 ready:
    W2.Subtract(W4 * 7 + W3 * 3);

    //W1 ready:
    buffer = W4;
    buffer.Add(W3);
    buffer.Add(W2);
    W1.Subtract(buffer);

    //Normalize:
    signum *= right_number.Signum();

    //*this = (W4 << 4 * n) + (W3 << 3 * n) + (W2 << 2 * n) + (W1 << n) + W0;
    buffer = W4;
    buffer.ShiftLeft(n);
    buffer.Add(W3);
    buffer.ShiftLeft(n);
    buffer.Add(W2);
    buffer.ShiftLeft(n);
    buffer.Add(W1);
    buffer.ShiftLeft(n);
    buffer.Add(W0);
    *this = buffer;
}


BigIntegerToomCook& BigIntegerToomCook::operator*(const BigIntegerToomCook &bigInt) const{
    BigIntegerToomCook *result = new BigIntegerToomCook(*this);
    result->Multiply(bigInt);
    return *result;
}


BigIntegerToomCook& BigIntegerToomCook::operator*(int x) const{
    BigIntegerToomCook *result = new BigIntegerToomCook(*this);
    result->MultiplyInt(x);
    return *result;
}