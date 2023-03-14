// student.h
#ifndef _STUDENT_
#define _STUDENT_
#include <string>
using namespace std;

#define SCORE_MAX 10
#define SCORE_MIN 0
class Student
{
private:
    // private data
public:
    // public data
    string name;
    int score1;
    int score2;
    int score3;

    // constructor
    Student(const string & _name, const int & s1, const int & s2, const int & s3);
    Student(const char* _name);
    Student();
    // Student(const Student & s);

    // destructor
    ~Student();

    // function
    float average() const;   // calculate average score

    // operator overloading
    // Student & operator=(const Student & s);

    // friends
};
#endif