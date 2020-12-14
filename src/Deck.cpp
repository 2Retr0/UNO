#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <sstream>
#include "Deck.h"
#include "NumberedCard.h"
#include "SkipCard.h"
#include "ReverseCard.h"
#include "DrawTwoCard.h"
#include "DrawFourCard.h"
#include "WildCard.h"
using namespace std;


namespace cs110c_uno {
    typedef Card::Color Color;

    Deck::Deck() {
        Color colors[] = { Color::Red, Color::Yellow, Color::Green, Color::Blue };
        int perColorCardAmount = NUMBERED_CARD_AMOUNT / 4;
        int i;
        int cardValue;

        for (Color color : colors) {
            i = perColorCardAmount;
            cardValue = 9;
            while(i > 0) {
                while (cardValue >= 0 && i > 0) {
                    cards.push_back(unique_ptr<Card>(new NumberedCard(color, cardValue)));
                    cardValue--;
                    i--;
                }
                cardValue = 9;
            }
            for (int j = 0; j < SKIP_CARD_AMOUNT / 4; j++) {
                cards.push_back(unique_ptr<Card>(new SkipCard(color)));
            }
            for (int j = 0; j < REVERSE_CARD_AMOUNT / 4; j++) {
                cards.push_back(unique_ptr<Card>(new ReverseCard(color)));
            }
            for (int j = 0; j < DRAW_TWO_CARD_AMOUNT / 4; j++) {
                cards.push_back(unique_ptr<Card>(new DrawTwoCard(color)));
            }
        }
        for (int j = 0; j < WILD_CARD_AMOUNT; j++) {
            cards.push_back(unique_ptr<Card>(new WildCard()));
        }
        for (int j = 0; j < DRAW_FOUR_CARD_AMOUNT; j++) {
            cards.push_back(unique_ptr<Card>(new DrawFourCard()));
        }

        shuffle();
    }





    Deck::Deck(const Deck &deck) {
        for (const auto& card : deck.cards) {
            cards.push_back(card->clone());
        }

        shuffle();
    }





    std::ostream &operator<<(ostream &out, const Deck &deck) {
        if (deck.cards.empty()) return out << "[EMPTY]";
        int cardNumber = 1;
        string separation = string(30, ' ') + " | ";
        ostringstream oss;

        out << string(100, '=') << "\n";
        out << "| ";
        for (const auto & card : deck.cards){
            oss << cardNumber << ") " << *card;
            oss << string(30 - oss.str().length(), ' ');
            out << oss.str() << " | ";
            if (cardNumber % 3 == 0)
                out << "\n| ";
            cardNumber++;
            oss.str("");
            oss.clear();
        }
        while (cardNumber % 3 != 0) {
            out << separation;
            cardNumber++;
        }
        out << separation << "\n";
        out << string(100, '=') << "\n";
        return out;
    }





    Deck &Deck::operator=(const Deck &right) {
        if (this != &right) {
            cards.clear();
            for (const auto &card : right.cards) {
                cards.push_back(card->clone());
            }
            shuffle();
        }
        return *this;
    }





    int Deck::getCardCount() const {
        return cards.size();
    }





    bool Deck::isEmpty() const {
        return cards.empty();
    }





    void Deck::add(std::unique_ptr<Card> card) {
        cards.push_front(move(card));
    }





    unique_ptr<Card> Deck::take() {
        unique_ptr<Card> frontCard = move(cards.back());
        cards.erase(--cards.end());
        return frontCard;
    }





    void Deck::clear() {
        cards.clear();
    }





    void Deck::shuffle() {
        auto randomDevice = std::random_device {};
        auto randomNumberGenerator = default_random_engine { randomDevice() };
        std::shuffle(begin(cards), end(cards), randomNumberGenerator);
    }
}