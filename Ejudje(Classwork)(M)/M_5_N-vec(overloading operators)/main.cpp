#include <iostream>
#include "Vec_operators.h"

using namespace std; 

int main()
{
    double y1[4] = {1,2,3,4};
    double y2[4] = {-2,1,3,-3};

    Vec u(4, y1), v(4, y2);
    Vec w(4);

    cout << "u = " << u << endl;
    cout << "v = " << v << endl;
    w = u = u;
    cout << "w = u = " << w << endl;
    w = 4.*u + v*3;
    cout << "w = 4.*u + v*3 = " << w << endl;
    w[2] = 3;
    w[0] = -1;
    cout << "w = " << w << endl;
        
    return 0;
}