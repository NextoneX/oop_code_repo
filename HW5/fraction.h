// fraction.h
#ifndef _FRACTION_
#define _FRACTION_
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;
class Fraction
{
private:
// private data

// private function
    // find the greatest common divisor
    int GCD(int a, int b) const {
        int r;
        a = abs(a); b = abs(b);
        if(a<b) swap(a, b);
        while(b!=0)
        {
            r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
    // find the least common multiple
    int LCM(const int & a, const int & b) const {
        int _max = (abs(a) > abs(b)) ? abs(a) : abs(b);
        int _min = abs(a) + abs(b) - _max;
        int lcm = _max;
        do
        {
            if(lcm % _min == 0)
                return lcm;
            else
                lcm += _max;
        } while (true);
    }

public:
// public data
    int dividend; // 被除数
    int divisor; // 除数

// constructor
    Fraction() 
        : dividend(0),
          divisor(1) {}
    Fraction(const Fraction & f) 
        : dividend(f.dividend),
          divisor(f.divisor) {}
    Fraction(const int & _dividend, const int & _divisor){
        assert(_divisor != 0);
        int gcd = 1;
        if(_dividend != 0) gcd = GCD(_dividend, _divisor);
        dividend = _dividend / gcd;
        divisor = _divisor / gcd;
    }
    Fraction(string f);
    

// destructor
    ~Fraction() {}

// function
    string to_string(int decimal_digits = 2) const;

// operator overloading
    Fraction & operator=(const Fraction & f) {
        dividend = f.dividend;
        divisor = f.divisor;
        return *this;
    }
    // arithmetical operators
    Fraction operator+(const Fraction & f) const;
    Fraction operator-(const Fraction & f) const;
    Fraction operator*(const Fraction & f) const;
    Fraction operator/(const Fraction & f) const;
    // relational operators
    bool operator<(const Fraction & f) const {
        return dividend * f.divisor < f.dividend * divisor;
    }
    bool operator<=(const Fraction & f) const {
        return dividend * f.divisor <= f.dividend * divisor;
    }
    bool operator==(const Fraction & f) const {
        return dividend * f.divisor == f.dividend * divisor;
    }
    bool operator!=(const Fraction & f) const {
        return dividend * f.divisor != f.dividend * divisor;
    }
    bool operator>=(const Fraction & f) const {
        return dividend * f.divisor >= f.dividend * divisor;
    }
    bool operator>(const Fraction & f) const {
        return dividend * f.divisor > f.dividend * divisor;
    }

// conversion functions
    operator double() const {
        double result = dividend;
        result /= divisor;
        return result;
    }

// friends
    friend ostream & operator<<(ostream & os, const Fraction & f) {
        os << f.dividend << "/" << f.divisor;
        return os;
    }
    friend istream & operator>>(istream & is, Fraction & f) {
        is >> f.dividend >> f.divisor;
        if(!is) f = Fraction();
        return is;
    }
};
#endif