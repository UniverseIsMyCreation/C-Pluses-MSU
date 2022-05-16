#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

typedef struct income_inf_about_figure{
    char * chess_name;
    char * origin_pos;
    char * final_pos;
}coordinates;

char * strtoken(char ** strtoken, char token){
    int pos = 0;
    while ((*strtoken)[pos] == token){
        if ((*strtoken)[pos] == '\0')
            return NULL; 
        pos++;
    }
    if ((*strtoken)[pos] == '\0')
        return NULL; 
    int length = pos;
    while((*strtoken)[pos] != token){
        if ((*strtoken)[pos] == '\0')
            break;
        pos++;
    }
    char * ret_strtoken = new char[pos - length];
    memcpy(ret_strtoken, (*strtoken) + length, pos - length);
    (*strtoken) += (pos + 1);
    ret_strtoken[pos - length] = '\0';
    return ret_strtoken;
}

//////////////////////////////////////////////////

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

bool Quenn::move(coordinates income_coordinates) const{
    int diagonal1 = abs(income_coordinates.origin_pos[0] - income_coordinates.final_pos[0]);
    int diagonal2 = abs(income_coordinates.origin_pos[1] - income_coordinates.final_pos[1]);
    if (diagonal2 == diagonal1)
        return true;
    if (income_coordinates.origin_pos[0] == income_coordinates.final_pos[0])
        return true;
    if (income_coordinates.origin_pos[1] == income_coordinates.final_pos[1])
        return true;
    return false;
}

class King: public Figure{
public:
    bool move(coordinates) const;
    ~King(){};
};

bool King::move(coordinates income_coordinates) const{
    if (abs(income_coordinates.final_pos[0] - income_coordinates.origin_pos[0]) > 1)
        return false;
    if (abs(income_coordinates.final_pos[1] - income_coordinates.origin_pos[1]) > 1)
        return false;
    return true;
}

class Elephant: public Figure{
public:
    bool move(coordinates) const; 
    ~Elephant(){};   
};

bool Elephant::move(coordinates income_coordinates) const{
    int diagonal1 = abs(income_coordinates.origin_pos[0] - income_coordinates.final_pos[0]);
    int diagonal2 = abs(income_coordinates.origin_pos[1] - income_coordinates.final_pos[1]);
    if (diagonal2 == diagonal1)
        return true;
    return false;
}

class Horse: public Figure{
public:
    bool move(coordinates) const; 
    ~Horse(){};   
};

bool Horse::move(coordinates income_coordinates) const{
    int letter_move = abs(income_coordinates.origin_pos[0] - income_coordinates.final_pos[0]);
    int digit_move = abs(income_coordinates.origin_pos[1] - income_coordinates.final_pos[1]);
    if ((letter_move == 2 && digit_move == 1) || (letter_move == 1 && digit_move == 2))
        return true;
    return false;
}

class Rook: public Figure{
public:
    bool move(coordinates) const;   
    ~Rook(){}; 
};

bool Rook::move(coordinates income_coordinates) const{
    if (income_coordinates.origin_pos[0] == income_coordinates.final_pos[0])
        return true;
    if (income_coordinates.origin_pos[1] == income_coordinates.final_pos[1])
        return true;
    return false;
}

//////////////////////////////////////////////////

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

int ChessChecker::check_coordinates(coordinates income_coordinates) const{
    if (strlen(income_coordinates.origin_pos) != ChessChecker::LENGTH_POS)
        throw "NO";
    if (strlen(income_coordinates.final_pos) != ChessChecker::LENGTH_POS)
        throw "NO";
    if (!(income_coordinates.origin_pos[0] >= 'a' && income_coordinates.origin_pos[0] <= 'h'))
        throw "NO";
    if (!(income_coordinates.origin_pos[1] >= '1' && income_coordinates.origin_pos[1] <= '8'))
        throw "NO";
    if (!(income_coordinates.final_pos[0] >= 'a' && income_coordinates.final_pos[0] <= 'h'))
        throw "NO";
    if (!(income_coordinates.final_pos[1] >= '1' && income_coordinates.final_pos[1] <= '8'))
        throw "NO";
    if (strcmp(income_coordinates.chess_name,"K") == 0)
        return ChessChecker::K;
    else if (strcmp(income_coordinates.chess_name,"Q") == 0)
        return ChessChecker::Q;
    else if (strcmp(income_coordinates.chess_name,"N") == 0)
        return ChessChecker::N;
    else if (strcmp(income_coordinates.chess_name,"B") == 0)
        return ChessChecker::B;
    else if (strcmp(income_coordinates.chess_name,"R") == 0)
        return ChessChecker::R;
    else
        throw "NO";
}

char * ChessChecker::get_command() const{
    return command;
}

Figure * ChessChecker::get_figure(int pos) const{
    return figures[pos];
}

void ChessChecker::read_command(){
    int length = 0;
    int bufsize = ChessChecker::STD_LENGTH;
    command = new char[bufsize];
    while (!cin.eof())
    {
        cin.get(command[length]);
        if (command[length] == '\n')
            break;
        length++;
        if (length >= bufsize)
        {
            bufsize += ChessChecker::STD_LENGTH;
            char * buf = new char[bufsize];
            memcpy(buf,command,length);
            delete [] command;
            command = buf;
        }
    }
    command[length] = '\0';
}

ChessChecker::ChessChecker(){
    command = nullptr;
    figures[ChessChecker::K] = new King();
    figures[ChessChecker::Q] = new Quenn();
    figures[ChessChecker::N] = new Horse();
    figures[ChessChecker::B] = new Elephant();
    figures[ChessChecker::R] = new Rook();
}

ChessChecker::~ChessChecker(){
    delete[] command;
    for (int i = 0; i < ChessChecker::R; i++){
        delete figures[i];
    }
}

//////////////////////////////////////////////////

class Parser{
public:
    coordinates parse_command(char *) const;
};

coordinates Parser::parse_command(char * command) const{
    coordinates income_coordinates;
    char * command_copy = command;
    income_coordinates.chess_name = strtoken(&command_copy,' ');
    if (income_coordinates.chess_name == NULL)
        throw "NO";
    income_coordinates.origin_pos = strtoken(&command_copy,' ');
    if (income_coordinates.origin_pos == NULL)
        throw "NO";
    income_coordinates.final_pos = strtoken(&command_copy,' ');
    if (income_coordinates.final_pos == NULL)
        throw "NO";
    char * rubbish = strtoken(&command_copy,' ');
    if (rubbish == NULL)
        return income_coordinates;
    else
        throw "NO";
}

int main()
{
    try{
        int num_of_figure;
        ChessChecker check_move;
        Parser parser;
        coordinates income_coordinates;
        check_move.read_command();
        income_coordinates = parser.parse_command(check_move.get_command());
        num_of_figure = check_move.check_coordinates(income_coordinates);
        if ((check_move.get_figure(num_of_figure))->move(income_coordinates))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    catch(const char * error){
        cout << error << endl;
    }
    catch(...){}
    return 0;
}