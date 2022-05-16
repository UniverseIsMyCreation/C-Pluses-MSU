#include <iostream>
#include "Quotient.h"

using namespace std;

int Quotient::NOD(int a, int b) const
{
    if (a == 0 || b == 0)
    {
        return (a + b);
    }
    else if (a > b)
    {  
        a = a % b;
        return NOD(a,b);
    }
    else
    {
        b = b % a;
        return NOD(a,b);
    }
}

void Quotient::print() const
{
    if (denominator == 1)
    {
        cout << numerator << endl;
    }
    else
    {
        cout << numerator << '/' << denominator << endl;
    }
}

Quotient::Quotient(int up, int down)
{
    if (down == 0)
    {
        numerator = up;
        denominator = 1;
        return;
    }
    int sign = 1;
    int ans = 1;
    if (up < 0)
    {
        sign *= (-1);
        up *= (-1);
    }
    if (down < 0)
    {
        sign *= (-1);
        down *= (-1);
    }
    ans = NOD(up,down);
    numerator = sign * up/ans;
    denominator = (unsigned int)down/ans;
}

Quotient::Quotient(int up)
{
    denominator = 1;
    numerator = up;
}

Quotient::Quotient()
{
    numerator = 0;
    denominator = 1;
}