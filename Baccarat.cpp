#include <iostream>
#include <string>
#include <algorithm>

#include "playingcards.h"

void PrintCards(vector<Card> bankerDeck, vector<Card> playerDeck){
    //Input: vector(Banker's Deck, Player's Deck)
    //Output: void
    //Displays the cards currently on the table

    //Header
    cout << "PLAYER        ";
    int player_size = playerDeck.size(); 
    int banker_size = bankerDeck.size();
    for (int i=0; i < player_size-1; i++){
        cout << "               ";
    }   
    cout << "     BANKER" << endl;

    //Displays the cards in row
    //Face up cards have the rank and suite in the middle, face down cards empty
    for (int i=0; i < player_size; i++){
        cout << "+----------+  ";
    }
    cout << "  |  ";
    for (int i=0; i < banker_size; i++){
        cout << "  +----------+  ";
    }
    cout << endl;

    for (int i=0; i<2; i++){
        for (int i =0; i < player_size; i++){
            cout << "|          |  ";
        }
        cout << "  |  ";
        for (int i =0; i < banker_size; i++){
            cout << "  |          |  ";
        }
        cout << endl;
    }
    
    for (int i=0; i<player_size; i++){
        cout << "|    " << playerDeck[i].rank <<playerDeck[i].suit << "    |  ";
    }

    cout << "  |  ";

    for (int i=0; i<banker_size; i++){
        cout << "  |    " << bankerDeck[i].rank << bankerDeck[i].suit << "    |  ";
    }
    cout << endl;

     for (int i=0; i<2; i++){
        for (int i =0; i < player_size; i++){
            cout << "|          |  ";
        }
        cout << "  |  ";
        for (int i =0; i < banker_size; i++){
            cout << "  |          |  ";
        }
        cout << endl;
    }
    for (int i=0; i < player_size; i++){
        cout << "+----------+  ";
    }
    cout << "  |  ";
    for (int i=0; i < banker_size; i++){
        cout << "  +----------+  ";
    }
    cout << endl;
}

int getSumBaccarat(vector<Card> deck){
    //Input: vector(Player/Banker deck of cards)
    //Output: int(sum of the values of the hand, according to the rules of Baccarat)
    int length = deck.size();
    int total = 0;
    for (int i=0; i<length; i++){
        char temp = deck[i].rank;
        int num; 
        if (temp == 'T' || temp == 'J' || temp == 'Q' || temp == 'K' ){ //10 and face cards are 0
            num = 0;
        }else if (temp == 'A') { //Ace is 1
            num= 1;
        }else {
            num = temp - '0'; //Converts the number to integer equivalent
        }
        total += num;
    }
    total = total%10; //Takes only the ones digit of final total
    return total;
}

void Baccarat(int& coins){
    //Input: int_by_reference(Player's coins)
    //Output: void
    // Initiates the game of Baccarat, making use of its helper functions

    /*
    HOW TO PLAY
    1. Bet on either banker or player or tie
    2. Two cards are dealt for both player and banker
    3. 2-9 retains their value, (10, J, Q, K) are zero, and Ace is 1
    4. If total value >9, take the first digit
    5. Third Card Draw Rules follows the link provided in GitHub
    6. Total closest to 9 wins
    */
    while(true){
        vector<Card> newDeck = createDeck(); //Shuffled deck of 52 cards
        char placeBet; //Player's bet choice
        int bet; //Player's bet amount
        string temp;

        cout << "Where would you like to place your bet?" << endl;
        cout << "Banker(B), Player(P), Tie(T)"<< endl;
        cout << "Place your bet: ";
        cin >> placeBet;
        while (placeBet != 'P' && placeBet != 'B' && placeBet != 'T'){
            cout << "Invalid input, try again: ";
            cin >> placeBet;
        }
        cout << "" << endl;
        cout << "How much would you like to bet: ";
        cin >> temp;
        while (!getValidNumber(temp, bet, 0, coins)){
            cout << "Invalid bet. Enter another bet: ";
            cin >> temp;
        }

        vector<Card> bankerDeck(newDeck.begin(), newDeck.begin() + 2); //Two cards for each banker and dealer initially
        vector<Card> playerDeck(newDeck.begin() + 2, newDeck.begin() + 4);

        PrintCards(bankerDeck, playerDeck);

        int bankerTotal = getSumBaccarat(bankerDeck);
        int playerTotal = getSumBaccarat(playerDeck);
        bool playerDraw = false;
        char win = '_';
        if ((playerTotal != 8 && playerTotal != 9) && (bankerTotal != 8 && bankerTotal != 9)){ //If neither banker nor player wins by natural hand
            if (playerTotal <= 5){ //Player's third card draw rule
                playerDeck.push_back(newDeck[5]);
                playerTotal = getSumBaccarat(playerDeck);
                playerDraw = true;
            } 

            if (playerDraw == false){ //The Player did not draw a first card
                if (bankerTotal <= 5){
                    bankerDeck.push_back(newDeck[5]);
                    bankerTotal = getSumBaccarat(bankerDeck);
                }
            } else{
                //Third card draw rule according to the banker's hand, given the player drew a third card
                if (bankerTotal <= 2){
                    bankerDeck.push_back(newDeck[6]);
                } else if (bankerTotal == 3 && playerDeck[2].rank != 8){
                    bankerDeck.push_back(newDeck[6]);
                } else if (bankerTotal == 4 && playerDeck[2].rank >= 2 && playerDeck[2].rank <= 7){
                    bankerDeck.push_back(newDeck[6]);
                } else if (bankerTotal == 5 && playerDeck[2].rank >= 4 && playerDeck[2].rank <= 7){
                    bankerDeck.push_back(newDeck[6]);
                } else if (bankerTotal == 6 && (playerDeck[2].rank == 6 || playerDeck[2].rank == 7)){
                    bankerDeck.push_back(newDeck[6]);
                }
                bankerTotal = getSumBaccarat(bankerDeck);
            }
        //Natural Win Conditions
        } else if ((playerTotal == 8 || playerTotal == 9) && (bankerTotal != 8 && bankerTotal != 9)){
            win = 'P';
        } else if ((bankerTotal == 8 || bankerTotal == 9) && (playerTotal != 8 && playerTotal != 9)){
            win = 'B';
        } else if ((bankerTotal == 8 || bankerTotal == 9) && (playerTotal == 8 || playerTotal == 9)){
            win = 'T';
        }
        if (win == '_'){ //If no one has won yet
            if (bankerTotal == playerTotal){
                win = 'T';
            } else if (bankerTotal < playerTotal){
                win = 'P';
            } else{
                win = 'B';
            }
        }
        cout << " " << endl;
        cout << "FINAL RESULT" << endl;
        cout << " " << endl;

        PrintCards(bankerDeck, playerDeck);

        cout << "Player Total: " << getSumBaccarat(playerDeck) << endl;
        cout << "Banker Total: " << getSumBaccarat(bankerDeck) << endl;
        cout << " " << endl;

        if (win == 'T'){
            cout << "TIE" << endl;
        } else if (win == 'P'){
            cout << "PLAYER WINS" << endl;
        } else{
            cout << "BANKER WINS" << endl;
        }
        cout << " " << endl;
        if (placeBet == win && win != 'T') { //Player wins
            coins += bet;
            cout << "You win: " << bet << endl;
        } else if (placeBet == win && win == 'T'){ //Player wins, Tie guess gets 8x bet value
            coins += 8*bet;
            cout << "You win: " << 8*bet << endl;
        } else{ //Player loses
            const int tempCoins = coins-bet;
            coins = max(tempCoins,0);
            cout << "You lose: " << bet << endl;
        }
        cout << "Net Worth: " << coins << endl;
        if (coins == 0){
            return;
        }
        // Asking if they still want to play this game
        char again;
        cout << "Would you like to play Higher or Lower again? (Y/N): ";
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

