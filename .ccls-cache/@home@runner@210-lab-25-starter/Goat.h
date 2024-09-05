// Goat.h

#ifndef GOAT_H
#define GOAT_H
#include <iostream>
using namespace std;

const int SIZE = 15, MAX_AGE = 20;

class Goat {
private:
    string name, color;
    int age;
    string names[SIZE] = {"Kid", "Baby", "Teen", "Adult", "Senior",
        "Grown", "Mature", "Old", "Veteran", "Elder", "Ancient",
        "Immortal", "Legendary", "Godlike", "God"};
    string colors[SIZE] = {"Black", "White", "Brown", "Red", "Blue",
        "Green", "Purple", "Yellow", "Orange", "Pink", "Gray",
        "Silver", "Gold", "Mauve", "Bronze"};

public:
    // constructors
    Goat() { 
        name = names[rand() % SIZE]; 
        color = colors[rand() % SIZE];
        age = rand() % MAX_AGE; 
    }
    Goat(string n, string c, int a) 
        { name = n; color = c; age = a; }

    // setters and getters
    void setName(string n)    { name = n;     }
    void setAge(int a)        { age = a;      }
    void setColor(string c)   { color = c;    }
    string getName()          { return name;  }
    int getAge()              { return age;   }
    string getColor()         { return color; }

    bool operator< (const Goat &other) const {
        return name < other.name;
    }

};

#endif