#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#include "playingcards.h"


using namespace std;

void PrintCards(vector<Card> dealerDeck, vector<Card> playerDeck, bool hit){
    //Input: vector(Dealer and Player deck of cards), boolean(whether the player hit a new card)
    //Output: void
    //Prints the cards currently on the table

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
    if (hit == true){ // If the player is still in hit phase, only the first card of the dealer is face up
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
    //Input: vector(Any deck of cards)
    //Output: void
    //Gets the sum of the hand, according to the rules of Blackjack

    int length = deck.size();
    int total = 0;
    int Ace_count = 0;
    for (int i=0; i<length; i++){
        char temp = deck[i].rank;
        int num; 
        if (temp == 'T' || temp == 'J' || temp == 'Q' || temp == 'K' ){ //face cards are 10
            num = 10;
        }else if (temp == 'A') { //Ace can be 11, or 1. Ace_count explained below
            num= 11;
            Ace_count ++;
        }else {
            num = temp - '0'; 
        }
        total += num;
        

        while(total > 21 && Ace_count > 0){ 
            /*If there exists more than one Ace in the hand that causes the 
            hand's value to exceed 21, keep changing the aces, one by one, from 
            11 to 1 until the hand's value is below 21
            */
            total -= 10;
            Ace_count--;
        }

    }
    return total;
}

string CheckBust(vector<Card> deck){
    //Input: vector(Any deck of cards)
    //Output: string(declaration of win/lose status)
    //Checks if the hand in play exceeds 21 aka BUST or equals 21 aka BLACKJACK
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
    //Input: int_by_reference(Player's coins)
    //Output: void
    //Initiates the game of blackjack, making use of its helper functions
    
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
                playerDeck.push_back(newDeck[4+hit_count]); //Adds a card to the players hand
                PrintCards(dealerDeck, playerDeck, hit);

                if (CheckBust(playerDeck) == "BUST"){ //Player Lose
                    cout << "BUST" << endl;
                    const int tempCoins = coins-bet;
                    coins = max(tempCoins,0);
                    cout << "Net Worth: " << coins << endl;
                    end = true;
                }else if (CheckBust(playerDeck) == "BLACKJACK"){ //Player Win
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
            if (CheckBust(dealerDeck) == "BUST"){//Player win
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "WIN" << endl;
                coins += bet*1.5;
                cout << "Net Worth: " << coins << endl;
                end = true;
            }else if (CheckBust(dealerDeck) == "BLACKJACK"){//Player lose
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "LOSE" << endl;
                const int tempCoins = coins-bet;
                coins = max(tempCoins,0);
                cout << "Net Worth: " << coins << endl;
                end = true;
            }
        }
        int dealer_count = 0;
        while (getSumBlackjack(dealerDeck) <= 16 && end == false){//Keep adding to the dealer's hand while the value of the hand is <17
            dealer_count ++;
            dealerDeck.push_back(newDeck[4+hit_count+dealer_count]);
            cout << endl;
            cout << endl;
            cout << endl;
            if (CheckBust(dealerDeck) == "BUST"){ // Player win
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "WIN" << endl;
                coins += bet*1.5;
                cout << "Net Worth: " << coins << endl;
                end = true;
                break;
            }
            
            if (getSumBlackjack(dealerDeck) >= getSumBlackjack(playerDeck)){ //Dealer's hand is greater than or equal to Player's
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "LOSE" << endl;
                const int tempCoins = coins-bet;
                coins = max(tempCoins,0);
                cout << "Net Worth: " << coins << endl;
                end = true;
                break;
            }
            if (dealer_count == 5){ //Dealer wins
                PrintCards(dealerDeck, playerDeck, hit);
                cout << "LOSE" << endl;
                const int tempCoins = coins-bet;
                coins = max(tempCoins,0);
                cout << "Net Worth: " << coins << endl;
                end = true;
                break;
            }
        }
        if (end == false){ // If no winner yet
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
        if (coins == 0){
            return;
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
