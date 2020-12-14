#ifndef UNO_REVERSECARD_H
#define UNO_REVERSECARD_H

#include "Card.h"


namespace cs110c_uno {
    class ReverseCard : public Card {
    public:
        explicit ReverseCard(Color color);
        [[nodiscard]] std::unique_ptr<Card> clone() const override;
    };
}


#endif //UNO_REVERSECARD_H
