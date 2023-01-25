// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
//Jacob Klingler
#include "stats.h"
#include "p1_library.h"
#include <iostream>
using namespace std;

int main() {
  //Input both the file an column name
  string fileName;
  string columnName;
  cout << "enter a filename" << endl;
  cin >> fileName;
  cout << "enter a column name" << endl;
  cin >> columnName;
  cout << "reading column " << columnName << " from " << fileName << endl;

  //Extract the file into the vector
  vector<double> column;
  column = extract_column(fileName, columnName);
  
  //Output the summary of the vector
  cout << "Summary (value: frequency)" << endl;
  vector<vector<double>> summary;
  summary = summarize(column);
  for (size_t i = 0; i < summary.size(); i++) {
    cout << summary[i][0] << ": " << summary[i][1] << endl;
  }
  cout << endl;

  //Output the statistic of the vector
  cout << "count = " << count(column) << endl;
  cout << "sum = " << sum(column) << endl;
  cout << "mean = " << mean(column) << endl;
  cout << "stdev = " << stdev(column) << endl;
  cout << "median = " << median(column) << endl;
  cout << "mode = " << mode(column) << endl;
  cout << "min = " << min(column) << endl;
  cout << "max = " << max(column) << endl;
  cout << "  0th percentile = " << percentile(column, 0) << endl;
  cout << " 25th percentile = " << percentile(column, 25) << endl;
  cout << " 50th percentile = " << percentile(column, 50) << endl;
  cout << " 75th percentile = " << percentile(column, 75) << endl;
  cout << "100th percentile = " << percentile(column, 100) << endl;
}