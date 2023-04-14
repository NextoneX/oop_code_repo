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
    cout << endl;
    Game::delay_print("Loading game.", false);
    Game::delay(1);cout << ".";Game::delay(1);cout << ".";Game::delay(1);cout << "." << endl << endl;
    Game::delay_print("Welcome to SAVING_HER!");
    Game::delay(0.5);
    Game::delay_print("In this game, you are asked to rescue a princess in a castle.");
    mygame.init();
    while(true){
        while(!mygame.is_over()){
            Game::delay_print("Enter your command:");
            string input;
            getline(cin, input);
            if(input.substr(0,3) != "go "){
                cout << "Invalid command!" << endl;
                cout << "Tips: You can input \"go (exit)\" to exit." << endl;
                continue;
            }
            input = input.substr(3);
            if(movement.find(input) == movement.end()){
                cout << "Invalid command!" << endl;
                cout << "Tips: You can input \"go (exit)\" to exit." << endl;
                continue;
            }
            mygame.move(movement[input]);
        }
        cout << endl;
        Game::delay(1);
        cout << "If you want to play again, input \"r\"." << endl;
        Game::delay(0.5);
        cout << "If you want to leave, input \"q\"." << endl;
        Game::delay_print("Enter your command:");
        string command;
        getline(cin, command);
        if(command[0] == 'r') continue;
        else break;
    }
    Game::delay_print("Thank you for your playing!");
    return 0;
}