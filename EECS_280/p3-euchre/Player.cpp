// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


class Human : public Player {
private: 
    std::string human_name;
    
    std::string strategy;
    std::vector <Card> player_cards;
public:
    Human(const std::string name_in,const std::string strategy_in)
        : human_name(name_in), strategy(strategy_in) {};

    //EFFECTS returns player's name
    const std::string & get_name() const override {
        return human_name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
            player_cards.push_back(c);
            std::sort(player_cards.begin(), player_cards.end());
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
                              std::string action;
                              for (size_t i = 0; i < player_cards.size(); i++){
                                  std::cout << "Human player " << this->get_name(); 
                                  std::cout << "'s hand: [" << i << "] ";
                                  std::cout << player_cards.at(i)<< '\n'; 
                              } 
                              
                                 std::cout << "Human player " << this->get_name(); 
                                 std::cout << ", please enter a suit, or \"pass\":";
                                 std::cout <<  '\n';
                                 std::cin >> action;
                                 if (action == "pass") {
                                     return false;
                                 }
                                 else{
                                     order_up_suit = action;
                                     return true;
                                 }
                              
                              return false;
                          }
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override{
        int discard;
        for (size_t i = 0; i < player_cards.size(); i++){
            std::cout << "Human player " << this->get_name();
            std::cout << "'s hand: [" << i << "] " << player_cards.at(i)<< '\n'; 
        }
        std::cout << "Discard upcard: [-1]" << '\n';
        std::cout << "Human player Judea, please select a card to discard:" << '\n';
        std::cin >> discard;
        if (discard != -1) {
            player_cards.push_back(upcard);
            player_cards.erase(player_cards.begin() + discard);
        }
        
        std::sort(player_cards.begin(), player_cards.end());
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) override{
        int lead_card;
        Card card_lead;
        for (size_t i = 0; i < player_cards.size(); i++){
            std::cout << "Human player " << this->get_name();
            std::cout << "'s hand: [" << i << "] " << player_cards.at(i) << '\n'; 
        }
        std::cout << "Human player " << this->get_name();
        std::cout << ", please select a card:" << '\n';
        std:: cin >> lead_card;
        card_lead = player_cards.at(lead_card);
        player_cards.erase(player_cards.begin()+lead_card);
        return card_lead;
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) override{
        int card_play;
        Card card_played;
        for (size_t i = 0; i < player_cards.size(); i++){
            std::cout << "Human player " << this->get_name();
            std::cout << "'s hand: [" << i << "] " << player_cards.at(i)<< '\n'; 
        }
        std::cout << "Human player " << this->get_name();
        std::cout << ", please select a card:" << '\n';
        std::cin >> card_play;
        card_played = player_cards.at(card_play);
        player_cards.erase(player_cards.begin()+card_play);
        return card_played;
    }


};

class Simple : public Player {
private: 
    std::string simple_name;
    std::string strategy;
    std::vector <Card> player_cards;
public:
    Simple(const std::string name_in, const std::string strategy_in)
        : simple_name(name_in), strategy(strategy_in) {};

    //EFFECTS returns player's name
    const std::string & get_name() const override {
        return simple_name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override{
        player_cards.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override{
                              int trump_face = 0;
                              std::string trump = upcard.get_suit();
                              if (round == 1) {
                                  int trump_face = 0;
                                  std::string trump = upcard.get_suit();
                                  for (int i = 0; i < 5; i++) {
                                      if (player_cards.at(i).get_suit() == trump && 
                                      player_cards.at(i).is_face()) {
                                          trump_face++;
                                      }
                                      if(player_cards.at(i).is_left_bower(trump)) {
                                          trump_face++;
                                      }
                                  }
                                  if (trump_face >= 2) {
                                      order_up_suit = trump;
                                      return true;
                                  } 
                                  return false;
                              }
                              if (round == 2) {
                                  if (is_dealer == true) {
                                      order_up_suit = Suit_next(trump);
                                      return true;
                                  }
                                  
                                      std::string new_trump = Suit_next(trump);
                                      for (int i = 0; i < 5; i++) {
                                          if(player_cards.at(i).get_suit() == new_trump 
                                          && player_cards.at(i).is_face()){
                                              trump_face++;
                                          }
                                          if(player_cards.at(i).is_left_bower(new_trump))
                                          {
                                              trump_face++;
                                          }
                                      }
                                      if (trump_face >= 1) {
                                          order_up_suit = new_trump;
                                          return true;
                                      }
                                  
                                  return false;
                              }
                              return false;
                          }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override{
        player_cards.push_back(upcard);
        int lowest_card = 0;
        Card low_card = player_cards.at(0);
        for(int i = 1; i < 6; i++) {
            if (Card_less(player_cards.at(i), low_card, upcard.get_suit())) {
                lowest_card = i;
                low_card = player_cards.at(i);
            }
        }
        player_cards.erase(player_cards.begin()+lowest_card);
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) override{
        int lead_card = 225;
        Card card_lead;
        for (size_t i = 0; i < player_cards.size(); i++) {
            if (player_cards.at(i).get_suit(trump) != trump) {
                if (lead_card == 225) {
                    lead_card = i;
                    card_lead = player_cards.at(i);
                }
            
                if (player_cards.at(i) > card_lead && 
                player_cards.at(i).get_suit(trump) != trump) {
                        lead_card = i;
                        card_lead = player_cards.at(i);
                }
                
            }
        }
        if (lead_card == 225) {
            lead_card = 0;
            card_lead = player_cards.at(0);
            for (size_t i = 1; i < player_cards.size(); i++) {
                if(Card_less(card_lead, player_cards.at(i), trump)) {
                    lead_card = i;
                    card_lead = player_cards.at(i);
                    
                }
            }
        }
        player_cards.erase(player_cards.begin() + lead_card);
        return card_lead;
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) override{
        int play_card = 225;
        Card card_play;
        for(size_t i = 0; i < player_cards.size(); i++) {
            if (player_cards.at(i).get_suit(trump) == led_card.get_suit(trump)){
                if (play_card == 225) {
                    play_card = i;
                    card_play = player_cards.at(i);
                }
                if (Card_less(card_play,player_cards.at(i),trump)) {
                    play_card = i;
                    card_play = player_cards.at(i);
                }
            }
        }
        if (play_card == 225) {
            play_card = 0;
            card_play =  player_cards.at(0);
            for (size_t i = 1; i < player_cards.size(); i++) {
                if (Card_less(player_cards.at(i), card_play, trump)){
                    play_card = i;
                    card_play = player_cards.at(i);
                }
            }
        }
        player_cards.erase(player_cards.begin() + play_card);
        return card_play;
    }
};

Player * Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new Simple(name, strategy);
    }
    if (strategy == "Human") {
        return new Human(name, strategy);
    }
    
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}