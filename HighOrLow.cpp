#include <iostream>
#include <vector>

#include "playingcards.h"

using namespace std;

void PrintCards(vector<Card> selectedCards, int current){
    for (int i=0; i < 5; i++){
        cout << "+----------+  ";
    }
    cout << endl;

    for (int i=0; i<2; i++){
        for (int i =0; i < 5; i++){
            cout << "|          |  ";
        }
        cout << endl;
    }

    for (int i=0; i<5; i++){
        if (i<current){
            cout << "|    " << selectedCards[i].rank << selectedCards[i].suit << "    |  ";
        }
        else{
            cout << "|          |  ";
        }
    }
    cout << endl;

    for (int i=0; i<2; i++){
        for (int i =0; i < 5; i++){
            cout << "|          |  ";
        }
        cout << endl;
    }

    for (int i=0; i < 5; i++){
        cout << "+----------+  ";
    }
    cout << endl;

}



void HighOrLow(int &coins){ 
    /*
    HOW TO PLAY
    1. Get 4 cards face down and 1 face up
    2. Starting from left to right, open a card once at a time
    3. Ask the player to guess if the next card is lower/higher than the next card
    4. If the player is wrong, reset
    5. If the player survives til the last card is flipped, get bonus
    6. Change the value of bet at each flip
    */

    while (true){
        vector<Card> newDeck = createDeck();
        vector<Card> selectedCards(newDeck.begin(), newDeck.begin() + 5);
        /*
        For Testing
        PrintCards(selectedCards, 6);
        */
        string temp;
        int current = 1; //current card being opened 1-4
        int bet;
        cout << "How much would you like to bet: ";
        cin >> temp;
        while (!getValidNumber(temp, bet, 0, coins)){
            cout << "Invalid bet. Enter another bet: ";
            cin >> temp;
        }

        PrintCards(selectedCards,current);

        while (current < 5){
            //Start round
            cout << "Is the next card Higher or Lower (H/L)?" << endl;
            char input;
            cout << "H/L: ";
            cin >> input;
            while (input != 'H' && input != 'L'){
                cout << "H or L only!" << endl;
                cout << "H/L: ";
                cin >> input;
                cout << input << endl;
            }
            //Converting Cards to their Numeric Values
            char first_temp = selectedCards[current-1].rank;
            char second_temp = selectedCards[current].rank;

            int first;
            int second;
            
            if (first_temp == 'T'){
                first = 10;
            }else if (first_temp == 'J') {
                first = 11; 
            }else if (first_temp == 'Q'){
                first = 12;
            }else if (first_temp == 'K'){
                first = 13;
            }else if (first_temp == 'A') {
                first = 1; 
            }else {
                first = first_temp - '0'; 
            }

            if (second_temp == 'T'){
                second = 10;
            }else if (second_temp == 'J'){
                second = 11;
            } else if (second_temp == 'Q'){ 
                second = 12; 
            } else if (second_temp == 'K'){
                second = 13;
            } else if (second_temp == 'A') {
                second = 1; 
            }else {
                second = second_temp - '0'; 
            }

            //Checking if player made the correct guess
            if ((input == 'H' && first > second) || (input == 'L' && first < second)){  //Lose
                coins -= bet;
                PrintCards(selectedCards,current+1);;
                cout << "You Lose" << endl;
                cout << "Net Worth: " << coins << endl;
                break;
            }
            if ((input == 'H' && first <= second) || (input == 'L' && first >= second)){ //Win
                cout << "Correct!" << endl;
            }

            current ++;
            PrintCards(selectedCards,current);

            if (current == 5){ //If reached 4 correct guesses
                coins += bet;
                cout << "You Win" << endl;
                cout << "Net Worth: " << coins << endl;
            }
        }
        
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
