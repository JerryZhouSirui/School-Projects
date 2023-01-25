// 1761414855B69983BD8035097EFBD312EB0527F0
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

enum loc {medical, border,non};

struct coord {
    int x;
    int y;
    loc location;
};



struct MST {
    bool k;
    double d;
    int p;
};

struct FASTTSP {
    bool k;
    double d;
    int n;
};



class OPTTSP {
    public: 
    double run_tot = 0;
    double curr_L = 0;
    double bestd = 0;
    std::vector<int> path;
    std::vector<int> best;
    std::vector<bool> visit;
    std::vector<std::vector<double>> distm;
    std::vector<double> sub;
    
    bool intersect(int one, int two, int three, int four);

    void fasttp(const std::vector<coord> &coords);
        

    void genPerms(size_t permLength);
       

    bool promising(size_t permLength);
        
};



