//Knuth 1977 RUS volume 2 page 314
//Knuth 1997 ENG volume 2 page 295


#include <algorithm>
#include <vector>


#include "BigInteger.h"
#include "BigIntegerSchonhage.h"


BigIntegerSchonhage::BigIntegerSchonhage(ll Base) : BigInteger(Base){}


BigIntegerSchonhage::BigIntegerSchonhage(const vll &vect, ll Base) : BigInteger(vect, Base){}


BigIntegerSchonhage::BigIntegerSchonhage(const BigInteger &bigInt, ll Base) : BigInteger(bigInt, Base){}


BigIntegerSchonhage::BigIntegerSchonhage(const std::string &str, ll Base) : BigInteger(str, Base){}


ll BigIntegerSchonhage::reverse_element(ll n, ll mod){
    ll res = 1, pow = 1;
    while (pow <= (mod - 2)){
        if (pow & (mod - 2)){
            res = res * n % mod;
        }
        n = (n * n) % mod;
        pow <<= 1;
    }

    return res;
}


void BigIntegerSchonhage::FastFourierTransform(vll &vect, bool invert){
    /*static const ll mod = 7340033; // 7 * (2**20) + 1 - simple
    static const ll root = 5;
    static const ll root_1 = 4404020;
    static const ll root_pw = 1 << 20;
    */

    static const ll mod = 1073741825; // 1 * (2**30) + 1 - simple
    static const ll root = 32768;
    static const ll root_1 = 1073709057;
    static const ll root_pw = 1 << 30;
    
    ll n = (ll) vect.size();

    for (ll i = 1, j = 0; i<n; ++i) {
        ll bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            std::swap(vect[i], vect[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {
        ll wlen = invert ? root_1 : root;

        for (ll i = len; i < root_pw; i <<= 1) wlen = ll(wlen * 1ll * wlen % mod);
        
        for (ll i = 0; i < n; i += len) {
            ll w = 1;
            for (ll j = 0; j<len / 2; ++j) {
                ll u = vect[i + j], v = ll(vect[i + j + len / 2] * 1ll * w % mod);
                vect[i + j] = u + v < mod ? u + v : u + v - mod;
                vect[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
                w = ll(w * 1ll * wlen % mod);
            }
        }

    }

    if (invert) {
        ll nrev = reverse_element(n, mod);
        for (ll i = 0; i<n; ++i) vect[i] = ll(vect[i] * 1ll * nrev % mod);
    }
}

void BigIntegerSchonhage::Multiply(const BigIntegerSchonhage &right_number){
    vll fa(number.begin(), number.end());
    auto right_arr = right_number.ToArray();
    vll fb(right_arr.begin(), right_arr.end());

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
        carry += fa[i];
        number[i] = carry % base;
        carry /= base;
    }

    while (number.size() && number.back() == 0) number.pop_back();
}


BigIntegerSchonhage& BigIntegerSchonhage::operator*(const BigIntegerSchonhage &bigInt) const{
    BigIntegerSchonhage *result = new BigIntegerSchonhage(*this);
    result->Multiply(bigInt);
    return *result;
}


BigIntegerSchonhage& BigIntegerSchonhage::operator*(ll x) const{
    BigIntegerSchonhage *result = new BigIntegerSchonhage(*this);
    result->MultiplyInt(x);
    return *result;
}