#include <iostream>

class Vec{
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
    friend std::ostream & operator<< (std::ostream & out, const Vec & obj_vec);


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