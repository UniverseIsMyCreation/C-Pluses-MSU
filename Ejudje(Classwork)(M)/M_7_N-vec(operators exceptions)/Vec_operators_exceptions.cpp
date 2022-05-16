#include <iostream>
#include <cmath>
#include <cstring>
#include "Vec_operators_exceptions.h"

using namespace std;

Vec_excpeption::Vec_excpeption(const char * name_operator, int arg1, int arg2, int amount_args)throw()
{
    strcpy(err_operator,name_operator);
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->amount_args = amount_args;
}

Vec_excpeption::Vec_excpeption(const Vec_excpeption & obj_excp)throw()
{
    strcpy(err_operator, obj_excp.err_operator);
    arg1 = obj_excp.arg1;
    arg2 = obj_excp.arg2;
    amount_args = obj_excp.amount_args;
}

Vec_excpeption & Vec_excpeption::operator=(const Vec_excpeption & obj_excp)throw()
{
    strcpy(err_operator, obj_excp.err_operator);
    arg1 = obj_excp.arg1;
    arg2 = obj_excp.arg2;
    amount_args = obj_excp.amount_args;
    return *this;
}

void Vec_excpeption::what() const throw()
{
    switch(amount_args)
    {
        case(0):
            cerr << "Exception: " << err_operator << endl;
            break;
        case(1):
            cerr << "Exception: " << err_operator << arg1 << endl;
            break;
        case(2):
            cerr << "Exception: " << err_operator << arg1 << " " << arg2 << endl;
            break;
        default:
            break;
    }
}

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
    if (n < 0 || n >= len)
    {
        Vec_excpeption new_obj_excp("incorrect indexing: ",n,EMPTY,AMOUNT_AGRS_1);
        throw new_obj_excp;
    }
    return v[n];
}

const Vec Vec::operator+ (const Vec & obj_vec) const
{
    if (len != obj_vec.len)
    {
        Vec_excpeption new_obj_excp("addition of vectors of different lengths: ",len,obj_vec.len,AMOUNT_AGRS_2);
        throw new_obj_excp;
    }
    Vec new_vec(len);
    for (int i = 0; i < len; i++)
    {
        new_vec.v[i] = v[i] + obj_vec.v[i]; 
    }
    return new_vec;
}

const Vec Vec::operator- (const Vec & obj_vec) const
{
    if (len != obj_vec.len)
    {
        Vec_excpeption new_obj_excp("addition of vectors of different lengths: ",len,obj_vec.len,AMOUNT_AGRS_2);
        throw new_obj_excp;
    }
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
    if (length < 0)
    {
        Vec_excpeption new_obj_excp("length error",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
    }
    len = length;   
    v = new double[len];
    copyvec(coord);
}
Vec::Vec(int length)
{
    if (length < 0)
    {
        Vec_excpeption new_obj_excp("length error",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
    }
    len = length;
    v = new double[len];
    copyvec();
}
Vec::Vec(const Vec & new_vec)
{
    if (new_vec.len < 0)
    {
        Vec_excpeption new_obj_excp("length error",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
    }
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
        Vec_excpeption new_obj_excp("coordinate error in set()",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
    }
    v[coord] = arg;
}

double Vec::get(int coord) const
{
    if (coord < 0 || coord >= len)
    {
        Vec_excpeption new_obj_excp("coordinate error in get()",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
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