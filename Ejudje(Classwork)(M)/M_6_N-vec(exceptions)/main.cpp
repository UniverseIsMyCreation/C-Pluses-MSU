#include <iostream>
#include "Vec_exceptions.h"

using namespace std;

void error()
{
    double y1[3] = {1,2,3};
    double y2[5] = {2,1,0,5,7};
    Vec x(-3, y1), y(5, y2), z(4);
    Vec u = x;
    y.print();
    x.print();
    z.print();
    u.print();
}

int main()
{
    try
    {
        error();
    }
    catch(const Vec_excpeption & obj_excp_caught)
    {
        obj_excp_caught.what();
    }
    catch(...)
    {
        cerr << "Exception: unknown error" << endl;
    }
    return 0;
}