// main.cpp
// header
#include "../diary.h"
#include <map>
//main
int main()
{
    Diary mydiary;
    cout << "------------------------------------------------" << endl;
    cout << "Welcome to use diary1.1!"                         << endl;
    cout << "You can input 'help' to obtain the command list." << endl;
    cout << "------------------------------------------------" << endl << endl;
    string command;
    while(!cin.eof()){
        cout << "Enter your command:" << endl;
        getline(cin, command);
        string input_command = command.substr(0,6);

        if(input_command == "pdadd " && command.size()==16){    //pdadd
            Diary::date date_in;
            date_in.year = stoi(command.substr(6,4));
            date_in.month = stoi(command.substr(11,2));
            date_in.day = stoi(command.substr(14,2));
            cout << "Enter the contents of the diary on " << date_in << ":"<< endl;
            string content;
            char input_char;
            while((input_char = getchar()) != EOF && input_char!=26){
                content += input_char;
                if(input_char == '.'){
                    getchar();
                    break;
                }
            }
            mydiary.pdadd(date_in, content);
            if(cin.eof()) cin.clear();
            continue;
        }

        if(input_command == "pdlist"){      //pdlist
            int start = command.find('[');
            int end = command.find(']');
            if (end == start+1){
                mydiary.pdlist();
                continue;
            }
            if(end - start < 22){
                cout << "Wrong command!" << endl;
                continue;
            }
            Diary::date date_start;//[xxxx-xx-xx
            date_start.year = stoi(command.substr(start + 1,4));
            date_start.month = stoi(command.substr(start + 6,2));
            date_start.day = stoi(command.substr(start + 9,2));
            Diary::date date_end;//xxxx-xx-xx]
            date_end.year = stoi(command.substr(end-10,4));
            date_end.month = stoi(command.substr(end-5,2));
            date_end.day = stoi(command.substr(end-2,2));
            mydiary.pdlist(date_start, date_end);
            continue;
        }

        if(input_command == "pdshow" && command.size() == 17){  //pdshow
            Diary::date date_in;
            date_in.year = stoi(command.substr(7,4));
            date_in.month = stoi(command.substr(12,2));
            date_in.day = stoi(command.substr(15,2));
            mydiary.pdshow(date_in);
            continue;
        }

        if(input_command == "pdremo" && command.size() == 19){ //pdremove
            Diary::date date_in;
            date_in.year = stoi(command.substr(9,4));
            date_in.month = stoi(command.substr(14,2));
            date_in.day = stoi(command.substr(17,2));
            mydiary.pdremove(date_in);
            continue;
        }

        if(input_command[0] == 'q' || input_command[0] == 'Q' || input_command == "exit"){ //exit
            break;
        }
        cout << "Wrong command!" << endl;
    }
    cout << "Bye" << endl;
}