#include <vector>
#include <cstring>
#include <set>
#include <iostream>

using namespace std;

class ExceptionSQL{
    string error;
    int mode;
public:
    ExceptionSQL(string,int);
    void PrintError() const;
};

class SQL_interp{
    vector<vector<string>> table;
    vector<string> column_names;
    vector<string> cur_values_columns;
    vector<string> cur_values_names;
    string command;
    string cur_name;
    string extra_symbols_K;
    string special_symbols;
    int count_command;
    int mode_command_sql;// which command we run
    char c;// current symbol in lex
    bool switched;// switch for gc()
    bool created;// if table is created it's true
    bool finished;// if we meet END then true
    int deep;

    void STATE_S();
    void STATE_A();
    void STATE_B();
    void STATE_O();
    void STATE_P();
    void STATE_Z();
    void STATE_E();
    void STATE_V();
    void STATE_K();
    void STATE_W();
    void STATE_D();
    void STATE_C();
    void STATE_L();
    void STATE_G();

    bool check_lex(string);
    void gc();

    string get_wrong_word();
    void check_values();
public:
    SQL_interp();
    
    bool get_query();
    void parse_query();
    void run_query();
    void print_db() const;
};