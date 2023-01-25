// Project UID af1f95f547e44c8ea88730dfb185559d
#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.h"
#include "Image.h"
#include "processing.h"
using namespace std;

 int main(int argc, char* argv[]) {
    if ((argc != 5 && argc != 4)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
     }
    
    if (argc == 5 && (atoi(argv[3]) < 0 || atoi(argv[4]) < 0)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
    if ((argc == 4 && atoi(argv[3]) < 0)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
    string file_in = argv[1];
    string file_out = argv[2];
    
    
    ifstream fin(file_in);
    ofstream fout(file_out);

    if( !fin.is_open() ) {
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    if( !fout.is_open() ) {
        cout << "Error opening file: " << argv[2] << endl;
        return 1;
    }

    Image *img = new Image;
    Image_init(img, fin);
    int new_width = 0;
    int new_height = 0;
    if (argc == 5) {
        new_width = atoi(argv[3]);
        new_height = atoi(argv[4]);
    }
    if (argc == 4) {
        new_width = atoi(argv[3]);
        new_height = Image_height(img);
    }
    
    seam_carve(img, new_width, new_height);
    Image_print(img, fout);
    fin.close();
    fout.close();
    delete img;
 }