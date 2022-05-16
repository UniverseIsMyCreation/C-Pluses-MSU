#include <iostream>
#include "mstring_exceptions.h"

using namespace std;

void error()
{
    mstring s ("hello world");
    mstring s1 = s;
    mstring s2;
    if (!s1.isempty())
    {
        s1.insert(' ', 5);
        s1.insert('m',6);
        s1.insert('y',7);
        s.insert(" my",5);
        s.print();
        s1.print();
    }
    s.del(9);
    s1.del(-5,7);
    s.print();
    s1.print();
}

int main()
{
    try
    {
        error();
    }
    catch(const mstring_excpeption & obj_excp_caugth)
    {
        obj_excp_caugth.what();
    }
    catch(bad_alloc)
    {
        cerr << "problem in new incorrect parameter:bad_alloc" << endl;
    }
    return 0;
}