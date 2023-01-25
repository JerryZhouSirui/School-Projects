// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_card_dc){
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_card_get_suit){
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c2(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.get_suit(Card::SUIT_CLUBS) == Card::SUIT_CLUBS);
    ASSERT_FALSE(c.get_suit(Card::SUIT_CLUBS) == Card::SUIT_SPADES);
    ASSERT_TRUE(c1.get_suit() == Card::SUIT_HEARTS);
    ASSERT_TRUE(c2.get_suit(Card::SUIT_HEARTS) == Card::SUIT_DIAMONDS);
}

TEST(test_card_get_rank){
    Card c(Card::RANK_SIX, Card::SUIT_CLUBS);
    Card c1(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(c.get_rank() == Card::RANK_SIX);
    ASSERT_TRUE(c1.get_rank() == Card::RANK_JACK);
}

TEST(test_card_is_face){
    Card c(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.is_face());

    Card c1(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(c1.is_face());

    Card c2(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_TRUE(c2.is_face());

    Card c3(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(c3.is_face());

    Card c4(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_FALSE(c4.is_face());
}

TEST(test_card_is_left_bower){
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_SPADES));

    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c1.is_left_bower(Card::SUIT_SPADES));

    Card c2(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c2.is_left_bower(Card::SUIT_DIAMONDS));
}

TEST(test_card_is_right_bower){
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(c.is_right_bower(Card::SUIT_CLUBS));

    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c1.is_right_bower(Card::SUIT_CLUBS));

    Card c2(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c2.is_right_bower(Card::SUIT_DIAMONDS));

    Card c3(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(c3.is_right_bower(Card::SUIT_SPADES));
}

TEST(test_card_is_trump){
    Card c(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_trump(Card::SUIT_HEARTS));

    Card c1(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c1.is_trump(Card::SUIT_HEARTS));

    Card c2(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_FALSE(c2.is_trump(Card::SUIT_SPADES));

    Card c3(Card::RANK_TWO, Card::SUIT_CLUBS);
    ASSERT_TRUE(c3.is_trump(Card::SUIT_CLUBS));
}

TEST(test_card_operators){
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card two_spades(Card::RANK_TWO, Card::SUIT_SPADES);
    
    ASSERT_TRUE(jack_clubs < queen_diamonds);
    ASSERT_TRUE(nine_spades < nine_hearts);
    ASSERT_TRUE(queen_diamonds <= ace_diamonds);
    ASSERT_TRUE(ace_diamonds <= ace_diamonds);
    ASSERT_TRUE(ace_diamonds > nine_spades);
    ASSERT_TRUE(jack_spades >= nine_hearts);
    ASSERT_TRUE(queen_diamonds >= queen_diamonds);
    ASSERT_TRUE(jack_clubs != jack_spades);
    ASSERT_TRUE(queen_diamonds == queen_diamonds);
    ASSERT_TRUE(two_spades < ace_diamonds);
}

//testing card_less function that doesn't take led card into account
TEST(test_card_less_nl){
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card two_spades(Card::RANK_TWO, Card::SUIT_SPADES);
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);

    ASSERT_TRUE(Card_less(ace_diamonds, nine_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(king_hearts, jack_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(two_spades, nine_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, Card::SUIT_SPADES));
}

//testing card_less function that takes led card into account
TEST(test_card_less_wl){
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_hearts(Card::RANK_KING, Card::SUIT_HEARTS);
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card two_spades(Card::RANK_TWO, Card::SUIT_SPADES);

    ASSERT_TRUE(Card_less(king_hearts, queen_diamonds, ace_diamonds, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(queen_diamonds, jack_clubs, ace_diamonds, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_diamonds, nine_spades, nine_spades, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(jack_clubs, nine_spades, jack_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_diamonds, two_spades, nine_spades, Card::SUIT_CLUBS));
}

TEST(test_suit_next){
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_NOT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
}

TEST(test_extraction_operator) {
    Card c(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);

    ostringstream output;
    output << c;
    string output_correct = "King of Diamonds";
    ASSERT_EQUAL(output.str(), output_correct);

    ostringstream output1;
    output1 << c1;
    string output_correct1 = "Jack of Spades";
    ASSERT_EQUAL(output1.str(), output_correct1);
}

// Add more test cases here

TEST_MAIN()
