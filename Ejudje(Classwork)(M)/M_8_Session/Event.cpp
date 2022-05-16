#include <iostream>
#include <cstring>
#include "Event.h"

using namespace std;

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