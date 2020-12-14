#include <cassert>
#include "SkipCard.h"

using namespace std;


namespace cs110c_uno {
    SkipCard::SkipCard(Color color) : Card(color, CardType::Skip) {
        assert(color != Color::Wild);
    }





    std::unique_ptr<Card> SkipCard::clone() const {
        return unique_ptr<Card>(new SkipCard(getColor()));
    }
}