#include <cstring>
#include <iostream>

using namespace std;

class Flower{
    static int amount_of_pink;
    static int amount_of_white;
    bool switch_colour;
public:
    static void Print_flowers();
    Flower (const char *, int);
    Flower();
    ~Flower();
};

Flower::~Flower(){
    if (switch_colour == true)
        amount_of_white--;
    else
        amount_of_pink--;
}

Flower::Flower(){
    int amount_of_leafs = 10;
    if (amount_of_white < amount_of_pink || amount_of_leafs % 2 == 1){
        amount_of_white++;
        switch_colour = true;
    }
    else{
        amount_of_pink++;
        switch_colour = false;
    }
}

Flower::Flower(const char * colour, int amount_of_leafs = 10){
    if (strcmp(colour,"white") == 0){
        amount_of_white++;
        switch_colour = true;
    }
    else if (strcmp(colour,"pink") == 0){
        amount_of_pink++;
        switch_colour = false;
    }
    else{
        if (amount_of_white < amount_of_pink || amount_of_leafs % 2 == 1){
            amount_of_white++;
            switch_colour = true;
        }
        else{
            amount_of_pink++;
            switch_colour = false;
        }
    }
}

void Flower::Print_flowers(){
    cout << "White: " << amount_of_white << " Pink: " << amount_of_pink << endl;
}

int Flower::amount_of_pink = 0;
int Flower::amount_of_white = 0;

int main()
{
    Flower fl1("white", 3);
    Flower fl2("pink", 5);
    Flower fl3("white", 7);
    Flower::Print_flowers();
    Flower fl4("green");
    Flower::Print_flowers();
    Flower fl5("blue", 17);
    Flower::Print_flowers();
    Flower fl6;
    Flower::Print_flowers();
    Flower fl7;
    Flower::Print_flowers();
    return 0;
}