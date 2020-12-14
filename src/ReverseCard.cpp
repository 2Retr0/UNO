#include <cassert>
#include "ReverseCard.h"

using namespace std;


namespace cs110c_uno {
    ReverseCard::ReverseCard(Color color) : Card(color, CardType::Reverse) {
        assert(color != Color::Wild);
    }





    unique_ptr<Card> ReverseCard::clone() const {
        return unique_ptr<Card>(new ReverseCard(getColor()));
    }
}