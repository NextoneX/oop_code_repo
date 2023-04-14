// game.cpp
#include "game.h"

void Game::init(){
    game_state = true;
    // choose level
    choose_level();
    // init player
    player.has_princess = false;
    player.current = &room_list[0];
    // input name
    {
        delay(0.5);
        cout << endl;
        delay_print("Please tell me your name:", false);
        string player_name;
        getline(cin, player_name);
        player.name = player_name;
    }
    // start
    cout << endl; delay(0.25);
    delay_print("Hello " + player.name + ", it is time to rescue the princess.");
    delay(0.5);
    delay_print("Pay attention! There is a monster lurking in the castle.");
    delay(0.5);
    delay_print("Remember, when you've saved the princess, go back to where you started.");
    delay(0.5);
    delay_print("Now, just start your adventure!");cout << endl;
    delay(1);
    delay_print("Entering the castle.", false);
    delay(1); cout << ".";delay(1); cout << ".";delay(1); cout << "." << endl << endl;
    delay(1);
    cout << "-------------------------------------------" << endl;
    delay_print("Welcome to " + player.current->name + ".");
    delay(1);
    delay_print("Searching.", false);
    delay(1);cout << ".";delay(1);cout << ".";delay(1);cout << "." << endl;
    cout << endl;
    print_exit();
    cout << "Tips: You can input \"go (exit)\" to exit." << endl;
    delay(1);
}

void Game::move(const Movement & move_to){
    cout << endl; delay(1);
    // update current
    _move_to(move_to);
    cout << "-------------------------------------------" << endl;
    delay_print("Welcome to " + player.current->name + ".");
    delay(1);
    delay_print("Searching.", false);
    delay(1); cout << "."; delay(1); cout << "."; delay(1); cout << "." << endl;
    cout << endl;
    // judge game state
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
        delay(0.5);
    }
    print_exit();
}

void Game::print_exit(){
    string exits;
    short exit_count = 0;
    if(player.current->west){
        exits += " west";
        ++exit_count;
    }
    if(player.current->south){
        exits += " south";
        ++exit_count;
    }
    if(player.current->east){
        exits += " east";
        ++exit_count;
    }
    if(player.current->north){
        exits += " north";
        ++exit_count;
    }
    delay(0.5);
    cout << "There are " << exit_count << " exits:" << exits << "." << endl;
    delay(0.5);
}

void Game::win(){
    delay_print("You escaped the castle with the princess.");
    delay(1);
    cout << endl;
    cout << "You win!" << endl;
    game_state = false;
}

void Game::lose(){
    delay_print("Unfortunately, you ran into a monster.");
    delay_print("Despite your efforts, the monster tore you to pieces.");
    if(player.has_princess) delay_print("The princess was taken back to her room.");
    delay(1);
    cout << endl;
    cout << "You lose!" << endl;
    game_state = false;
}

void Game::find_princess(){
    delay_print("You have find the princess!");
    player.has_princess = true;
    delay(0.25);
    cout << "Princess: "; delay(0.25);
    delay_print("Oh my warrior, have you come to save me?"); delay(0.25);
    cout << player.name << ": "; delay(0.25);
    delay_print("Yes, princess. Please come out with me."); delay(1);
    cout << "Tips: The princess has joined your team." << endl; delay(0.5); cout << endl;
    delay_print("Now! Run! Get out of here!"); delay(0.5);
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

void Game::choose_level()
{
    delay_print("There are 3 levels: 1, 2, 3."); delay(0.5);
    delay_print("Enter your choise:", false);
    string choise;
    getline(cin, choise);
    while(choise.length()>1 || choise[0] > '3' || choise[0] < '1'){
        cout << "Invaild level!" << endl;
        cout << "Enter your choise:";
        getline(cin, choise);
    }
    cout << endl;
    switch (choise[0])
    {
    case '1':
        init_easy();
        break;
    case '2':
        init_medium();
        break;
    case '3':
        init_hard();
        break;
    default:
        break;
    }
}

void Game::init_easy()
{
    // init room
    room_list.clear();
// game map:
//                              room_1 -- princess
//                                |         |
//                              lobby -- room_2(M)
    // create room
    room_list.emplace_back("Lobby", false, false, true);
    room_list.emplace_back("Garden", false, false, false);
    room_list.emplace_back("Blood Room", true, false, false);
    room_list.emplace_back("Princess's Room", false, true, false);
    // set neighbor
    room_list[0].set_neighbor(nullptr, nullptr, &room_list[2], &room_list[1]);
    room_list[1].set_neighbor(nullptr, &room_list[0], &room_list[3], nullptr);
    room_list[2].set_neighbor(&room_list[0], nullptr, nullptr, &room_list[3]);
    room_list[3].set_neighbor(&room_list[1], &room_list[2], nullptr, nullptr);
    delay_print("You have choose level 1, good luck!");
}
void Game::init_medium()
{
    // init room
    room_list.clear();
// game map:
//                              room_3 -- room_4 -- room_5
//                                |         |         |
//                   room_1 -- lobby -- room_2(M) -- princess
    // create room
    room_list.emplace_back("Lobby", false, false, true);
    room_list.emplace_back("Balcony", false, false, false);
    room_list.emplace_back("Blood Room", true, false, false);
    room_list.emplace_back("Broken Room", false, false, false);
    room_list.emplace_back("Corridor", false, false, false);
    room_list.emplace_back("Garden", false, false, false);
    room_list.emplace_back("princess's room", false, true, false);
    // set neighbor
    room_list[0].set_neighbor(&room_list[1], nullptr, &room_list[2], &room_list[3]);
    room_list[1].set_neighbor(nullptr, nullptr, &room_list[0], nullptr);
    room_list[2].set_neighbor(&room_list[0], nullptr, &room_list[6], &room_list[4]);
    room_list[3].set_neighbor(nullptr, &room_list[0], &room_list[4], nullptr);
    room_list[4].set_neighbor(&room_list[3], &room_list[2], &room_list[5], nullptr);
    room_list[5].set_neighbor(&room_list[4], &room_list[6], nullptr, nullptr);
    room_list[6].set_neighbor(&room_list[2], nullptr, nullptr, &room_list[5]);
    delay_print("You have choose level 2, good luck!");
}
void Game::init_hard()
{
    // init room
    room_list.clear();
// game map:
//                              room_9 -- princess
//                                |         |
//                              room_7 -- room_8(M)
//                                |         |
//                              room_3 -- room_6
//                                |         |
//         room_4  -- room_1 -- lobby -- room_2 -- room_5
    // create room
    room_list.emplace_back("Lobby", false, false, true);
    room_list.emplace_back("Corridor", false, false, false);
    room_list.emplace_back("Corridor", false, false, false);
    room_list.emplace_back("Corridor", false, false, false);
    room_list.emplace_back("Balcony", false, false, false);
    room_list.emplace_back("Balcony", false, false, false);
    room_list.emplace_back("Broken Room", false, false, false);
    room_list.emplace_back("Corridor", false, false, false);
    room_list.emplace_back("Blood Room", true, false, false);
    room_list.emplace_back("Garden", false, false, false);
    room_list.emplace_back("Princess's Room", false, true, false);
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
    delay_print("You have choose level 3, good luck!");
}