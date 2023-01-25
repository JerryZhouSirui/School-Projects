// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
//Jacob Klingler

#include "stats.h"
#include "p1_library.h"
#include <cassert>
#include <vector>
#include <cmath>
#include <iostream>


using namespace std;

//Requires: Vector of doubles that is not empty.
//Effects: Returns a vector of a vector of doubles, the first value in the inner vector
//is the value and the second is the number of occurences.

vector<vector<double> > summarize(vector<double> v) {
  vector<vector<double>> summary;
  vector<double> ValandOcr;
  
  double Ocr = 0;

  sort(v); //Sort vector

  //Iterate through the vector, find the next new value as well as the number of times
  //that it appears, add it to a vector and put the vector inside the vector of vectors.
  for(size_t i = 0; i < v.size(); i = i + Ocr) {
    Ocr = 0;
    ValandOcr.clear();
    for(size_t j = i; j < v.size(); j++) {
      if(v[j] == v[i]) {
        Ocr++;
      }
    }
    ValandOcr.push_back(v[i]);
    ValandOcr.push_back(Ocr);
    summary.push_back(ValandOcr);
  }
  return summary;
}

//Requires: a vector of doubles that is not empty.
//Effects: returns the size of the vector.
int count(vector<double> v) {
  //Return the number of values as the size of the vector.
  int number = 0;
  number = v.size();
  return number;
}

//Requries: a vector of doubles that is not empty.
//Effects: returns the sum of the values within the vector.
double sum(vector<double> v) {
  //Iterate through the vector and add each value to a running sum.
  double sum = 0;
  for (size_t i = 0; i < v.size(); i++) {
    sum = sum + v[i];
  }
  return sum;
}

//Requires: a vector of doubles that is not empty.
//Effects: returns the mean of the values within the vector.
double mean(vector<double> v) {
  double mean = 0;
  double sum = 0;
  //Calculate the sum of the vector and divide by it's size.
  for (size_t i = 0; i < v.size(); i++) {
    sum = sum + v[i];
  }
  mean = sum / v.size();
  return mean;
}

//Requires: a vector of doubles that is not empty.
//Effects: returns the median of the values within the vector.
double median(vector<double> v){
  sort(v); //sort vector
  double median;
  //If the number of elements is even, average the two middle values in the vector.
 if (v.size() % 2 == 0) {
   median = (v[v.size()/2] + v[v.size()/2 -1])/2;
 }
 //If the number of elements is odd, find the middle element and its value.
 else{ 
   median = v[floor(v.size()/2)];
 }
 return median;
}

//Requires: a vector of doubles that is not empty.
//Effects: returns the mode of the values within the vector.
double mode(vector<double> v) {
   double newcounts = 0;
   double counts = 0;
   double num = 0;
   sort(v); //Sort vector
   //Iterate through the vector, for each next new number, find the number of times it occurs,
   //and compare it to the current value which occurs the most. Return the vale with the most occurences.
   for(size_t i = 0; i < v.size(); i = i + newcounts) {
     newcounts = 0;
     for (size_t j = i; j < v.size(); j++){
       if (v[j] == v[i]) {
         newcounts++;
       }
     }
     if (newcounts > counts) {
       counts = newcounts;
       num = v[i];
     }
   }
   return num;
}

//Requires: a vector of doubles that is not empty.
//Effects: returns the minimum of the values within the vector.
double min(vector<double> v) {
  sort(v); //sort vector
  return v[0];
}

//Requires: a vector of doubles that is not empty.
//Effects: returns the maximum of the values within the vector.
double max(vector<double> v) {
  sort(v); //sort vector
  return v[v.size()-1];
}

//Requires: a vector of doubles that is not empty.
//Effects: returns the standard deviation of the values within the vector.
double stdev(vector<double> v) {
  sort(v); //sort vector
  double stdev = 0;
  double sum = 0;
  double mean = 0;
  //Calculate the sum and mean for the vector
  for(size_t i = 0; i < v.size(); i++) {
    sum = sum + v[i];
  }
  mean = sum / v.size();
  //Use the sum and mean by plugging them into the standard
  //deviation formula for a sample and return the value
  for (size_t i = 0; i < v.size(); i++){
    stdev = stdev + pow((v[i] - mean), 2);
  }
  stdev = stdev / (v.size() - 1);
  stdev = sqrt(stdev);
  return stdev;
}

//Requires: a vector of doubles that is not empty, and a double.
//Effects: returns the percentile for the vector based on the given value.
double percentile(vector<double> v, double p) {
  double percentile = 0;
  double rank = 0;
  double rankint = 0;
  double rankfract = 0;
  sort(v); //sor the vector
  //Use the percentile formula to calculate the percentile, subtracting one from the vector indexes on the formula.
  rank = p/100 * (v.size() - 1) + 1;
  rankfract = modf(rank , &rankint);
  if (p < 100) {
    percentile = v[rankint - 1] + rankfract*(v[rankint] - v[rankint - 1]);
  }
  //Create an exception case for p = 100 to prevent indexing out of the vector
  if (p == 100) {
    percentile = v[v.size()-1];
  }
  return percentile; 
}