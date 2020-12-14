#ifndef UNO_DRAWFOURCARD_H
#define UNO_DRAWFOURCARD_H

#include "WildCard.h"


namespace cs110c_uno {
    class DrawFourCard : public WildCard {
    public:
        DrawFourCard();
        [[nodiscard]] std::unique_ptr<Card> clone() const override;
    };
}


#endif //UNO_DRAWFOURCARD_H
