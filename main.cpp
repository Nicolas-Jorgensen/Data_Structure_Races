// Nicolas Jorgensen

// compares run times for data structure read, insert, sort, and delete times
// Structures compared are: array, vector, list, and set.

#include <iostream>
#include <thread>
#include <chrono> //for timing
#include <array>
#include <vector>
#include <list>
#include <set>
#include <algorithm> //for std::sort
#include <iomanip>
#include <fstream>
using namespace std;

const int IDSIZE = 20000, WIDTH = 15, STRUCTS = 3, RACETYPE = 4, RACENUM = 15;

void structureRace(vector<string>, list<string>, set<string>, string [],
array<array<double,STRUCTS>,RACETYPE>, int);
double vecReadTime(vector<string> &container, string ids[]);
double listReadTime(list<string> &container, string ids[]);
double setReadTime(set<string> &container, string ids[]);
double vecSortTime(vector<string> &container);
double listSortTime(list<string> &container);
double vecInsertTime(vector<string> &container);
double listInsertTime(list<string> &container);
double setInsertTime(set<string> &container);
double vecDelTime(vector<string> &container);
double listDelTime(list<string> &container);
double setDelTime(set<string> &container);

int main() {
    array<array<double,STRUCTS>,RACETYPE> raceTimes; //to hold times
    vector<string> vec;
    list<string> list;
    set<string> set;
    
    ifstream fin("codes.txt");
    string ids[IDSIZE];
    int i = 0;
    while(getline(fin,ids[i++]));
    
    fin.close();
    
    structureRace(vec,list,set,ids,raceTimes, RACENUM);
    return 0;
}
//assigns race times to the racetimes array then prints it
void structureRace(vector<string> vec, list<string> list, set<string> set,
                    string ids[], array<array<double, STRUCTS>, RACETYPE> raceTimes,
                    int raceNum) {
    if (raceNum < 1) {
        cerr << "raceNum must be greater than 0";
        return;
    }//first race
    raceTimes[0][0] = vecReadTime(vec,ids);
    raceTimes[0][1] = vecSortTime(vec);
    raceTimes[0][2] = vecInsertTime(vec);
    raceTimes[0][3] = vecDelTime(vec);
    raceTimes[1][0] = listReadTime(list,ids);
    raceTimes[1][1] = listSortTime(list);
    raceTimes[1][2] = listInsertTime(list);
    raceTimes[1][3] = listDelTime(list);
    raceTimes[2][0] = setReadTime(set,ids);
    raceTimes[2][1] = -1;
    raceTimes[2][2] = setInsertTime(set);
    raceTimes[2][3] = setDelTime(set);
    vec.clear();
    list.clear();
    set.clear();
    for(int i = 0; i < raceNum-1; i++) { //if racetime is > 1
        raceTimes[0][0] += vecReadTime(vec,ids);
        raceTimes[0][1] += vecSortTime(vec);
        raceTimes[0][2] += vecInsertTime(vec);
        raceTimes[0][3] += vecDelTime(vec);
        raceTimes[1][0] += listReadTime(list,ids);
        raceTimes[1][1] += listSortTime(list);
        raceTimes[1][2] += listInsertTime(list);
        raceTimes[1][3] += listDelTime(list);
        raceTimes[2][0] += setReadTime(set,ids);
        raceTimes[2][1] = -1;
        raceTimes[2][2] += setInsertTime(set);
        raceTimes[2][3] += setDelTime(set);
        vec.clear();
        list.clear();
        set.clear();
    }
        
    for(int i = 0; i < STRUCTS; i++) { // avg
        for(int k = 0; k <RACETYPE; k++) {
            if(i == 2 && k == 1) {}//do nothing
            else {
                raceTimes[i][k] /= (static_cast<double>(raceNum));
            }
        }
    }
    //printing outputs
    cout << fixed << setprecision(2);
    cout << setw(WIDTH) << "Number of " <<"simulations: " << RACENUM << endl;
    cout << setw(WIDTH) << "Time in " << "milliseconds\n";
    cout << setw(WIDTH) << "Operation" << setw(WIDTH) << "Vector";
    cout << setw(WIDTH) << "List" << setw(WIDTH) << "Set" << endl;
    cout << setw(WIDTH) << "Read" << setw(WIDTH) << raceTimes[0][0];
    cout << setw(WIDTH) << raceTimes[1][0] << setw(WIDTH) << raceTimes[2][0];
    cout << endl << setw(WIDTH) << "Sort";
    cout << setw(WIDTH) << raceTimes[0][1] << setw(WIDTH) << raceTimes[1][1];
    cout << setw(WIDTH) << raceTimes[2][1] << endl;
    cout << setw(WIDTH) << "Insert" << setw(WIDTH) << raceTimes[0][2];
    cout << setw(WIDTH) << raceTimes[1][2] << setw(WIDTH) << raceTimes[2][2];
    cout << endl << setw(WIDTH) << "Delete" << setw(WIDTH) << raceTimes[0][3];
    cout << setw(WIDTH) << raceTimes[1][3] << setw(WIDTH) << raceTimes[2][3];
    cout << endl;
    
}
//reading into vector and returning elapsed time            
double vecReadTime(vector<string> &container, string ids[]) {
    
    auto start = chrono::high_resolution_clock::now();
    
    for(int i = 0; i < IDSIZE; i++) 
        container.push_back(ids[i]);
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
    
}
//reading into list and returning elapsed time            
double listReadTime(list<string> &container, string ids[]) {
    auto start = chrono::high_resolution_clock::now();

    for(int i = 0; i <IDSIZE; i++) 
        container.push_back(ids[i]);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
//reading into set and returning elapsed time            
double setReadTime(set<string> &container, string ids[]) {
    auto start = chrono::high_resolution_clock::now();

    for(int i = 0; i <IDSIZE; i++) 
        container.insert(ids[i]);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
//sorts a vector and returns elapsed time
double vecSortTime(vector<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    sort(container.begin(),container.end());

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
//sorts a list and returns elapsed time
double listSortTime(list<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    container.sort();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
//inserts TESTCODE into approx middle of vector and returns elapsed time
double vecInsertTime(vector<string> &container){
    auto start = chrono::high_resolution_clock::now();
    
    container.insert(container.begin() + (IDSIZE/2), "TESTCODE");
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
//inserts TESTCODE into approx middle of list and returns elapsed time
double listInsertTime(list<string> &container) {
    auto start = chrono::high_resolution_clock::now();
    
    auto it = next(container.begin(), IDSIZE/2);
    container.insert(it, "TESTCODE");
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
//inserts TESTCODE into approx middle of set and returns elapsed time
double setInsertTime(set<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    container.emplace("TESTCODE");

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
//deletes value from approx middle of vector and returns elapsed time
double vecDelTime(vector<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    container.erase(container.begin() + (IDSIZE/2));

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
//deletes value from approx middle of list and returns elapsed time
double listDelTime(list<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    auto it = next(container.begin(),IDSIZE/2);
    container.erase(it);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
//deletes value from approx middle of set and returns elapsed time
double setDelTime(set<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    container.erase("TESTCODE");

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
