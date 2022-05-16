#include <iostream>
#include <cstring>
#include <unistd.h>

using namespace std;

class PlayerException{
    enum{
        STD_LENGTH = 100,
        AMOUNT_OF_ARGS_2 = 3,
        AMOUNT_OF_ARGS_1 = 2
    };
    char name_team[STD_LENGTH];
    char name_error[STD_LENGTH];
    int number_of_player;
    int amount_of_args;
public:
    PlayerException(const char *, const char *, int,int)throw();

    void what() const throw();
};

void PlayerException::what()const throw(){
    if (amount_of_args == AMOUNT_OF_ARGS_1)
        cerr << "Exception: " << name_error << " in team " << name_team << endl;
    else
        cerr << "Exception: " << name_error << " in team " << name_team << " Error number: " << number_of_player << endl;
}

PlayerException::PlayerException(const char * name_error, const char * name_team, int number_of_player,int amount_of_args)throw(){
    strcpy(this->name_team, name_team);
    strcpy(this->name_error, name_error);
    this->number_of_player = number_of_player;
    this->amount_of_args = amount_of_args;
}

class Player{
    enum{
        AMOUNT_OF_ARGS_2 = 3,
        AMOUNT_OF_ARGS_1 = 2,
        Zenit_num = 0,
        Cska_num = 1
    };
    int number_of_player;
    char * name_team;
    static int amount_of_players_Cska;
    static int amount_of_players_Zenit;
    static int * Cska_numbers;
    static int * Zenit_numbers;

    bool array_find(int *,int,int);
    void push_to_array(int,int,int&);
    void copy_array(int *, int *,int);
    void erase_from_array(int,int,int&);
    void copy_array_without_elem(int *,int*,int,int);

public:
    Player(const char *,int);
    ~Player();

    void Print() const;
    static void Print_teams();
};

void Player::copy_array_without_elem(int * dest, int * src, int number, int amount){
    int pos = 0;
    for (int i = 0; i<amount; i++){
        if (src[i] == number)
            continue;
        dest[pos] = src[i];
        pos++;
    }
}

void Player::erase_from_array(int num, int number_of_player, int & amount_of_players){
    if (num == Zenit_num){
        int * new_number_of_team = new int[amount_of_players - 1];
        copy_array_without_elem(new_number_of_team,Zenit_numbers,number_of_player,amount_of_players);
        delete[] Zenit_numbers;
        Zenit_numbers = new_number_of_team;
    }
    else if (num == Cska_num){
        int * new_number_of_team = new int[amount_of_players - 1];
        copy_array_without_elem(new_number_of_team,Cska_numbers,number_of_player,amount_of_players);
        delete[] Cska_numbers;
        Cska_numbers = new_number_of_team;
    }
    amount_of_players--;
}

void Player::copy_array(int * dest, int * src, int amount){
    for (int i = 0; i<amount; i++)
        dest[i] = src[i];
}

void Player::push_to_array(int num, int number, int & amount_of_players){
    if (num == Zenit_num){
        int * new_number_of_team = new int[amount_of_players + 1];
        copy_array(new_number_of_team,Zenit_numbers,amount_of_players);
        delete[] Zenit_numbers;
        Zenit_numbers = new_number_of_team;
        Zenit_numbers[amount_of_players] = number;
    }
    else if (num == Cska_num){
        int * new_number_of_team = new int[amount_of_players + 1];
        copy_array(new_number_of_team,Cska_numbers,amount_of_players);
        delete[] Cska_numbers;
        Cska_numbers = new_number_of_team;
        Cska_numbers[amount_of_players] = number;
    }
    amount_of_players++;
}

bool Player::array_find(int * numbers_of_team, int number, int amount_of_players){
    for (int i = 0; i<amount_of_players; i++)
            if (numbers_of_team[i] == number)
                return true;
    return false;
}

void Player::Print() const{
    cout << name_team << " " << number_of_player << endl;
}

void Player::Print_teams(){
    if (amount_of_players_Zenit != 0){
        cout << "Zenit: ";
        for (int i = 0; i<amount_of_players_Zenit; i++)
            cout << Zenit_numbers[i] << " ";
        cout << endl;
    }
    if (amount_of_players_Cska != 0){
        cout << "CSKA: ";
        for (int i = 0; i<amount_of_players_Cska; i++)
            cout << Cska_numbers[i] << " ";
        cout << endl;
    }
}

Player::Player(const char * name_team, int number_of_player){
    if (strcmp(name_team,"Zenit") == 0){
        if (number_of_player < 1){
            PlayerException new_player_exception("Wrong number","Zenit",number_of_player,AMOUNT_OF_ARGS_2);
            throw new_player_exception;
        }
        if (array_find(Zenit_numbers,number_of_player,amount_of_players_Zenit)){
            PlayerException new_player_exception("Double number","Zenit",number_of_player,AMOUNT_OF_ARGS_2);
            throw new_player_exception;
        }
        push_to_array(Zenit_num,number_of_player,amount_of_players_Zenit);
        if (amount_of_players_Zenit > 11){
            PlayerException new_player_exception("Too many players","Zenit",0,AMOUNT_OF_ARGS_1);
            throw new_player_exception;
        }
        this->number_of_player = number_of_player;
        this->name_team = new char[strlen(name_team) + 1];
        strcpy(this->name_team,name_team);
    }
    else if (strcmp(name_team,"CSKA") == 0){
        if (number_of_player < 1){
            PlayerException new_player_exception("Wrong number","CSKA",number_of_player,AMOUNT_OF_ARGS_2);
            throw new_player_exception;
        }
        if (array_find(Cska_numbers,number_of_player,amount_of_players_Cska)){
            PlayerException new_player_exception("Double number","CSKA",number_of_player,AMOUNT_OF_ARGS_2);
            throw new_player_exception;
        }
        push_to_array(Cska_num,number_of_player,amount_of_players_Cska);
        if (amount_of_players_Cska > 11){
            PlayerException new_player_exception("Too many players","CSKA",0,AMOUNT_OF_ARGS_1);
            throw new_player_exception;
        }
        this->number_of_player = number_of_player;
        this->name_team = new char[strlen(name_team) + 1];
        strcpy(this->name_team,name_team);
    }
    else{
        PlayerException new_player_exception("Wrong name",name_team,0,AMOUNT_OF_ARGS_1);
        throw new_player_exception;
    }
}

Player::~Player(){
    if (strcmp(name_team,"Zenit") == 0){
        erase_from_array(Zenit_num,number_of_player,amount_of_players_Zenit);
        delete[] name_team;
    }
    else if (strcmp(name_team,"CSKA") == 0){
        erase_from_array(Cska_num,number_of_player,amount_of_players_Cska);
        delete[] name_team;
    }
}

int Player::amount_of_players_Cska = 0;
int Player::amount_of_players_Zenit = 0;
int * Player::Cska_numbers = nullptr;
int * Player::Zenit_numbers = nullptr;

int main(){
    try{
        test_players();
    }
    catch(const PlayerException & obj_player_exception){
        obj_player_exception.what();
    }
    return 0;
}