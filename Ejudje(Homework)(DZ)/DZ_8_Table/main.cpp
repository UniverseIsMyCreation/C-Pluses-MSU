#include <iostream>
#include "Matrix.h"

using namespace std;

int main(int argc, char ** argv){
    Matrix matrix;
    matrix.ClearMatrix();
    try{
        matrix.ReadMatrix();
        matrix.BuildMatrix();
        matrix.Operation(argc,argv);
    }
    catch(const MatrixError&){}
    matrix.PrintMatrix();
    return 0;
}