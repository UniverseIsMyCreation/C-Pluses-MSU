#include <iostream>

class mstring_excpeption{
    enum {STD_LENGTH = 100};
    char err_operator[STD_LENGTH];
    int arg1;
    int arg2;
    int amount_args;
public:
    mstring_excpeption(const char *,int,int,int)throw();
    mstring_excpeption(const mstring_excpeption &)throw();
    mstring_excpeption & operator=(const mstring_excpeption &)throw();
    
    void what() const throw();
};

class mstring{
    char * m_string;
    
    void step_right(int, int);
    void step_left(int,int);

    enum{
        FIRST_SYMBOL = 0,
        AMOUNT_ARGS_1 = 1,
        AMOUNT_ARGS_2 = 2,
        ERROR = 1,
        EMPTY= 0,
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