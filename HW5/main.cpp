// main.cpp
// header
#include "fraction.h"
//main
int main()
{   
    // Default ctor
    cout << "Default ctor:" << endl;
    Fraction f0;
    cout << f0 << endl;
    // Conversion from a finite decimal string like: 0.1
    cout << "Conversion from a finite decimal string:" << endl;
    Fraction f1("0.1");
    cout << f1 << endl;
    // Ctor takes two integers as parameters
    cout << "Ctor takes two integers as parameters:" << endl;
    Fraction f2(3,6);
    cout << f2 << endl;
    // Copy ctor
    cout << "Copy ctor:" << endl;
    f0 = f2;
    cout << f0 << endl;
    // Arithmetical operators: + - * /
    cout << "Arithmetical operators: + - * /:" << endl;
    cout << f1+f2 << endl;
    cout << f1-f2 << endl;
    cout << f1*f2 << endl;
    cout << f1/f2 << endl;
    // Relational operators: < <= == != >= >
    cout << "Relational operators: < <= == != >= >:" << endl;
    cout << (f1<f2) << endl;
    cout << (f1<=f2) << endl;
    cout << (f1==f2) << endl;
    cout << (f1!=f2) << endl;
    cout << (f1>=f2) << endl;
    cout << (f1>f2) << endl;
    // Typecast to double
    cout << "Typecast to double:" << endl;
    Fraction f3 = f1 - f2;
    double d3 = f3;
    cout << d3 << endl;
    // To string
    cout << "To string:" << endl;
    string s3 = f3.to_string();
    cout << s3 << endl;
    // Inserter and extractor for streams
    cout << "Inserter and extractor for streams:" << endl;
    cout << "Input two integer:";
    cin >> f0;
    cout << f0;
}