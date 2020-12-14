#ifndef UNO_CARD_H
#define UNO_CARD_H

#include <memory>


/** The abstract Card class sets up the attributes for any subclass by allowing them to each assign themselves
 *  a pseudo-static CardType for comparisons as well as a variable color depending on their needs. The abstract
 *  Card class also comes with some pre-implemented methods for getting the Colors and CardTypes as well as
 *  basic operator overloading for the '<<', '<' and '==' operators which can be overwritten using the protected
 *  'print', 'lessThan', and 'equals' methods.
**/
namespace cs110c_uno {
    // deck of cards for uno: https://exceptionnotfound.net/content/images/2016/08/uno-card-deck.png
    class Card {
    public:
        enum class Color { Red, Yellow, Green, Blue, Wild };
        enum class CardType { Numbered, Skip, Reverse, DrawTwo, Wild, DrawFour };

        virtual ~Card() = default;

        [[nodiscard]] virtual Color getColor() const;
        [[nodiscard]] virtual CardType getCardType() const;
        friend std::ostream& operator<<(std::ostream& out, const Card& card);
        friend bool operator<(const Card& left, const Card& right);
        friend bool operator==(const Card& left, const Card& right);
        [[nodiscard]] virtual std::unique_ptr<Card> clone() const = 0; // 'deep copy'
    protected:
        explicit Card(Color color, CardType cardType);
        [[nodiscard]] virtual bool lessThan(const Card& right) const;
        [[nodiscard]] virtual bool equals(const Card& right) const;
        virtual void print(std::ostream& out) const;
    private:
        CardType cardType;
        Color color;
    };
}


#endif //UNO_CARD_H
