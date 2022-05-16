#include <iostream>
#include <vector>

using namespace std;

typedef struct command{
    string command_name;
    int arg1;
    int arg2;
    int amount_of_args;
}Command;

class MatrixError{
    char * name_error;
public:
    MatrixError(const char *);
    ~MatrixError();
};

class Matrix{  
    enum{
        __MINUS__ = -1,
        __PLUS__ = 1
    };
    
    vector<vector<int>> matr;
    vector<int> numbers;
    Command command;

    int ConvertToInt(char *) const;
    vector<vector<int>> GetTransMatr(int,int);
public:
    void ReadMatrix() throw();
    void ClearMatrix() throw();
    void BuildMatrix();
    void PrintMatrix() const throw();
    void Operation(int,char**);
};