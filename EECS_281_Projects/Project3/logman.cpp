// 01BD41C3BF016AD7E8B6F837DF18926EC3E83350
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <getopt.h>
#include <fstream>
#include <unordered_map>
#include <deque>
#include "logdata.h"

using namespace std;



void getoptions(int argc, char *argv[]) {

    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        
        {"help", no_argument, nullptr, 'h'},
        { nullptr, 0,        nullptr, '\0' }
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "vmit", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            cout << "This program looks through logs and stuff" << endl;
            exit(0);
        default:
            cerr << "Error: Unknown command line option" << endl;
            exit(1);
    } 
    }
}

void append_ex(const vector<log> &master, deque<int> &exerpt, int index) {
    for(int i = 0; i < static_cast<int>(master.size()); i++) {
        if(master[i].id == index) {
            exerpt.push_back(i);
            break;
        }
    }
    cout << "log entry " << index << " appended" << '\n';
} 

void print_exerpt(const deque<int> &exerpt, const vector<log> &master) {
    for(int i = 0; i < static_cast<int>(exerpt.size()); i++) {
        cout << i << "|" << master[exerpt[i]].id << "|" << master[exerpt[i]].timestamp << "|" << master[exerpt[i]].category << "|" << master[exerpt[i]].message << '\n';
    }
}

void print_search(const vector<log> &master, const vector<int> &search) {
    for(int i = 0; i < static_cast<int>(search.size()); i++) {
        cout << master[search[i]].id << "|" << master[search[i]].timestamp << "|" << master[search[i]].category << "|" << master[search[i]].message << '\n';
    }
}

void match_time(vector<log> &master, vector<int> &search, long long time_key) {
    std::vector<log>::iterator low;
    low = lower_bound(master.begin(), master.end(), time_key, time_comp());
    if(low == master.end()) {
        cout << "Timestamp search: 0 entries found" << '\n';
        search.clear();
        return;
    }
    else{
        while(low->time == time_key) {
            int index = static_cast<int>(distance(master.begin(), low));
            search.push_back(index);
            low++;
            if(low == master.end()) {
                break;
            }
        }
        cout << "Timestamp search: " << search.size() << " entries found" << '\n'; 
    }
}

void time_range(vector<log> &master, vector<int> &search, long long timeone, long long timetwo) {
    std::vector<log>::iterator low;
    std::vector<log>::iterator up;
    low = lower_bound(master.begin(), master.end(), timeone, time_comp());
    up = upper_bound(master.begin(), master.end(), timetwo, time_comp_two());
    if(low == master.end()) {
        cout << "Timestamps search: 0 entries found" << '\n';
        search.clear();
        return;
    }
    int indexlow = static_cast<int>(distance(master.begin(), low));
    int indexup = static_cast<int>(distance(master.begin(), up));
    for(int i = indexlow; i < indexup; i++) {
        search.push_back(i);
    }
    cout << "Timestamps search: " << search.size() << " entries found" << '\n';
}

void ctg_search(vector<int> &search, unordered_map<string, vector<int>> &ctgmp, string ctg) {
    auto ctgfind = ctgmp.find(ctg);
    if (ctgfind == ctgmp.end()) {
        cout << "Category search: 0 entries found" << '\n';
        search.clear();
        return;
    }
    else {
        for(int i = 0; i < static_cast<int>(ctgmp[ctg].size()); i++) {
            search.push_back(ctgmp[ctg][i]);
        }
        cout << "Category search: " << search.size() << " entries found" << '\n';
    }
}

void msgmap_fill(unordered_map<string, vector<int>> &msgmp, log &currlog, int curr_index) {
    string ctg;
    for(int i = 0; i < static_cast<int>(currlog.category.size()); i++) {
        
        if(!isalnum(currlog.category[i])) {
            if(!ctg.empty()) {
                if(msgmp[ctg].empty()) {
                    msgmp[ctg].push_back(curr_index);
                }
                else if(msgmp[ctg].back() != curr_index) {
                    msgmp[ctg].push_back(curr_index);
                }
                ctg.clear();
            }
        }
        else {
            ctg += static_cast<char>(tolower(currlog.category[i]));
            if(i == static_cast<int>(currlog.category.size() - 1)) {
                if(msgmp[ctg].empty()) {
                    msgmp[ctg].push_back(curr_index);
                }
                else if(msgmp[ctg].back() != curr_index) {
                    msgmp[ctg].push_back(curr_index);
                }
                ctg.clear();
            }
        }
    }
    string msg;
    for(int i = 0; i < static_cast<int>(currlog.message.size()); i++) {
        
        if(!isalnum(currlog.message[i])) {
            if(!msg.empty()) {
                if(msgmp[msg].empty()) {
                    msgmp[msg].push_back(curr_index);
                }
               else if(msgmp[msg].back() != curr_index) {
                    msgmp[msg].push_back(curr_index);
                }
                msg.clear();
            }
        }
        else {
            msg += static_cast<char>(tolower(currlog.message[i]));
            if(i == static_cast<int>(currlog.message.size() - 1)) {
                if(msgmp[msg].empty()) {
                    msgmp[msg].push_back(curr_index);
                }
                else if(msgmp[msg].back() != curr_index) {
                    msgmp[msg].push_back(curr_index);
                }
                msg.clear();
            }
        }
    }
}

void search_key(vector<string> &keys, vector<int> &search, unordered_map<string, vector<int>> &keymap) {
    
    for(int i = 0; i < static_cast<int>(keys.size()); i++) {
        auto keyit = keymap.find(keys[i]);
        if (keyit == keymap.end()) {
            cout << "Keyword search: 0 entries found" << '\n';
            search.clear();
            return;
        }
        else{
            if(search.empty()) {
                auto keyvec = keymap[keys[i]].begin();
                while(keyvec != keymap[keys[i]].end()){
                    search.push_back(*keyvec);
                    keyvec++;
                }

            }
            else {
                vector<int> both;
                auto first1 = search.begin();
                auto last1 = search.end();
                auto first2 = keymap[keys[i]].begin();
                auto last2 = keymap[keys[i]].end();
                set_intersection(first1, last1, first2, last2, back_inserter(both));

                
                search = both;
                if(search.empty()) {
                    cout << "Keyword search: " << search.size() << " entries found" << '\n';
                    return;
                }
            }
        }
    }
    cout << "Keyword search: " << search.size() << " entries found" << '\n';
}

int main(int argc, char *argv[]){
    ios_base::sync_with_stdio(false);
    getoptions(argc, argv);
    ifstream fin;
    
    fin.open(argv[1]);
    unordered_map<string, vector<int>> ctgmap;
    unordered_map<string, vector<int>> msgmap;
    deque<int> exerpt;
    vector<int> search;
    vector<log> masterlog;
    string ts;
    string ctg;
    string msg;
    int ids = 0;
    //read the input text file and insert the elements into the master log vecotr
    while(getline(fin,ts,'|')){
        getline(fin,ctg,'|');
        getline(fin,msg);
        string time_temp;
        time_temp += ts[0]; //remove : from the string and convert new numeric string to long long int
        time_temp += ts[1];
        time_temp += ts[3];
        time_temp += ts[4];
        time_temp += ts[6];
        time_temp += ts[7];
        time_temp += ts[9];
        time_temp += ts[10];
        time_temp += ts[12];
        time_temp += ts[13];
        log temp;
        temp.category = ctg;
        temp.timestamp = ts;
        temp.message = msg;
        temp.time = stoll(time_temp);
        temp.id = ids++;
        masterlog.push_back(temp); //add to the master log with the temp log entry
    }
    cout << ids << " entries read" << '\n';
    fin.close(); //close the input log file that we read from
    sort(masterlog.begin(), masterlog.end(), mastersort());
    for(int i = 0; i < static_cast<int>(masterlog.size()); i++) {
        string elmnt = lower(masterlog[i].category);
        ctgmap[elmnt].push_back(i);
        msgmap_fill(msgmap, masterlog[i], i);
    }
    char cmd;
    bool search_done = false;
    int line = 0;
    do {
        cout << "% ";
        cin >> cmd;
        line++;
        if(cmd == '#') {
            string trash;
            getline(cin, trash);
        }
        else if(cmd == 'a'){
            int index;
            cin >> index;
            if(index >= static_cast<int>(masterlog.size())) {
                cerr << "invalid index" << '\n';
                continue;
            }
            if(index > static_cast<int>(masterlog.size())-1) {
                continue;
            }
            append_ex(masterlog, exerpt, index);
        }
        else if(cmd == 'm'){
            
            string input_key;
            
            cin >> input_key;
            long long int convert_time;
            if(input_key.size() != 14) {
                cerr << "invalid size" << '\n';
                continue;
            }
            search.clear();
            
            input_key.erase(11, 1);
            input_key.erase(8, 1);
            input_key.erase(5, 1);
            input_key.erase(2, 1);

            convert_time = stoll(input_key);

            match_time(masterlog, search, convert_time);
            search_done = true;
        }
        else if(cmd == 'p'){
            print_exerpt(exerpt, masterlog);
        }
        else if(cmd == 'g'){
            if(search_done == false) {
                cerr << "no search done" << '\n';
                continue;
            }
            print_search(masterlog, search);
        }
        else if(cmd == 't') {
            
            string timeone;
            string timetwo;
            getline(cin, timeone, '|');
            getline(cin, timetwo);
            timeone.erase(0, 1);
            if(timeone.size() !=  14) {
                cerr << "invalid size" << '\n';
                continue;
            } 
            search.clear();
            timeone.erase(11, 1);
            timeone.erase(8, 1);
            timeone.erase(5, 1);
            timeone.erase(2, 1);
            if(timetwo.size() != 14) {
                cerr << "invalid size" << '\n';
                continue;
            }
            timetwo.erase(11, 1);
            timetwo.erase(8, 1);
            timetwo.erase(5, 1);
            timetwo.erase(2, 1);

            long long ctimeone;
            long long ctimetwo;
            ctimeone = stoll(timeone);
            ctimetwo = stoll(timetwo);

            time_range(masterlog, search, ctimeone, ctimetwo);
            search_done = true;
        }
        else if(cmd == 'c') {
            search.clear();
            string cat;
            getline(cin, cat);
            cat.erase(0,1);
            transform(cat.begin(), cat.end(), cat.begin(), ::tolower);
            ctg_search(search, ctgmap, cat);
            search_done = true;
        }
        else if(cmd == 'k') {
            search.clear();
            string msgs;
            string msg;
            getline(cin, msgs);
            msgs.erase(0, 1);
            vector<string> keys;
            for(int i = 0; i < static_cast<int>(msgs.size()); i++) {
                if(!isalnum(msgs[i])){
                    if(!msg.empty()) {
                        keys.push_back(msg);
                        msg.clear();
                    }
                }
                else{
                    msg += static_cast<char>(tolower(msgs[i]));
                    if(i == static_cast<int>(msgs.size() - 1)){
                        keys.push_back(msg);
                        msg.clear();
                    }
                }
            }
            search_key(keys, search, msgmap);
            search_done = true;
            
        }
        else if(cmd == 'r') {
            if(search_done == false) {
                cerr << "no search done" << '\n';
                continue;
            }
            if(search.empty()) {
                cout << "0 log entries appended" << '\n';
                continue;
                
            }
            
            for(int i = 0; i < static_cast<int>(search.size()); i++){
                exerpt.push_back(search[i]);
            }
            cout << search.size() << " log entries appended" << '\n';
        }
        else if(cmd == 'l') {
            if(exerpt.size() == 0){
                cout << "excerpt list cleared" << '\n';
                cout << "(previously empty)" << '\n';
            }
            else{
                cout << "excerpt list cleared" << '\n';
                cout << "previous contents:" << '\n';
                cout << "0|" << masterlog[exerpt[0]].id << '|' << masterlog[exerpt[0]].timestamp << '|' << masterlog[exerpt[0]].category << '|' << masterlog[exerpt[0]].message << '\n';
                cout << "..." << '\n';
                cout << exerpt.size() - 1 << '|' << masterlog[exerpt[exerpt.size() -1]].id << '|' << masterlog[exerpt[exerpt.size() -1]].timestamp << '|' << masterlog[exerpt[exerpt.size() -1]].category << '|' << masterlog[exerpt[exerpt.size() -1]].message << '\n';
                exerpt.clear();
            }
        }
        else if(cmd == 'b') {
            int index;
            cin >> index;
            if(index >= static_cast<int>(exerpt.size())) {
                cerr << "invalid index" << '\n';
                continue;
            }
            auto loc = exerpt.begin() + index;
            int value = *loc;
            exerpt.erase(loc);
            exerpt.push_front(value);
            cout << "Moved excerpt list entry " << index << '\n';
        }
        else if(cmd == 'e') {
            int index;
            cin >> index;
            if(index >= static_cast<int>(exerpt.size())) {
                cerr << "invalid index" << '\n';
                continue;
            }
            auto loc = exerpt.begin() + index;
            int value = *loc;
            exerpt.erase(loc);
            exerpt.push_back(value);
            cout << "Moved excerpt list entry " << index << '\n';
        }
        else if(cmd == 'd') {
            int index;
            cin>> index;
            if(index >= static_cast<int>(exerpt.size())) {
                cerr << "invalid index" << '\n';
                continue;
            }
            exerpt.erase(exerpt.begin()+index);
            cout << "Deleted excerpt list entry " << index << '\n';
        }
        else if(cmd == 's') {
            if(exerpt.size() == 0) {
                cout << "excerpt list sorted" << '\n';
                cout << "(previously empty)" << '\n';
                continue;
            }
            cout << "excerpt list sorted" << '\n';
            cout << "previous ordering:" << '\n';
            cout << "0|" << masterlog[exerpt[0]].id << '|' << masterlog[exerpt[0]].timestamp << '|' << masterlog[exerpt[0]].category << '|' << masterlog[exerpt[0]].message << '\n';
            cout << "..." << '\n';
            cout << exerpt.size() - 1 << '|' << masterlog[exerpt[exerpt.size() -1]].id << '|' << masterlog[exerpt[exerpt.size() -1]].timestamp << '|' << masterlog[exerpt[exerpt.size() -1]].category << '|' << masterlog[exerpt[exerpt.size() -1]].message << '\n';
            cout << "new ordering:" << '\n';
            sort(exerpt.begin(), exerpt.end());
            cout << "0|" << masterlog[exerpt[0]].id << '|';
            cout << masterlog[exerpt[0]].timestamp << '|';
            cout << masterlog[exerpt[0]].category << '|';
            cout << masterlog[exerpt[0]].message << '\n';
            cout << "..." << '\n';
            cout << exerpt.size() - 1 << '|';
            cout << masterlog[exerpt[exerpt.size() -1]].id << '|';
            cout << masterlog[exerpt[exerpt.size() -1]].timestamp << '|';
            cout << masterlog[exerpt[exerpt.size() -1]].category << '|';
            cout << masterlog[exerpt[exerpt.size() -1]].message << '\n';
        }
        else if(cmd != 'q') {
            cerr << "invalid command" << '\n';
            continue;
        }
    } while(cmd != 'q'); 
}