// Identifier: 50EB44D3F029ED934858FFFCEAC3547C68768FC9
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>

struct dict {
    std::string word;
    int prev;
    bool discovered; 
};

class Letterman {
public:
Letterman(){
    stackSpecified = false;
    queueSpecified = false;
    change = false;
    swap = false;
    length = false;
    output_s = false;
    begin_s = false;
    begin_exists = false;
    end_exists = false;
    dict_words_num = 0;
    discovereds = 0;
    begin_word_index = -1;
    end_word_index = -1;
    
}
void c_b_e(std::string word);
void getoptions(int argc, char *argv[]);
void readdict();
void search();
void output();
bool check_end(size_t index);
bool begin_exists;
bool end_exists;
private:
bool change;
bool swap;
bool length;
bool output_s;
bool begin_s;
bool end_s;
char dict_type;
bool stackSpecified;
bool queueSpecified;
int discovereds;
int dict_words_num;
int begin_word_index;
int end_word_index;
 

std::string output_mode;
std::string begin;
std::string end;
std::deque<size_t> search_dict;
std::vector<dict> dictionary;
}; 

