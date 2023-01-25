/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */
//Jacob Klingler

#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_sum_neg_data_set();

void test_median_even();
void test_median_odd();

void test_summarize_mult();

void test_count_neg();

void test_mean_neg();

void test_min_neg();

void test_max_neg();

void test_stdev_neg();

void test_percentile_neg();
// Add prototypes for you test functions here.

const double epsilon = 0.00001;

int main() {
  
  test_sum_neg_data_set();
  test_median_even();
  test_median_odd();
  test_summarize_mult();
  test_count_neg();
  test_mean_neg();
  test_min_neg();
  test_max_neg();
  test_stdev_neg();
  test_percentile_neg();

  // Call your test functions here

  return 0;
}
//Test percentile function with negative numbers
void test_percentile_neg(){
  cout << "test_percentile_neg" << endl;
  vector<double> data;
  data.push_back(-5.5);
  data.push_back(-3);
  data.push_back(1.5);
  data.push_back(2);
  data.push_back(4.5);
  assert(percentile(data, 20) == -3.5);
  cout << "PASS!" << endl;
}
//Test standard deviation formula with negative numbers
void test_stdev_neg(){
  cout << "test_stdev_neg" << endl;
  vector<double> data;
  data.push_back(-5.5);
  data.push_back(-3);
  data.push_back(1.5);
  data.push_back(2);
  data.push_back(4.5);
  assert(abs(stdev(data) - 	4.0527768258319) < epsilon);
  cout << "PASS!" << endl;
}
//Test max function with negative numbers
void test_max_neg(){
   cout << "test_max_neg" << endl;
  vector<double> data;

  data.push_back(-5.5);
  data.push_back(-3);
  data.push_back(1.5);
  data.push_back(2);
  data.push_back(4.5);
  assert(max(data) == 4.5);
  cout << "PASS!" << endl;
}
//Test min function with negative numbers
void test_min_neg(){
  cout << "test_min_neg" << endl;
  vector<double> data;

  data.push_back(-5.5);
  data.push_back(-3);
  data.push_back(1.5);
  data.push_back(2);
  data.push_back(4.5);
  assert(min(data) == -5.5);
  cout << "PASS!" << endl;
}
//Test mean function with negative numbers 
void test_mean_neg() {
  cout << "test_mean_neg" << endl;
  vector<double> data;
  data.push_back(-5.5);
  data.push_back(-3);
  data.push_back(1.5);
  data.push_back(2);
  data.push_back(4.5);
  assert(mean(data) == -0.1);
  cout << "PASS!" << endl;
}
//Test count function with negative numbers
void test_count_neg() {
  cout << "test_count_neg" << endl;
  vector<double> data;
  data.push_back(-5.5);
  data.push_back(-3);
  data.push_back(1.5);
  data.push_back(2);
  data.push_back(4.5);

  assert(count(data) == 5);
  cout << "PASS!" << endl;
}
//Test summarize function with repeating values
void test_summarize_mult() {
  cout << "test_summarize_mult" << endl; 
  vector<vector<double>> summary;
  vector<double> occurOne;
  vector<double> occurTwo;
  vector<double> occurThree;
  vector<double> data;

  data.push_back(1);
  data.push_back(2);
  data.push_back(2);
  data.push_back(3);

  occurOne.push_back(1);
  occurOne.push_back(1);
  occurTwo.push_back(2);
  occurTwo.push_back(2);
  occurThree.push_back(3);
  occurThree.push_back(1);

  summary.push_back(occurOne);
  summary.push_back(occurTwo);
  summary.push_back(occurThree);

  assert(summarize(data) == summary);
  cout << "PASS!" << endl;
}
//Test the median function with an even number of values
void test_median_even() {
  cout << "test_median_even" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);

  assert(median(data) == 2.5);
  
  cout << "PASS!" << endl;
}
//Test the odd function with an odd number of values
void test_median_odd(){
  cout << "test_median_odd" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(3);
  data.push_back(7);
  data.push_back(11);
  data.push_back(515);

  assert(median(data) == 7);
  cout << "PASS!" << endl;
}
//Test the sum function with negative numbers
void test_sum_neg_data_set() {
  cout << "test_sum_neg_data_set" << endl;

  vector<double> data;
  data.push_back(-5.5);
  data.push_back(-3);
  data.push_back(1.5);
  data.push_back(2);
  data.push_back(4.5);

  assert(sum(data) == -0.5);

  cout << "PASS!" << endl;
}

// Add the test function implementations here.
