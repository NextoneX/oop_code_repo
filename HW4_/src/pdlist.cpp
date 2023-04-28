// main.cpp
// header
#include "../diary.h"
#include <map>
//main
int main(int argc, char* argv[])
{
    Diary mydiary;
    string start, end;
    Diary::date date_start, date_end;
    switch (argc)
    {
    case 2:
        start = argv[1];
        date_start.year = stoi(start.substr(0,4));
        date_start.month = stoi(start.substr(5,2));
        date_start.day = stoi(start.substr(8,2));
        mydiary.pdlist(date_start);
        return 0;
    case 3:
        start = argv[1];
        end = argv[2];
        date_start.year = stoi(start.substr(0,4));
        date_start.month = stoi(start.substr(5,2));
        date_start.day = stoi(start.substr(8,2));
        date_end.year = stoi(start.substr(0,4));
        date_end.month = stoi(start.substr(5,2));
        date_end.day = stoi(start.substr(8,2));
        mydiary.pdlist(date_start, date_end);
        return 0;
    default:
        mydiary.pdlist();
        return 0;
    }
    
}