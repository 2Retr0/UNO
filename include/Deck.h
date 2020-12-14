#ifndef UNO_DECK_H
#define UNO_DECK_H

#include <deque>
#include "Card.h"


/** Using an internal STL deque, the Deck class functions as one would think of a deck, with minor
 *  adjustments. By default Decks will create themselves with a standard sorted UNO deck, but also
 *  have a copy constructor to set its Cards to those of another Deck. While the deck is built using
 *  an internal STL deque, it functions much like a queue, only allowing insertions in the 'back'
 *  and removals from the 'front'. The Deck class also has a getter for the cardCount, as well as an
 *  isEmpty() method to check if the Deck is empty. Decks can have Cards added to them (through the
 *  back), can be cleared, and could be shuffled as well.
**/
namespace cs110c_uno {
    class Deck {
    public:
        // or maybe a file to hold the types of cards?
        static const int NUMBERED_CARD_AMOUNT = 76;
        static const int SKIP_CARD_AMOUNT = 8;
        static const int REVERSE_CARD_AMOUNT = 8;
        static const int DRAW_TWO_CARD_AMOUNT = 8;
        static const int DRAW_FOUR_CARD_AMOUNT = 4;
        static const int WILD_CARD_AMOUNT = 4;

        Deck(); // standard deck
        Deck(const Deck& deck); // unused
        friend std::ostream& operator<<(std::ostream& out, const Deck& deck);
        Deck& operator=(const Deck& right);

        [[nodiscard]] int getCardCount() const;
        [[nodiscard]] bool isEmpty() const;

        void add(std::unique_ptr<Card> card);
        [[nodiscard]] std::unique_ptr<Card> take();
        void clear();
        void shuffle();
    private:
        std::deque<std::unique_ptr<Card>> cards;
    };
}


#endif //UNO_DECK_H
