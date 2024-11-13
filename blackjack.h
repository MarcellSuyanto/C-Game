#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#include "playingcards.h"

void PrintCards(vector<Card> dealerDeck, vector<Card> playerDeck, bool hit);

int getSum(vector<Card> deck);

string CheckBust(vector<Card> deck);

void Blackjack(double &coins);

#endif