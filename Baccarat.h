#ifndef BACCARAT_H
#define BACCARAT_H

#include <iostream>
#include <string>

#include "playingcards.h"

void PrintCards(vector<Card> bankerDeck, vector<Card> playerDeck);

int getSum(vector<Card> deck);

void Baccarat(int& coins);

#endif