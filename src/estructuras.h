#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>

using namespace std;

struct User {
    string name;
    int age;
};


struct Card {
    string name;
    int value;
};


struct Player {
    string name;
    float balance;
    float bet;
    Card cards[10];
    int total;
    int aces;
    bool eliminated;
};
#endif // ESTRUCTURAS_H