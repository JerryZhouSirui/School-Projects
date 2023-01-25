//Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <string>
#include <cassert>
#include <utility>
#include <cmath>
#include <map>
#include <set>
#include "csvstream.h"

using namespace std;


class Classifier{
    private:
        int total_posts = 0; //done
        int total_unique_words; //done
        string train_file;
        string test_file;
        map<string, double> posts_with_word; //done
        map<string, double> posts_with_label; //done
        map<pair<string, string>, double> label_with_word;
        map<string, double> log_priors; // done
        map<pair<string, string>, double> log_likelihoods;
        
    public:
        set<string> unique_words(const string &str);
        void determine_log_likelihood();
        void determine_log_prior();
        void read_in();
        void train_classifier(const string &train_file_in);
        void test_classifier(const string &test_file_in);
        int get_total_posts();
        int get_unique_words();
        void print_debug_output();
};

int Classifier::get_total_posts(){
    return total_posts;
}

int Classifier::get_unique_words(){
    return total_unique_words;
}

set<string> Classifier::unique_words(const string &str){
     // Fancy modern C++ and STL way to do it
    istringstream source{str};
    return {istream_iterator<string>{source},
    istream_iterator<string>{}};
}

void Classifier::determine_log_likelihood(){
    double log_likelihood_curr;
    for (auto &node:label_with_word){
        
            log_likelihood_curr = log(node.second / posts_with_label.find((node.first).first)->second);
        
       
        log_likelihoods[node.first] = log_likelihood_curr;
    }
}

void Classifier::determine_log_prior(){
    double current_prior = 0;
    for (auto &label:posts_with_label){
        current_prior = log(double(label.second) / total_posts);
        log_priors[label.first] = current_prior;
    }
}

void Classifier::read_in(){
    csvstream train_in(train_file);

    map<string, string> row;
    pair<string, string> label_word;
    while (train_in >> row){
        label_word.first = row["tag"];
        posts_with_label[row["tag"]] += 1;

        for (auto &word:unique_words(row["content"])){
            posts_with_word[word] += 1;
            total_unique_words++;
            label_word.second = word;
            label_with_word[label_word] += 1;         
        }
        total_posts++;
    }
}

void Classifier::train_classifier(const string &train_file_in){
    train_file = train_file_in;
    read_in();
    determine_log_prior();
    determine_log_likelihood();
}

void Classifier::test_classifier(const string &test_file_in){ 
    test_file = test_file_in;
    csvstream test_in(test_file);

    map<string, string> row;
    cout << "test data:" << endl;
    while(test_in >> row){
        //creating map of each label's log probability for a particular post
        map<string, double> log_probabilities; 
        for(auto &label:posts_with_label){
            double likelihood_sum = 0;
            double log_probabilty = 0;
            for(auto &word:unique_words(row["content"])){
                pair<string, string> label_word;
                label_word.first = label.first;
                label_word.second = word;
               
                if (log_likelihoods[label_word] != 0){
                    likelihood_sum += log_likelihoods[label_word];
                   
                }
                else if (posts_with_word[word] != 0){
                    likelihood_sum += log(posts_with_word[word] / total_posts);
                    
                }
                else{
                    likelihood_sum += log(1.0 / total_posts);
                    
                }
            }
            log_probabilty = log_priors[label.first] + likelihood_sum;
            log_probabilities[label.first] = log_probabilty;
        }

        double current_max_lp = log_probabilities.begin()->second;
        string current_key = log_probabilities.begin()->first;
        for(auto &lp:log_probabilities){
            if (lp.second > current_max_lp){
                current_key = lp.first;
                current_max_lp = lp.second;
            }
        }
        cout << "  correct = " << row["tag"] << ", predicted = " << current_key
             << ", log-probability score = " << log_probabilities[current_key] << endl;
        cout << "  content = " << row["content"] << endl << endl;
    }
}

void Classifier::print_debug_output(){
    csvstream train_in(train_file);
    map<string, string> row;

    cout << "training data:" << endl;
    while (train_in >> row){
        cout << "  label = " << row["tag"] << ", ";
        cout << "content = " << row["content"] << endl; 
        
    }

    cout << "trained on " << total_posts << " examples" << endl;
    cout << "vocabulary size = " << posts_with_word.size() << endl << endl;
    cout << "classes:" << endl;
    for (auto &element:log_priors){
        cout << "  " << element.first << ", " << posts_with_label[element.first] 
             << " examples, log-prior = " << element.second << endl; 
    }

    cout << "classifier parameters:" << endl;
    for(auto &element:label_with_word){
        cout << "  " << element.first.first << ":" << element.first.second 
             << ", count = " << element.second << ", log-likelihood = " 
             << log_likelihoods[element.first] << endl;
    }
    cout << endl;
}

//end classifier class functions

int main(int argc, char* argv[]){
    const string train_file = argv[1];
    const string test_file = argv[2];
    string debug = ""; //Used to cast debug argument
    

    cout.precision(3);

    //checking arguments
    if (argc == 4){
        debug = argv[3];
        if (debug == "--debug"){
            assert(true);
        }
        else{
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return -1;
        }
    }
    else if(argc == 3){
        assert(true);
    }
    else{
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }

    Classifier c1;
    c1.train_classifier(train_file);

    if(debug == "--debug"){
        c1.print_debug_output();
    }
    
    else{
        cout << "trained on " << c1.get_total_posts() << " examples" << endl << endl;
    }
    
    c1.test_classifier(test_file);

return 0;
}