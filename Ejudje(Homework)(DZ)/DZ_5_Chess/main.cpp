#include <iostream>
#include "Chess.h"
using namespace std;

int main()
{
    try{
        int num_of_figure;
        ChessChecker check_move;
        Parser parser;
        coordinates income_coordinates;
        check_move.read_command();
        income_coordinates = parser.parse_command(check_move.get_command());
        num_of_figure = check_move.check_coordinates(income_coordinates);
        if ((check_move.get_figure(num_of_figure))->move(income_coordinates))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    catch(const char * error){
        cout << error << endl;
    }
    catch(...){}
    return 0;
}
