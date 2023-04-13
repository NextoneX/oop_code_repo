// main.cpp
// header
#include "game.h"
#include <map>
//main
int main()
{
    // movement define
    map<string, Game::Movement> movement;
    movement["east"] = Game::move_to_east;
    movement["south"] = Game::move_to_south;
    movement["west"] = Game::move_to_west;
    movement["north"] = Game::move_to_north;

    // start game
    Game mygame;
    mygame.init();
    while(!mygame.is_over()){
        cout << "Enter your command:" << endl;
        string input;
        getline(cin, input);
        if(input.substr(0,3) != "go "){
            cout << "Invalid command!" << endl;
            continue;
        }
        input = input.substr(3);
        if(movement.find(input) == movement.end()){
            cout << "Invalid command!" << endl;
            continue;
        }
        mygame.move(movement[input]);
    }
    cout << "Thank you for your playing!" << endl;
    
    return 0;
}
