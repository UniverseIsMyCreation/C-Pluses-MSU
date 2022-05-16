#include <iostream>
#include <cmath>

using namespace std;

int count_symbols(int arg)
{
    if (arg == 0)
    {
        return 1;
    }
    if (arg < 0)
    {
        arg *= (-1);
    }
    int ans = 0;
    while (arg > 0)
    {
        ans++;
        arg = arg / 10;
    }
    return ans;
}

int count_symbols(int* arr, int n = 1)
{
    int ans = 0;
    for(int i = 0; i<n; i++)
    {
        ans += count_symbols(arr[i]);
    }
    return ans;
}

int count_symbols(const char* str)
{
    int ans = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
        ans++;
    }
    return ans;
}

int count_symbols(double f, int n = 0)
{
    int ans = 0;
    f = floor(f);
    if (f == 0.0)
    {
        return (1 + n);
    }
    if (f < 0.0)
    {
        f *= (-1);
    }
    while (f > 1.0)
    {
        ans++;
        f = f / 10.0;
    } 
    return (ans + n);
}