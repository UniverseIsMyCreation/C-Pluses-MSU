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