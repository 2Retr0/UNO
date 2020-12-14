#ifndef UNO_WILDCARD_H
#define UNO_WILDCARD_H

#include "Card.h"


namespace cs110c_uno {
    class WildCard : public Card {
    public:
        WildCard();

        [[nodiscard]] std::unique_ptr<Card> clone() const override;
    protected:
        explicit WildCard(int); // a VERY bad way of doing this...
    };
}


#endif //UNO_WILDCARD_H
