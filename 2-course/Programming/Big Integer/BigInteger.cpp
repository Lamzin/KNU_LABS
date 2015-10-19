#include <algorithm>

#include "BigInteger.h"


BigInteger::BigInteger(int Base) : base(Base), signum(1){}


BigInteger::BigInteger(const BigInteger &bigInt, int Base){
    base = Base;
    if (Base != bigInt.Base()) ToBigInteger(bigInt.ToString());
    else{
        signum = bigInt.Signum();
        number = std::vector<int>(bigInt.ToArray());
    }
}


BigInteger::BigInteger(const std::string &str, int Base){
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
    
        int current = 0, first = 0;
        for (int i = 0; i < buffer.length(); i++){
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

}


const std::vector<int> &BigInteger::ToArray() const {
    return number;
}


int BigInteger::Size() const{
    return number.size();
}


int BigInteger::Base() const{
    return base;
}


int BigInteger::Signum() const{
    return signum;
}


std::string BigInteger::ToString() const{
    std::string result;
    std::vector<int> buffer(number), buffer_tmp;

    std::reverse(buffer.begin(), buffer.end());
    while (buffer.size()){
        buffer_tmp.clear();

        int current = 0, first = 0;
        for (int i = 0; i < buffer.size(); i++){
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


void BigInteger::ShiftLeft(int n){
    if (n < 0) return;
    int size_old = (int)number.size();

    number.resize(size_old + n);
    for (int i = size_old - 1; i >= 0; i--){
        number[i + n] = number[i];
        number[i] = 0;
    }
}


void BigInteger::ShiftRight(int n){
    if (n < 0) return;
    if (n >= (int)number.size()){
        number.resize(0);
        return;
    }

    for (int i = n; i < number.size(); i++){
        number[i - n] = number[i];
    }

    number.resize((int)number.size() - n); 
}


bool BigInteger::absoluteCompareLesser(const BigInteger &right_number) const {
    // 1 if left_operand <= right_operand else 0
    if (number.size() != right_number.Size()) return number.size() < right_number.Size();

    auto right_arr = right_number.ToArray();

    for (int i = number.size() - 1; i >= 0; i--){
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
    int sz = std::max(number.size(), right_arr.size()), current = 0;

    for (int i = 0; i < sz; i++){
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
}


void BigInteger::SubtractWithoutChecking(const BigInteger &right_number, bool compareResult){
    auto right_arr = right_number.ToArray();
    int current = 0;

    if (compareResult){
        number.resize(right_arr.size(), 0);
        for (int i = 0; i < right_arr.size() || current; i++){
            number[i] = right_arr[i] - current - number[i];
            current = number[i] < 0;
            if (current) number[i] += base;
        }
    }
    else{
        for (int i = 0; i < right_arr.size() || current; i++){
            number[i] -= current + (i < right_arr.size() ? right_arr[i] : 0);
            current = number[i] < 0;
            if (current) number[i] += base;
        }
    }
}


void BigInteger::Multiply(const BigInteger &right_number){
    auto right_arr = right_number.ToArray();
    std::vector<int> result(number.size() + right_arr.size(), 0);

    for (int i = 0; i < number.size(); i++){
        for (int j = 0, current = 0; j < right_arr.size() || current; j++){
            current += result[i + j] + number[i] * (j < right_arr.size() ? right_arr[j] : 0);
            result[i + j] = current % base;
            current /= base;
        }
    }
    
    while (result.size() > 0 && result.back() == 0) result.pop_back();

    signum = signum * right_number.Signum();
    number.swap(result);
}


BigInteger& BigInteger::operator << (int n) const {
    BigInteger *result = new BigInteger(*this);
    result->ShiftLeft(n);
    return *result;
}


BigInteger& BigInteger::operator>>(int n) const {
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


BigInteger& BigInteger::operator*(const BigInteger &bigInt){
    BigInteger *result = new BigInteger(*this);
    result->Multiply(bigInt);
    return *result;
}


BigInteger& BigInteger::operator = (const BigInteger &bigInt){
    base = bigInt.Base();
    number = std::vector<int>(bigInt.ToArray());

    return *this;
}