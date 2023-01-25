// 0E04A31E0D60C01986ACB20081C9D8722A1899B6
#include<queue>
#include<vector>
#include <sstream>

struct Time_State {
    int purchase = 0;
    int sells = 0;
    int time_one = 0;
    int time_two = 0;
    int potential_time = 0;
    int potential_buy = 0;
    
    bool canbuy = false;
    bool complete_trade = false;
    bool potential = false;
};



struct Trade {
    uint32_t trader = 0;
    mutable uint32_t quantity = -1;
    uint32_t price = -1;
    
    uint32_t identifier = -1;
    
};

struct Trader{
    int sold = 0;
    int bought = 0;
    int transfer = 0;
};

struct CompareBuy{
    bool operator() (Trade const &p1, Trade const &p2){
        if (p1.price == p2.price) {
            return p1.identifier > p2.identifier;
        }
        return p1.price < p2.price;
    }
};

struct CompareSell{
    bool operator() (const Trade &p1, const Trade &p2){
        if (p1.price == p2.price) {
            return p1.identifier > p2.identifier;
        }
        return p1.price > p2.price;
    } 
};

struct CompareMedL{
    bool operator() (const int &p1, const int &p2) {
        return p1 < p2;
    }
};

struct CompareMedU{
    bool operator() (const int &p1, const int &p2) {
        return p1 > p2;
    }
};

class Stock {
    public:
    std::priority_queue<Trade, std::vector<Trade>, CompareBuy> buy;
    std::priority_queue<Trade, std::vector<Trade>, CompareSell> sell;
    
    std::priority_queue<uint32_t, std::vector<uint32_t>, CompareMedL> medL;
    std::priority_queue<uint32_t, std::vector<uint32_t>, CompareMedU> medU;

};

class Market {
    private:
    std::string mode;
    int Num_Traders = 0;
    int Num_Stocks = 0;
    int num_trades = 0;
    bool verbose = false;
    bool median = false;
    bool trader_info = false;
    bool time_travelers = false;

    public:
    void getoptions(int argc, char *argv[]);
    void input();
    std::string getMode();
    void trade_list(int identifier, std::string action, int trader, int stock, int price, int quantity, std::vector<Stock> &stonk_list);
    bool compare(); 
    int getStocks();
    int getTraders();
    bool getMedian();
    void execute_trades(std::vector<Stock> &stonk_list,const int &i, std::vector<Trader> &trader_list);
    void median_c(std::vector<Stock> &stonk_list, const int &time);
    bool getTrader_Info();
    bool getTime_travel();
    int getTrades();
    void trader_info_o(const std::vector<Trader> &trader_list);
    void time_travelo(const std::vector<Time_State> &time_travel);
    void median_add(std::vector<Stock> &stonk_list, const int &index, const int &price);
};
bool Market::getMedian() {
    return median;
}

int Market::getStocks() {
    return Num_Stocks;
}

int Market::getTraders() {
    return Num_Traders;
}

std::string Market::getMode() {
    return mode;
}

int Market::getTrades() {
    return num_trades;
}

bool Market::getTrader_Info() {
    return trader_info;
}

bool Market::getTime_travel() {
    return time_travelers;
}