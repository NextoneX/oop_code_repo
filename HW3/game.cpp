// game.cpp
#include "game.h"

void Game::init(){
    game_state = true;
// init room
    room_list.clear();
// game map:
//                              room_9 -- princess
//                                |         |
//                              room_7 -- room_8(monster)
//                                |         |
//                              room_3 -- room_6
//                                |         |
// room_4(monster) -- room_1 -- lobby -- room_2 -- room_5
    // create room
    room_list.emplace_back("lobby", false, false, true);
    room_list.emplace_back("room_1", false, false, false);
    room_list.emplace_back("room_2", false, false, false);
    room_list.emplace_back("room_3", false, false, false);
    room_list.emplace_back("room_4", true, false, false);
    room_list.emplace_back("room_5", false, false, false);
    room_list.emplace_back("room_6", false, false, false);
    room_list.emplace_back("room_7", false, false, false);
    room_list.emplace_back("room_8", true, false, false);
    room_list.emplace_back("room_9", false, false, false);
    room_list.emplace_back("princess's room", false, true, false);
    // set neighbor
    room_list[0].set_neighbor(&room_list[1], nullptr, &room_list[2], &room_list[3]);
    room_list[1].set_neighbor(&room_list[4], nullptr, &room_list[0], nullptr);
    room_list[2].set_neighbor(&room_list[0], nullptr, &room_list[5], &room_list[6]);
    room_list[3].set_neighbor(nullptr, &room_list[0], &room_list[6], &room_list[7]);
    room_list[4].set_neighbor(nullptr, nullptr, &room_list[1], nullptr);
    room_list[5].set_neighbor(&room_list[2], nullptr, nullptr, nullptr);
    room_list[6].set_neighbor(&room_list[3], &room_list[2], nullptr, &room_list[8]);
    room_list[7].set_neighbor(nullptr, &room_list[3], &room_list[8], &room_list[9]);
    room_list[8].set_neighbor(&room_list[7], &room_list[6], nullptr, &room_list[10]);
    room_list[9].set_neighbor(nullptr, &room_list[7], &room_list[10], nullptr);
    room_list[10].set_neighbor(&room_list[9], &room_list[8], nullptr, nullptr);

// init plater
    player.has_princess = false;
    // input name
    {
        cout << "Welcome to SAVING_HER, in this game, you are asked to rescue a princess in a castle. Tell me what's yout name:" << endl;
        string player_name;
        getline(cin, player_name);
        player.name = player_name;
    }
    cout << "Hello " << player.name << ", it is time to rescue the princess." << endl;
    delay(1);
    cout << "Pay attention! There are many monsters roaming the castle." << endl;
    delay(1);
    cout << "Remember, when you've saved the princess, go back to where you started." << endl;
    delay(1);
    cout << "Now, just start your adventure!" << endl;
    delay(1);
    cout << "Entering the castle.";
    delay(1);cout << ".";delay(1);cout << ".";delay(1);cout << "." << endl;
    
    player.current = &room_list[0];
    cout << "-------------------------------------------" << endl;
    cout << "Welcome to " << player.current->name << "." <<endl;
    print_exit();
    cout << "You can input \"go (exit)\" to exit." << endl;
    delay(1);
}

void Game::move(const Movement & move_to){
    _move_to(move_to);
    cout << "-------------------------------------------" << endl;
    cout << "Welcome to " << player.current->name << "." <<endl;
    delay(1);
    cout << "Searching.";
    delay(1);cout << ".";delay(1);cout << ".";delay(1);cout << "." << endl;
    if( player.current->is_monster ){
        lose();
        return;
    }
    if( player.has_princess && player.current->is_start ){
        win();
        return;
    }
    if( !player.has_princess && player.current->is_princess ){
        find_princess();
        player.has_princess = true;
        delay(0.5);
    }
    print_exit();
    
}

void Game::print_exit(){
    string exits;
    short exit_count = 0;
    if(player.current->east){
        exits += " east";
        ++exit_count;
    }
    if(player.current->south){
        exits += " south";
        ++exit_count;
    }
    if(player.current->west){
        exits += " west";
        ++exit_count;
    }
    if(player.current->north){
        exits += " north";
        ++exit_count;
    }
    cout << "There are " << exit_count << " exits:" << exits << "." << endl;
}

inline void Game::win(){
    cout << "You win!" << endl;
    game_state = false;
}
inline void Game::lose(){
    cout << "" << endl;
    cout << "You lose!" << endl;
    game_state = false;
}
inline void Game::find_princess(){
    cout << "You have find the princess!" << endl;

    cout << "Now! Run! Get out of here!" << endl;
    delay(1);
}

void Game::_move_to(const Movement & move_to){
    switch(move_to){
        case move_to_east:
            if(player.current->east){
                player.current = player.current->east;
            }else{
                cout << "Invalid movement!" << endl;
                return;
            }
            break;
        case move_to_south:
            if(player.current->south){
                player.current = player.current->south;
            }else{
                cout << "Invalid movement!" << endl;
                return;
            }
            break;
        case move_to_west:
            if(player.current->west){
                player.current = player.current->west;
            }else{
                cout << "Invalid movement!" << endl;
                return;
            }
            break;
        case move_to_north:
            if(player.current->north){
                player.current = player.current->north;
            }else{
                cout << "Invalid movement!" << endl;
                return;
            }
            break;
        default :
            cout << "Invalid movement!" << endl;
            return;
    }
}

inline void Game::delay(const int & delay_time)
{
    clock_t start_time;
    start_time = clock();// clock()返回当前时间
    for (; (clock() - start_time) < delay_time * CLOCKS_PER_SEC;);// 延迟delay_time秒
}