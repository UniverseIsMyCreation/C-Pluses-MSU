#include <iostream>
#include <cstring>
#define LENGTH 7
#define FIRST_SYMBOL 0
#define STR_LENGTH 101

char* left(char* str, int N)
{
    char* new_str = str;
    if (N <= 0)
    {
        while (*new_str != '\0')
        {
            new_str++;
        }
        return new_str;
    }
    while (N != 0)
    {
        if (*new_str == '\0')
        {
            return str;
        }
        new_str++;
        N--;
    }
    *new_str = '\0';
    return str;
}

unsigned long left(unsigned long num, int N)
{
    if (N <= 0)
    {
        return 0;
    }
    unsigned long temp = 0;
    unsigned long ans = 0;
    while (num > 0)
    {
        temp = (temp + (num%10)) * 10;
        num = num / 10;
    }
    temp = temp / 10;
    for (int i = 0; i < N; i++)
    {
        ans = (ans + (temp%10)) * 10;
        temp = temp / 10;
        if (temp == 0)
        {
            break;
        }
    }
    ans = ans / 10;
    return ans;
}

using namespace std;

int main()
{
    char option[LENGTH] = {};
    int N;
    cin.getline(option,STR_LENGTH);
    if (strcmp(option,"string") == 0)
    {
        char str[STR_LENGTH];
        cin.getline(str,STR_LENGTH);
        cin >> N;
        cout << left(str,N) << endl;
    }
    else
    {
        unsigned long num;
        cin >> num >> N;
        cout << left(num,N) << endl;
    }  
    return 0;
}