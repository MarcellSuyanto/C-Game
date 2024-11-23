#include "playingcards.h"

#include <vector>
#include <algorithm> /*random_shuffle*/
#include <stdio.h>   /* printf, NULL */
#include <stdlib.h>  /* srand, rand */
#include <time.h>
#include <sstream>
#include <random>


using namespace std;

vector<Card> createDeck() {
    vector<Card> deck;

    srand (time(NULL));

    char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    char suits[] = {'H','D','S','C'};

    for (char rank : ranks) {
        for (char suit : suits) {
            deck.push_back({rank, suit});
        }
    }

    random_shuffle(deck.begin(), deck.end());

    return deck;
}


bool getValidNumber(const string& input, int& number, int minRange, int maxRange) {
    stringstream ss(input); // Create a stringstream from the input
    if (!(ss >> number)) { // Try to convert the input to an integer
        return false; // Return false for invalid input
    }

    // Check if the number is within range
    if (number <= minRange || number > maxRange) {
        return false; // Return false for out-of-range number
    }

    return true; // Return true for valid input
}


