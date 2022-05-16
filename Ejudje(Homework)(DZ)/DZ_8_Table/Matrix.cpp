#include <iostream>
#include <vector>
#include <cstring>
#include "Matrix.h"

using namespace std;

MatrixError::MatrixError(const char * new_error){
    name_error = new char[strlen(new_error) + 1];
    strcpy(name_error, new_error);
}

MatrixError::~MatrixError(){
    delete[] name_error;
}

vector<vector<int>> Matrix::GetTransMatr(int rows,int columns){
    vector<vector<int>> trans_matr;
    trans_matr.clear();
    vector<int> add_vec;
    add_vec.clear();
    for (int j = 0; j<columns; j++){
        for(int i = 0; i<rows; i++){
            add_vec.push_back(matr[i][j]);
        }
        trans_matr.push_back(add_vec);
        add_vec.clear();
    }
    return trans_matr;
}

int Matrix::ConvertToInt(char * str) const{
    int sign = Matrix::__PLUS__;
    int i = 0;
    if (str[0] == '-'){
        sign = Matrix::__MINUS__;
        i = 1;
    }
    else if (str[0] == '+'){
        sign = Matrix::__PLUS__;
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

void Matrix::Operation(int argc, char ** argv){
    if (argc < 2 || argc > 4)
        throw MatrixError("Error in amount args");
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
    if (command.command_name == "-irb"){
        if (command.amount_of_args < 2)
            throw MatrixError("Error in amount args");
        else if (numbers.size() < (numbers[0] * numbers[1] + numbers[1] + 2))
            throw MatrixError("Error in income vector(operation)");
        else if (command.arg1 < 1 || command.arg1 > numbers[0])
            throw MatrixError("Error in args");
        vector<int> copy;
        copy.clear();
        for (int i = 2 + numbers[0] * numbers[1]; i < numbers.size(); i++)
            copy.push_back(numbers[i]);
        auto iter = matr.begin() + command.arg1 - 1;
        matr.insert(iter,copy);
    }
    else if (command.command_name == "-ira"){
        if (command.amount_of_args < 2)
            throw MatrixError("Error in amount args");
        else if (numbers.size() < (numbers[0] * numbers[1] + numbers[1] + 2))
            throw MatrixError("Error in income vector(operation)");
        else if (command.arg1 < 1 || command.arg1 > numbers[0])
            throw MatrixError("Error in args");
        vector<int> copy;
        copy.clear();
        for (int i = 2 + numbers[0] * numbers[1]; i < numbers.size(); i++)
            copy.push_back(numbers[i]);
        auto iter = matr.begin() + command.arg1;
        matr.insert(iter,copy);
    }
    else if (command.command_name == "-icb"){
        if (command.amount_of_args < 2)
            throw MatrixError("Error in amount args");
        else if (numbers.size() < (numbers[0] * numbers[1] + numbers[0] + 2))
            throw MatrixError("Error in income vector(operation)");
        else if (command.arg1 < 1 || command.arg1 > numbers[1])
            throw MatrixError("Error in args");
        vector<int> copy;
        copy.clear();
        matr = GetTransMatr(numbers[0],numbers[1]);
        for (int i = 2 + numbers[0] * numbers[1]; i < numbers.size(); i++)
            copy.push_back(numbers[i]);
        auto iter = matr.begin() + command.arg1 - 1;
        matr.insert(iter,copy);
        matr = GetTransMatr(numbers[1] + 1,numbers[0]);
    }
    else if (command.command_name == "-ica"){
        if (command.amount_of_args < 2)
            throw MatrixError("Error in amount args");
        else if (numbers.size() < (numbers[0] * numbers[1] + numbers[0] + 2))
            throw MatrixError("Error in income vector(operation)");
        else if (command.arg1 < 1 || command.arg1 > numbers[1])
            throw MatrixError("Error in args");
        vector<int> copy;
        copy.clear();
        matr = GetTransMatr(numbers[0],numbers[1]);
        for (int i = 2 + numbers[0] * numbers[1]; i < numbers.size(); i++)
            copy.push_back(numbers[i]);
        auto iter = matr.begin() + command.arg1;
        matr.insert(iter,copy);
        matr = GetTransMatr(numbers[1] + 1,numbers[0]);
    }
    else if (command.command_name == "-dr"){
        if (command.amount_of_args < 2)
            throw MatrixError("Error in amount args");
        else if (command.arg1 < 1 || command.arg1 > numbers[0])
            throw MatrixError("Error in args");
        auto iter = matr.begin() + command.arg1 - 1;
        matr.erase(iter);
    }
    else if (command.command_name == "-dc"){
        if (command.amount_of_args < 2)
            throw MatrixError("Error in amount args");
        else if (command.arg1 < 1 || command.arg1 > numbers[1])
            throw MatrixError("Error in args");
        matr = GetTransMatr(numbers[0],numbers[1]);
        auto iter = matr.begin() + command.arg1 - 1;
        matr.erase(iter);
        matr = GetTransMatr(numbers[1] - 1,numbers[0]);
    }
    else if (command.command_name == "-sr"){
        if (command.amount_of_args < 3)
            throw MatrixError("Error in amount args");
        else if (command.arg1 < 1 || command.arg1 > numbers[0])
            throw MatrixError("Error in args");
        else if (command.arg2 < 1 || command.arg2 > numbers[0])
            throw MatrixError("Error in args");
        vector<int> copy = matr[command.arg1-1];
        matr[command.arg1-1] = matr[command.arg2-1];
        matr[command.arg2-1] = copy;
    }
    else if (command.command_name == "-sc"){
        if (command.amount_of_args < 3)
            throw MatrixError("Error in amount args");
        else if (command.arg1 < 1 || command.arg1 > numbers[1])
            throw MatrixError("Error in args");
        else if (command.arg2 < 1 || command.arg2 > numbers[1])
            throw MatrixError("Error in args");
        matr = GetTransMatr(numbers[0],numbers[1]);
        vector<int> copy = matr[command.arg1-1];
        matr[command.arg1-1] = matr[command.arg2-1];
        matr[command.arg2-1] = copy;
        matr = GetTransMatr(numbers[1],numbers[0]);
    }
    else if (command.command_name == "-t")
        matr = GetTransMatr(numbers[0],numbers[1]);
    else 
        throw MatrixError("Error in command");
}

void Matrix::PrintMatrix() const throw(){
    int pos = 0;
    for (auto iter = matr.begin(); iter != matr.end(); iter++){
        for(auto iter_inner = matr[pos].begin(); iter_inner != matr[pos].end(); iter_inner++){
            if (iter_inner == matr[pos].end() - 1)
                cout << *iter_inner;
            else
                cout << *iter_inner << " ";
        }
        pos++;
        cout << endl;
    }
}

void Matrix::BuildMatrix(){
    if ((numbers.size() - 2) < (numbers[0] * numbers[1]))
        throw MatrixError("Error in income vector");
    vector<int> copy;
    copy.clear();
    int pos = 2;
    for (int i = 0; i<numbers[0]; i++){
        for(int j = 0; j<numbers[1]; j++){
            copy.push_back(numbers[pos]);
            pos++;
        }
        matr.push_back(copy);
        copy.clear();
    }
}

void Matrix::ClearMatrix() throw(){
    for (auto iter = matr.begin(); iter != matr.end(); iter++)
        iter->clear();
    matr.clear();
}

void Matrix::ReadMatrix() throw(){
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