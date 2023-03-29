// main.cpp
// header
#include "student.h"
#include <iostream>
using namespace std;
// function
const int & max(const int & a, const int & b){return (a>b) ? a : b;}
const int & min(const int & a, const int & b){return (a<b) ? a : b;}

//main
int main()
{
    // output tips
    cout << "The program takes data from ten students as input and outputs a statistical table." <<endl;
    cout << "Tips: You need to enter the student's data one by one, using newlines as a partition." << endl;
    cout << "Sample input: Lihua 1 2 3" << endl << "Start input:" << endl;
    
    // init data
    Student students[10];
    string name_;
    int s1,s2,s3;
    int total1 = 0, total2 = 0,total3 = 0;
    int max1, max2, max3;
    int min1, min2, min3;
    max1 = max2 = max3 = SCORE_MIN;
    min1 = min2 = min3 = SCORE_MAX;

    // input date
    for( int i = 0; i < 10; i++){
        cin >> name_ >> s1 >> s2 >> s3;
        students[i] = Student(name_, s1, s2, s3);
        // update total, max, min
        total1 += s1; max1 = max(max1, s1); min1 = min(min1, s1);
        total2 += s2; max2 = max(max1, s1); min2 = min(min1, s1);
        total3 += s3; max3 = max(max1, s1); min3 = min(min1, s1);
        // output tips
        cout << "Number of remaining students: " << 9-i << endl;
    }
    // output
    cout << "----------------------------------------------" << endl;
    cout << "no\tname\tscore1\tscore2\tscore3\taverage" << endl;
    for( int i = 0; i < 10; i++){
        // restrict name length
        cout << i+1 << "\t" << students[i].name.substr(0,7) << "\t"
            << students[i].score1 << "\t" << students[i].score2 << "\t"
            << students[i].score3 << "\t" << students[i].average() << endl;
    }
    cout << "\taverage\t" << total1/10.0 << "\t" << total2/10.0 << "\t" << total3/10.0 << endl;
    cout << "\tmin\t" << min1 << "\t" << min2 << "\t" << min3 << endl;
    cout << "\tmax\t" << max1 << "\t" << max2 << "\t" << max3 << endl;
    cin.get();
    return 0;
}
