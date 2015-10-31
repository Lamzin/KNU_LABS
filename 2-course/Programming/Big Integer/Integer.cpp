//Knuth 1977 RUS volume 2 page 314
//Knuth 1997 ENG volume 2 page 295


#include <algorithm>
#include <vector>

#include "config.h"
#include "BigInteger.h"
#include "BigIntegerKaratsuba.h"
#include "Integer.h"


Integer::Integer(ll Base) : BigIntegerKaratsuba(Base){}


Integer::Integer(const vll &vect, ll Base) : BigIntegerKaratsuba(vect, Base){}


Integer::Integer(const BigInteger &bigInt, ll Base) : BigIntegerKaratsuba(bigInt, Base){}


Integer::Integer(const std::string &str, ll Base) : BigIntegerKaratsuba(str, Base){}


void Integer::Multiply(const Integer &right_number){
    this->BigIntegerKaratsuba::Multiply(right_number);
}


Integer& Integer::operator*(const Integer &bigInt) const{
    Integer *result = new Integer(*this);
    result->Multiply(bigInt);
    return *result;
}


Integer& Integer::operator*(ll x) const{
    Integer *result = new Integer(*this);
    result->MultiplyInt(x);
    return *result;
}



bool Integer::cmp_equal(const Integer &left, const Integer &right){
    if (left.Size() != right.Size()) return false;

    auto left_arr = left.ToArray();
    auto right_arr = right.ToArray();

    for (int i = 0; i < left_arr.size(); i++){
        if (left_arr[i] != right_arr[i]) return false;
    }

    return true;
}



std::pair<Integer, int> Integer::multiplicative_inverse() const{
    // 1. b = 1 / x
    // 2. x0 = 1^(2*n)
    // 3. x <- 2*x - b*x*x
    //
    //https://en.wikipedia.org/wiki/Multiplicative_inverse
    //
    //


    if (this->Size() == 1){
        auto arr = this->ToArray();
        if (arr[0] == 1) return std::make_pair(*this, 0);
    }


    int precision = 4 * number.size(), count = 0;
    int sign = this->Signum();

    Integer two("2", this->base), b = *this;
    two.ShiftLeft(2 * precision);
    b.SignumAbs();
    b.ShiftLeft(2 * precision);

    Integer x("0", this->base);
    Integer xbuf1("0", this->base), xbuf2("0", this->base), x_new("1", this->base);
    x_new.ShiftLeft(precision);

    do{
        std::swap(x, x_new);
        xbuf1 = x * two;
        xbuf1.ShiftRight(2 * precision);
        xbuf2 = x * x * b;
        xbuf2.ShiftRight(4 * precision);
        x_new = xbuf1;
        x_new.Subtract(xbuf2);
    } while (!cmp_equal(x, x_new) && count++ < 100 * precision);
    

    if (sign == -1) x_new.SignumChange();
    return std::make_pair(x_new, 2 * precision);
}


void Integer::Divide(const Integer &right_number){
    auto right = right_number.multiplicative_inverse();

    right.first.Multiply(*this);
    right.first.ShiftRight(right.second);
    *this = right.first;

}


Integer& Integer::operator/(const Integer &right_number) const{
    Integer *result = new Integer(*this);
    result->Divide(right_number);
    return *result;
}


Integer& Integer::operator%(const Integer &right_number) const{
    Integer integer_part = *this / right_number;
    integer_part.Multiply(right_number);
    Integer *fractional_part = new Integer(*this);
    fractional_part->Subtract(integer_part);
    
    if (fractional_part->Signum() == -1) fractional_part->Add(right_number);
    return *fractional_part;
}


bool Integer::operator==(const Integer &right_number) const{
    Integer sub = *this;
    sub.Subtract(right_number);

    return sub.Size() == 0;
}


bool Integer::operator==(const ll &right_number) const{
    Integer right(std::to_string(right_number), BASE_INTEGER);
    return *this == right;
}


bool Integer::operator<(const Integer &right_number) const{
    auto res = right_number - *this;

    return res.Signum() == 1 && res.Size();
}


Integer& Integer::operator%(const int &right_number) const{
    Integer right(std::to_string(right_number), BASE_INTEGER);
    return *this % right;
}