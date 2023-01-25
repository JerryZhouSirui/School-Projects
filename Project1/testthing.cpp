#include <fstream>
#include <iostream>

using namespace std;

ifstream fin("test.txt");

int gpa;
string name;

fin >> gpa;
while(fin >> gpa >> name) {
    if(gpa > 3.0)
}