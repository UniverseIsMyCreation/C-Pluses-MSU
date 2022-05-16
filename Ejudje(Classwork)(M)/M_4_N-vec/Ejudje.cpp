#include <iostream>
#include <cmath>
using namespace std;
class Vec{
    double *v;
    int len;
    void copyvec(double *);
    void copyvec();
    void copyvec(const Vec &);
public:
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

Vec::Vec(int length, double *coord)
{
    len = length;   
    v = new double[len];
    copyvec(coord);
}
Vec::Vec(int length)
{
    len = length;
    v = new double[len];
    copyvec();
}
Vec::Vec(const Vec & new_vec)
{
    len = new_vec.len;
    v = new double[len];
    copyvec(new_vec);
}
Vec::~Vec()
{
    delete [] v;
}

void Vec::copyvec(const Vec & new_vec)
{
    for (int i = 0; i<len; i++)
    {
        v[i] = new_vec.v[i];
    }
}

void Vec::copyvec()
{
    for (int i = 0; i<len; i++)
    {
        v[i] = 0.0;
    }
}

void Vec::copyvec(double *coord)
{
    for (int i = 0; i<len; i++)
    {
        v[i] = coord[i];
    }
}

void Vec::set(double arg, int coord)
{
    if (coord < 0 || coord >= len)
    {
        return;
    }
    v[coord] = arg;
}

double Vec::get(int coord) const
{
    if (coord < 0 || coord >= len)
    {
        return 0;
    }
    return v[coord];
}

double Vec::euc_norm() const
{
    double ans = 0;
    for (int i = 0; i<len; i++)
    {
        ans += pow(v[i],2);
    }
    return sqrt(ans);
}

double Vec::max_norm() const
{
    double max = abs(v[0]);
    for (int i = 1; i<len; i++)
    {
        if (abs(v[i]) > max)
        {
            max = abs(v[i]);
        }
    }
    return max;
}

void Vec::print() const
{
    cout << '(';
    for (int i = 0; i<len; i++)
    {
        if (i == (len - 1))
        {
            cout << v[i];
            continue;
        }
        cout << v[i] << ',';
    }
    cout << ')' << endl;
}