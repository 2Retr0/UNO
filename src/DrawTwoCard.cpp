#include <cassert>
#include "DrawTwoCard.h"

using namespace std;


namespace cs110c_uno {
    DrawTwoCard::DrawTwoCard(Color color) : Card(color, CardType::DrawTwo) {
        assert(color != Color::Wild);
    }





    unique_ptr<Card> DrawTwoCard::clone() const {
        return unique_ptr<Card>(new DrawTwoCard(getColor()));
    }
}