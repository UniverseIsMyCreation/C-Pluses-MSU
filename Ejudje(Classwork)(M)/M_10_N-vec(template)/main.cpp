#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

class Vec_excpeption{
    enum {STD_LENGTH = 100};
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

template <typename T>
class Vec{
    enum {
        EMPTY = 0,
        AMOUNT_AGRS_1 = 1,
        AMOUNT_AGRS_2 = 2,
        NOTHING = 0
    };
    T *v;
    int len;
    void copyvec(T *);
    void copyvec();
    void copyvec(const Vec<T> &);
public:
    bool operator== (const Vec<T> & obj_vec) const;
    const Vec<T> & operator= (const Vec<T> & obj_vec);
    const Vec<T> operator+ (const Vec<T> & obj_vec) const;
    T & operator[] (int n) const;
    const Vec<T> operator* (T n) const;
    T operator^ (const Vec<T> & obj_vec) const;
    const Vec<T> & operator+= (const Vec<T> & obj_vec) const;

    template<typename A>
    friend const Vec<A> operator* (A n, const Vec<A> & obj_vec);
    
    template<typename A>
    friend ostream & operator<< (ostream & out, const Vec<A> & obj_vec);


    Vec(int length, T * coord);
    Vec(int length);
    Vec(const Vec<T> & new_vec);
    ~Vec();

    void set(T, int);
    T get(int) const;
    T max_norm() const;

};

template<typename T>
const Vec<T> & Vec<T>::operator+= (const Vec<T> & obj_vec) const{
    if (len != obj_vec.len){
        Vec_excpeption new_obj_excp("addition of vectors of different lengths: ",len,obj_vec.len,AMOUNT_AGRS_2);
        throw new_obj_excp;
    }
    for (int i = 0; i<len; i++){
        v[i] += obj_vec[i];
    }
    return *this;
}

template<typename T>
T Vec<T>::operator^ (const Vec<T> & obj_vec) const{
    if (len != obj_vec.len){
        Vec_excpeption new_obj_excp("multiplication of vectors of different lengths: ",len,obj_vec.len,AMOUNT_AGRS_2);
        throw new_obj_excp;
    }
    T skal_multiplication = 0;
    for (int i = 0; i<len; i++){
        skal_multiplication += v[i] * obj_vec[i];
    }
    return skal_multiplication;
}

template<typename T>
ostream & operator<< (ostream & out, const Vec<T> & obj_vec)
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

template<typename T>
const Vec<T> operator* (T n, const Vec<T> & obj_vec)
{
    Vec<T> new_vec(obj_vec.len);
    for (int i = 0; i<obj_vec.len; i++)
    {
        new_vec.v[i] = obj_vec.v[i] * n;
    }
    return new_vec;
}

template<typename T>
const Vec<T> Vec<T>::operator* (T n) const
{
    Vec<T> new_vec(len);
    for (int i = 0; i < len; i++)
    {
        new_vec.v[i] = v[i] * n;
    }
    return new_vec;
}

template<typename T>
T & Vec<T>::operator[] (int n) const
{
    if (n < 0 || n >= len)
    {
        Vec_excpeption new_obj_excp("incorrect indexing: ",n,EMPTY,AMOUNT_AGRS_1);
        throw new_obj_excp;
    }
    return v[n];
}

template<typename T>
const Vec<T> Vec<T>::operator+ (const Vec<T> & obj_vec) const
{
    if (len != obj_vec.len)
    {
        Vec_excpeption new_obj_excp("addition of vectors of different lengths: ",len,obj_vec.len,AMOUNT_AGRS_2);
        throw new_obj_excp;
    }
    Vec<T> new_vec(len);
    for (int i = 0; i < len; i++)
    {
        new_vec.v[i] = v[i] + obj_vec.v[i]; 
    }
    return new_vec;
}

template<typename T>
bool Vec<T>::operator== (const Vec<T> & obj_vec) const
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

template<typename T>
const Vec<T> & Vec<T>::operator= (const Vec<T> & obj_vec)
{
    if (obj_vec == *this)
    {
        return *this;
    }
    delete[] v;
	v = new T[obj_vec.len];
    for(int i = 0; i<obj_vec.len; i++)
    {
        v[i] = obj_vec[i];
    }
    len = obj_vec.len;
    return * this;
}

/////////////////////////////////////////////////////////////////////////////////

template<typename T>
Vec<T>::Vec(int length, T * coord)
{
    if (length < 0)
    {
        Vec_excpeption new_obj_excp("length error",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
    }
    len = length;   
    v = new T[len];
    copyvec(coord);
}

template<typename T>
Vec<T>::Vec(int length)
{
    if (length < 0)
    {
        Vec_excpeption new_obj_excp("length error",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
    }
    len = length;
    v = new T[len];
    copyvec();
}

template<typename T>
Vec<T>::Vec(const Vec<T> & new_vec)
{
    if (new_vec.len < 0)
    {
        Vec_excpeption new_obj_excp("length error",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
    }
    len = new_vec.len;
    v = new T[len];
    copyvec(new_vec);
}

template<typename T>
Vec<T>::~Vec()
{
    delete [] v;
}

template<typename T>
void Vec<T>::copyvec(const Vec<T> & new_vec)
{
    for (int i = 0; i<len; i++)
    {
        v[i] = new_vec.v[i];
    }
}

template<typename T>
void Vec<T>::copyvec()
{
    for (int i = 0; i<len; i++)
    {
        v[i] = 0.0;
    }
}

template<typename T>
void Vec<T>::copyvec(T *coord)
{
    for (int i = 0; i<len; i++)
    {
        v[i] = coord[i];
    }
}

template<typename T>
void Vec<T>::set(T arg, int coord)
{
    if (coord < 0 || coord >= len)
    {
        Vec_excpeption new_obj_excp("coordinate error in set()",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
    }
    v[coord] = arg;
}

template<typename T>
T Vec<T>::get(int coord) const
{
    if (coord < 0 || coord >= len)
    {
        Vec_excpeption new_obj_excp("coordinate error in get()",EMPTY,EMPTY,NOTHING);
        throw new_obj_excp;
    }
    return v[coord];
}

template<typename T>
T Vec<T>::max_norm() const
{
    T max = abs(v[0]);
    for (int i = 1; i<len; i++)
    {
        if (abs(v[i]) > max)
        {
            max = abs(v[i]);
        }
    }
    return max;
}

int main()
{
    try
    {
        Vector();
    }
    catch(const Vec_excpeption & obj_excp_caught)
    {
        obj_excp_caught.what();
    }
    catch(...)
    {
        cerr << "Exception: unknown error" << endl;
    }
    return 0;
}