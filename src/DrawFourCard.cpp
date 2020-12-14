#include "DrawFourCard.h"

using namespace std;


namespace cs110c_uno {
    // TODO: very bad need to find another way to implement this.
    DrawFourCard::DrawFourCard() : WildCard(0) {}





    unique_ptr<Card> DrawFourCard::clone() const {
        return unique_ptr<Card>(new DrawFourCard());
    }
}