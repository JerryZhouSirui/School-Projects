// 01BD41C3BF016AD7E8B6F837DF18926EC3E83350
#include <algorithm>


struct log{
    std::string timestamp;
    std::string category;
    std::string message;
    long long int time;
    int id;
};

std::string lower(std::string og) {
    std::string temp;
    for(size_t i = 0; i < og.size(); i++ ) {
        temp += static_cast<char>(tolower(og[i]));
    }
    return temp;
}

struct mastersort{
    bool operator()(const log &l1, const log &l2){
        if (l1.time != l2.time) {
            return l1.time < l2.time;
        }
        else if(lower(l1.category) != lower(l2.category)) {
            return lower(l1.category) < lower(l2.category);
        }
        else{
            return l1.id < l2.id;
        }
    }
};

struct time_comp{
    bool operator()(const log &l1, long long time_key){
        return l1.time < time_key;
    }
};

struct time_comp_two{
    bool operator()(long long time_key, const log &l1){
        return time_key < l1.time;
    }
};