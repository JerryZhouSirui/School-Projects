// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    Player * jacob = Player_factory("Jacob", "Human");
    ASSERT_EQUAL("Jacob", jacob->get_name());
    delete alice;
    delete jacob;
}

TEST(simple_make_trump_round_one_skip) {
  Player * jacob = Player_factory("Jacob", "Simple");
  jacob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  jacob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  string trump = "None";
  bool orderup = jacob->make_trump(
    Card(Card::RANK_TEN,Card::SUIT_CLUBS),    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, "None");
  delete jacob;
}

TEST(simple_make_trump_round_two_skip) {
  Player * jacob = Player_factory("Jacob", "Simple");
  jacob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  jacob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  string trump = "None";
  bool orderup = jacob->make_trump(
    Card(Card::RANK_TEN,Card::SUIT_HEARTS),    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, "None");
  delete jacob;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob makes tump
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(make_trump_simple) {
    Player * jacob = Player_factory("Jacob", "Simple");
   
    jacob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    jacob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = jacob->make_trump(
    nine_spades,    // Upcard
    true,           // jacob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete jacob;

}

TEST(manke_trump_round_two_dealer) {
    Player * jacob = Player_factory("Jacob", "Simple");
   
    jacob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    jacob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = jacob->make_trump(
    nine_spades,    // Upcard
    true,           // jacob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  delete jacob;
}

TEST(simple_lead_card) {
    Player * jacob = Player_factory("Jacob", "Simple");
   
    jacob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    jacob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card c1(Card::RANK_ACE, Card::SUIT_SPADES);
    Card lead_card = jacob->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(lead_card, c1);
    delete jacob;
    
}

TEST(simple_lead_card_all_trump) {
    Player * jacob = Player_factory("Jacob", "Simple");
   
    jacob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card lead_card = jacob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(lead_card, c1);
    delete jacob;

}

TEST(simple_play_match_led) {
  Player * jacob = Player_factory("Jacob", "Simple");
   
    jacob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    jacob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Card c1(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card played_card = jacob->play_card(c1,Card::SUIT_HEARTS);
    Card c2(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_EQUAL(c2,played_card);
    delete jacob;
}

TEST(simple_play_no_match_led) {
  Player * jacob = Player_factory("Jacob", "Simple");
   
    jacob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    jacob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card played_card = jacob->play_card(c1,Card::SUIT_HEARTS);
    Card c2(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(c2,played_card);
    delete jacob;
}

TEST(simple_play_short_hand) {
  Player * jacob = Player_factory("Jacob", "Simple");

  jacob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

  Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  Card played_card = jacob->play_card(c1,Card::SUIT_SPADES);
  ASSERT_EQUAL(played_card,Card(Card::RANK_NINE,Card::SUIT_SPADES));
  delete jacob;
}

TEST(simple_add_discard_play) {
  Player * jacob = Player_factory("Jacob", "Simple");
  jacob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
  jacob->add_and_discard(Card(Card::RANK_NINE,Card::SUIT_SPADES));
  Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  Card played_card = jacob->play_card(c1, Card::SUIT_SPADES);
  ASSERT_EQUAL(played_card, Card(Card::RANK_NINE,Card::SUIT_SPADES));
  delete jacob;
}

TEST(simple_add_discard_discard) {
  Player * jacob = Player_factory("Jacob", "Simple");
  jacob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  jacob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
  jacob->add_and_discard(Card(Card::RANK_NINE,Card::SUIT_SPADES));
  Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
  Card played_card = jacob->play_card(c1, Card::SUIT_SPADES);
  ASSERT_EQUAL(played_card, Card(Card::RANK_TEN,Card::SUIT_SPADES));
  delete jacob;
}


// Add more tests here

TEST_MAIN()
