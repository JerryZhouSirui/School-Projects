// Identifier: 50EB44D3F029ED934858FFFCEAC3547C68768FC9
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "project1.h"
#include <stack>
#include <queue>
#include <deque>
#include <string>
using namespace std;


void Letterman::getoptions(int argc, char *argv[]) {
    
    

    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        {"stack", no_argument, nullptr, 's'},
        {"queue", no_argument, nullptr, 'q'},
        {"change", no_argument, nullptr, 'c'},
        {"swap", no_argument, nullptr, 'p'},
        {"length", no_argument, nullptr, 'l'},
        {"output", required_argument, nullptr, 'o'},
        {"begin", required_argument, nullptr, 'b'},
        {"end", required_argument, nullptr, 'e'},
        {"help", no_argument, nullptr, 'h'},
        { nullptr, 0,        nullptr, '\0' }
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "sqcplo:b:e:h", long_options, &option_index)) != -1) {
        switch (choice) {
        case 's':
            if(stackSpecified) {
                cerr << "Conflicting or duplicate stack and queue specified" << endl;
                exit(1);
            }
           stackSpecified = true;
           break;
        case 'q':
            if(queueSpecified) {
                cerr << "Conflicting or duplicate stack and queue specified" << endl;
                exit(1);
            }
           queueSpecified = true;
            break;
        case 'c':
            change = true;
            break;
        case 'p':
            swap = true;
            break;
        case 'l':
            length = true;
            break;
        case 'o':
            output_mode = optarg;
            output_s = true; //output will have to go elsewhere, haven't figured that out yet though
            break;
        case 'b':
            begin = optarg;
            begin_s = true;
            break;
        case 'e':
            end = optarg;
            end_s = true;
            break;
        case 'h':
            cout << "This program does some stuff :)" << endl;
            exit(0);
        default:
            exit(1);
    } // while
    //Error checking goes here
    //
    
}

if(queueSpecified && stackSpecified) {
        cerr << "Conflicting or duplicate stack and queue specified" << endl;
        exit(1);
    }
    if(!queueSpecified && !stackSpecified) {
        cerr << "Must specify one of stack or queue" << endl;
        exit(1);
    }
    if (!(change || swap || length)) {
       cerr << "Must specify at least one modification mode (change length swap)" << endl; 
       exit(1);
    }
    if(output_s && ((output_mode != "M") && (output_mode != "W"))) {
        cerr << "Invalid output mode specified" << endl;
        exit(1);
    }
    if(!(begin_s)) {
       cerr << "Beginning word not specified" << endl; 
       exit(1);
    }
    if(!end_s){
        cerr << "Ending word not specified" << endl;
        exit(1);
    }
    if((begin.size() != end.size()) && !length) {
        cerr << "The first and last words must have the same length when length mode is off" << endl;
        exit(1);
    }
}

void Letterman::c_b_e(string word) {
    if(begin_word_index == -1) {
        if(word == begin) {
            begin_word_index = static_cast<int>((dictionary.size() - 1));
        }
    }
    if(end_word_index == -1) {
        if(word == end) {
            end_word_index = static_cast<int>((dictionary.size() - 1));
        }
    }
}

void Letterman::readdict() {
    string word;
    cin >> dict_type; 

    cin >> dict_words_num;
    getline(cin, word);
    if (dict_type == 'S'){
        dictionary.reserve(dict_words_num);
        
        while (getline(cin, word)){
            if(word[0] == '/' || word.size() == 0) {
            }
            else {
                if(!length) {
                    if(word.size() != begin.size()) {
                        continue;
                    }
                }
                dictionary.push_back({word, -1, false}); 
                c_b_e(word);
            }
            
        }
    }
    if (dict_type == 'C') {
        dictionary.reserve(dict_words_num);
        while(getline(cin, word)) {
            if(word[0] == '/' && word[1] == '/'){

            }
            
            else {
                bool modes = false;
                for(size_t j = 0; j < word.length(); j++) {
                    if(word[j] == '&') { // reverse the string and add it to the dictionary
                        modes = true; 
                        string word_two;
                        word.erase(word.begin()+j);
                        j--;
                        while(word[j]) {
                            word_two += word[j];
                            j--;
                        }
                        dictionary.push_back({word, -1, false});
                        c_b_e(word);
                        dictionary.push_back({word_two, -1, false});
                        c_b_e(word_two);
                        break;
                    }
                    if(word[j] == '?') {
                        modes = true; 
                        word.erase(word.begin()+j);
                        j--;
                        dictionary.push_back({word, -1, false});
                        c_b_e(word);
                        word.insert(j, 1, word[j]);
                        dictionary.push_back({word, -1, false});
                        c_b_e(word);
                        break;
                    }
                    if(word[j] == '!') {
                        modes = true; 
                        word.erase(word.begin()+j);
                        dictionary.push_back({word, -1, false});
                        c_b_e(word);
                        word.insert(j, 1, word[j-2]);
                        word.erase(word.begin()+j-2);
                        dictionary.push_back({word, -1, false});
                        c_b_e(word);
                        break;
                    }
                    if(word[j] == '[') {
                        modes = true; 
                        for(size_t k = j; k < word.length(); k++) {
                            if(word[k] == ']') {
                                string word_two = word;
                                word.erase(j, k-j+1);
                                
                                size_t i = j+1;
                                while(i < k) {
                                    word.insert(j,1, word_two[i]); 
                                    dictionary.push_back({word, -1, false});
                                    c_b_e(word);
                                    word.erase(j,1);
                                    i++;
                                }
                            }
                        }
                        break;
                    }
                }
                if (modes == false) {
                    dictionary.push_back({word, -1, false});
                   c_b_e(word);
                }
            }
        }
    }
} 

bool Letterman::check_end(size_t index) {
    
    if(static_cast<int>(index) == end_word_index) {
        Letterman::output();
        return true;
    }
    else {
        return false;
    }
}

void Letterman::search() {
    
    if(begin_word_index == end_word_index) {
        cout << dictionary[begin_word_index].word << '\n';
        return;
    }
    
    if (begin_word_index == -1) {
        cerr << "Beginning word does not exist in the dictionary" << '\n';
        exit(1);
    }
    if (end_word_index == -1) {
        cerr << "Ending word does not exist in the dictionary" << '\n';
        exit(1);
    }

     search_dict.push_back(begin_word_index);
     dictionary[begin_word_index].discovered = true;
     discovereds++;

    while(!search_dict.empty()) {
        string current_word = dictionary[search_dict.front()].word;
        

        int current_index = static_cast<int>(search_dict.front());
        search_dict.pop_front();
       for(size_t i = 0; i < dictionary.size(); i++) {

        if(!dictionary[i].discovered) {
        if(change) {
            if((dictionary[i].word.size() == current_word.size())) {
                bool changed = false;
               for(size_t j = 0; j < current_word.size(); j++) {
                   if (dictionary[i].word[j] != current_word[j]) {
                       
                       if(changed) {
                           changed = false;
                           break;
                       }
                       changed = true;
                   }
               }
               if(changed) {
                    if (stackSpecified) {
                        search_dict.push_front(i);
                        dictionary[i].discovered = true; 
                        dictionary[i].prev = current_index;
                        discovereds++;
                        if(check_end(i)) {
                            return;
                        }
                        continue;        
                    }
                    if (queueSpecified) {
                        search_dict.push_back(i);
                        dictionary[i].discovered = true; 
                        dictionary[i].prev = current_index; 
                        discovereds++;
                        if(check_end(i)) {
                            return;
                        }
                        continue;    
                    }
               }
            }
            
        }
        if(swap) {
             if((dictionary[i].word.size() == current_word.size())) {
                int changed = 0;
                int ind_one = -1;
                int ind_two = -1;
                
                for(size_t j = 0; j < dictionary[i].word.size(); j++) {
                    if(current_word[j] != dictionary[i].word[j]) {
                        
                       if(changed == 0) {
                           ind_one = static_cast<int>(j);
                           changed++;
                           continue;
                       }
                       if(changed == 1) {
                           ind_two = static_cast<int>(j);
                           changed++;
                           continue;
                       }
                       if(changed == 2) {
                           changed++;
                           break;
                       }
                    
                    }
                }
                if(changed == 2) {
                    if ((ind_two-ind_one) == 1) {
                        if (dictionary[i].word[ind_one] == current_word[ind_two]) {
                            if (dictionary[i].word[ind_two] == current_word[ind_one]) {
                                if (stackSpecified) {
                                search_dict.push_front(i);
                                dictionary[i].discovered = true; 
                                dictionary[i].prev = current_index;
                                discovereds++;
                                if(check_end(i)) {
                                    return;
                                }
                                continue;
                                }
                                if (queueSpecified) {
                                search_dict.push_back(i);
                                dictionary[i].discovered = true; 
                                dictionary[i].prev = current_index;
                                discovereds++;
                                if(check_end(i)) {
                                    return;
                                }
                                continue;
                                }
                            }

                        }
                    
                    }
                }
            }
        }
        if(length) {
            if(dictionary[i].word.size() - current_word.size() == 1) {
                int diff = 0;
                
                
                for(int j = 0; j < static_cast<int>(current_word.size()); j++) {
                    if(current_word[j] != dictionary[i].word[j+diff]) {
                        
                        if(diff == 1) {
                            diff++;
                            break;
                        }
                        
                        diff++;
                        
                        j--;
                    }

                }
                if((diff == 0) || (diff == 1)) {
                    if (stackSpecified) {
                        search_dict.push_front(i);
                        dictionary[i].discovered = true; 
                        dictionary[i].prev = current_index;
                        discovereds++;        
                        if(check_end(i)) {
                            return;
                        }
                    }
                    if (queueSpecified) {
                        search_dict.push_back(i);
                        dictionary[i].discovered = true; 
                        dictionary[i].prev = current_index;   
                        discovereds++;
                        if(check_end(i)) {
                            return;
                        }
                    }
                }

            }
            if(current_word.size() - dictionary[i].word.size() == 1) {
                int diff = 0;
                
                for(int j = 0; j < static_cast<int>(dictionary[i].word.size()); j++) {
                    if(current_word[j+diff] != dictionary[i].word[j]) {
                        if(diff == 1) {
                            diff++;
                            break;
                        }
                        
                        diff++;
                        
                        j--;
                    }

                }
                if((diff == 0) || (diff == 1))  {
                    if (stackSpecified) {
                        search_dict.push_front(i);
                        dictionary[i].discovered = true; 
                        dictionary[i].prev = current_index;
                        discovereds++;        
                        if(check_end(i)) {
                            return;
                        }
                    }
                    if (queueSpecified) {
                        search_dict.push_back(i);
                        dictionary[i].discovered = true; 
                        dictionary[i].prev = current_index; 
                        discovereds++;  
                        if(check_end(i)) {
                            return;
                        }
                    }
                }
               
            }
        }
        }
        
       }
    }
    cout << "No solution, " << discovereds << " words discovered." << '\n';
}

void Letterman::output() {
    int temp = static_cast<int>(end_word_index);
        deque<int> path;
        
        while(temp >= 0) {
            path.push_front(temp);
            temp = dictionary[temp].prev;
        }
    cout << "Words in morph: " << path.size() << '\n';
    if(output_mode != "M") {
        for(size_t i = 0; i < path.size(); i++) {
            cout << dictionary[path[i]].word << '\n';
        }
    }
    
    if(output_mode == "M") {
        cout << path[0] << '\n';
        for (size_t i = 0; i <  path.size() -1; i++) {
            if(dictionary[path[i]].word.size() == dictionary[path[i+1]].word.size()) {
                int changed = 0;
                int ind = -1;
                int ind_two = -1;
                char tempc = '?';
                for(size_t j = 0; j < dictionary[path[i]].word.size(); j++) {
                    if(dictionary[path[i]].word[j] != dictionary[path[i+1]].word[j]) {
                        tempc = dictionary[path[i+1]].word[j];
                        
                        changed ++;
                        if(changed == 1) {
                            ind = static_cast<int>(j);
                            continue;
                        }
                        if(changed == 2) {
                            ind_two = static_cast<int>(j);
                        }
                        if(changed > 2) {
                            break;
                        }
                    }
                    
                }
                if (changed == 1) {
                    cout << "c," << ind << "," << tempc << '\n';
                }
               
                if(changed==2) {
                        if(((ind_two-ind)==1)&&(dictionary[path[i]].word[ind] == dictionary[path[i+1]].word[ind_two])) {
                            if(dictionary[path[i]].word[ind_two] == dictionary[path[i+1]].word[ind]) {
                                cout << "s," << ind << '\n';
                            }
                        }
                }
            }
            if(dictionary[path[i]].word.size() > dictionary[path[i+1]].word.size()) {
                int index = -1;
                int dummy = 0;
                for(int j = 0; j < static_cast<int>(dictionary[path[i+1]].word.size()); j++) {
                    if(dictionary[path[i]].word[j+dummy] != dictionary[path[i+1]].word[j]) {
                        
                        if(dummy == 1) {
                            dummy++;
                            break;
                        }
                        index = j;
                        dummy++;
                        j--;
                    }
                }
                if((dummy == 0) || (dummy == 1)) {
                    cout << "d,";
                    if(dummy == 0) {
                        cout << dictionary[path[i]].word.size() -1 << '\n';
                    } 
                    else {
                        cout << index << '\n';
                    }
                }
            }
            if(dictionary[path[i+1]].word.size() > dictionary[path[i]].word.size()) {

                int index = -1;

                char insert = dictionary[path[i+1]].word[dictionary[path[i+1]].word.size()-1];
                int dummy = 0;

                for(int j = 0; j < static_cast<int>(dictionary[path[i]].word.size()); j++) {
                    if(dictionary[path[i]].word[j] != dictionary[path[i+1]].word[j+dummy]) {
                        
                        if(dummy == 1) {
                            dummy++;
                            break;
                        }
                        index = j;
                        insert = dictionary[path[i+1]].word[j];
                        dummy++;
                        j--;
                    }
                }
                if((dummy == 0) || (dummy == 1)) {
                    cout << "i,";

                    if(dummy == 0) {
                        cout << dictionary[path[i]].word.size()  << ",";
                    } 
                    else {
                        cout << index << ",";
                    }
                    cout << insert << '\n';
                }
            }
        }
    }
    
}

int main (int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);

    Letterman letter;

    letter.getoptions(argc, argv);

    letter.readdict();

    letter.search();

    
    

    

    //Create default constructor which initializes the member variables to false
}