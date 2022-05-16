#include <iostream>
#include <cstring>
#include "mstring.h"

using namespace std;

mstring::mstring()
{
    m_string = new char;
    m_string[mstring::FIRST_SYMBOL] = '\0';
}
mstring::mstring(const mstring & new_str)
{
    m_string = new char[new_str.length() + 1];
    strcpy(m_string,new_str.m_string);
}
mstring::mstring(const char * str)
{
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    m_string = new char[++length];
    strcpy(m_string,str);
}
mstring::~mstring()
{
    delete [] m_string;
}

void mstring::step_right(int pos, int amount = 1)//one step right
{
    int len = length();
    amount--;
    m_string[len + 1 + amount] = '\0';
    while (len != pos)
    {
        m_string[len + amount] = m_string[len - 1];
        len--;
    }
}

void mstring::step_left(int pos, int amount = 1)//one step left
{
    amount--;
    while (m_string[pos] != '\0')
    {
        m_string[pos] = m_string[pos + 1 + amount];
        pos++;
    }
}

int mstring::length() const //string length
{
    int length_str = 0;
    while (m_string[length_str] != '\0')
    {
        length_str++;
    }
    return length_str;
}

bool mstring::isempty() const //check for empty string
{
    if (m_string[mstring::FIRST_SYMBOL] == '\0')
    {
        return true;
    }
    return false;
}

void mstring::add(char c)//add symbol to end of string
{
    char * new_str = new char[length() + 2];
    memcpy(new_str,m_string,length() + 1);
    new_str[length()] = c;
    new_str[length() + 1] = '\0';
    delete [] m_string;
    m_string = new_str;
}

void mstring::add(const char *c)//add str to end of str
{
    char * new_str = new char[length() + 2 + strlen(c)];
    memcpy(new_str,m_string,length() + 1);
    memcpy(new_str + length(), c,strlen(c) + 1);
    delete [] m_string;
    m_string = new_str;
}

void mstring::insert(char c,int i)//insert symbol on position(also 0)
{
    char * new_str = new char[length() + 2];
    memcpy(new_str,m_string,length() + 1);
    delete [] m_string;
    m_string = new_str;
    step_right(i);
    m_string[i] = c;
}

void mstring::insert(const char *c, int i)//insert str on position(also 0) 
{
    char * new_str = new char[length() + 2 + strlen(c)];
    memcpy(new_str,m_string,length() + 1);
    delete [] m_string;
    m_string = new_str;
    step_right(i,(int)strlen(c));
    memcpy(m_string + i,c,(int)strlen(c));
}

void mstring::del(int i)//delete symbol on position
{
    step_left(i);
    char * new_str = new char[length()];
    memcpy(new_str,m_string,length());
    delete [] m_string;
    m_string = new_str;
}

void mstring::del(int i, int j)//delete str on position
{
    step_left(i,j-i+1);
    char * new_str = new char[length() + j - i];
    memcpy(new_str,m_string,length() + j - i);
    delete [] m_string;
    m_string = new_str;
}

int mstring::search(const char *str) const//searching for str (return position of beginning or -1 otherwise)
{
    int len = length();
    for (int i = 0; i<len; i++)
    {
        if (m_string[i] == str[mstring::FIRST_SYMBOL])
        {
            int j = i;
            int k = mstring::FIRST_SYMBOL;
            while(str[k] == m_string[j])
            {
                j++;
                k++;
                if (str[k] == '\0')
                {
                    return i;
                }
            }
            if (str[k] == '\0')
            {
                return i;
            }
        }
    }
    return -1;
}

void mstring::replace(const char *sub_str, const char *new_str)//replace first incoming of sub_str 
{
    int pos;
    if ((pos = search(sub_str)) == -1)
    {
        return;
    }
    del(pos,pos + strlen(sub_str) - 1);
    insert(new_str,pos);
}

void mstring::print() const//print str on screen
{
    int i = 0;
    while (m_string[i] != '\0')
    {
        cout << m_string[i];
        i++;
    }
    cout << endl;
}