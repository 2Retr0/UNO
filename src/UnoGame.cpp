#include <iostream>
#include <string>
#include "Card.h"
#include "Deck.h"
#include "Gamemaster.h"

using namespace std;
using namespace cs110c_uno;


int main(int argc, char *argv[], char *pString[]) {
    cout << "Initializing UNO!\n" << endl;
    Gamemaster gamemaster;
    string selection = "n";

    do {
        cin.clear();
        while (!gamemaster.isGameFinished()) {
            gamemaster.takeTurn();
        }

        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> GAME COMPLETE! <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
        cout << "\"UNO!\" " << gamemaster.getCurrentPlayer()->getName() << " is the winner!\n";
        cout << "Play another game? (y/n): ";
        cin >> selection;

        if (selection == "y")
            gamemaster.reset();
    } while (selection == "y");
    cout << "\nExiting UNO!";
}