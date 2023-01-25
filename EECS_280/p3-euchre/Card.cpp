// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
static int const return_suit_index (const Card *c1);
static int const return_rank_index (const Card *c1);

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
  //EFFECTS Initializes Card to the Two of Spades
  Card::Card(): rank(RANK_TWO), suit(SUIT_SPADES){}

  //REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
  //  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
  //  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
  //EFFECTS Initializes Card to specified rank and suit
  Card::Card(const std::string &rank_in, const std::string &suit_in):
    rank(rank_in), suit(suit_in){}

  //EFFECTS Returns the rank
  std::string Card::get_rank() const{
      return rank;
  }

  //EFFECTS Returns the suit.  Does not consider trump.
  std::string Card::get_suit() const{
      return suit;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  std::string Card::get_suit(const std::string &trump) const{
      if (is_left_bower(trump)){
          return trump;
      }
      else 
        return suit;
  }

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool Card::is_face() const{
      if (rank == RANK_JACK || rank == RANK_QUEEN 
      || rank == RANK_KING || rank == RANK_ACE){
          return true;
      }
      else
        return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(const std::string &trump) const{
      if (rank == RANK_JACK && suit == trump){
        return true;
      }
      else
        return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
  bool Card::is_left_bower(const std::string &trump) const{
      if (rank == RANK_JACK){
          if (trump == SUIT_SPADES && suit == SUIT_CLUBS){
            return true;
          }
          if (trump == SUIT_CLUBS && suit == SUIT_SPADES){
            return true;
          }
          if (trump == SUIT_HEARTS && suit == SUIT_DIAMONDS){
            return true;
          }
          if (trump == SUIT_DIAMONDS && suit == SUIT_HEARTS){
            return true;
          }
          else
            return false;
      }
      else
        return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool Card::is_trump(const std::string &trump) const{
      if (get_suit(trump) == trump){
          return true;
      }
      else
        return false;
  }

  //EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() == rhs.get_rank()){
    return (return_suit_index(&lhs) < return_suit_index(&rhs));
  }
  else {
    return (return_rank_index(&lhs) < return_rank_index(&rhs));
  }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() == rhs.get_rank()){
    return (return_suit_index(&lhs) <= return_suit_index(&rhs));
  }
  else {
    return (return_rank_index(&lhs) < return_rank_index(&rhs));
  }
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() == rhs.get_rank()){
    return (return_suit_index(&lhs) > return_suit_index(&rhs));
  }
  else {
    return (return_rank_index(&lhs) > return_rank_index(&rhs));
  }
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() == rhs.get_rank()){
    return (return_suit_index(&lhs) >= return_suit_index(&rhs));
  }
  else {
    return (return_rank_index(&lhs) > return_rank_index(&rhs));
  }
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
    if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()){
        return true;
    }
    else
        return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
    if (lhs.get_rank() != rhs.get_rank() || lhs.get_suit() != rhs.get_suit()){
        return true;
    }
    else
        return false;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit){
    if (suit == Card::SUIT_SPADES){
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_CLUBS){
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_DIAMONDS){
        return Card::SUIT_HEARTS;
    }
    else {
        return Card::SUIT_DIAMONDS;
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){

  if (b.is_right_bower(trump)) {
    return true;
  }
  if (a.is_right_bower(trump)) {
    return false;
  }
  if (a.is_left_bower(trump) && !b.is_left_bower(trump)) {
    return false;
  }
  if (b.is_left_bower(trump) && !a.is_right_bower(trump)) {
    return true;
  }
  if (a.is_trump(trump) && b.is_trump(trump) && a < b) {
    return true;
  }
    if (!a.is_trump(trump) && !b.is_trump(trump) && a < b) {
    return true; 
  }
  if (!a.is_trump(trump) && b.is_trump(trump)) {
    return true;
  }
  return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
  if (a.get_suit(trump) != led_card.get_suit(trump) 
  && b.get_suit(trump) != led_card.get_suit(trump)) {
    return Card_less(a,b,trump);
  }
  if(trump == led_card.get_suit(trump)) {
    return Card_less(a,b,trump);
  }
  if(a.get_suit(trump) == led_card.get_suit(trump)
  && b.get_suit(trump) == led_card.get_suit(trump) && a < b)
  {
    return true;
  }
  
  if (a.get_suit(trump) != led_card.get_suit(trump) && !a.is_trump(trump) 
  && b.get_suit(trump) == led_card.get_suit(trump)) {
    return true;
  }
  if (a.get_suit(trump) != led_card.get_suit(trump) && a.is_trump(trump) 
  && b.get_suit(trump) == led_card.get_suit(trump)) {
    return false;
  }
  if (a.get_suit(trump) == led_card.get_suit(trump) 
  && b.get_suit(trump) != led_card.get_suit(trump) && !b.is_trump(trump)) {
    return false;
  }
  if (a.get_suit(trump) == led_card.get_suit(trump) 
  && b.get_suit(trump) != led_card.get_suit(trump) && b.is_trump(trump)) {
    return true;
  }
  
  return false;
}

static int const return_suit_index(const Card *c1){
  std::string cardSuit = c1->get_suit();
  int i = 0;

  while (cardSuit != SUIT_NAMES_BY_WEIGHT[i]){
    i++;
  }
  return i;
}

static int const return_rank_index(const Card *c1){
  std::string cardRank = c1->get_rank();
  int i = 0;

  while (cardRank != RANK_NAMES_BY_WEIGHT[i]){
    i++;
  }
  return i;
}
