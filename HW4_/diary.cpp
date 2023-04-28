// diary.cpp
#include "diary.h"
map<int,int> Diary::month_to_day{{{1,31},{2,28},{3,31},{4,30},{5,31},
                {6,30},{7,31},{8,31},{9,30},{10,31},{11,30},{12,31}}};  //static variable init
void Diary::load_data(const string & load_path){    //load data
    // if(load_path.substr(load_path.find('.')) != ".diary"){
    //     cerr << "Wrong path or incorrect file extension." << endl;
    //     return;
    // }
    ifstream load_file;
    load_file.open(load_path, ios::in );
    if(!load_file.is_open()){
        // cerr << "Fail to open file! No data has been read." << endl;
        return;
    }
    int record_num;
    load_file >> record_num;
    for(int i = 0; i < record_num; ++i){
        Diary::date date_in;
        load_file >> date_in.year >> date_in.month >> date_in.day;
        string content;
        string read;
        int record_line;
        load_file >> record_line;
        load_file.get();
        getline(load_file, read);
        content = read;
        for(int j = 0; j < record_line; ++j){
            getline(load_file, read);
            content += '\n' + read;
        }
        diary_data[date_in] = content;
    }
    load_file.close();
    // cerr << "Load data successfully. " << record_num << " records have been read."<< endl;
}
void Diary::write_data() const{ //write data
    ofstream store_file;
    store_file.open(diary_address, ios::trunc | ios::out );
    if(!store_file.is_open()){
        cerr << "Fail to open file! No data has been writen." << endl;
        return;
    }
    store_file << diary_data.size() << endl; //To make it easier to read the data
    for(auto i = diary_data.begin(); i != diary_data.end(); ++i){
        store_file << i->first.year << " " << i->first.month << " " << i->first.day << endl;
        store_file << count(i->second.begin(), i->second.end(), '\n') << endl; //To make it easier to read the data
        store_file << i->second << endl;
    }
    store_file.close();
    // cerr << "Save data successfully." << endl;
}
void Diary::pdadd(date in, const string & content){
    if(!judge_date(in)){
        cerr << "Wrong date!" << endl;
        return;
    }
    diary_data[in] = content;
    // cerr << "Executed successfully." << endl;
}
void Diary::pdlist() const{
    int count = 0;
    // cerr << endl << "Result:" << endl;
    for(auto i = diary_data.begin(); i != diary_data.end(); ++i){
        cout << i->first << endl;
        ++count;
    }
    if(count == 0) cerr << "There's no record here that matches your request.";
    // cerr << endl << "Executed successfully. List " << count << " entrys." << endl;
}
void Diary::pdlist(date start) const{
    if(!judge_date(start)){
        cerr << "Wrong date!" << endl;
        return;
    }
    int count = 0;
    // cerr << "Result:" << endl;
    for(auto i = diary_data.begin(); i != diary_data.end(); ++i){
        if(start <= i->first){
            cout << i->first << endl;
            ++count;
        }
    }
    if(count == 0) cerr << "There's no record here that matches your request.";
    // cerr << endl << "Executed successfully. List " << count << " entrys." << endl;
}
void Diary::pdlist(date start, date end) const{
    if(!judge_date(start) || !judge_date(end) || end < start){
        cerr << "Wrong date!" << endl;
        return;
    }
    int count = 0;
    // cerr << "Result:" << endl;
    for(auto i = diary_data.begin(); i != diary_data.end(); ++i){
        if((start <= i->first && i->first <= end)){
            cout << i->first << endl;
            ++count;
        }
    }
    if(count == 0) cerr << "There's no record here that matches your request.";
    // cerr << endl << "Executed successfully. List " << count << " entrys." << endl;
}
void Diary::pdshow(date show_date) const{
    if(diary_data.find(show_date) == diary_data.end()){
        cerr << "No recond of" << show_date << '.' << endl;
        return;
    }
    cout << show_date << ":" << endl << diary_data.at(show_date) << endl;
    // cerr << endl << "Executed successfully." << endl;
}
int Diary::pdremove(date remove_date){
    if(diary_data.find(remove_date) == diary_data.end()){
        cerr << "No recond of" << remove_date << '.' << endl;
        return -1;
    }
    diary_data.erase(diary_data.find(remove_date));
    // cerr << endl << "Executed successfully." << endl;
    return 0;
}