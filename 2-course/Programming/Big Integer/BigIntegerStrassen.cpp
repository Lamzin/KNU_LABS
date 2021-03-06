//Knuth 1977 RUS volume 2 page 328
//Knuth 1997 ENG volume 2 page 305
//http://e-maxx.ru/algo/fft_multiply#5


#include <algorithm>
#include <vector>
#include <complex>
#include <math.h>


#include "BigInteger.h"
#include "BigIntegerStrassen.h"


BigIntegerStrassen::BigIntegerStrassen(ll Base) : BigInteger(Base){}


BigIntegerStrassen::BigIntegerStrassen(const vll &vect, ll Base) : BigInteger(vect, Base){}


BigIntegerStrassen::BigIntegerStrassen(const BigInteger &bigInt, ll Base) : BigInteger(bigInt, Base){}


BigIntegerStrassen::BigIntegerStrassen(const std::string &str, ll Base) : BigInteger(str, Base){}


void BigIntegerStrassen::FastFourierTransform(vcomp &vect, bool invert){
    //static long double PI = 3.14159265358979323846;
    static long double PI = 3.14159265358979323846264338327950288419716939937510L;
    
    ll n = (ll)vect.size();
    if (n == 1)  return;

    vcomp vect0(n / 2), vect1(n / 2);
    for (ll i = 0, j = 0; i<n; i += 2, ++j){
        vect0[j] = vect[i];
        vect1[j] = vect[i + 1];
    }

    FastFourierTransform(vect0, invert);
    FastFourierTransform(vect1, invert);

    long double ang = 2 * PI / n * (invert ? -1 : 1);
    std::complex<long double> w(1), wn(cos(ang), sin(ang));
    for (ll i = 0; i < n / 2; ++i) {
        vect[i] = vect0[i] + w * vect1[i];
        vect[i + n / 2] = vect0[i] - w * vect1[i];
        if (invert){
            vect[i] /= 2;
            vect[i + n / 2] /= 2;
        }
        w *= wn;
    }

}


void BigIntegerStrassen::Multiply(const BigIntegerStrassen &right_number){
    vcomp fa(number.begin(), number.end());
    auto right_arr = right_number.ToArray();
    vcomp fb(right_arr.begin(), right_arr.end());

    ll n = 1;
    while (n < std::max(number.size(), right_arr.size())) n <<= 1;
    n <<= 1;

    fa.resize(n);
    fb.resize(n);

    FastFourierTransform(fa, false);
    FastFourierTransform(fb, false);

    for (ll i = 0; i < n; i++) fa[i] *= fb[i];
    FastFourierTransform(fa, true);
    
    number.resize(n);
    ll carry = 0;
    for (ll i = 0; i < n; i++){
        carry += ll(fa[i].real() + 0.5);
        number[i] = carry % base;
        carry /= base;
    }

    while (number.size() && number.back() == 0) number.pop_back();

}


BigIntegerStrassen& BigIntegerStrassen::operator*(const BigIntegerStrassen &bigInt) const{
    BigIntegerStrassen *result = new BigIntegerStrassen(*this);
    result->Multiply(bigInt);
    return *result;
}