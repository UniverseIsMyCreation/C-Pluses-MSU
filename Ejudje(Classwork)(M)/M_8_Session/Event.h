class event{
protected:
    int day,month,year;
    char * name_subject;
public:
    event(const char *, int, int, int);
    virtual ~event(){};
    virtual void print_res() const = 0;

    virtual void change_grade(bool){};
    virtual void change_grade(int){};
    void change_date(int, int, int);
};

class test: public event{
    bool grade;
public:
    ~test();
    test(const char *, int, int, int, bool);

    void print_res() const;
    void change_grade(bool);
};

class exam: public event{
    int grade;
public:
    ~exam();
    exam(const char *, int, int, int, int);
    
    void print_res() const;
    void change_grade(int);
};