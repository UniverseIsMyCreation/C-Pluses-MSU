#include <iostream>
#include <list>
#include <cstring>

using namespace std;

typedef struct command{
    string command_name;
    int arg1;
    int arg2;
    int amount_of_args;
}Command;

class ListException{
public:
    ListException()throw(){}
};

class WorkWithList{
    enum{
        __PLUS__ = 1,
        __MINUS__ = -1
    };
    list<int> numbers;
    Command command;
    int ConvertToInt(char *) const;
public:
    void ReadList();
    void ReadExecuteCommand(int,char**);
    void PrintList() const;
};

bool Comparison(int a, int b){
    if (a > b)
        return true;
    return false;
}

int WorkWithList::ConvertToInt(char * str) const{
    int sign = WorkWithList::__PLUS__;
    int i = 0;
    if (str[0] == '-'){
        sign = WorkWithList::__MINUS__;
        i = 1;
    }
    else if (str[0] == '+'){
        sign = WorkWithList::__PLUS__;
        i = 1;
    }
    int number = 0;
    while(str[i] != '\0'){
        number = number * 10 + str[i] - '0';
        i++;
    }
    number *= sign;
    return number;
}

void WorkWithList::PrintList() const{
    for (auto iter = numbers.begin(); iter != numbers.end(); iter++)
        cout << *iter << " ";
    cout << endl;
}

void WorkWithList::ReadExecuteCommand(int argc, char ** argv){
    if (argc < 2 || argc > 4)
        throw ListException();
    command.command_name = argv[1];
    switch(argc){
        case 2:
            command.amount_of_args = 1;
            break;
        case 3:
            command.amount_of_args = 2;
            command.arg1 = ConvertToInt(argv[2]);
            break;
        case 4:
            command.amount_of_args = 3;
            command.arg1 = ConvertToInt(argv[2]);
            command.arg2 = ConvertToInt(argv[3]);
            break;
    }
    if (command.command_name == "-af"){
        if (command.amount_of_args < 2)
            throw ListException();
        numbers.push_front(command.arg1);
    }
    else if (command.command_name == "-ae"){
        if (command.amount_of_args < 2)
            throw ListException();
        numbers.push_back(command.arg1);
    }
    else if (command.command_name == "-ib"){
        if (command.amount_of_args < 3)
            throw ListException();
        for (auto iter = numbers.begin(); iter != numbers.end();iter++){
            if (*iter == command.arg2){
                numbers.insert(iter, command.arg1);
                break;
            }
        }
    }
    else if (command.command_name == "-ia"){
        if (command.amount_of_args < 3)
            throw ListException();
        for (auto iter = numbers.begin(); iter != numbers.end();iter++){
            if (*iter == command.arg2){
                iter++;
                numbers.insert(iter, command.arg1);
                break;
            }
        }
    }
    else if (command.command_name == "-d"){
        if (command.amount_of_args < 2)
            throw ListException();
        for (auto iter = numbers.begin(); iter != numbers.end();iter++){
            if (*iter == command.arg1){
                numbers.erase(iter);
                break;
            }
        }
    }
    else if (command.command_name == "-sa")
        numbers.sort();
    else if (command.command_name == "-sd")
        numbers.sort(Comparison);
    else if (command.command_name == "-mf"){
        auto iter = numbers.begin();
        auto iter_max = numbers.begin();
        int max = *iter;
        iter++;
        for (; iter != numbers.end();iter++){
            if (*iter > max){
                max = *iter;
                iter_max = iter;
            }
        }
        numbers.erase(iter_max);
        numbers.push_front(max);
    }
    else if (command.command_name == "-me"){
        auto iter = numbers.begin();
        auto iter_max = numbers.begin();
        int max = *iter;
        iter++;
        for (; iter != numbers.end();iter++){
            if (*iter > max){
                max = *iter;
                iter_max = iter;
            }
        }
        numbers.erase(iter_max);
        numbers.push_back(max);
    }
    else
        throw ListException();
}

void WorkWithList::ReadList(){
    numbers.clear();
    int num;
    char symbol;
    cin.get(symbol);
    if (symbol == ' ' || symbol == '\t'){
        while(symbol == ' ' || symbol == '\t')
            cin.get(symbol);
        if (symbol == '\n' || symbol == EOF)
            return;
        cin.putback(symbol);
    }
    else if (symbol == '\n' || symbol == EOF)
        return;
    else
        cin.putback(symbol);
    while (cin>>num){
        numbers.push_back(num);
        cin.get(symbol);
        while(symbol == ' ' || symbol == '\t')
            cin.get(symbol);
        if (symbol == '\n')
            return;
        else if (symbol == EOF)
            return;
        cin.putback(symbol);
    }
}

int main(int argc, char ** argv){
    WorkWithList income_lst;
    try{
        income_lst.ReadList();
        income_lst.ReadExecuteCommand(argc,argv);
        income_lst.PrintList();
    }
    catch(const ListException &){
        income_lst.PrintList();
    }
    return 0;
}