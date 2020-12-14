#include <iostream>
#include <string>
#include "WildCard.h"
#include "Player.h"
#include "Gamemaster.h"

using namespace std;


namespace cs110c_uno {
    Player::Player() : name("unnamed") {}

    Player::Player(string& name) : name(name) {}





    std::ostream &operator<<(ostream &out, const Player &player) {
        return out << player.hand;
    }





    int Player::getCardCount() const {
        return hand.getCardCount();
    }





    std::string Player::getName() const {
        return name;
    }





    std::unique_ptr<Card> Player::selectCard(Gamemaster& gamemaster) {
        string selection;
        unique_ptr<Card> selectedCard;

        cout << hand << "Select a card to deal with its index! (Use 'n' to grab a new card from the draw deck): ";
        cin >> selection;
        // Handling for an invalid input asking the Player again.
        while (validInput(selection, 1, hand.getCardCount(), selection == "n")) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: Invalid selection.\n";
            cout << "Select a card to play with its index! (Use 'n' to grab a new card from the draw deck): ";
            cin >> selection;
        }
        // From this point onwards, we know that the Player selection must either be 'n' or a valid index.
        if (selection == "n") {
            // Give the Player a card from the drawDeck and play it.
            // The card will automatically be given to the player if the Gamemaster rejects it.
            selectedCard = gamemaster.giveCard();
        } else {
            // Deal the Card found at the correct index. We can safely use stoi() since we know that the
            // selection could only exist as valid digits at this point.
            selectedCard = hand.deal(stoi(selection));
        }

        // If the selectedCard is a wildCard, ensure that the Player selects a Color for the wildCard.
        if (selectedCard->getColor() == Card::Color::Wild) {
            gamemaster.setLastPlayedWildCardColor(selectWildColor());
        }
        return move(selectedCard);
    }





    Card::Color Player::selectWildColor() {
        string selectedColor;

        // TODO: Perhaps move this logic to a separate method for compatibility?
        cout << string(100, '=') << "\n";
        cout << "| 1) Red                 | 2) Yellow              | 3) Green               | 4) Blue               |\n";
        cout << string(100, '=') << "\n";
        cout << "Select a color to set for the next player with its index!: ";
        cin >> selectedColor;

        // Handling for an invalid input asking the Player again.
        while (validInput(selectedColor, 1, 4, false)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: Invalid selection.\n";
            cout << "Select a color to set for the next player with its index!: ";
            cin >> selectedColor;
        }
        // From this point onwards, we know that the Player selection must be a valid int.

        // We cast the selectedColor first to an int then to an enum Color subtracted by 1
        // to correct for the implicit value.
        return static_cast<Card::Color>(stoi(selectedColor) - 1);
    }





    void Player::giveCard(std::unique_ptr<Card> card) {
        hand.add(move(card));
    }





    void Player::sortHand() {
        hand.sort();
    }





    // Checks if string is either within the specified int range when converted to an int,
    // or results in a string comparison returning true.
    bool Player::validInput(const string& string, int lowIntRange, int highIntRange, bool strComp) {
        int stringValue;
        // Try to convert the string to an int.
        try {
            stringValue = stoi(string);
            // Return whether the int is within the range of selectable cards.
            return stringValue < lowIntRange || stringValue > highIntRange;
        } catch (std::invalid_argument& e) {
            // Return whether the string is NOT valid for a string comparison
            // (as validInput() is used in a while loop to continue running).
            return !strComp;
        }
    }
}