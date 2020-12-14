#ifndef UNO_PLAYER_H
#define UNO_PLAYER_H

#include <functional>
#include "Hand.h"


/** The Player class contains a Hand as well as a name std::string to give the Player an identifiying
 *  name. The Player class includes the necessary methods to have the player choose and return a Card
 *  (and choose a color if the Card they return is a wildCard) as well as the ability to sort their
 *  hand when called. The Player class contains getters for the cardCount and can be given Cards as well.
**/
namespace cs110c_uno {
    class Gamemaster;
    class Player {
    public:
        Player();
        explicit Player(std::string& name);
        friend std::ostream& operator<<(std::ostream& out, const Player& player);

        [[nodiscard]] int getCardCount() const;
        [[nodiscard]] std::string getName() const;

        std::unique_ptr<Card> selectCard(Gamemaster& gamemaster);
        [[nodiscard]] static Card::Color selectWildColor();
        void giveCard(std::unique_ptr<Card> card);
        void sortHand();
    private:
        std::string name;
        Hand hand;
        static bool validInput(const std::string &string, int lowIntRange, int highIntRange, bool strComp);
    };
}


#endif //UNO_PLAYER_H
