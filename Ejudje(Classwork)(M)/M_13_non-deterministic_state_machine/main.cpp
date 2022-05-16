#include<iostream>
#include<cstring>
using namespace std;

namespace Grammar{
    enum{
        H = 1,
        A,
        B,
        S
    };
}
char c;

void gc(){
    c = cin.get();
}

int main(){
    bool move = true;
    string answer = "";
    try{
        gc();
        int state = Grammar::H;
        while (true){
            switch(state){
                case Grammar::H:
                    if (c == 'a'){
                        state = Grammar::A;
                        answer += "a";
                    }
                    else
                        throw c;
                    break;
                case Grammar::A:
                    if (c == 'd')
                        answer += "d";
                    else if (c == 'a'){
                        state = Grammar::B;
                        answer += "a";
                    }
                    else 
                        throw c;
                    break;
                case Grammar::B:
                    if (c == 'a'){
                        state = Grammar::A;
                        answer += "a";
                    }
                    else if (c == '\n'){
                        state = Grammar::S;
                        move = false;
                    }
                    else
                        throw c;
                    break;
                case Grammar::S:
                    cout << answer << endl;
                    return 0;
            }
            if (move)
                gc();
        }
    }
    catch (char err_symbol){
        cerr << "Error in Lexcem: " << err_symbol << endl;
    }
    return 0;
}