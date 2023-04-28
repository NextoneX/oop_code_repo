// diary.h
#ifndef _DIARY_
#define _DIARY_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

class Diary
{
public:
    struct date
    {
        int year;
        int month;
        int day;
        bool operator<(const date & d) const{
            if(year == d.year){
                if(month == d.month) return day<d.day;
                return month < d.month;
            }
            return year < d.year;
        }
        bool operator<=(const date & d) const{
            if(year == d.year){
                if(month == d.month) return day <= d.day;
                return month < d.month;
            }
            return year < d.year;
        }
        friend ostream & operator<<(ostream & os, const date & d){ // overload 
            os << d.year << '-'; 
            if(d.month < 10) os << 0;
            os << d.month << '-'; 
            if(d.day < 10) os << 0;
            os << d.day;
            return os;
        }
    };
    static map<int, int> month_to_day; // Store the available days per month
    static bool judge_date(date date_in){ // Determine whether a date is valid
        if(date_in.month < 1 || date_in.month > 12 || date_in.year < 1000 || date_in.year > 9999 || date_in.day < 1){
            return false;
        }
        if((date_in.month != 2 || date_in.year % 4 != 0) && date_in.day <= month_to_day.at(date_in.month)){
            return true;
        }
        // month == 2
        if(date_in.year % 100 == 0 && date_in.year % 400 != 0 ){
            if(date_in.day < 29) return true;
            return false;
        }
        // leap year
        if(date_in.day < 30) return true; // month == 2, year % 4 == 0
        return false;
    }

    
private:
    // private data
    string diary_address;
    map<date, string> diary_data;

    // private function
    void load_data(const string & load_path);
    void write_data() const;

public:
    // public data

    // constructor
    Diary() : diary_address("temp.diary") {
        load_data(diary_address);
    }
    // Diary(const Diary & s);

    // destructor
    ~Diary(){
        // cout << "(Automatic execution)";
        write_data();
    }

    // function
    void pdadd(date in, const string & content);
    void pdlist() const;
    void pdlist(date start) const;
    void pdlist(date start, date end) const;
    void pdshow(date show_date) const;
    int pdremove(date remove_date);
    // void save(){
    //     write_data();
    // }
    // void store_to(const string & store_path){
    //     diary_address = store_path;
    // }
    // void load_from(const string & load_path){
    //     diary_address = load_path;
    //     diary_data.clear();
    //     load_data(load_path);
    // }

    // operator overloading
    // Diary & operator=(const Diary & s);

    // friends

};
#endif