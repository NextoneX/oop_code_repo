// student.cpp
#include "student.h"
Student::Student(const string & _name){
    name = _name;
}
Student::Student(const char* _name){
    name = _name;
}
Student::Student(){
    name = "Unknow";
}

Student::~Student(){
}

float Student::average() const{
    if(course_.size() == 0) return 0;
    double sum = 0;
    for( auto & i : course_){
        sum += i.second;
    }
    sum/= course_.size();
    return sum;
}

void Student::addcourse(const string & course_name, const int & course_score){
    // restrict input
    int score = (course_score >= SCORE_MIN) ? ((course_score <= SCORE_MAX) ? course_score : SCORE_MAX) : SCORE_MIN;
    course_[course_name] = score;
}

void Student::outcourse(const string & course_name) const{
    if(course_.find(course_name) == course_.end()){
        cout << "NULL\t";
    }else{
        cout << course_.find(course_name)->second << "\t";
    }
}

void Student::printname() const{
    if(name.length() < 8){
        cout << name << "\t";
    }else{
        cout << name.substr(0,6) << ".\t";
    }
}