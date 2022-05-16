#include <iostream>
#include <cstring>

using namespace std;

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

event::event(const char * new_name_subject, int new_year, int new_month, int new_day){
    name_subject = new char[strlen(new_name_subject) + 1];
    strcpy(name_subject, new_name_subject);
    day = new_day;
    month = new_month;
    year = new_year;
}

void event::change_date(int new_year, int new_month, int new_day){
    day = new_day;
    month = new_month;
    year = new_year;
}

class test: public event{
    bool grade;
public:
    ~test();
    test(const char *, int, int, int, bool);
    void print_res() const;
    void change_grade(bool);
};

test::~test(){
    delete[] event::name_subject;
}

void test::print_res() const{
    if (grade)
        cout << event::name_subject << " " << event::year << " " << event::month << " " << event::day << " " << "true" << endl;
    else
        cout << event::name_subject << " " << event::year << " " << event::month << " " << event::day << " " << "false" << endl;
}

void test::change_grade(bool new_grade){
    grade = new_grade;
}

test::test(const char * new_name_subject, int new_year, int new_month, int new_day, bool new_grade):event(new_name_subject,new_year,new_month,new_day){
    grade = new_grade;
}

class exam: public event{
    int grade;
public:
    ~exam();
    exam(const char *, int, int, int, int);
    void print_res() const;
    void change_grade(int);
};

exam::~exam(){
    delete[] event::name_subject;
}

void exam::print_res() const{
    cout << event::name_subject << " " << event::year << " " << event::month << " " << event::day << " Grade " << grade << endl;
}

void exam::change_grade(int new_grade){
    grade = new_grade;
}

exam::exam(const char * new_name_subject, int new_year, int new_month, int new_day, int new_grade):event(new_name_subject,new_year,new_month,new_day){
    grade = new_grade;
}

int main()
{
    const int NUM =7;
    event *session[NUM];

    session[0]=new test("MS Office",2020,12,23,true);
    session[1]=new exam("Operation System",2021,1,15,2);
    session[2]=new test("Practicum",2020,12,25,false);
    session[3]=new exam("Differential equation",2021,1,20,3);
    session[4]=new test("Theory of probability",2020,12,29,true);
    session[5]=new exam("Philosophy",2021,1,24,5);
    session[6]=new exam("C++",2021,1,11,4);

    for (int i=0;i<NUM;i++)
        session[i]->print_res();

    session[2]->change_date(2021,2,24);
    session[2]->change_grade(true);

    session[1]->change_date(2021,2,13);
    session[1]->change_grade(3);

    cout<<endl;
    for (int i=0;i<NUM;i++)
        session[i]->print_res();

    for (int i=0;i<NUM;i++)
    delete session[i];
    return 0;
}