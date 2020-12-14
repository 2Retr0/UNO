#include <iostream>
#include "Card.h"
using namespace std;


namespace cs110c_uno {
    Card::Card(Color color, CardType cardType) : color(color), cardType(cardType) {}

    Card::CardType Card::getCardType() const {
        return cardType;
    }





    Card::Color Card::getColor() const {
        return color;
    }





    std::ostream &operator<<(ostream &out, const Card &card) {
        card.print(out);
        return out;
    }





    bool operator<(const Card& left, const Card& right) {
        return left.lessThan(right);
    }





    bool operator==(const Card &left, const Card &right) {
        return left.equals(right);
    }





    bool Card::lessThan(const Card &right) const {
        if (color == right.color) {
            return cardType < right.cardType;
        }
        return color < right.color;
    }





    bool Card::equals(const Card &right) const {
        if (color == right.color) {
            return cardType == right.cardType;
        }
        return color == right.color;
    }





    void Card::print(ostream& out) const {
        string colors[] = { "Red", "Yellow", "Green", "Blue", "Wild" };
        string cardTypes[] = { "Numbered Card", "Skip Card", "Reverse Card", "Draw Two Card", "Wild Card", "Draw Four Card" };
        out << cardTypes[static_cast<int>(cardType)] << ": " << colors[static_cast<int>(getColor())];
    }
}