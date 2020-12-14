#ifndef UNO_DRAWTWOCARD_H
#define UNO_DRAWTWOCARD_H

#include "Card.h"


namespace cs110c_uno {
    class DrawTwoCard : public Card {
    public:
        explicit DrawTwoCard(Color color);
        [[nodiscard]] std::unique_ptr<Card> clone() const override;
    };
}


#endif //UNO_DRAWTWOCARD_H
