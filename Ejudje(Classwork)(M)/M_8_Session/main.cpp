#include <iostream>
#include "Event.h"

using namespace std;

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