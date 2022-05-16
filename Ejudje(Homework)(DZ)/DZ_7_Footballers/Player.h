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