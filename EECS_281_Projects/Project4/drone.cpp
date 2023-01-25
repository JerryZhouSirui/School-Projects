// 1761414855B69983BD8035097EFBD312EB0527F0
#include <iostream>
#include <getopt.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include "drones.h"
#include <iomanip>

using namespace std;

typedef pair<double, int> pq_elt;

void getoptions(int argc, char *argv[], string &mode) {

    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        {"mode", required_argument, nullptr, 'm'},
        {"help", no_argument, nullptr, 'h'},
        { nullptr, 0,        nullptr, '\0' }
    };
    
    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "m:h", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'm':
            mode = optarg;
            break;
        case 'h':
            cout << "This program does drones and shtuff" << endl;
            exit(0);
        default:
            cerr << "Error: Unknown command line option" << endl;
            exit(1);
    } 
    }
    
}

double distance (coord one, coord two) {
    if(one.location == medical && two.location == non) {
        return INFINITY;
    }
    else if(one.location == non && two.location == medical) {
        return INFINITY;
    }
    else {
        double x = static_cast<double>(one.x) - static_cast<double>(two.x);
        double y = static_cast<double>(one.y) - static_cast<double>(two.y);
        double dist = x * x + y * y;
        return sqrt(dist);
    }
}

void read_in(vector<coord> &coords) {
    int size;
    std::cin >> size;
    coords.reserve(size);
    int x;
    int  y;
    while(std::cin >> x >> y) {
        coord temp;
        temp.x = x;
        temp.y = y;
        if(x < 0 && y < 0) {
            temp.location = medical;
        }
        else if(x == 0 && y <= 0) {
            temp.location = border;
        }
        else if(y == 0 && x <= 0) {
            temp.location = border;
        }
        else {
            temp.location = non;
        }
        coords.push_back(temp);
    }
}

void minn_s_t(const vector<coord> &coords) {
    double runn_dist = 0;
    vector<MST> prim;
    prim.resize(coords.size());
    
    prim[0].d = 0;
    prim[0].p = -1;
    prim[0].k = true;
    int prev = 0;
    for(int i = 1; i < static_cast<int>(coords.size()); i++) {
        prim[i].d = INFINITY;
    }
    for(int i = 1; i < static_cast<int>(coords.size()); i++) {
        double min = INFINITY;
        int min_index = -1;
        for(int j = 0; j < static_cast<int>(coords.size()); j++) {
            if(!prim[j].k){
                double dist = distance(coords[prev], coords[j]);
                if(prim[j].d > dist) {
                    prim[j].d = dist;
                    prim[j].p = prev;
                }
                if(prim[j].d < min) {
                    min = prim[j].d;
                    min_index = j;
                }
            }
        }
        prim[min_index].k = true; 
        runn_dist += prim[min_index].d;
        prev = min_index;
    }

    cout << runn_dist << endl;
    for(int i = 1; i < static_cast<int>(coords.size()); i++) {
        if(i < prim[i].p) {
            cout << i << " " << prim[i].p << endl;
        }
        else {
            cout << prim[i].p << " " << i << endl;
        }
    }
}

double fdistance(coord one, coord two) {
    double x = static_cast<double>(one.x) - static_cast<double>(two.x);
    double y = static_cast<double>(one.y) - static_cast<double>(two.y);
    double dist = x * x + y * y;
    return sqrt(dist);
}

void fast_tsp(const vector<coord> &coords){
    vector<FASTTSP> ftp;
    double run_dist = 0;
    ftp.resize(coords.size());
    ftp[0].d = 0;
    ftp[0].k = true;
    
    int prev = 0;
    for(int i = 1; i < static_cast<int>(coords.size()); i++) {
        double min_dist = INFINITY;
        int min_ind = -1;
        for(int j = 1; j < static_cast<int>(coords.size()); j++) {
            if(!ftp[j].k) {
                double distance = fdistance(coords[prev], coords[j]);
                if(min_dist > distance) {
                    min_dist = distance;
                    min_ind = j;
                }
            }
        }
        run_dist += min_dist;
        ftp[min_ind].k = true;
        ftp[min_ind].d = min_dist;
        ftp[prev].n = min_ind;
        prev = min_ind;
    }
    run_dist += fdistance(coords[0], coords[prev]);
    cout << run_dist << endl;
    prev = 0;
    for(int i = 0; i < static_cast<int>(coords.size()); i++) {
        cout << prev << " ";
        prev = ftp[prev].n;
    }
}

bool OPTTSP::intersect(int one, int two, int three, int four) {
        double dist_ab = distm[one][two];
        double dist_cd = distm[three][four];
        double dist_ac = distm[one][three];
        double dist_bd = distm[two][four];

        if(dist_ab + dist_cd > dist_ac + dist_bd) {
            return true;
        }
        return false;
    }

    void OPTTSP::fasttp(const std::vector<coord> &coords) {
        std::vector<FASTTSP> ftp;
        double run_dist = 0;
        ftp.resize(coords.size());
        ftp[0].d = 0;
        ftp[0].k = true;
    
        int prev = 0;
        for(int i = 1; i < static_cast<int>(coords.size()); i++) {
            double min_dist = INFINITY;
            int min_ind = -1;
            for(int j = 1; j < static_cast<int>(coords.size()); j++) {
                if(!ftp[j].k) {
                    double distance = distm[prev][j];
                    if(min_dist > distance) {
                        min_dist = distance;
                        min_ind = j;
                    }
                }
            }
            run_dist += min_dist;
            ftp[min_ind].k = true;
            ftp[min_ind].d = min_dist;
            ftp[prev].n = min_ind;
            prev = min_ind;
        }
        run_dist += distm[0][prev];
        std::vector<int> temp;
        temp.resize(coords.size()+1);
        prev = 0;
        for(int i = 0; i < static_cast<int>(coords.size()); i++) {
            temp[i] = prev;
            prev = ftp[prev].n;
        }
        temp[coords.size()] = 0;
    // 2 - Opt checking hopefully this doesn't screw anything up for now
        
        for(int i = 0; i < static_cast<int>(coords.size()-2); i++) {
            for(int j = 2+i; j < static_cast<int>(coords.size()); j++) {
                if(intersect(temp[i], temp[i+1], temp[j],temp[j+1])) {
                    run_dist -= distm[temp[i]][temp[i+1]];
                    run_dist -= distm[temp[j]][temp[j+1]];
                    run_dist += distm[temp[i]][temp[j]];
                    run_dist += distm[temp[i+1]][temp[j+1]];
                    std::reverse(temp.begin()+i+1,temp.begin()+j+1);
                    i = 0; 
                    break;
                }
            }
                
        } 
        
        temp.pop_back();
        best = temp;
        path = temp;
        bestd = run_dist;
    }

    void OPTTSP::genPerms(size_t permLength) {
        if (permLength == path.size()) {
            if(run_tot + distm[0][path.back()] < bestd) {
                bestd = run_tot + distm[0][path.back()];
                best = path;
            }
            return;
        } // if
        if (!promising(permLength)){
            return;
        }    
        for (size_t i = permLength; i < path.size(); ++i) {
            
            std::swap(path[permLength], path[i]);
           
            run_tot += distm[path[permLength]][path[permLength-1]];
            genPerms(permLength + 1);
            
            run_tot -= distm[path[permLength]][path[permLength-1]];
            std::swap(path[permLength], path[i]);
        }   // for
    } // genPerms()

    bool OPTTSP::promising(size_t permLength) {
        if(path.size() - permLength < 5) {
            return true;
        }
        if(run_tot > bestd) {
            return false;
        }


        fill(visit.begin(), visit.end(), false);
        fill(sub.begin(), sub.end(), INFINITY);
        double tot = 0;
        
        int subi = static_cast<int>(permLength);
        for(int i = static_cast<int>(permLength); i < static_cast<int>(path.size()); i++) {
            int nex = -1;
            double min = INFINITY;
            for(int j = static_cast<int>(permLength); j < static_cast<int>(path.size()); j++) {
                if(!visit[j]) {
                    double dist = distm[path[subi]][path[j]];
                    if(sub[j] > dist) {
                        sub[j] = dist;
                    }
                    if(min > sub[j]) {
                        min = sub[j];
                        nex = j;
                    }
                }
            }
            visit[nex] = true;
            tot += min;
            subi = nex;
        }
        if(run_tot + tot > bestd) {
            return false;
        }
        double b = INFINITY;
        double e = INFINITY;
        int bi = 0;
        int ei = path[permLength-1];
        for(int i = static_cast<int>(permLength); i < static_cast<int>(path.size()); i++) {
            if(distm[bi][path[i]] < b) {
                b = distm[bi][path[i]];
            }
            if(distm[ei][path[i]] < e) {
                e = distm[ei][path[i]];
            }
        }
        if(b + e + tot + run_tot >= bestd) {
            return false;
        }
        return true;
    }

int main(int argc, char *argv[]) {
    string mode;
    ios_base::sync_with_stdio(false);
    vector<coord> coords;
    getoptions(argc, argv, mode);
    
    read_in(coords);
    cout << setprecision(2); //Always show 2 decimal places
    cout << fixed; //Disable scientific notation for large numbers
    if(mode == "MST") {
        minn_s_t(coords);
    }
    else if (mode == "FASTTSP") {
        fast_tsp(coords);
    }
    else if (mode == "OPTTSP") {
        OPTTSP opts;
        opts.path.resize(coords.size());
        opts.best.resize(coords.size());
        opts.visit.resize(coords.size());
        opts.distm.resize(coords.size());
        opts.sub.resize(coords.size());

        for(int i = 0; i < static_cast<int>(coords.size()); i++) {
            opts.distm[i].resize(coords.size());
            for(int j = 0; j < static_cast<int>(coords.size()); j++) {
                opts.distm[i][j] = fdistance(coords[i], coords[j]);
            }
        }
        opts.fasttp(coords);
        
        opts.genPerms(1);
        cout << opts.bestd << '\n';
        for(int i = 0; i < static_cast<int>(opts.best.size()); i++) {
            cout << opts.best[i] << " ";
        }
    }

}