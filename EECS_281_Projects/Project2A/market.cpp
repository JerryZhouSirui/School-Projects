// 0E04A31E0D60C01986ACB20081C9D8722A1899B6
#include <getopt.h>
#include <iostream>
#include "P2random.h"
#include "P2Market.h"
#include <queue>
#include <sstream>

using namespace std;

void Market::getoptions(int argc, char *argv[]) {
     
    

    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        {"verbose", no_argument, nullptr, 'v'},
        {"median", no_argument, nullptr, 'm'},
        {"trader_info", no_argument, nullptr, 'i'},
        {"time_travelers", no_argument, nullptr, 't'},
        {"help", no_argument, nullptr, 'h'},
        { nullptr, 0,        nullptr, '\0' }
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "vmit", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'v':
            verbose = true;
            break;
        case 'm':
            median = true;
            break;
        case 'i':
            trader_info = true;
            break;
        case 't':
            time_travelers = true;
            break;
        case 'h':
            cout << "This program does some stuff with stocks ... yeah" << endl;
            exit(0);
        default:
            cerr << "Error: Unknown command line option" << endl;
            exit(1);
    } 
}
}

void Market::input(){
    string trash;
    
    getline(cin, trash); //Read the begining of the file and assign values to appropriate member variables defined in the class
    cin >> trash;
    cin >> mode;
    cin >> trash;
    cin >> Num_Traders;
    cin >> trash;
    cin >> Num_Stocks;
}

void Market::trade_list(int identifier, string action, int trader, int stock, int price, int quantity, vector<Stock> &stonk_list) {
    Trade new_trade;
    
    
    new_trade.identifier = identifier;
    new_trade.trader = trader;
    
    new_trade.price = price;
    new_trade.quantity = quantity;
    if(action == "BUY") {
        stonk_list[stock].buy.push(new_trade);
    }
    if(action == "SELL") {
        stonk_list[stock].sell.push(new_trade);

    }
    
}


void Market::execute_trades(vector<Stock> &stonk_list,const int &i, vector<Trader> &trader_list) {
        if(stonk_list[i].buy.empty() || stonk_list[i].sell.empty()) {
            return;
        }
        while(stonk_list[i].buy.top().price >= stonk_list[i].sell.top().price) {
        if(stonk_list[i].buy.empty() || stonk_list[i].sell.empty()) {
            return;
        }
            if(stonk_list[i].buy.top().identifier > stonk_list[i].sell.top().identifier) {
                int exchange_price = stonk_list[i].sell.top().price;
                num_trades++;
                if(stonk_list[i].buy.top().quantity >= stonk_list[i].sell.top().quantity) {
                    int quantity_traded = stonk_list[i].sell.top().quantity;
                    stonk_list[i].buy.top().quantity -= quantity_traded;
                    stonk_list[i].sell.top().quantity -= quantity_traded;
                    if(trader_info) {
                        trader_list[stonk_list[i].buy.top().trader].bought += quantity_traded;
                        trader_list[stonk_list[i].sell.top().trader].sold += quantity_traded;
                        trader_list[stonk_list[i].buy.top().trader].transfer -= exchange_price * quantity_traded;
                        trader_list[stonk_list[i].sell.top().trader].transfer += exchange_price * quantity_traded;
                    }
                    if(median) {
                        median_add(stonk_list, i, exchange_price);
                    }
                    if(verbose) {
                        cout << "Trader " << stonk_list[i].buy.top().trader << " purchased " << quantity_traded;
                        cout << " shares of Stock " << i << " from Trader " << stonk_list[i].sell.top().trader << " for $";
                        cout << exchange_price << "/share" << '\n'; 
                    }
                    if(stonk_list[i].buy.top().quantity == 0){
                        stonk_list[i].buy.pop();
                    }
                    if(stonk_list[i].sell.top().quantity == 0){
                        stonk_list[i].sell.pop();
                    }
                    continue;
                }
                if(stonk_list[i].buy.top().quantity <= stonk_list[i].sell.top().quantity) {
                    int quantity_traded = stonk_list[i].buy.top().quantity;
                    stonk_list[i].buy.top().quantity -= quantity_traded;
                    stonk_list[i].sell.top().quantity -= quantity_traded;
                    if(trader_info) {
                        trader_list[stonk_list[i].buy.top().trader].bought += quantity_traded;
                        trader_list[stonk_list[i].sell.top().trader].sold += quantity_traded;
                        trader_list[stonk_list[i].buy.top().trader].transfer -= exchange_price * quantity_traded;
                        trader_list[stonk_list[i].sell.top().trader].transfer += exchange_price * quantity_traded;
                    }
                    if(median) {
                        median_add(stonk_list, i, exchange_price);
                    }
                    if(verbose) {
                        cout << "Trader " << stonk_list[i].buy.top().trader << " purchased " << quantity_traded;
                        cout << " shares of Stock " << i << " from Trader " << stonk_list[i].sell.top().trader << " for $";
                        cout << exchange_price << "/share" << '\n'; 
                    }
                    if(stonk_list[i].buy.top().quantity == 0){
                        stonk_list[i].buy.pop();
                    }
                    if(stonk_list[i].sell.top().quantity == 0){
                        stonk_list[i].sell.pop();
                    }
                    continue;
                }
            }
            if(stonk_list[i].buy.top().identifier < stonk_list[i].sell.top().identifier) {
                int exchange_price = stonk_list[i].buy.top().price;
                num_trades++;
                if(stonk_list[i].buy.top().quantity >= stonk_list[i].sell.top().quantity) {
                    int quantity_traded = stonk_list[i].sell.top().quantity;
                    stonk_list[i].buy.top().quantity -= quantity_traded;
                    stonk_list[i].sell.top().quantity -= quantity_traded;
                    if(trader_info) {
                        trader_list[stonk_list[i].buy.top().trader].bought += quantity_traded;
                        trader_list[stonk_list[i].sell.top().trader].sold += quantity_traded;
                        trader_list[stonk_list[i].buy.top().trader].transfer -= exchange_price * quantity_traded;
                        trader_list[stonk_list[i].sell.top().trader].transfer += exchange_price * quantity_traded;
                    }
                    if(median) {
                        median_add(stonk_list, i, exchange_price);
                    }
                    if(verbose) {
                        cout << "Trader " << stonk_list[i].buy.top().trader << " purchased " << quantity_traded;
                        cout << " shares of Stock " << i << " from Trader " << stonk_list[i].sell.top().trader << " for $";
                        cout << exchange_price << "/share" << '\n'; 
                    }
                    if(stonk_list[i].buy.top().quantity == 0){
                        stonk_list[i].buy.pop();
                    }
                    if(stonk_list[i].sell.top().quantity == 0){
                        stonk_list[i].sell.pop();
                    }
                    continue;
                }
                if(stonk_list[i].buy.top().quantity <= stonk_list[i].sell.top().quantity) {
                    int quantity_traded = stonk_list[i].buy.top().quantity;
                    stonk_list[i].buy.top().quantity -= quantity_traded;
                    stonk_list[i].sell.top().quantity -= quantity_traded;
                    if(trader_info) {
                        trader_list[stonk_list[i].buy.top().trader].bought += quantity_traded;
                        trader_list[stonk_list[i].sell.top().trader].sold += quantity_traded;
                        trader_list[stonk_list[i].buy.top().trader].transfer -= exchange_price * quantity_traded;
                        trader_list[stonk_list[i].sell.top().trader].transfer += exchange_price * quantity_traded;
                    }
                    if(median) {
                        median_add(stonk_list, i, exchange_price);
                    }
                    if(verbose) {
                        cout << "Trader " << stonk_list[i].buy.top().trader << " purchased " << quantity_traded;
                        cout << " shares of Stock " << i << " from Trader " << stonk_list[i].sell.top().trader << " for $";
                        cout << exchange_price << "/share" << '\n'; 
                        
                    }
                    if(stonk_list[i].buy.top().quantity == 0){
                        stonk_list[i].buy.pop();
                    }
                    if(stonk_list[i].sell.top().quantity == 0){
                        stonk_list[i].sell.pop();
                    }
                    continue;
                    
                }
            }
        }
    
}

void Market::median_add(vector<Stock> &stonk_list, const int &index, const int &price) {
if(stonk_list[index].medL.size() == 0 || price < static_cast<int>(stonk_list[index].medL.top())) {
    stonk_list[index].medL.push(static_cast<uint32_t>(price));
}
else {
    stonk_list[index].medU.push(static_cast<uint32_t>(price));
}
}



void Market::median_c(vector<Stock> &stonk_list, const int &time) {
    for(int i = 0; i < static_cast<int>(stonk_list.size()); i++) {
       
        if(static_cast<int>(stonk_list[i].medL.size()) - static_cast<int>(stonk_list[i].medU.size()) > 1) {
            while(static_cast<int>(stonk_list[i].medL.size()) - static_cast<int>(stonk_list[i].medU.size()) > 1){
                stonk_list[i].medU.push(stonk_list[i].medL.top());
                stonk_list[i].medL.pop();
            }
        }
        else if(static_cast<int>(stonk_list[i].medU.size()) - static_cast<int>(stonk_list[i].medL.size()) > 1) {
            while(static_cast<int>(stonk_list[i].medU.size()) - static_cast<int>(stonk_list[i].medL.size()) > 1){
                int value = stonk_list[i].medU.top();
                stonk_list[i].medL.push(value);
                stonk_list[i].medU.pop();
            }
        }
        int median_a = -1;
        if(stonk_list[i].medU.empty() && stonk_list[i].medL.empty()) {
            continue;
        }
        if(static_cast<int>(stonk_list[i].medU.size()) - static_cast<int>(stonk_list[i].medL.size())== 1) {
            median_a = stonk_list[i].medU.top();
        }
        else if(static_cast<int>(stonk_list[i].medL.size()) - static_cast<int>(stonk_list[i].medU.size()) == 1) {
            median_a = stonk_list[i].medL.top();
        }
        else {
            median_a = (stonk_list[i].medU.top() + stonk_list[i].medL.top())/2;
        }
        cout << "Median match price of Stock " << i << " at time " << time << " is $" << median_a << '\n';
    }
}

void Market::trader_info_o(const vector<Trader> &trader_list) {
    for(int i = 0; i < static_cast<int>(trader_list.size()); i++) {
        cout << "Trader " << i << " bought " << trader_list[i].bought << " and sold " << trader_list[i].sold;
        cout << " for a net transfer of $" << trader_list[i].transfer << '\n';
    }
}

void Market::time_travelo(const vector<Time_State> &time_travel) {
    for(int i = 0; i < static_cast<int>(time_travel.size()); i++) {
        if(!time_travel[i].complete_trade) {
            cout << "A time traveler could not make a profit on Stock " << i << '\n';
        }
        else {
            cout << "A time traveler would buy Stock " << i << " at time " << time_travel[i].time_one << " for $";
            cout << time_travel[i].purchase << " and sell it at time " << time_travel[i].time_two;
            cout << " for $" << time_travel[i].sells << '\n';  
        }
    }
}

void traverse_time(vector<Time_State> &time_travel, int time, string action, int stock, int price) {
    if(action == "SELL") {
        if(!time_travel[stock].canbuy) {
            time_travel[stock].canbuy = true;
            time_travel[stock].time_one = time;
            time_travel[stock].purchase = price;
        }
        else if(!time_travel[stock].complete_trade && (time_travel[stock].purchase > price) ) {
            time_travel[stock].time_one = time;
            time_travel[stock].purchase = price;
        }
        else if(time_travel[stock].complete_trade) {
            if(!time_travel[stock].potential && price < time_travel[stock].purchase) {
                time_travel[stock].potential = true;
                time_travel[stock].potential_time = time;
                time_travel[stock].potential_buy = price;
            }
            else if(price < time_travel[stock].potential_buy) {
                time_travel[stock].potential_time = time;
                time_travel[stock].potential_buy = price;
            }
        }
    }
    if (action == "BUY") {
        if(time_travel[stock].canbuy) {
            if(!time_travel[stock].complete_trade && price > time_travel[stock].purchase ) {
                time_travel[stock].complete_trade = true;
                time_travel[stock].time_two = time;
                time_travel[stock].sells = price;
            }
            else if (time_travel[stock].complete_trade) {
                if(!time_travel[stock].potential) {
                    if(price > time_travel[stock].sells) {
                        time_travel[stock].time_two = time;
                        time_travel[stock].sells = price;
                    }
                }
                else if(time_travel[stock].potential) {
                    int potential = price - time_travel[stock].potential_buy;
                    int current = time_travel[stock].sells - time_travel[stock].purchase;
                    int possible = price - time_travel[stock].purchase;
                    if(potential > current) {
                        time_travel[stock].potential = false;
                        time_travel[stock].time_one = time_travel[stock].potential_time;
                        time_travel[stock].purchase = time_travel[stock].potential_buy;
                        time_travel[stock].time_two = time;
                        time_travel[stock].sells = price;
                    }
                    else if(possible > current) {
                        time_travel[stock].time_two = time;
                        time_travel[stock].sells = price;
                    }



                }
            }
        }
    }
}

void check_error(int time, int timeprev, int trader, int stock, int price, int quantity, int numtraders, int numstocks){
    if(time < 0 ) {
        cerr << "Error: Negative timestamp" << endl;
        exit(1);
    }
    if(trader < 0) {
        cerr << "Error: Invalid trader ID" << endl;
        exit(1);
    }
    if(stock < 0) {
        cerr << "Error: Invalid stock ID" << endl;
        exit(1);
    }
    if(trader > numtraders - 1) {
        cerr << "Error: Invalid trader ID" << endl;
        exit(1);
    }
    if(stock > numstocks - 1) {
        cerr << "Error: Invalid stock ID" << endl;
        exit(1);
    }
    if(price <= 0) {
        cerr << "Error: Invalid price" << endl;
        exit(1);
    }
    if(quantity <= 0) {
        cerr << "Error: Invalid quantity" << endl;
        exit(1);
    }
    if(time < timeprev) {
        cerr << "Error: Decreasing timestamp" << endl;
        exit(1);
    }
}

int main (int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);

    Market stonks;
    stringstream ss;
    stonks.getoptions(argc, argv);
    stonks.input();
    cout << "Processing orders..." << '\n';
    vector<Stock> stonk_list;
    vector<Trader> trader_list;
    vector<Time_State> time_travel;
    time_travel.resize(stonks.getStocks());
    stonk_list.resize(stonks.getStocks());
    trader_list.resize(stonks.getTraders());
    int identifier = 0;
    int time;
    string action;
    char t;
    int trader;
    char s;
    int stock;
    char dolen;
    int price;
    char number;
    int quantity;
    int timeprev = 0;
    
    
    if(stonks.getMode() == "TL") {
        while(cin >> time >> action >> t >> trader >> s >> stock >> dolen >> price >> number >> quantity) {
            check_error(time, timeprev, trader, stock, price, quantity, stonks.getTraders(), stonks.getStocks());
            if (stonks.getTime_travel()) {
                traverse_time(time_travel, time, action, stock, price);
            }
            if (timeprev != time) {
                
               if(stonks.getMedian()) {
                   stonks.median_c(stonk_list, timeprev);
               }
            }
            stonks.trade_list(identifier, action, trader, stock, price, quantity, stonk_list);
            stonks.execute_trades(stonk_list, stock, trader_list);
            identifier++;
            timeprev = time;
        }
    }
    if(stonks.getMode() == "PR") {
        string trashpr;
        int seed;
        cin >> trashpr;
        cin >> seed;
        int orders;
        cin >> trashpr;
        cin >> orders;
        int arrival_rate;
        cin >> trashpr;
        cin >> arrival_rate;
        P2random two_r;
        
    
        two_r.PR_init(ss, seed, stonks.getTraders(), stonks.getStocks(), orders, arrival_rate);
        while (ss >> time >> action >> t >> trader >> s >> stock >> dolen >> price >> number >> quantity) {
            
            check_error(time, timeprev, trader, stock, price, quantity, stonks.getTraders(), stonks.getStocks());
            if (stonks.getTime_travel()) {
                traverse_time(time_travel, time, action, stock, price);
            }
            if (timeprev != time) {
            if(stonks.getMedian()) {
                stonks.median_c(stonk_list, timeprev);
            }
            }
            stonks.trade_list(identifier, action, trader, stock, price, quantity, stonk_list);
            stonks.execute_trades(stonk_list, stock, trader_list);
            identifier++;
            timeprev = time;
        }
    }
    if(stonks.getMedian()) {
        stonks.median_c(stonk_list, timeprev);
    }
    cout << "---End of Day---" << '\n';
    cout << "Trades Completed: " << stonks.getTrades() << '\n';
    if(stonks.getTrader_Info()) {
        cout << "---Trader Info---" << '\n';
        stonks.trader_info_o(trader_list);
    }
    if (stonks.getTime_travel()) {
        cout << "---Time Travelers---" << '\n';
        stonks.time_travelo(time_travel);
    }
    
}