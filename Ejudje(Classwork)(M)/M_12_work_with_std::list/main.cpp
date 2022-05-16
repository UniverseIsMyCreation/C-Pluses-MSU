#include <iostream>
#include "List.h"

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