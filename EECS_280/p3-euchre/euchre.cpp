// Project UID 1d9f47bfc76643019cfbf037641defe1

#include<iostream>
#include<vector>
#include<fstream>
#include<cassert>
#include "Player.h"
#include "Card.h"
#include "Pack.h"

using namespace std;

class Game {
    private: 
        vector <Player*> players;
        vector <string> player_names;
        vector <string> player_strategies;
        Pack pack_of_cards;
        int team_even_total = 0;
        int team_odd_total = 0;
        

        string trump;
        bool shuffle;
        int dealer;
        int player_one;
        int player_two;
        int player_three;
        Card upcard;
        Card ledcard;
        int winner;
        bool even_order;
        bool odd_order;
        int even_hands;
        int odd_hands;
    public: 

        vector <Player*> get_players(){
            return players;
        }
        //player helper functions
        bool determine_switch (int round) {
            if(round % 2 == 0) {
                return false;
            }
            else{
                return true;
            }
        }
        void determine_winner() {
            
            if (team_even_total > team_odd_total) {
                cout << *(players.at(0)) << " and " << *(players.at(2)); 
                cout << " win!" << endl;
            }
            else{
                cout << *(players.at(1)) << " and " << *(players.at(3));
                cout << " win!" << endl;
            }
        }
        bool round_determine (int points) {
            if (team_even_total < points && team_odd_total < points) {
                return true;
            }
            return false;
        }

        void delete_players() {
            for (int i = 0; i < int(players.size()); ++i) {
            delete players.at(i);
            }
        }

        void set_player_name(int player, string name) {
            player_names.push_back(name);
        }

        void set_player_strategy(int player, string strategy) {
            player_strategies.push_back(strategy);
        }

        void add_players() {
            for (int i = 0; i < 4; i++){
                players.push_back(Player_factory(player_names.at(i), 
                player_strategies.at(i)));
            }
        }
        //end of player helper functions

        //setup_table helper functions
        void read_in_pack(string filename) {
            ifstream fin (filename);
            Pack p1(fin);
            pack_of_cards = p1;
        }

        void determine_shuffle(string choice) {
            if (choice == "shuffle"){
                shuffle = true;
            }
            else {
                shuffle = false;
            }
        }

        void shuffle_cards() {
            if (shuffle){
                pack_of_cards.shuffle();
            }
            else {
                pack_of_cards.reset();
            }
        }

        int player_to_left(int index) {
            if (index == 0){
                return 1;
            }
            else if (index == 1){
                return 2;
            }
            else if (index == 2){
                return 3;
            }
            else if (index == 3){
                return 0;
            }
            return 225;
        }

        void determine_player_order(int round) {
            cout << "Hand " << round << endl;
            dealer = (round) % 4;
            vector <Player*> players_check = get_players();
            cout << *(players.at(dealer)) << " deals" << endl;
            player_one = player_to_left(dealer);
            player_two = player_to_left(player_one);
            player_three = player_to_left(player_two);
        }

        void deal_player(int index) {
            players.at(index)->add_card(pack_of_cards.deal_one());
        }

        void deal_table() {
            even_hands = 0;
            odd_hands = 0;
            deal_player(player_one);
            deal_player(player_one);
            deal_player(player_one);

            deal_player(player_two);
            deal_player(player_two);

            deal_player(player_three);
            deal_player(player_three);
            deal_player(player_three);

            deal_player(dealer);
            deal_player(dealer);

            deal_player(player_one);
            deal_player(player_one);

            deal_player(player_two);
            deal_player(player_two);
            deal_player(player_two);

            deal_player(player_three);
            deal_player(player_three);

            deal_player(dealer);
            deal_player(dealer);
            deal_player(dealer);            
        }
        void who_order(int player) {
            if (player % 2 == 0) {
                    odd_order = false;
                    even_order = true;
            }
            else {
                    odd_order = true;
                    even_order = false;
            }
        }
        //End of setup_table helper functions
        void make_trump() {
            upcard = pack_of_cards.deal_one();
            cout << upcard << " turned up" << endl;
            winner = player_one;
            
            if (players.at(player_one)->make_trump(upcard, false, 1, 
            trump)) {
                cout << *(players.at(player_one)) << " orders up ";
                cout << trump << endl;
                players.at(dealer)->add_and_discard(upcard);
                this->who_order(player_one);
                return;
            }
            cout << *(players.at(player_one)) << " passes" << endl;
            if (players.at(player_two)->make_trump(upcard, false, 1, 
            trump)) {
                cout << *(players.at(player_two)) << " orders up ";
                cout << trump << endl;
                players.at(dealer)->add_and_discard(upcard);
                this->who_order(player_two);
                return;
            }
            cout << *(players.at(player_two)) << " passes" << endl;
            if (players.at(player_three)->make_trump(upcard, false, 
            1, trump)) {
                cout << *(players.at(player_three)) << " orders up ";
                cout << trump << endl;
                players.at(dealer)->add_and_discard(upcard);
                this->who_order(player_three);
                return;
            }
            cout << *(players.at(player_three)) << " passes" << endl;
            if (players.at(dealer)->make_trump(upcard, true, 1,
             trump)) {
                cout << *(players.at(dealer)) << " orders up ";
                cout << trump << endl;
                players.at(dealer)->add_and_discard(upcard);
                this->who_order(dealer);
                return;
            }
            cout << *(players.at(dealer)) << " passes" << endl;
            this->make_trump_two();
        }
        void make_trump_two() {
            if (players.at(player_one)->make_trump(upcard, 
            false, 2, trump)) {
                cout << *(players.at(player_one)) << " orders up ";
                cout << trump << endl;
                this->who_order(player_one);
                return;
            }
            cout << *(players.at(player_one)) << " passes" << endl;
            if (players.at(player_two)->make_trump(upcard, false, 
            2, trump)) {
                cout << *(players.at(player_two)) << " orders up ";
                cout << trump << endl;
                this->who_order(player_two);
                return;
            }
            cout << *(players.at(player_two)) << " passes" << endl;
            if (players.at(player_three)->make_trump(upcard, false,
             2, trump)) {
                cout << *(players.at(player_three)) << " orders up ";
                cout << trump << endl;
                this->who_order(player_three);
                return;
            }
            cout << *(players.at(player_three)) << " passes" << endl;
            if(players.at(dealer)->make_trump(upcard, true, 2, 
            trump)) {
                cout << *(players.at(dealer)) << " orders up ";
                cout << trump << endl;
                this->who_order(dealer);
                return;
            }
        }
        //Switch after round % 2 to determine teams
        void determine_hand(const vector<Card> played) {
            int hand_card = 0;
            Card card_hand = played.at(0);
            for (size_t i = 1; i < played.size(); i++) {
                if (Card_less(card_hand, played.at(i), ledcard, 
                trump)) {
                    card_hand = played.at(i);
                    hand_card = i;
                }
            }
            for (int i = 0; i < hand_card; i++) {
                winner = player_to_left(winner);
            }
            if (winner == 0 || winner == 2) {
                even_hands++;
            }
            if (winner == 1 || winner == 3) {
                odd_hands++;
            }
            cout << *(players.at(winner)) << " takes the trick";
            cout << endl;
            
        }

        void lead_hand() {
            cout << endl;
            ledcard = players.at(winner)->lead_card(trump);
            cout << ledcard << " led by " << *(players.at(winner)); 
            cout << endl;
        }

        void play_hand() {
            vector <Card> played;
            int temp_player_two = player_to_left(winner);
            int temp_player_three = player_to_left(temp_player_two);
            int temp_player_four = player_to_left(temp_player_three);
            Card one = players.at(temp_player_two)->play_card(ledcard
            , trump);
            played.push_back(ledcard);
            played.push_back(one);
            cout << one << " played by ";
            cout << *(players.at(temp_player_two));
            cout << endl;
            Card two=players.at(temp_player_three)->
            play_card(ledcard, trump);
            played.push_back(two);
            cout << two << " played by ";
            cout << *(players.at(temp_player_three)) << endl;
            Card three=players.at(temp_player_four)->
            play_card(ledcard, trump);
            played.push_back(three);
            cout << three << " played by ";
            cout << *(players.at(temp_player_four)) << endl;
            this->determine_hand(played);
        }
        void odd_euchred(){
            team_odd_total += 2;
                    cout << endl;
                    cout << *(players.at(1)) << " and ";
                    cout << *(players.at(3)) << " win the hand";
                    cout << endl;
                    cout << "euchred!" << endl;
                    cout << *(players.at(0)) << " and ";
                    cout << *(players.at(2)) << " have ";
                    cout << team_even_total << " points" << endl; 
                    cout << *(players.at(1)) << " and ";
                    cout << *(players.at(3)) << " have ";
                    cout << team_odd_total << " points" << endl;
                    cout << endl;
                    return;
        }
        void even_euchred() {
             team_even_total += 2;
                    cout << endl;
                    cout << *(players.at(0)) << " and ";
                    cout << *(players.at(2)) << " win the hand";
                    cout << endl;
                    cout << "euchred!" << endl;
                    cout << *(players.at(0)) << " and ";
                    cout << *(players.at(2)) << " have ";
                    cout << team_even_total << " points" << endl; 
                    cout << *(players.at(1)) << " and ";
                    cout << *(players.at(3)) << " have ";
                    cout << team_odd_total << " points" << endl;
                    cout << endl;
                    return;
        }
        void score_set_even() {
            if(even_order == true){
                if(even_hands == 5) {
                    cout << endl;
                    team_even_total += 2;
                    cout << *(players.at(0)) << " and ";
                    cout << *(players.at(2)) << " win the hand";
                    cout << endl;
                    cout << "march!" << endl;
                    cout << *(players.at(0)) << " and ";
                    cout << *(players.at(2)) << " have ";
                    cout << team_even_total << " points" << endl; 
                    cout << *(players.at(1)) << " and ";
                    cout << *(players.at(3)) << " have ";
                    cout << team_odd_total << " points" << endl;
                    cout << endl;
                    return;
                }
                else if(even_hands >= 3) {
                    team_even_total += 1;
                    cout << endl;
                    cout << *(players.at(0)) << " and ";
                    cout << *(players.at(2)) << " win the hand" << endl;
                    cout << *(players.at(0)) << " and ";
                    cout << *(players.at(2)) << " have ";
                    cout << team_even_total << " points" << endl; 
                    cout << *(players.at(1)) << " and ";
                    cout << *(players.at(3)) << " have ";
                    cout << team_odd_total << " points" << endl;
                    cout << endl;
                    return;
                }
                else {
                    this->odd_euchred();
                }

            }
            
            
        }
        void score_set_odd() {
             if(odd_order == true) {
                 if(odd_hands == 5) {
                    team_odd_total += 2; 
                    cout << endl;
                    cout << *(players.at(1)) << " and ";
                    cout << *(players.at(3)) << " win the hand";
                    cout << endl;
                    cout << "march!" << endl;
                    cout << *(players.at(0)) << " and ";
                    cout << *(players.at(2)) << " have ";
                    cout << team_even_total << " points" << endl; 
                    cout << *(players.at(1)) << " and ";
                    cout << *(players.at(3)) << " have ";
                    cout << team_odd_total << " points" << endl;
                    cout << endl;
                    return;
                }
                else if(odd_hands >= 3) {
                    team_odd_total += 1;
                    cout << endl;
                    cout << *(players.at(1)) << " and ";
                    cout << *(players.at(3)) << " win the hand";
                    cout << endl;
                    cout << *(players.at(0)) << " and ";
                    cout << *(players.at(2)) << " have ";
                    cout << team_even_total << " points" << endl; 
                    cout << *(players.at(1)) << " and ";
                    cout << *(players.at(3)) << " have ";
                    cout << team_odd_total << " points" << endl;
                    cout << endl;
                    return;
                }
                else {
                   this->even_euchred();
                }
        }
        }
    void print_c_line (char* argv[]) {
    cout << argv[0] << " " << argv[1] << " " << argv[2] << " ";
    cout << argv[3] << " " << argv[4] << " " << argv[5];
    cout << " " << argv[6] << " " << argv[7] << " " << argv[8];
    cout << " " << argv[9] << " " << argv[10] << " "<< argv[11];
    cout << " " << endl;
    }
    
    
};

int error () {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
    return 1;
}

int main (int argc, char* argv[]){
    int player_index = 0;
    string player_name = " ";
    string player_strategy = " ";
    string shuffle = argv[2];
    string player_type_one = argv[5];
    string player_type_two = argv[7];
    string player_type_three = argv[9];
    string player_type_four = argv[11];
    
    if (argc == 12 && atoi(argv[3]) <= 100 && atoi(argv[3]) >= 1
        && (shuffle == "shuffle" || shuffle == "noshuffle")
        && (player_type_one == "Simple" || player_type_one == "Human")
        && (player_type_two == "Simple" || player_type_two == "Human")
        && (player_type_three == "Simple" || player_type_three == "Human")
        && (player_type_four == "Simple" || player_type_four == "Human")){
            assert(true);
        }
    else {
        return error();
    }
    Game g1;
    g1.print_c_line(argv);
    g1.determine_shuffle(argv[2]);
    g1.read_in_pack(argv[1]);
    for (int i = 4; i < 12; i += 2){
        player_name = argv[i];
        player_strategy = argv[i + 1];
        g1.set_player_name(player_index, player_name);
        g1.set_player_strategy(player_index, player_strategy);
        player_index++;
    }
    g1.add_players();
    int winning_score = atoi(argv[3]);
    int round = 0;
    while (g1.round_determine(winning_score)) {
        g1.shuffle_cards();
        g1.determine_player_order(round);
        g1.deal_table();
        g1.make_trump();
        for(int i = 0; i < 5; i++) {
            g1.lead_hand();
            g1.play_hand();
        }
        g1.score_set_even();
        g1.score_set_odd();
        round++;
    }
    g1.determine_winner();
    g1.delete_players();
    return 0;
}