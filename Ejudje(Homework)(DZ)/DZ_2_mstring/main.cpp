#include <iostream>
#include "mstring.h"

using namespace std;

int main()
{
    mstring s ("hello world");
    mstring s1 = s;
    mstring s2;
    cout << s.length() << endl;
    if (s2.isempty())
    {
        s.add('!');
        s2.add("HI!");
        s.print();
        s2.print();
    }
    if (!s1.isempty())
    {
        s1.insert(' ',5);
        s1.insert('m',6);
        s1.insert('y',7);
        s.insert(" my",5);
        s.print();
        s1.print();
    }
    s.del(9);
    s1.del(5,7);
    s.print();
    s1.print();
    return 0;
}