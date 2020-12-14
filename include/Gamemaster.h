#ifndef UNO_GAMEMASTER_H
#define UNO_GAMEMASTER_H

#include <queue>
#include "Player.h"
#include "Hand.h"
#include "Deck.h"


/** The gamemaster class sets the rules for a game of UNO and communicates with the Player class in order
 *  to ask them for selections and such. The Gamemaster class uses an STL queue to decide which player gets
 *  to go next as well as a pointer to a lastPlayedCard for game information. The Gamemaster class also
 *  contains two Decks, a drawDeck and discardDeck which correspond to the two piles in an actual game of UNO.
 *  When the drawDeck becomes empty, it is refilled from the discardDeck.
**/
namespace cs110c_uno {
    class Player;
    class Gamemaster {
    public:
        Gamemaster();
        explicit Gamemaster(int playerCount, int startingCardCount);
        friend std::ostream& operator<<(std::ostream& out, const Gamemaster& gamemaster); // for debug purposes

        void setLastPlayedWildCardColor(Card::Color color);
        [[nodiscard]] bool isGameFinished() const;
        [[nodiscard]] std::unique_ptr<Player>& getCurrentPlayer() const;

        std::unique_ptr<Card> giveCard();
        void takeTurn();
        void reset();
    private:
        std::queue<std::unique_ptr<Player>> playerQueue;
        std::unique_ptr<Card> lastPlayedCard = nullptr;
        Card::Color lastPlayedWildCardColor;
        Deck drawDeck;
        Deck discardDeck;
        bool gameFinished = false;
        int startingCardCount;
        void lastPlayedCardActionOnPlayer();
        [[nodiscard]] std::string printPlayerTurn() const;
        [[nodiscard]] std::string printLastPlayedCard() const;
        [[nodiscard]] bool validPlayedCard(std::unique_ptr<Card>& card) const;
        void checkForGameStart();
        void ensureCapacity();
        static bool playerHasWon(std::unique_ptr<Player>& player);
        template <class T> static void reverseUniquePtrQueue(std::queue<std::unique_ptr<T>>& queue);
    };
}


#endif //UNO_GAMEMASTER_H
