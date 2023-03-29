// student.h
#ifndef _STUDENT_
#define _STUDENT_
#include <vector>
#include <string>
#include <map>
#include <iostream>
using namespace std;

#define SCORE_MAX 5
#define SCORE_MIN 0
class Student
{
private:
    // private data
    string name;
    map<string,int> course_;

public:
    // public data

    // constructor
    Student(const string & _name);
    Student(const char* _name);
    Student();
    // Student(const Student & s);

    // destructor
    ~Student();

    // function
    float average() const;   // calculate average score
    void addcourse(const string & course_name, const int & course_score);
    void outcourse(const string & course_name) const;
    void printname() const;

    // operator overloading
    // Student & operator=(const Student & s);

    // friends

};
#endif