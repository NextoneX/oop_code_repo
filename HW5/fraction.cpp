// fraction.cpp
#include "fraction.h"
string Fraction::to_string(int decimal_digits) const {
    if(dividend == 0) return string("0");
    if(decimal_digits < 0) decimal_digits = 0;
    long temp = dividend;
    for(int i = 0; i < decimal_digits; ++i) temp *= 10;
    temp /= divisor;
    string result;
    if(temp == 0) { // handle 0
        result = "0.";
        for(int i = 0; i < decimal_digits; ++i) result += '0';
        return result;
    }
    if(temp < 0) {  // handle negetive result
        result.push_back('-');
        temp = -temp;
    }
    while(temp > 0) {
        if(decimal_digits == 0) result.insert(result.begin() + 1, '.');
        char c = '0' + (temp % 10);
        result.insert(result.begin() + 1, c);
        --decimal_digits;
        temp /= 10;
    }
    if(decimal_digits == 0) { // handle too small result
        result.insert(result.begin() + 1, '.');
        result.insert(result.begin() + 1, '0');
    }
    return result;
}
Fraction Fraction::operator+(const Fraction & f) const {
    int new_divisor = LCM(divisor, f.divisor);
    // cout << new_divisor << endl;
    int new_dividend = dividend * new_divisor / divisor +
                        f.dividend * new_divisor / f.divisor;
    return Fraction(new_dividend, new_divisor);
}
Fraction Fraction::operator-(const Fraction & f) const {
    int new_divisor = LCM(divisor, f.divisor);
    int new_dividend = dividend * new_divisor / divisor -
                        f.dividend * new_divisor / f.divisor;
    return Fraction(new_dividend, new_divisor);
}
Fraction Fraction::operator*(const Fraction & f) const {
    int new_divisor = divisor * f.divisor;
    int new_dividend = dividend * f.dividend;
    return Fraction(new_dividend, new_divisor);
}
Fraction Fraction::operator/(const Fraction & f) const {
    int new_divisor = divisor * f.dividend;
    int new_dividend = dividend * f.divisor;
    return Fraction(new_dividend, new_divisor);
}
Fraction::Fraction(string f) {
    size_t pos = f.find('.');
    if(pos == string::npos){
        dividend = stoi(f);
        divisor = 1;
        return;
    }
    int pows = f.length() - pos - 1;
    f.erase(f.begin() + pos);
    long _dividend = stoi(f);
    long _divisor = 1;
    for(int i = 0; i < pows; ++i) _divisor *= 10;
    long gcd = GCD(_dividend, _divisor);
    dividend = _dividend / gcd;
    divisor = _divisor / gcd;
}
