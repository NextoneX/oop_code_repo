// game.h
#ifndef _GAME_
#define _GAME_
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
using namespace std;

class Room
{
private:
    // private data

public:
    // public data
    string name;
    bool is_monster;
    bool is_princess;
    bool is_start;
    Room * west;
    Room * south;
    Room * east;
    Room * north;

    // constructor
    Room(const string & _name, const bool & _is_monster, const bool & _is_princess, const bool & _is_start)
    : name(_name), is_monster(_is_monster), is_princess(_is_princess), is_start(_is_start) {}
    Room(): name("NULL"), is_monster(false), is_princess(false), is_start(false) {}
    // Room(const Room & s);

    // destructor
    ~Room() {}

    // function
    void set_neighbor(Room * _west, Room * _south, Room * _east, Room * _north) { // left, down, right, up
        east = _east; south = _south; west = _west; north = _north;
    }

    // operator overloading
    // Room & operator=(const Room & s);

    // friends

};

class Player
{
private:
    // private data

public:
    // public data
    string name;
    Room * current;
    bool has_princess;

    // constructor
    Player() : name("NULL"), current(nullptr), has_princess(false){}
    // Player(const Player & s);

    // destructor
    ~Player() {}

    // function

    // operator overloading
    // Player & operator=(const Player & s);

    // friends

};

class Game
{
public:
    // public data
    enum Movement{move_to_east, move_to_south, move_to_west, move_to_north};

private:
    // private data
    Player player;
    vector<Room> room_list;
    bool game_state;

    // private function
    // game state
    void win();
    void lose();
    void find_princess();
    // move
    void print_exit();
    void _move_to(const Movement & move_to);
    // choose level
    void choose_level();
    // init level
    void init_easy();
    void init_medium();
    void init_hard();

public:
    // constructor
    Game() {}
    // Game(const Game & s);

    // destructor
    ~Game() {}

    // function
    void init();    // game init
    void move(const Movement & move_to); // player move
    bool is_over(){ // return !game_state
        return !game_state;
    }

    // static function
    static void delay(const float & delay_time){ // sleep
        clock_t start_time;
        start_time = clock();// clock() return current time
        for (; (clock() - start_time) < delay_time * CLOCKS_PER_SEC;);// delay delay_time seconds
    }
    static void delay_print(const string & text, bool has_endl = true){ // Print text one by one
        int n = text.size();
        for(int i=0; i<n; ++i){
            cout << text[i];
            delay(0.03125);
        }
        if(has_endl) cout << endl; 
    }

    // operator overloading
    // Game & operator=(const Game & s);

    // friends

};
#endif