#include <iostream>
#include <vector>
#include <cstring>
#include <set>
using namespace std;

class ExceptionSQL{
    string error;
    int mode;
public:
    ExceptionSQL(string,int);
    void PrintError() const;
};

ExceptionSQL::ExceptionSQL(string error, int mode){
    this->error = error;
    this->mode = mode;
}

void ExceptionSQL::PrintError() const{
    switch(mode){
        case 1:
            cerr << "Exception: No tables" << endl;
            break;
        case 2:
            cerr << "Exception: Wrong command " << error << endl;
            break;
        case 3:
            cerr << "Exception: No tables" << endl;
            break;
        case 4:
            cerr << "Exception: INSERT Error in " << error << " column" << endl;
            break;
        case 5:
            cerr << "Exception: INSERT Error in " << error << endl;
            break;
    }
}

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

void SQL_interp::check_values(){
    set<string> copies;
    copies.clear();
    for(auto iter = cur_values_columns.begin(); iter != cur_values_columns.end(); iter++){
        if (copies.find(*iter) == copies.end())
            copies.insert(*iter);
        else
            throw ExceptionSQL(*iter,4);
    }
}

string SQL_interp::get_wrong_word(){
    string error_word = "";
    while ((command[count_command] != ' ') && (count_command > 0))
        count_command--;
    if (count_command != 0)
        count_command++;
    while (true){
        if (special_symbols.find(command[count_command]) != -1)
            break;
        error_word.push_back(command[count_command]);
        count_command++;
    }
    return error_word;
}

SQL_interp::SQL_interp(){
    table.clear();
    created = false;
    finished = false;
    column_names.clear();
    deep = 0;
    extra_symbols_K = "!@#$%^&*()., ";
    special_symbols = " \n(,\")";
}

bool SQL_interp::get_query(){
    if (finished)
        return false;
    command = "";
    cur_values_columns.clear();
    cur_values_names.clear();
    switched = true;
    char symbol;
    while(true){
        cin.get(symbol);
        command.push_back(symbol);
        if (symbol == '\n')
            break;
    }
    return (!finished);
}

void SQL_interp::parse_query(){
    STATE_S();
}

void SQL_interp::print_db() const{
    for (auto iter = column_names.begin(); iter != column_names.end(); iter++)
        cout << *iter << " ";
    cout << endl;
    for (int i = 0; i < deep; i++){
        for (int j = 0; j < table.size(); j++)
            cout << table[j][i] << " ";
        cout << endl;
    }
}

void SQL_interp::run_query(){
    check_values();
    if (mode_command_sql == 1){
        vector<string> tmp;
        tmp.clear();
        for(auto iter = cur_values_columns.begin(); iter != cur_values_columns.end(); iter++){
            column_names.push_back(*iter);
            table.push_back(tmp);
        }
    }
    else if (mode_command_sql == 2){
        for(auto iter = cur_values_columns.begin(); iter != cur_values_columns.end(); iter++){
            bool found = false;
            for(auto iter_table = column_names.begin(); iter_table != column_names.end(); iter_table++){
                if (*iter_table == *iter)
                    found = true;
            }
            if (!found)
                throw ExceptionSQL(*iter,4);
        }
        if (cur_values_columns.size() != cur_values_names.size()){
            if (cur_values_columns.size() < cur_values_names.size()){
                auto iter = cur_values_names.begin();
                iter += cur_values_columns.size();
                throw ExceptionSQL(*iter,5);
            }
            else if (cur_values_columns.size() > cur_values_names.size()){
                auto iter = cur_values_columns.begin();
                iter += cur_values_names.size();
                throw ExceptionSQL(*iter,4);
            }
        }
        auto iter_table = column_names.begin();
        int counter = 0;
        while(iter_table != column_names.end()){
            auto iter_columns = cur_values_columns.begin();
            auto iter_names = cur_values_names.begin();
            while (*iter_table != *iter_columns){
                iter_columns++;
                iter_names++;
            }
            table[counter].push_back(*iter_names);
            iter_table++;
            counter++;
        }
    }
    else if (mode_command_sql == 3)
        finished = true;
}

void SQL_interp::gc(){
    if (switched){
        count_command = 0;
        switched = false;
    }
    else
        count_command++;
    c = command[count_command];
}

bool SQL_interp::check_lex(string lex){
    gc();
    for(int i = 0; i < lex.size(); i++){
        if(c == lex[i])
            gc();
        else{
            while(i >= 0){
                count_command--;
                i--;
            }
            return false;
        }
    }
    count_command--;
    return true;
}

void SQL_interp::STATE_S(){
    if (check_lex("CREATE")){
        created = true;
        mode_command_sql = 1;
        STATE_P();
        STATE_A();
    }
    else if (check_lex("INSERT")){
        if (!created)
            throw ExceptionSQL("",3);
        mode_command_sql = 2;
        deep++;
        STATE_P();
        STATE_B();
    }
    else if (check_lex("END")){
        mode_command_sql = 3;
        return;
    }
    else
        throw ExceptionSQL(get_wrong_word(),2);
}

void SQL_interp::STATE_A(){
    //cout << "A" << endl;
    if (check_lex("TABLE")){
        STATE_P();
        STATE_D();
    }
    else
        throw ExceptionSQL(get_wrong_word(),2);
}

void SQL_interp::STATE_B(){
    //cout << "B" << endl;
    if (check_lex("INTO")){
        STATE_P();
        STATE_E();
    }
    else
        throw ExceptionSQL(get_wrong_word(),2);
}

void SQL_interp::STATE_O(){
    //cout << "O" << endl;
    if (check_lex("(")){
        STATE_G();
        cur_name.erase();
        STATE_W();
        if (!cur_name.empty())
            cur_values_columns.push_back(cur_name);
        count_command--;
        STATE_G();
        STATE_Z();
        STATE_G();
        if (!check_lex(")"))
            throw ExceptionSQL(get_wrong_word(),2);
    }
    else
        throw ExceptionSQL(get_wrong_word(),2);
}

void SQL_interp::STATE_P(){
    //cout << "P" << endl;
    if (check_lex(" "))
        STATE_G();
    else
        throw ExceptionSQL(get_wrong_word(),2);
}

void SQL_interp::STATE_D(){
    //cout << "D" << endl;
    if (check_lex("tbl")){
        STATE_G();
        STATE_O();
    }
    else
        throw ExceptionSQL(get_wrong_word(),2);
}

void SQL_interp::STATE_Z(){
    //cout << "Z" << endl;
    if (check_lex(",")){
        STATE_G();
        cur_name.erase();
        STATE_W();
        cur_values_columns.push_back(cur_name);
        count_command--;
        STATE_G();
        STATE_Z();
    }
}

void SQL_interp::STATE_E(){
    //cout << "E" << endl;
    if (check_lex("tbl")){
        STATE_G();
        STATE_O();
        STATE_G();
        STATE_V();
    }
    else
        throw ExceptionSQL(get_wrong_word(),2);
}

void SQL_interp::STATE_V(){
    //cout << "V" << endl;
    if (check_lex("VALUES")){
        STATE_G();
        STATE_C();
    }
    else
        throw ExceptionSQL(get_wrong_word(),2);
}

void SQL_interp::STATE_K(){
    //cout << "K" << endl;
    gc();
    if ((c>= '0' && c <= '9') || (c>= 'a' && c <= 'z') || (c>= 'A' && c <= 'Z') || (extra_symbols_K.find(c) != -1)){
        cur_name.push_back(c);
        STATE_K();
    }
}

void SQL_interp::STATE_W(){
    //cout << "W" << endl;
    gc();
    if ((c>= '0' && c <= '9') || (c>= 'a' && c <= 'z') || (c>= 'A' && c <= 'Z')){
        cur_name.push_back(c);
        STATE_W();
    }
}

void SQL_interp::STATE_C(){
    //cout << "C" << endl;
    if (check_lex("(")){
        STATE_G();
        if (check_lex("\"")){
            cur_name.erase();
            STATE_K();
            cur_values_names.push_back(cur_name);
            count_command--;
            STATE_L();
            if (check_lex("\"")){
                STATE_G();
                if (!check_lex(")"))
                    throw "log_err_4";
            }
            else
                throw "log_err_3";
        }
        else
            throw "log_err_2";
    }
    else throw "log_err_1";
}

void SQL_interp::STATE_L(){
    //cout << "L" << endl;
    if (check_lex("\",")){
        STATE_G();
        if (check_lex("\"")){
            cur_name.erase();
            STATE_K();
            cur_values_names.push_back(cur_name);
            count_command--;
            STATE_L();
        }
        else
            throw "log_err_2";
    }
}

void SQL_interp::STATE_G(){
    //cout << "G" << endl;
    if (check_lex(" "))
        STATE_G();
}

int main(){           
    try{                
        SQL_interp sql;   
        while(sql.get_query()){ 
            sql.parse_query();   
            sql.run_query();   
        }                 
        sql.print_db();   
    }          
    catch(ExceptionSQL & err_obj){
        err_obj.PrintError();
    }  
    catch(const char * err){
        cerr << err << endl;
    }           
    return 0;         
}