#include <iostream>
#include <cstring>

using namespace std;
class mstring{
    enum{
        FIRST_SYMBOL = 0,
        STD_LENGTH = 100
    };
    char * m_string;
    void step_right(int, int);
    void step_left(int,int);
public:
    mstring();
    mstring(const mstring & new_str);
    mstring(const char * str);
    ~mstring();

    const mstring operator+ (const mstring & obj_str) const;
    const mstring & operator= (const mstring & obj_str); 
    const mstring operator* (int n) const;
    bool operator> (const mstring & obj_str) const;
    bool operator< (const mstring & obj_str) const;
    bool operator<= (const mstring & obj_str) const;
    bool operator>= (const mstring & obj_str) const;
    bool operator== (const mstring & obj_str) const;
    char & operator[] (int i) const;

    friend const mstring operator* (int n,const mstring & obj_str);
    friend const mstring operator+ (const char * str,const mstring & obj_str);
    friend ostream & operator<< (ostream & out, const mstring & obj_str);
    friend istream & operator>> (istream & in, mstring & obj_str);
    
    int length() const;
    bool isempty() const;
    void add(char);
    void add(const char *);
    void insert(char,int);
    void insert(const char *, int);
    void print() const;
    void replace(const char *, const char *);
    int search(const char *) const;
    void del(int);
    void del(int, int);
};

///////////////////////////////////////////////////////////// OPERATORS

const mstring operator+ (const char * str,const mstring & obj_str)
{
    char * new_str = new char[strlen(str) + obj_str.length() + 1];
    memcpy(new_str,str,strlen(str) + 1);
    memcpy(new_str + strlen(str),obj_str.m_string,obj_str.length() + 1);
    mstring new_obj_str(new_str);
    return new_obj_str;
}

ostream & operator<< (ostream & out, const mstring & obj_str)
{
    for (int i = 0; i < obj_str.length(); i++)
    {
        out << obj_str[i];
    }
    return out;
}

istream & operator>> (istream & in, mstring & obj_str)
{
    int length = 0;
    int bufsize = mstring::STD_LENGTH;
    char * buf = new char[bufsize];
    while (!in.eof())
    {
        in.get(buf[length]);
        if (buf[length] == '\n')
            break;
        length++;
        if (length >= bufsize)
        {
            bufsize += mstring::STD_LENGTH;
            char * buf_copy = new char[bufsize];
            memcpy(buf_copy,buf,length);
            delete [] buf;
            buf = buf_copy;
        }
    }
    buf[length] = '\0';
    if (obj_str.length() > 0)
    {
        obj_str.del(0,obj_str.length()-1);
    }
    obj_str.add(buf);
    return in;
}

char & mstring::operator[] (int i) const
{
    return m_string[i];
}

bool mstring::operator> (const mstring & obj_str) const
{
    return (strcmp(m_string, obj_str.m_string) > 0);
}

bool mstring::operator< (const mstring & obj_str) const
{
    return (strcmp(m_string, obj_str.m_string) < 0);
}

bool mstring::operator== (const mstring & obj_str) const
{
    return (strcmp(m_string, obj_str.m_string) == 0);
}

bool mstring::operator>= (const mstring & obj_str) const
{
    return (strcmp(m_string, obj_str.m_string) >= 0);
}

bool mstring::operator<= (const mstring & obj_str) const
{
    return (strcmp(m_string, obj_str.m_string) <= 0);
}

const mstring mstring::operator+ (const mstring & obj_str) const
{
    char * new_str = new char[length() + obj_str.length() + 1];
    memcpy(new_str,m_string,length() + 1);
    memcpy(new_str + length(),obj_str.m_string,obj_str.length() + 1);
    mstring new_obj_str(new_str);
    return new_obj_str;
}

const mstring & mstring::operator= (const mstring & obj_str)
{
    char * new_str = new char[obj_str.length() + 1];
    memcpy(new_str,obj_str.m_string,obj_str.length() + 1);
    delete [] m_string;
    m_string = new_str;
    return *this;
}

const mstring mstring::operator* (int n) const
{
    mstring new_obj_str;
    if (n < 0)
        return new_obj_str;
    else
    {
        for (int i = 0; i<n; i++)
        {
            new_obj_str.add(m_string);
        }
        return new_obj_str;
    }
}

const mstring operator* (int n,const mstring & obj_str)
{
    mstring new_obj_str;
    if (n < 0)
        return new_obj_str;
    else
    {
        for (int i = 0; i<n; i++)
        {
            new_obj_str.add(obj_str.m_string);
        }
        return new_obj_str;
    }
}

///////////////////////////////////////////////////////////// CONTRUCTORS

mstring::mstring()
{
    m_string = new char;
    m_string[FIRST_SYMBOL] = '\0';
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

///////////////////////////////////////////////////////////// METHODS

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
    if (m_string[FIRST_SYMBOL] == '\0')
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
        if (m_string[i] == str[FIRST_SYMBOL])
        {
            int j = i;
            int k = FIRST_SYMBOL;
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