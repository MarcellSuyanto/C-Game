#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#include "playingcards.h"


using namespace std;

void PrintCards(vector<Card> dealerDeck, vector<Card> playerDeck, bool hit){
    //Printing Dealer's Deck
    cout << "DEALER" << endl;
    for (int i=0; i < dealerDeck.size(); i++){
        cout << "+----------+  ";
    }
    cout << endl;

    for (int i=0; i<2; i++){
        for (int i =0; i < dealerDeck.size(); i++){
            cout << "|          |  ";
        }
        cout << endl;
    }
    if (hit == true){
        for (int i=0; i<2; i++){
            cout << "|    " << dealerDeck[0].rank << dealerDeck[0].suit << "    |  " << "|          |  ";
            break;
        }
    } else{
        for (int i=0; i<dealerDeck.size(); i++){
           cout << "|    " << dealerDeck[i].rank << dealerDeck[i].suit << "    |  ";
        }
    }
    
    cout << endl;

    for (int i=0; i<2; i++){
        for (int i =0; i < dealerDeck.size(); i++){
            cout << "|          |  ";
        }
        cout << endl;
    }

    for (int i=0; i < dealerDeck.size(); i++){
        cout << "+----------+  ";
    }
    cout << endl;

    //Printing Player's Deck
    int num = playerDeck.size();
    cout << "PLAYER" << endl;
    for (int i=0; i < num; i++){
        cout << "+----------+  ";
    }
    cout << endl;

    for (int i=0; i<2; i++){
        for (int i =0; i < num; i++){
            cout << "|          |  ";
        }
        cout << endl;
    }

    for (int i=0; i<num; i++){
        cout << "|    " << playerDeck[i].rank << playerDeck[i].suit << "    |  ";
    }
    cout << endl;

    for (int i=0; i<2; i++){
        for (int i =0; i < num; i++){
            cout << "|          |  ";
        }
        cout << endl;
    }

    for (int i=0; i < num; i++){
        cout << "+----------+  ";
    }
    cout << endl; 
}

int getSumBlackjack(vector<Card> deck){
    int length = deck.size();
    int total = 0;
    int Ace_count = 0;
    for (int i=0; i<length; i++){
        char temp = deck[i].rank;
        int num; 
        if (temp == 'T' || temp == 'J' || temp == 'Q' || temp == 'K' ){
            num = 10;
        }else if (temp == 'A') {
            num= 11;
            Ace_count ++;
        }else {
            num = temp - '0'; 
        }
        total += num;
        

        while(total > 21 && Ace_count > 0){
            total -= 10;
            Ace_count--;
        }

    }
    return total;
}

string CheckBust(vector<Card> deck){
    int total = getSumBlackjack(deck);
    if (total > 21){
        return "BUST";
    }
    if (total == 21){
        return "BLACKJACK";
    }
    return "OKAY";
    
}

void Blackjack(int &coins){
    vector<Card> deck = createDeck();
    /*
    HOW TO PLAY
    1. Player places bets
    2. Dealer deals one card face up to player and themself
    3. Dealer deals one more card face up to player and one face down to themselves
    4. ranks = 2-10 equivalent value, J,Q,K = 10, A can be 11 or 1 
    5. if hand totals to 21, auto win
    6. else, can ask for a hit until bust and lose
    7. or stay and dealer flips face down card
        7i. if 16 or under, take another card
        7ii. if 17 or higher, stay
    8. if higher than dealer, win
    9. if equal or lower to dealer, lose
    */

    while (true){ //while the player continues to sit on the blackjack table
        string temp;
        int bet;
        bool win = false;

        cout << "How much to bet: ";
        cin >> temp;

        while (!getValidNumber(temp, bet, 0, coins)){
            cout << "Invalid bet. Enter another bet: ";
            cin >> temp;
        }

        // Create deck and hands for both dealer and player (2 cards each)
        vector<Card> newDeck = createDeck();
        vector<Card> dealerDeck(newDeck.begin(), newDeck.begin() + 2);
        vector<Card> playerDeck(newDeck.begin() + 2, newDeck.begin() + 4);

        //Hit Phase, only one card face up for the dealer, two for the player
        //Player can call to ask for another card, maximum 5 cards total in the players hand
        bool hit = true;
        char choice;
        int hit_count = 0;
        bool end = false;

        PrintCards(dealerDeck, playerDeck, hit);

        while (hit_count < 4 and end == false){
            cout << "Would like to add another card? (Y/N): ";
            cin >> choice;
            while (choice != 'Y' && choice != 'N'){
                cout << "Y or N only!" << endl;
                cout << "Y/N: ";
                cin >> choice;
            }
            if (choice == 'N'){
                break;
            }
            else{
                hit_count++;
                playerDeck.push_back(newDeck[4+hit_count]);
                PrintCards(dealerDeck, playerDeck, hit);

                if (CheckBust(playerDeck) == "BUST"){ //Lose
                    cout << "BUST" << endl;
                    const int tempCoins = coins-bet;
                    coins = max(tempCoins,0);
                    cout << "Net Worth: " << coins << endl;
                    end = true;
                }else if (CheckBust(playerDeck) == "BLACKJACK"){ //Win
                    cout << "BLACKJACK" << endl;
                    coins += bet*1.5;
                    cout << "Net Worth: " << coins << endl;
                    end = true;
                }
            }

        }

        hit = false;

        //Play Phase, Dealer opens the face down card
        if (end == false){
            if (CheckBust(dealerDeck) == "BUST"){ //win
                cout << "WIN" << endl;
                coins += bet*1.5;
                cout << "Net Worth: " << coins << endl;
                end = true;
            }else if (CheckBust(dealerDeck) == "BLACKJACK"){
                cout << "LOSE" << endl;
                const int tempCoins = coins-bet;
                coins = max(tempCoins,0);
                cout << "Net Worth: " << coins << endl;
                end = true;
            }
        }
        int dealer_count = 0;
        while (getSumBlackjack(dealerDeck) <= 16 && end == false){
            dealer_count ++;
            dealerDeck.push_back(newDeck[4+hit_count+dealer_count]);
            cout << endl;
            cout << endl;
            cout << endl;
            if (CheckBust(dealerDeck) == "BUST"){
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "WIN" << endl;
                coins += bet*1.5;
                cout << "Net Worth: " << coins << endl;
                end = true;
                break;
            }
            
            if (getSumBlackjack(dealerDeck) >= getSumBlackjack(playerDeck)){
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "LOSE" << endl;
                const int tempCoins = coins-bet;
                coins = max(tempCoins,0);
                cout << "Net Worth: " << coins << endl;
                end = true;
                break;
            }
            if (dealer_count == 5){
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "LOSE" << endl;
                const int tempCoins = coins-bet;
                coins = max(tempCoins,0);
                cout << "Net Worth: " << coins << endl;
                end = true;
                break;
            }
        }
        if (end == false){
            if (getSumBlackjack(dealerDeck) >= getSumBlackjack(playerDeck)){
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "LOSE" << endl;
                const int tempCoins = coins-bet;
                coins = max(tempCoins,0);
                cout << "Net Worth: " << coins << endl;
            }else{
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "WIN" << endl;
                coins += bet*1.5;
                cout << "Net Worth: " << coins << endl;
            }
        }
        char again;
        cout << "Would you like to play Blackjack again? (Y/N): ";
        cin >> again;
        while (again != 'Y' && again != 'N'){
                cout << "Y or N only!" << endl;
                cout << "Y/N: ";
                cin >> again;
            }
        if (again == 'N'){
            break;
        }else if (again == 'Y'){
            continue;
        }
    }
}
