#ifndef UNO_SKIPCARD_H
#define UNO_SKIPCARD_H

#include "Card.h"


namespace cs110c_uno {
    class SkipCard : public Card {
    public:
        explicit SkipCard(Color color);
        [[nodiscard]] std::unique_ptr<Card> clone() const override;
    };
}


#endif //UNO_SKIPCARD_H
