#include <iostream>
#include "SQL_interprener.h"

using namespace std;

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