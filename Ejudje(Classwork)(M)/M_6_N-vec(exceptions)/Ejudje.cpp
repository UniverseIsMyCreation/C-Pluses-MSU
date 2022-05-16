#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

class Vec_excpeption{
    enum{
        STD_LENGTH = 100
    };

    char err_operator[STD_LENGTH];
public:
    Vec_excpeption(const char *)throw();
    Vec_excpeption(const Vec_excpeption &)throw();
    
    Vec_excpeption & operator=(const Vec_excpeption &)throw();
    
    void what() const throw();
};

Vec_excpeption::Vec_excpeption(const char * name_operator)throw()
{
    strcpy(err_operator,name_operator);
}

Vec_excpeption::Vec_excpeption(const Vec_excpeption & obj_excp)throw()
{
    strcpy(err_operator, obj_excp.err_operator);
}

Vec_excpeption & Vec_excpeption::operator=(const Vec_excpeption & obj_excp)throw()
{
    strcpy(err_operator, obj_excp.err_operator);
    return *this;
}

void Vec_excpeption::what() const throw()
{
    cerr << "Exception: " << err_operator << endl;
}

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
    if (length < 0)
    {
        Vec_excpeption new_obj_excp("length error");
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
        Vec_excpeption new_obj_excp("length error");
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
        Vec_excpeption new_obj_excp("length error");
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
        Vec_excpeption new_obj_excp("coordinate error in set()");
        throw new_obj_excp;
    }
    v[coord] = arg;
}

double Vec::get(int coord) const
{
    if (coord < 0 || coord >= len)
    {
        Vec_excpeption new_obj_excp("coordinate error in get()");
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

void error()
{
    double y1[3] = {1,2,3};
    double y2[5] = {2,1,0,5,7};
    Vec x(-3, y1), y(5, y2), z(4);
    Vec u = x;
    y.print();
    x.print();
    z.print();
    u.print();
}

int main()
{
    try
    {
        error();
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