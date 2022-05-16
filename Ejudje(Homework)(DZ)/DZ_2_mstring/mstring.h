class mstring{
    char * m_string;
    
    void step_right(int,int);
    void step_left(int,int);

    enum {FIRST_SYMBOL = 0};
public:
    mstring();
    mstring(const mstring & new_str);
    mstring(const char * str);
    ~mstring();
    
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