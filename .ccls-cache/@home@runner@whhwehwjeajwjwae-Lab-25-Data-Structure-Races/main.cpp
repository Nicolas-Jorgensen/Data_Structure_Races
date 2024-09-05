#include <iostream>
#include <thread>
#include <chrono>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <algorithm> //for std::sort
#include <iomanip>
#include <fstream>
using namespace std;

const int IDSIZE = 20000, WIDTH = 15, STRUCTS = 3, RACETYPE = 4;

void structureRace(vector<string>, list<string>, set<string>, string [],
array<array<int,STRUCTS>,RACETYPE>, int);
int vecReadTime(vector<string> &container, string ids[]);
int listReadTime(list<string> &container, string ids[]);
int setReadTime(set<string> &container, string ids[]);
int vecSortTime(vector<string> &container);
int listSortTime(list<string> &container);
int vecInsertTime(vector<string> &container);
int listInsertTime(list<string> &container);
int setInsertTime(set<string> &container);
int vecDelTime(vector<string> &container);
int listDelTime(list<string> &container);
int setDelTime(set<string> &container);

int main() {
    array<array<int,STRUCTS>,RACETYPE> raceTimes;
    vector<string> vec;
    list<string> list;
    set<string> set;
    
    ifstream fin("codes.txt");
    string ids[IDSIZE];
    //int i = 0;
    //while(getline(fin,ids[i++]));
    for(int i = 0; i < IDSIZE; i++) {
        getline(fin,ids[i]);
    }
    fin.close();
    
    structureRace(vec,list,set,ids,raceTimes, 1);
    return 0;
}

void structureRace(vector<string> vec, list<string> list, set<string> set,
                    string ids[], array<array<int, STRUCTS>, RACETYPE> raceTimes, int raceNum) {
    if (raceNum < 1) {
        cerr << "raceNum must be greater than 0";
        return;
    }
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
    for(int i = 0; i < raceNum-1; i++) {
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
    /*for(int i = 0; i < STRUCTS; i++) { // avg
        for(int k = 0; k <RACETYPE; k++) {
            if(i == 2 && k == 1) {}//do nothing
            else {
                raceTimes[i][k] /= static_cast<double>(raceNum);
            }
        }
    }*/

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
            
int vecReadTime(vector<string> &container, string ids[]) {
    
    auto start = chrono::high_resolution_clock::now();
    
    for(int i = 0; i < IDSIZE; i++) 
        container.push_back(ids[i]);
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
    
}
int listReadTime(list<string> &container, string ids[]) {
    auto start = chrono::high_resolution_clock::now();

    for(int i = 0; i <IDSIZE; i++) 
        container.push_back(ids[i]);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
int setReadTime(set<string> &container, string ids[]) {
    auto start = chrono::high_resolution_clock::now();

    for(int i = 0; i <IDSIZE; i++) 
        container.insert(ids[i]);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
int vecSortTime(vector<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    sort(container.begin(),container.end());

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
int listSortTime(list<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    container.sort();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
int vecInsertTime(vector<string> &container){
    auto start = chrono::high_resolution_clock::now();
    
    container.insert(container.begin() + (IDSIZE/2), "TESTCODE");
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
int listInsertTime(list<string> &container) {
    auto start = chrono::high_resolution_clock::now();
    
    auto it = next(container.begin(), IDSIZE/2);
    container.insert(it, "TESTCODE");
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
int setInsertTime(set<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    container.emplace("TESTCODE");

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
int vecDelTime(vector<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    container.erase(container.begin() + (IDSIZE/2));

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
int listDelTime(list<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    auto it = next(container.begin(),IDSIZE/2);
    container.erase(it);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}
int setDelTime(set<string> &container) {
    auto start = chrono::high_resolution_clock::now();

    container.erase("TESTCODE");

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}


/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/