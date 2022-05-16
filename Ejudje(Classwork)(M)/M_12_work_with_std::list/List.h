#include <iostream>
#include <list>

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