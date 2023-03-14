// student.cpp
#include "student.h"
Student::Student(const string & _name, const int & s1, const int & s2, const int & s3){
    name = _name;
    // restrict input
    score1 = (s1 >= SCORE_MIN) ? ((s1 <= SCORE_MAX) ? s1 : SCORE_MAX) : SCORE_MIN;
    score2 = (s2 >= SCORE_MIN) ? ((s2 <= SCORE_MAX) ? s2 : SCORE_MAX) : SCORE_MIN;
    score3 = (s3 >= SCORE_MIN) ? ((s3 <= SCORE_MAX) ? s3 : SCORE_MAX) : SCORE_MIN;
}
Student::Student(const char* _name){
    name = _name;
    score1 = score2 = score3 = 0;
}
Student::Student(){
    name = "";
    score1 = score2 = score3 = 0;
}
Student::~Student(){
}
float Student::average() const{
    return (score1 + score2 + score3) / 3.0;
}