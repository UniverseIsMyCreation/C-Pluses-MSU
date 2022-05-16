#include<iostream>
using namespace std;

namespace Grammar{
    enum{
        S = 1,
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O
    };
}
char c;

void gc(){
    c = cin.get();
}

int main(){
    int state = Grammar::S;
    int buf = 0;
    bool move = true;
    bool move_gc = true;
    int amount_of_zeroes = 0;
    try{
        gc();
        while(true){
            switch(state){
                case Grammar::S:
                    if (c == '.')
                        state = Grammar::B;
                    else if (c == '-')
                        state = Grammar::A;
                    else if (c == '\n'){
                        for (int i = 0; i < amount_of_zeroes; i++)
                            cout << '0';
                        if (!move)
                            cout << buf;
                        return 0;
                    }
                    else 
                        throw c;
                    break;
                case Grammar::A:  
                    if (c == '.'){
                        state = Grammar::D;
                        buf = buf * 10 + 6;
                        move = false;
                    }
                    else if (c == '-')
                        state = Grammar::C;
                    else 
                        throw c;
                    break;
                case Grammar::B: 
                    if (c == '-'){
                        state = Grammar::E;
                        buf = buf * 10 + 1;
                        move = false;
                    }
                    else if (c == '.')
                        state = Grammar::F;
                    else 
                        throw c;  
                    break;
                case Grammar::C:
                    if (c == '.'){
                        state = Grammar::H;
                        buf = buf * 10 + 7;
                        move = false;
                    }
                    else if (c == '-')
                        state = Grammar::G;
                    else 
                        throw c; 
                    break;
                case Grammar::D: 
                    if (c == '.')
                        state = Grammar::H;
                    else 
                        throw c;   
                    break;
                case Grammar::E:
                    if (c == '-')
                        state = Grammar::I;
                    else 
                        throw c;   
                    break;
                case Grammar::F:
                    if (c == '-'){
                        state = Grammar::I;
                        buf = buf * 10 + 2;
                        move = false;
                    }
                    else if (c == '.')
                        state = Grammar::J;
                    else 
                        throw c;   
                    break;
                case Grammar::G:
                    if (c == '.'){
                        state = Grammar::L;
                        buf = buf * 10 + 8;
                        move = false;
                    }
                    else if (c == '-')
                        state = Grammar::K;
                    else 
                        throw c;   
                    break;
                case Grammar::H: 
                    if (c == '.')
                        state = Grammar::L;
                    else 
                        throw c;   
                    break;
                case Grammar::I:
                    if (c == '-')
                        state = Grammar::M;
                    else 
                        throw c;  
                    break;
                case Grammar::J:
                    if (c == '-'){
                        state = Grammar::M;
                        buf = buf * 10 + 3;
                        move = false;
                    }
                    else if (c == '.')
                        state = Grammar::N;
                    else 
                        throw c;    
                    break;
                case Grammar::K:
                    if (c == '.'){
                        state = Grammar::O;
                        buf = buf * 10 + 9;
                        move = false;
                    }
                    else if (c == '-'){
                        state = Grammar::O;
                        buf = buf * 10 + 0;
                        if (move)
                            amount_of_zeroes++;
                    }
                    else 
                        throw c;  
                    break;
                case Grammar::L: 
                    if (c == '.')
                        state = Grammar::O;
                    else 
                        throw c;   
                    break;
                case Grammar::M:
                    if (c == '-')
                        state = Grammar::O;
                    else 
                        throw c;
                    break;
                case Grammar::N:
                    if (c == '-'){
                        state = Grammar::O;
                        buf = buf * 10 + 4;
                        move = false;
                    }
                    else if (c == '.'){
                        state = Grammar::O;
                        buf = buf * 10 + 5;
                        move = false;
                    }
                    else 
                        throw c;   
                    break;
                case Grammar::O:
                    if (c == ' ' || c == '\n'){
                        state = Grammar::S;
                        if (c == '\n')
                            move_gc = false;
                    }
                    else
                        throw c;
                    break;
            }
            if (move_gc)
                gc();
        }
    }
    catch(char & c){
        cerr << "Error in Lexeme: " << c;
    }
    return 0;
}