bool check_x_proection(int x1, long long x2, int x3, long long x4)
{
    if ((long long)x3 > x2 || x4 < (long long)x1)
    {
        return false;
    }
    return true;
}

bool check_y_proection(int y1, long long y2, int y3, long long y4)
{
    if ((long long)y1 > y4 || y2 < (long long)y3)
    {
        return false;
    }
    return true;
}

class Rect{
    int x,y;
    unsigned int wd,hd;
public:
    Rect(int x_1,int y_1,unsigned int wd_1,unsigned int hd_1)
    {
        x = x_1;
        y = y_1;
        wd = wd_1;
        hd = hd_1;
    }
    Rect()
    {
        x = 0;
        y = 0;
        wd = 1;
        hd = 1;
    }
    Rect(unsigned int num)
    {
        x = 0;
        y = 0;
        wd = num;
        hd = num;
    }
    void print_corner();
    void print_sz();
    int area();
    int perimeter();
    bool intersect(Rect r);
};

void Rect::print_corner()
{
    cout << '(' << Rect::x << ',' << Rect::y << ')' << endl; 
}

void Rect::print_sz()
{
    cout << "wd=" << Rect::wd << ' ' << "hd=" << Rect::hd << endl;
}

int Rect::area()
{
    return (Rect::wd * Rect::hd);
}

int Rect::perimeter()
{
    return 2 * (Rect::wd + Rect::hd);
}


bool Rect::intersect(Rect r)
{
    if (check_x_proection(x,(long long)(x+wd),r.x,(long long)(r.x+r.wd)))
    {
        if (check_y_proection(y,(long long)(y+hd),r.y,(long long)(r.y+r.hd)))
        {
            return true;
        }
        return false;
    }
    return false;
}