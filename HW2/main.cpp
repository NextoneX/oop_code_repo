// main.cpp
// header
#include "student.h"
using namespace std;
// function
const int & max(const int & a, const int & b){return (a>b) ? a : b;}
const int & min(const int & a, const int & b){return (a<b) ? a : b;}

struct course
{
    int count = 0;
    int sum = 0;
    int max = 0;
    int min = 5;
};

//main
int main()
{
    // output tips
    cout << "The program takes scoring records of students as input and outputs a statistical table." <<endl;
    cout << "For each student, you need to enter the number of courses that student has." << endl;
    cout << "Sample input: Lihua 3 course1 1 course2 2 course3 3" << endl;
    cout << "You need to enter the student's data one by one, using newlines as a partition." << endl;
    cout << "First of all, you must input the number of student:" << endl;

    // init data
    map<string, course> course_list;
    vector<Student> student_list;
    int student_num;

    // input date
    cin >> student_num;
    for( int i = 0; i < student_num; ++i){
        string name_;
        int course_num;
        cin >> name_ >> course_num;
        student_list.emplace_back(name_);
        for( int j = 0; j < course_num; ++j){
            string course_name;
            int course_score;
            cin >> course_name >> course_score;
            student_list[i].addcourse(course_name, course_score);
            course_list[course_name].count++;
            course_list[course_name].sum += course_score;
            course_list[course_name].max = max(course_list[course_name].max, course_score);
            course_list[course_name].min = min(course_list[course_name].min, course_score);
        }
    }

    // output
    cout.precision(6);
    cout << "----------------------------------------------" << endl;
    cout << "no\tname\t";
    for( auto & j : course_list){
        if(j.first.length() < 8){
            cout << j.first << "\t";
        }else{
            cout << j.first.substr(0,6) << ".\t";
        }
    }
    cout << "average" << endl;
    // output student
    for(int i = 0; i < student_num; ++i){
        cout << i+1 << "\t";
        student_list[i].printname();
        for( auto & j : course_list){
            student_list[i].outcourse(j.first);
        }
        cout << student_list[i].average() << endl;
    }
    // output course statis
    cout << "\taverage\t";
    for( auto & j : course_list)
        cout << j.second.sum/(double)j.second.count << "\t";
    cout << endl;
    cout << "\tmin\t";
    for( auto & j : course_list)
        cout << j.second.min << "\t";
    cout << endl;
    cout << "\tmax\t";
    for( auto & j : course_list)
        cout << j.second.max << "\t";
    cout << endl;
    cin.get();
    return 0;
}
