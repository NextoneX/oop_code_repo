// main.cpp
// header
#include "../diary.h"
#include <map>
//main
int main(int argc, char* argv[])
{
    Diary mydiary;
    string command;
    if(argc < 2){
        cerr << "No input date!" << endl;
        return -1;
    }
    command = argv[1];
    if(command.length() != 10){
        cerr << "Wrong command!" << endl;
        return -1;
    }
    Diary::date date_in;
    date_in.year = stoi(command.substr(0,4));
    date_in.month = stoi(command.substr(5,2));
    date_in.day = stoi(command.substr(8,2));
    string content;
    getline(cin, command);
    if(command != ".") content = command;
    while(command != "."){
        if(cin.eof()) break;
        getline(cin, command);
        content += "\n" + command;
    }
    mydiary.pdadd(date_in, content);
}