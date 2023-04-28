// main.cpp
// header
#include "../diary.h"
#include <map>
//main
int main()
{
    Diary mydiary;
    string command;
    Diary::date date_in;
    int state = 0;
    getline(cin, command);
    while(command.size() == 10){
        date_in.year = stoi(command.substr(0,4));
        date_in.month = stoi(command.substr(5,2));
        date_in.day = stoi(command.substr(8,2));
        state += mydiary.pdremove(date_in);
        getline(cin, command);
    }
    return state;
}
            