#include "WildCard.h"

using namespace std;


namespace cs110c_uno {
    WildCard::WildCard() : Card(Color::Wild, CardType::Wild) {}

    // there is probably a better way than using a protected constructor for DrawFour
    // this is bad and needs to be changed
    WildCard::WildCard(int) : Card(Color::Wild, CardType::DrawFour) {}





    std::unique_ptr<Card> WildCard::clone() const {
        return unique_ptr<Card>(new WildCard());
    }
}