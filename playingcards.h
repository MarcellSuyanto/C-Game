#ifndef PLAYINGCARDS_H
#define PLAYINGCARDS_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Card {
    char rank;
    char suit; 
};
vector<Card> createDeck();
bool getValidNumber(const string& input, double& number, int minRange, int maxRange);

#endif