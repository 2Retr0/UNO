#include <iostream>
#include <cassert>
#include "NumberedCard.h"

using namespace std;


namespace cs110c_uno {
    NumberedCard::NumberedCard(Color color, int value) : Card(color, CardType::Numbered), value(value) {
        assert(color != Color::Wild);
        assert(value >= MIN_VALUE && value <= MAX_VALUE);
    }





    int NumberedCard::getValue() const {
        return value;
    }





    bool NumberedCard::lessThan(const Card &right) const {
        // this is probably not efficient, but will do for now...
        if (getColor() == right.getColor() && right.getCardType() == CardType::Numbered) {
            return value < dynamic_cast<const NumberedCard&>(right).getValue();
        }
        return Card::lessThan(right);
    }





    bool NumberedCard::equals(const Card &right) const {
        if (getColor() == right.getColor() && right.getCardType() == CardType::Numbered) {
            return value == dynamic_cast<const NumberedCard&>(right).getValue();
        }
        return Card::equals(right);
    }





    void NumberedCard::print(ostream &out) const {
        Card::print(out);
        out << ", " << value;
    }





    unique_ptr<Card> NumberedCard::clone() const {
        return unique_ptr<Card>(new NumberedCard(getColor(), getValue()));
    }
}