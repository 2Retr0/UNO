#ifndef UNO_NUMBEREDCARD_H
#define UNO_NUMBEREDCARD_H

#include "Card.h"


namespace cs110c_uno {
    class NumberedCard : public Card {
    public:
        static const int MIN_VALUE = 0;
        static const int MAX_VALUE = 9;

        NumberedCard(Color color, int value);
        [[nodiscard]] int getValue() const;
        [[nodiscard]] std::unique_ptr<Card> clone() const override;
    protected:
        [[nodiscard]] bool lessThan(const Card& right) const override;
        [[nodiscard]] bool equals(const Card& right) const override;
        void print(std::ostream& out) const override;
    private:
        int value;
    };
}


#endif //UNO_NUMBEREDCARD_H
