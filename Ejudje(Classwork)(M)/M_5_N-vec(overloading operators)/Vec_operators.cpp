#include <iostream>
#include <cmath>
#include "Vec_operators.h"

using namespace std;

ostream & operator<< (ostream & out, const Vec & obj_vec)
{
    cout << "(";
    for (int i = 0; i<obj_vec.len; i++)
    {
        out << obj_vec[i];
        if (i == (obj_vec.len - 1))
        {
            break;
        }
        cout << ",";
    }
    cout << ")";
    return out;
}

const Vec operator* (double n, const Vec & obj_vec)
{
    Vec new_vec(obj_vec.len);
    for (int i = 0; i<obj_vec.len; i++)
    {
        new_vec.v[i] = obj_vec.v[i] * n;
    }
    return new_vec;
}

const Vec Vec::operator* (double n) const
{
    Vec new_vec(len);
    for (int i = 0; i < len; i++)
    {
        new_vec.v[i] = v[i] * n;
    }
    return new_vec;
}

double & Vec::operator[] (int n) const
{
    return v[n];
}

const Vec Vec::operator+ (const Vec & obj_vec) const
{
    Vec new_vec(len);
    for (int i = 0; i < len; i++)
    {
        new_vec.v[i] = v[i] + obj_vec.v[i]; 
    }
    return new_vec;
}

const Vec Vec::operator- (const Vec & obj_vec) const
{
    Vec new_vec(len);
    for (int i = 0; i < len; i++)
    {
        new_vec.v[i] = v[i] - obj_vec.v[i];
    }
    return new_vec;
}

bool Vec::operator== (const Vec & obj_vec) const
{   
    if (len != obj_vec.len)
    {
        return false;
    }
    for (int i = 0; i<len; i++)
    {
        if (v[i] != obj_vec.v[i])
        {
            return false;
        }
    }
    return true;
}

const Vec & Vec::operator= (const Vec & obj_vec)
{
    if (obj_vec == *this)
    {
        return *this;
    }
    delete[] v;
	v = new double[obj_vec.len];
    for(int i = 0; i<obj_vec.len; i++)
    {
        v[i] = obj_vec[i];
    }
    len = obj_vec.len;
    return * this;
}

/////////////////////////////////////////////////////////////////////////////////

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