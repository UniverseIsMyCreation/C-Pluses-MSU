#include <iostream>
#include "Player.h"

using namespace std;

int Player::amount_of_players_Cska = 0;
int Player::amount_of_players_Zenit = 0;
int * Player::Cska_numbers = nullptr;
int * Player::Zenit_numbers = nullptr;

/*void test_players()
{
    Player pl1("Zenit", 10);
    Player pl2("Zenit", 11);
    Player pl3("CSKA", 23);
    Player pl4("CSKA", 10);
    Player pl5("Zenit", 4);
    Player pl6("Zenit", 1);
    Player pl7("CSKA", 7);
    Player pl8("Zenit", 8);

    pl1.Print();
    pl3.Print();
    Player::Print_teams();
}*/

void test_players()
{
    Player pl1("Zenit", 10);
    Player pl2("Zenit", 11);
    Player pl3("CSKA", 23);
    Player pl4("CSKA", 10);
    Player pl5("Zenit", 4);
    Player pl6("Zenit", 1);
    Player pl7("CSKA", 7);
    Player pl8("Zenit", 4);

    pl1.Print();
    pl3.Print();
    Player::Print_teams();
}

int main(){
    try{
        test_players();
    }
    catch(const PlayerException & obj_player_exception){
        obj_player_exception.what();
    }
    return 0;
}