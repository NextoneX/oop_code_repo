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
    Room * east;
    Room * west;
    Room * north;
    Room * south;

    // constructor
    Room(const string & _name, const bool & _is_monster, const bool & _is_princess, const bool & _is_start)
    : name(_name), is_monster(_is_monster), is_princess(_is_princess), is_start(_is_start) {}
    Room(const char* _name, const bool & _is_monster, const bool & _is_princess, const bool & _is_start)
    : name(_name), is_monster(_is_monster), is_princess(_is_princess), is_start(_is_start) {}
    Room(): name("NULL"), is_monster(false), is_princess(false), is_start(false) {}
    // Room(const Room & s);

    // destructor
    ~Room() {}

    // function
    void set_neighbor(Room * _east, Room * _south, Room * _west, Room * _north){
        east = _east;
        south = _south;
        west = _west;
        north = _north;
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
    void win();
    void lose();
    void delay(const int & delay_time);
    void find_princess();
    void print_exit();
    void _move_to(const Movement & move_to);

public:
    // constructor
    Game() {}
    // Game(const Game & s);

    // destructor
    ~Game() {}

    // function
    void init();
    void move(const Movement & move_to);
    bool is_over(){
        return !game_state;
    }
    // operator overloading
    // Game & operator=(const Game & s);

    // friends

};
#endif