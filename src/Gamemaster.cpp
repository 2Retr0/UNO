#include <iostream>
#include <memory>
#include <string>
#include <cassert>
#include <iterator>
#include <sstream>
#include <stack>
#include "NumberedCard.h"
#include "Gamemaster.h"

using namespace std;


namespace cs110c_uno {
    Gamemaster::Gamemaster() : Gamemaster(4, 7) {}

    Gamemaster::Gamemaster(int playerCount, int startingCardCount) {
        string name;
        assert(drawDeck.getCardCount() / playerCount > startingCardCount);
        this->startingCardCount = startingCardCount;

        // Adding Players.
        for (int i = 0; i < playerCount; i++) {
            cout << "Enter player #" << i + 1 << "'s name:";
            getline(cin, name);

            // If the inputted name is an empty string, give a default Player name.
            if (name.empty())
                name = "Player #" + to_string(i + 1);

            // Push a new Player onto the playerQueue.
            playerQueue.push(std::make_unique<Player>(name));

            // Giving startingCardCount cards to Player.
            for (int j = 0; j < startingCardCount; j++) {
                playerQueue.back()->giveCard(drawDeck.take());
            }
            // Sort the hand of the Player.
            playerQueue.back()->sortHand();
            // Flush the stream.
            cin.clear();
        }
        // TODO: Find another way to have a deck initialize empty!
        discardDeck.clear();
    }





    unique_ptr<Card> Gamemaster::giveCard() {
        ensureCapacity();
        return drawDeck.take();
    }





    void Gamemaster::takeTurn() {
        unique_ptr<Card> selectedCard;

        // Checking if the game has just started. If so, run the proper setup.
        checkForGameStart();
        // Checking for the lastPlayedCard and if it should have any action on the currently playing Player.
        lastPlayedCardActionOnPlayer();

        // Print Player turn.
        cout << printPlayerTurn() << "\n";
        // Print out the Player's Deck for them to view.
        cout << playerQueue.front()->getName() << "'s Deck: " << printLastPlayedCard() << "\n";

        // Ask the player for a Card.
        selectedCard = playerQueue.front()->selectCard(*this);
        // While a lastPlayedCard exists and the selected Card is not valid ask for another Card.
        while (!validPlayedCard(selectedCard)) {
            cout << "[" << *selectedCard << "] is not of the same color or value! " << printLastPlayedCard() << "\n";
            playerQueue.front()->giveCard(move(selectedCard));
            playerQueue.front()->sortHand();
            selectedCard = playerQueue.front()->selectCard(*this);
        }

        // Set lastPlayedCard to the selectedCard and move the selectedCard to the discardDeck.
        lastPlayedCard = selectedCard->clone();
        discardDeck.add(move(selectedCard));
        cout << playerQueue.front()->getName() << " has played [" << *lastPlayedCard << "]!\n" << endl;

        // Check if the playing Player has won.
        if (playerHasWon(playerQueue.front())) {
            gameFinished = true;
            return;
        }

        // Move the Player to the back of the playerQueue only if the played Card isn't a reverse.
        // This is to ensure that when the playerQueue is reversed next turn, the Player that just
        // went will not go again.
        if (lastPlayedCard->getCardType() != Card::CardType::Reverse) {
            playerQueue.push(move(playerQueue.front()));
            playerQueue.pop();
        }
    }





    void Gamemaster::reset() {
        stack<string> playerNameStack;

        // Resetting member fields.
        lastPlayedCard = nullptr;
        gameFinished = false;

        // Resetting decks.
        discardDeck.clear();
        drawDeck = Deck();

        // Emptying playerQueue holding their names into playerNameStack.
        while (!playerQueue.empty()) {
            playerNameStack.push(playerQueue.front()->getName());
            playerQueue.pop();
        }

        // Emptying playerNameStack, using the names to create new players to fill playerQueue.
        while (!playerNameStack.empty()) {
            // Push a new Player onto the playerQueue.
            playerQueue.push(std::make_unique<Player>(playerNameStack.top()));

            // Giving startingCardCount cards to Player.
            for (int j = 0; j < startingCardCount; j++) {
                playerQueue.back()->giveCard(drawDeck.take());
            }
            // Sort the hand of the Player.
            playerQueue.back()->sortHand();
            playerNameStack.pop();
        }
    }





    // TODO: Man, this prints out some crap.
    ostream &operator<<(ostream &out, const Gamemaster &gamemaster) {
        return out << "DRAW DECK:\n" << gamemaster.drawDeck << "cardCount: " << gamemaster.drawDeck.getCardCount() << "\n\n"
                   << gamemaster.playerQueue.front()->getName() << "'S HAND: " << endl << *gamemaster.playerQueue.front()
                   << "cardCount: " << gamemaster.playerQueue.front()->getCardCount() << "\n";
    }





    void Gamemaster::setLastPlayedWildCardColor(Card::Color color) {
        lastPlayedWildCardColor = color;
    }





    bool Gamemaster::isGameFinished() const {
        return gameFinished;
    }





    std::unique_ptr<Player> &Gamemaster::getCurrentPlayer() const {
        return (unique_ptr<Player> &)playerQueue.front();
    }





    void Gamemaster::checkForGameStart() {
        unique_ptr<Card> initialDrawCard;

        // If there isn't a lastPlayedCard (aka the game has just started), draw a Card from the drawDeck.
        if (lastPlayedCard == nullptr) {
            initialDrawCard = drawDeck.take();
            // If the initialDrawCard is a DrawFourCard, put the Card back into the drawDeck, reshuffle, and re-deal.
            while (initialDrawCard->getCardType() == Card::CardType::DrawFour) {
                drawDeck.add(move(initialDrawCard));
                drawDeck.shuffle();
                initialDrawCard = drawDeck.take();
            }

            cout << "The first played card of the game is [" << *initialDrawCard << "]! ";
            cout << playerQueue.front()->getName() << " will go first.\n\n";

            // If the initialDrawCard is a WildCard, have the first Player select a Color for the WildCard.
            if (initialDrawCard->getCardType() == Card::CardType::Wild) {
                cout << "Since the first played card was a wild card, " << playerQueue.front()->getName();
                cout << " will choose the color for their turn:\n";
                lastPlayedWildCardColor = Player::selectWildColor();
                cout << "\n";
            } else if (initialDrawCard->getCardType() == Card::CardType::Reverse) {
                // If the initialDrawCard is a ReverseCard move the Player that is currently in the front
                // of the playerQueue to the back, so when the queue is reversed, that Player is pushed back
                // to the front of the queue.
                playerQueue.push(move(playerQueue.front()));
                playerQueue.pop();
            }
            // set lastPlayedCard to the initialDrawCard and move the initialDrawCard to the discardDeck.
            lastPlayedCard = initialDrawCard->clone();
            discardDeck.add(move(initialDrawCard));
        }
    }





    void Gamemaster::lastPlayedCardActionOnPlayer() {
        unique_ptr<Card> cardToGive;

        if (lastPlayedCard->getCardType() == Card::CardType::Reverse) {
            reverseUniquePtrQueue(playerQueue);
            cout << "Since the last played card was a reverse card, the ordering of players will be flipped!";
            cout << " (" << playerQueue.front()->getName() << " will now be going next)\n\n";
            // When reversing the playerQueue, the Player that has just played has been moved to the back
            // of the queue. This means that they would play again for their own next turn. To compensate for
            // this, we skip their turn.
        }
        else if (lastPlayedCard->getCardType() == Card::CardType::Skip) {
            cout << "Since the last played card was a skip card, " << playerQueue.front()->getName();
            cout << " will have their turn skipped!\n\n";
            // Push the Player that is to play *next* (front of playerQueue) to the back.
            // This means that that Player will play for the current turn skipping the original Player.
            playerQueue.push(move(playerQueue.front()));
            playerQueue.pop();
        }
        else if (lastPlayedCard->getCardType() == Card::CardType::DrawTwo) {
            cout << "Since the last played card was a draw two card, " << playerQueue.front()->getName();
            cout << " will be drawn two cards (";
            // Give the Player two Cards and skip their turn.
            for (int i = 0; i < 2; i++) {
                cout << "["; cardToGive = giveCard(); cout << *cardToGive << "]";
                playerQueue.front()->giveCard(giveCard());
                if (i < 1) cout << " and ";
            }
            playerQueue.front()->sortHand();
            cout << ") as well as have their turn skipped!\n\n";
            playerQueue.push(move(playerQueue.front()));
            playerQueue.pop();
        }
        else if (lastPlayedCard->getCardType() == Card::CardType::DrawFour) {
            cout << "Since the last played card was a draw four card, " << playerQueue.front()->getName();
            cout << " will be drawn four cards (";
            // Give the Player four Cards and skip their turn.
            for (int i = 0; i < 4; i++) {
                cout << "["; cardToGive = giveCard(); cout << *cardToGive << "]";
                if (i < 2) cout << ", ";
                if (i == 2) cout << ", and ";
                playerQueue.front()->giveCard(giveCard());
            }
            playerQueue.front()->sortHand();
            cout << ") as well as have their turn skipped!\n\n";
            playerQueue.push(move(playerQueue.front()));
            playerQueue.pop();
        }
    }





    std::string Gamemaster::printPlayerTurn() const {
        int arrowLength = (91 - (int)playerQueue.front()->getName().length()) / 2;
        ostringstream oss;  // Building the string using an ostringstream.

        oss << string(arrowLength, '>') << " " << playerQueue.front()->getName() << "'s Turn " << string(arrowLength, '<');
        // Add any needed '<' to make sure that the string is flush with 100 characters for the later printed Deck.
        if (oss.str().length() < 100) {
            oss << string(100 - oss.str().length(), '<');
        }
        return oss.str();
    }





    string Gamemaster::printLastPlayedCard() const {
        string colors[] = { "Red", "Yellow", "Green", "Blue" };
        ostringstream oss;  // Building the string using an ostringstream.

        oss << "(Last played card: [" << *lastPlayedCard;
        // If the lastPlayedCard is a WildCard, also add the selected color to the string.
        if (lastPlayedCard->getColor() == Card::Color::Wild) {
            // We cast the lastPlayedWildCardColor to an int as to specify an index for
            // the carefully made colors array.
            oss << ", Chosen Color: " << colors[static_cast<int>(lastPlayedWildCardColor)];
        }
        oss << "])";
        return oss.str();
    }





    bool Gamemaster::validPlayedCard(unique_ptr<Card>& card) const {
        if (lastPlayedCard->getColor() == card->getColor() || card->getColor() == Card::Color::Wild) {
            // If the color of the Cards are the same or the Card is a WildCard, return true.
            return true;
        } else if (lastPlayedCard->getColor() == Card::Color::Wild) {
            // If the last played Card is a WildCard, return whether the chosen Card color equals the Card color.
            return lastPlayedWildCardColor == card->getColor();
        } else if (lastPlayedCard->getCardType() == card->getCardType()) {
            if (lastPlayedCard->getCardType() == Card::CardType::Numbered &&
                card->getCardType() == Card::CardType::Numbered) {
                // If both Cards are numberedCards, return whether their values match.
                return dynamic_cast<const NumberedCard&>(*lastPlayedCard).getValue() == dynamic_cast<const NumberedCard&>(*card).getValue();
            }
            // For all other Cards that are not numberedCards, as long as they are the same cardType, return true.
            return true;
        }
        // Otherwise, both the colors and cardTypes do not match so return false.
        return false;
    }





    void Gamemaster::ensureCapacity() {
        // If the both the drawDeck and discardDeck are empty, throw an exception.
        if (drawDeck.isEmpty() && discardDeck.isEmpty()) {
            throw runtime_error("Need to re-add cards to drawDeck but discardDeck is somehow empty!");
        } else if (drawDeck.isEmpty()) {
            // Otherwise, simply set the drawDeck to whatever the discardDeck is and clear the discardDeck.
            // The drawDeck will be automatically shuffled.
            drawDeck = discardDeck;
            discardDeck.clear();
        }
    }





    bool Gamemaster::playerHasWon(unique_ptr<Player> &player) {
        return player->getCardCount() <= 1;
    }





    template<class T>
    void Gamemaster::reverseUniquePtrQueue(queue<std::unique_ptr<T>>& queue) {
        stack<unique_ptr<T>> stack;

        while (!queue.empty()) {
            stack.push(move(queue.front()));
            queue.pop();
        }
        while (!stack.empty()) {
            queue.push(move(stack.top()));
            stack.pop();
        }
    }
}