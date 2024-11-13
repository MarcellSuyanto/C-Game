#include <iostream>
#include <string>

#include "playingcards.h"

void PrintCards(vector<Card> bankerDeck, vector<Card> playerDeck){
    cout << "PLAYER        ";
    int player_size = playerDeck.size();
    int banker_size = bankerDeck.size();

    for (int i=0; i < player_size-1; i++){
        cout << "               ";
    }   

    cout << "     BANKER" << endl;

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

    //Printing Player's Deck
}

int getSum(vector<Card> deck){
    int length = deck.size();
    int total = 0;
    for (int i=0; i<length; i++){
        char temp = deck[i].rank;
        int num; 
        if (temp == 'T' || temp == 'J' || temp == 'Q' || temp == 'K' ){
            num = 0;
        }else if (temp == 'A') {
            num= 1;
        }else {
            num = temp - '0'; 
        }
        total += num;
    }
    total = total%10;
    return total;
}

void Baccarat(double& coins){
    /*
    HOW TO PLAY
    1. Bet on either banker or player or tie
    2. Two cards are dealt for both player and banker
    3. 0-9 retains their value, (10, J, Q, K) are zero, and Ace is 1
    4. If total value >9, take the first digit
    5. Third Card Draw Player:
        a. If Player total is 0-5, player draws a third card
        b. If the total is 6 or 7, the Player stands.
        c. If the total is 8 or 9 (a "natural"), the Player stands.
    6. Third Card Draw banker:
        a. If the Banker has a total of 0-2, they draw a third card.
        b. If the Banker has a total of 3, they draw unless the Player's third card is an 8.
        c. If the Banker has a total of 4, they draw if the Player's third card is 2-7.
        d. If the Banker has a total of 5, they draw if the Player's third card is 4-7.
        e. If the Banker has a total of 6, they draw if the Player's third card is 6 or 7.
        f. If the Banker has a total of 7, they stand.
        g. If player did not draw a third card, banker follows player's third card draw rules
    7. Total closest to 9 wins
    */
    while(true){
        vector<Card> newDeck = createDeck();
        char placeBet; 
        double bet;
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

        vector<Card> bankerDeck(newDeck.begin(), newDeck.begin() + 2);
        vector<Card> playerDeck(newDeck.begin() + 2, newDeck.begin() + 4);

        PrintCards(bankerDeck, playerDeck);

        int bankerTotal = getSum(bankerDeck);
        int playerTotal = getSum(playerDeck);
        bool playerDraw = false;
        char win = '_';
        if ((playerTotal != 8 && playerTotal != 9) && (bankerTotal != 8 && bankerTotal != 9)){
            if (playerTotal <= 5){
                playerDeck.push_back(newDeck[5]);
                playerTotal = getSum(playerDeck);
                playerDraw = true;
            } 

            if (playerDraw == false){
                if (bankerTotal <= 5){
                    bankerDeck.push_back(newDeck[5]);
                    bankerTotal = getSum(bankerDeck);
                    cout << "1" << endl;
                }
            } else{
                if (bankerTotal <= 2){
                    bankerDeck.push_back(newDeck[6]);
                    cout << "2" << endl;
                } else if (bankerTotal == 3 && playerDeck[2].rank != 8){
                    bankerDeck.push_back(newDeck[6]);
                    cout << "3" << endl;
                } else if (bankerTotal == 4 && playerDeck[2].rank >= 2 && playerDeck[2].rank <= 7){
                    bankerDeck.push_back(newDeck[6]);
                    cout << "4" << endl;
                } else if (bankerTotal == 5 && playerDeck[2].rank >= 4 && playerDeck[2].rank <= 7){
                    bankerDeck.push_back(newDeck[6]);
                    cout << "5" << endl;
                } else if (bankerTotal == 6 && (playerDeck[2].rank == 6 || playerDeck[2].rank == 7)){
                    bankerDeck.push_back(newDeck[6]);
                    cout << "6" << endl;
                }
                bankerTotal = getSum(bankerDeck);
            }
        
        } else if ((playerTotal == 8 || playerTotal == 9) && (bankerTotal != 8 && bankerTotal != 9)){
            win = 'P';
        } else if ((bankerTotal == 8 || bankerTotal == 9) && (playerTotal != 8 && playerTotal != 9)){
            win = 'B';
        } else if ((bankerTotal == 8 || bankerTotal == 9) && (playerTotal == 8 || playerTotal == 9)){
            win = 'T';
        }
        if (win == '_'){
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

        cout << "Player Total: " << getSum(playerDeck) << endl;
        cout << "Banker Total: " << getSum(bankerDeck) << endl;
        cout << " " << endl;

        if (win == 'T'){
            cout << "TIE" << endl;
        } else if (win == 'P'){
            cout << "PLAYER WINS" << endl;
        } else{
            cout << "BANKER WINS" << endl;
        }
        cout << " " << endl;
        if (placeBet == win && win != 'T') {
            coins += bet;
            cout << "You win: " << bet << endl;
        } else if (placeBet == win && win == 'T'){
            coins += 8*bet;
            cout << "You win: " << 8*bet << endl;
        } else{
            coins -= bet;
            cout << "You lose: " << bet << endl;
        }
        cout << "Net Worth: " << coins << endl;
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

