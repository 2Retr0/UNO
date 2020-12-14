#ifndef UNO_HAND_H
#define UNO_HAND_H

#include <list>
#include <memory>
#include "Card.h"


/** Using an internal STL list Hand class functions similarly to a sorted list, however is specified so that
 *  the user must decide when the Hand should be sorted (as to prevent excessive sorting from multiple Cards
 *  being added). The Hand class is constructed without any Cards. The Hand Class has a getter for getting
 *  the cardCount as well as two deal methods one for dealing a Card from its list with a reference, and
 *  another dealing a Card from its list with a known index. The Hand class also contains a method for sorting
 *  its internal list by color then by cardType or value in the case of a NumberedCard; this is achieved
 *  using the private ptrLessThan method which compares two std::unique_ptr<Card>'s.
**/
namespace cs110c_uno {
    class Hand {
    public:
        Hand() = default; // empty hand
        friend std::ostream& operator<<(std::ostream& out, const Hand& hand);

        [[nodiscard]] int getCardCount() const;

        void add(std::unique_ptr<Card> card);
        std::unique_ptr<Card> deal(std::unique_ptr<Card> card);
        std::unique_ptr<Card> deal(int index);
        void sort(); // user is responsible for calling sort after adding
    private:
        std::list<std::unique_ptr<Card>> cards;
        static bool ptrLessThan(std::unique_ptr<Card>& left, std::unique_ptr<Card>& right);
    };
}


#endif //UNO_HAND_H
