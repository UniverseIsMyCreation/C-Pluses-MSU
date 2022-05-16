#include <iostream>
#include "mstring_operators.h"

int main()
{
    mstring u("Hello"), v("world!"), w(v), z;

    std::cout << "u+v = " << u+" "+ v << std::endl;
    if (u == w)
            w = 2*u + w;
    else
            w = u + v*2;
    std::cout << "w = " << w << std::endl;
    w[10] = '?';
    std::cout << "w = " << w << std::endl;
    std::cin >> z;
    std::cout << "z = " << z << std::endl;
    return 0;
}