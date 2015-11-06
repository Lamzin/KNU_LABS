#include <algorithm>


#include "BigInteger.h"


BigInteger::BigInteger(ll Base) : base(Base), signum(1){}


BigInteger::BigInteger(const vll &vect, ll Base){
    base = Base;
    signum = 1;
    number = vect;

    for (auto it = number.begin(); it != number.end(); it++) *it %= base;
    while (number.size() && number.back() == 0) number.pop_back();
}


BigInteger::BigInteger(const BigInteger &bigInt, ll Base){
    base = Base;
    if (Base != bigInt.Base()) ToBigInteger(bigInt.ToString());
    else{
        signum = bigInt.Signum();
        number = vll(bigInt.ToArray().begin(), bigInt.ToArray().end());
    }
}


BigInteger::BigInteger(const std::string &str, ll Base){
    base = Base;
    ToBigInteger(str);
}


void BigInteger::ToBigInteger(const std::string &str){
    if (str.length() == 0){
        signum = 1;
        return;
    }
    
    signum = (str[0] == '-') ? -1 : 1;

    std::string buffer = str.substr(str[0] == '+' || str[0] == '-'), buffer_tmp;

    while (buffer.length()){
        buffer_tmp.clear();
    
        ll current = 0, first = 0;
        for (ll i = 0; i < buffer.length(); i++){
            current = current * 10 + buffer[i] - '0';
            if (!first && current >= base) first = 1;
            if (first){
                buffer_tmp += current / base + '0';
                current %= base;
            }
        }

        number.push_back(current);
        buffer.swap(buffer_tmp);
    }

    while (number.size() && number.back() == 0) number.pop_back();
}


const vll &BigInteger::ToArray() const {
    return number;
}


ll BigInteger::Size() const{
    return number.size();
}


ll BigInteger::Base() const{
    return base;
}


ll BigInteger::Signum() const{
    return signum;
}


void BigInteger::SignumChange(){
    signum *= -1;
}


void BigInteger::SignumAbs(){
    signum = 1;
}


std::string BigInteger::ToString() const{
    if (number.size() == 0) return "0";
    
    std::string result;
    vll buffer = number, buffer_tmp;

    std::reverse(buffer.begin(), buffer.end());
    while (buffer.size()){
        buffer_tmp.clear();

        ll current = 0, first = 0;
        for (ll i = 0; i < buffer.size(); i++){
            current = current * base + buffer[i];
            if (!first && current >= 10) first = 1;
            if (first){
                buffer_tmp.push_back(current / 10);
                current %= 10;
            }
        }

        result += current + '0';
        buffer.swap(buffer_tmp);
    }

    if (result.size() == 0) result += '0';
    if (signum == -1) result += '-';

    std::reverse(result.begin(), result.end());
    return result;
}


void BigInteger::ShiftLeft(ll n){
    if (n < 0 || number.size() == 0 || (number.size() == 1 && number[0] == 0)) return;
    ll size_old = (ll)number.size();

    number.resize(size_old + n);
    for (ll i = size_old - 1; i >= 0; i--){
        number[i + n] = number[i];
        number[i] = 0;
    }
}


void BigInteger::ShiftRight(ll n){
    if (n < 0) return;
    if (n >= (ll)number.size()){
        signum = 1;
        number.clear();
        return;
    }

    for (ll i = n; i < number.size(); i++){
        number[i - n] = number[i];
    }

    number.resize((ll)number.size() - n);
    while (number.size() && number.back() == 0) number.pop_back();
}


void BigInteger::ModuleByBase(ll n){
    if (n < number.size()) number.resize(n);
    while (number.size() && number.back() == 0) number.pop_back(); // because {1 0 0 0 0 2 3} -> {1 0 0} -> {1} - NEED!!!
}


bool BigInteger::absoluteCompareLesser(const BigInteger &right_number) const {
    // 1 if left_operand <= right_operand else 0
    if (number.size() != right_number.Size()) return number.size() < right_number.Size();
    if (number.size() == 0) return false;

    auto right_arr = right_number.ToArray();

    for (ll i = number.size() - 1; i >= 0; i--){
        if (number[i] != right_arr[i]) return number[i] < right_arr[i];
    }

    return false;
}


void BigInteger::Add(const BigInteger &right_number){
    if (signum * right_number.Signum() == 1){
        //signum don't change
        AddWithoutChecking(right_number);
    }
    else{
        bool cmp = absoluteCompareLesser(right_number);
        
        signum = (cmp) ? right_number.Signum() : signum;
        SubtractWithoutChecking(right_number, cmp);
    }
}


void BigInteger::Subtract(const BigInteger &right_number){
    if (signum * right_number.Signum() == 1){
        bool cmp = absoluteCompareLesser(right_number);
        
        signum = (cmp) ? -right_number.Signum() : signum;
        SubtractWithoutChecking(right_number, cmp);
    }
    else{
        //signum don't change
        AddWithoutChecking(right_number);
    }
}


void BigInteger::AddWithoutChecking(const BigInteger &right_number){
    auto right_arr = right_number.ToArray();
    ll sz = std::max(number.size(), right_arr.size()), current = 0;

    for (ll i = 0; i < sz; i++){
        if (i < right_arr.size()) current += right_arr[i];

        if (i < number.size()){
            current += number[i];
            number[i] = current % base;
        }
        else number.push_back(current % base);

        current /= base;
    }

    while (current){
        number.push_back(current % base);
        current /= base;
    }

    while (number.size() && number.back() == 0) number.pop_back();
}


void BigInteger::SubtractWithoutChecking(const BigInteger &right_number, bool compareResult){
    auto right_arr = right_number.ToArray();
    auto tmp1 = number;
    auto tmp2 = right_number.ToArray();
    ll current = 0;

    if (compareResult){//if a < b
        number.resize(right_arr.size(), 0);
        for (ll i = 0; i < right_arr.size(); i++){
            number[i] = right_arr[i] - current - number[i];
            current = number[i] < 0;
            if (current) number[i] += base;
        }
    }
    else{// if a >= b
        for (ll i = 0; i < right_arr.size() || current; i++){
            number[i] -= current + (i < right_arr.size() ? right_arr[i] : 0);
            current = number[i] < 0;
            if (current) number[i] += base;
        }
    }

    while (number.size() && number.back() == 0) number.pop_back();
}


void BigInteger::Multiply(const BigInteger &right_number){
    auto right_arr = right_number.ToArray();
    vll result(number.size() + right_arr.size() + 10, 0);

    for (ll i = 0; i < number.size(); i++){
        for (ll j = 0, current = 0; j < right_arr.size() || current; j++){
            if (i + j >= result.size()) break;
            current += result[i + j] + number[i] * (j < right_arr.size() ? right_arr[j] : 0);
            result[i + j] = current % base;
            current /= base;
        }
    }
    
    signum = signum * right_number.Signum();
    number.swap(result);
    while (number.size() && number.back() == 0) number.pop_back();
}


BigInteger& BigInteger::operator << (ll n) const {
    BigInteger *result = new BigInteger(*this);
    result->ShiftLeft(n);
    return *result;
}


BigInteger& BigInteger::operator>>(ll n) const {
    BigInteger *result = new BigInteger(*this);
    result->ShiftRight(n);
    return *result;
}

BigInteger& BigInteger::operator + (const BigInteger &bigInt) const{
    BigInteger *result = new BigInteger(*this);
    result->Add(bigInt);
    return *result;
}


BigInteger& BigInteger::operator - (const BigInteger &bigInt) const{
    BigInteger *result = new BigInteger(*this);
    result->Subtract(bigInt);
    return *result;
}


BigInteger& BigInteger::operator*(const BigInteger &bigInt) const{
    BigInteger *result = new BigInteger(*this);
    result->Multiply(bigInt);
    return *result;
}


BigInteger& BigInteger::operator = (const BigInteger &bigInt){
    base = bigInt.Base();
    signum = bigInt.Signum();
    number = vll(bigInt.ToArray().begin(), bigInt.ToArray().end());

    return *this;
}


void BigInteger::MultiplyInt(ll x){
    if (x == 0){
        number.clear();
        signum = 1;
        return;
    }
    
    ll next = 0;
    for (auto it = number.begin(); it != number.end(); it++){
        next += *it * x;
        *it = next % base;
        next /= base;
    }
    while (next){
        number.push_back(next);
        next /= base;
    }

    while (number.size() && number.back() == 0) number.pop_back();
}


void BigInteger::DivideInt(ll x){
    if (x == 0 || number.size() == 0) return;

    vll arr;
    ll carry = 0;
    for (ll i = number.size() - 1; i >= 0 ; i--){
        carry = number[i] + carry * base;
        number[i] = carry / x;
        carry = carry % x;
    }

    while (number.size() && number.back() == 0) number.pop_back();
}


BigInteger& BigInteger::operator*(ll x) const{
    BigInteger *result = new BigInteger(*this);
    result->MultiplyInt(x);
    return *result;
}


BigInteger& BigInteger::operator/(ll x) const{
    BigInteger *result = new BigInteger(*this);
    result->DivideInt(x);
    return *result;
}