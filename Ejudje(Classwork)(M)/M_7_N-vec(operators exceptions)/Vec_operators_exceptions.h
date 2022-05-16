#include <iostream>

using namespace std;

class Vec_excpeption{
    enum{
        STD_LENGTH = 100
    };

    char err_operator[STD_LENGTH];
    int arg1;
    int arg2;
    int amount_args;
public:
    Vec_excpeption(const char *,int,int,int)throw();
    Vec_excpeption(const Vec_excpeption &)throw();

    Vec_excpeption & operator=(const Vec_excpeption &)throw();
    
    void what() const throw();
};

class Vec{
    enum{
        EMPTY = 0,
        AMOUNT_AGRS_1 = 1,
        AMOUNT_AGRS_2 = 2,
        NOTHING = 0
    };

    double *v;
    int len;

    void copyvec(double *);
    void copyvec();
    void copyvec(const Vec &);
public:
    bool operator== (const Vec & obj_vec) const;
    const Vec & operator= (const Vec & obj_vec);
    const Vec operator+ (const Vec & obj_vec) const;
    const Vec operator- (const Vec & obj_vec) const;
    double & operator[] (int n) const;
    const Vec operator* (double n) const;

    friend const Vec operator* (double n, const Vec & obj_vec);
    friend ostream & operator<< (ostream & out, const Vec & obj_vec);


    Vec(int length, double *coord);
    Vec(int length);
    Vec(const Vec & new_vec);
    ~Vec();

    void set(double, int);
    double get(int) const;
    double euc_norm() const;
    double max_norm() const;
    void print() const;

};