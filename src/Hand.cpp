#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include "Hand.h"

using namespace std;


namespace cs110c_uno {
    ostream &operator<<(ostream& out, const Hand& hand) {
        if (hand.cards.empty()) return out << "[EMPTY]";
        int cardNumber = 1;
        string separation = string(30, ' ') + " | ";
        ostringstream oss;

        out << string(100, '=') << "\n";
        out << "| ";
        for (const auto & card : hand.cards) {
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





    int Hand::getCardCount() const {
        return cards.size();
    }





    unique_ptr<Card> Hand::deal(unique_ptr<Card> card) {
        auto it = find_if(cards.begin(), cards.end(), [&](const unique_ptr<Card>& searchCard){ return *searchCard == *card; });

        if (it != cards.end()) {
            auto cardReturned = move(*it);
            cards.erase(it);
            return move(cardReturned);
        }
        return nullptr;
    }





    std::unique_ptr<Card> Hand::deal(int index) {
        unique_ptr<Card> cardReturned;
        auto it = cards.begin();
        for (int i = 0 ; i < index - 1; i++) {
            ++it;
        }
        cardReturned = move(*it);
        cards.erase(it);
        return move(cardReturned);
    }





    void Hand::add(unique_ptr<Card> card) {
        cards.push_back(move(card));
    }





    void Hand::sort() {
        cards.sort(ptrLessThan);
    }





    bool Hand::ptrLessThan(std::unique_ptr<Card>& left, std::unique_ptr<Card>& right) {
        return *left < *right;
    }
}