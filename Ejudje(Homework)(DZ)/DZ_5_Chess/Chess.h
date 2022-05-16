typedef struct income_inf_about_figure{
    char * chess_name;
    char * origin_pos;
    char * final_pos;
}coordinates;

class Figure{
public:
    virtual bool move(coordinates) const = 0;
    virtual ~Figure(){};
};

class Quenn: public Figure{
public:
    bool move(coordinates) const;
    ~Quenn(){};
};

class King: public Figure{
public:
    bool move(coordinates) const;
    ~King(){};
};

class Elephant: public Figure{
public:
    bool move(coordinates) const; 
    ~Elephant(){};   
};

class Horse: public Figure{
public:
    bool move(coordinates) const; 
    ~Horse(){};   
};

class Rook: public Figure{
public:
    bool move(coordinates) const;   
    ~Rook(){}; 
};

class ChessChecker{
    enum{
        K = 0,
        Q = 1,
        N = 2,
        B = 3,
        R = 4,
        FIRST_SYMBOl = 0,
        STD_LENGTH = 100,
        AMOUNT_OF_FIGURES = 5,
        LENGTH_POS = 2
    };
    
    char * command;
    Figure * figures[ChessChecker::AMOUNT_OF_FIGURES];
public:
    ChessChecker();
    virtual ~ChessChecker();

    void read_command();
    char * get_command() const;
    int check_coordinates(coordinates) const;
    Figure * get_figure(int) const;
};

class Parser{
public:
    coordinates parse_command(char *) const;
};