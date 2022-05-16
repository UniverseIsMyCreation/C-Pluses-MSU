#include <iostream>
#include "Vec_operators_exceptions.h"

using namespace std;

void error()
{
    Vec v1(3), v2(5), v3(4);

    v3 = v1+v2;

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