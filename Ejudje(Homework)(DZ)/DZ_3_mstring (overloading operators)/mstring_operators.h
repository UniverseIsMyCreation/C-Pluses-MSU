#include <iostream>

class mstring{
    char * m_string;

    void step_right(int, int);
    void step_left(int,int);
    enum{
        FIRST_SYMBOL = 0,
        STD_LENGTH = 100
    };
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
    friend std::ostream & operator<< (std::ostream & out, const mstring & obj_str);
    friend std::istream & operator>> (std::istream & in, mstring & obj_str);
    
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