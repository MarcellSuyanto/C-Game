#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>   /* NULL */
#include <stdlib.h>  /* srand, rand */
#include <ctime>
#include <vector>

#include "playingcards.h"

void PrintSlots(int slots[3]){
    //Input: array[3](the slot shapes chosen)
    //Output: void
    //Prints out the slot screen with 3 shapes

    // 1 = Square, 2 = Circle, 3 = Triangle, 4 = Hexagon, 5 = Parallelogram, 6 = Arrow

    vector<string> square = {
        "+-------------+",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "+-------------+"
    };
    
    vector<string> circle = {
        "     *****     ",
        "  **       **  ",
        " *           * ",
        "*             *",
        " *           * ",
        "  **       **  ",
        "     *****     "
    };
    
    vector<string> triangle = {
        "      /\\      ",
        "     /  \\     ",
        "    /    \\    ",
        "   /      \\   ",
        "  /        \\  ",
        " /          \\ ",
        "/____________\\",
    };

    vector<string> hexagon = {
        "   _______     ",
        "  /       \\    ",
        " /         \\   ",
        "/           \\  ",
        "\\           /  ",
        " \\_________/   ",
        "               "
    };


    vector<string> parallelogram = {
        "   ___________  ",
        "  /          /  ",
        " /          /   ",
        "/          /    ",
        "\\          \\    ",
        " \\          \\   ",
        "  \\__________\\  "
    };

    vector<string> arrow = {
        "      ^      ",
        "     / \\     ",
        "    /   \\    ",
        "   /     \\   ",
        "  /_______\\  ",
        "      |      ",
        "      |      "
    };

    vector<string>* slotshapes = new vector<string>[3]; //The three chosen slots

    for (int i = 0; i < 3; i++) {//Assigning the equivalent shapes
        if (slots[i] == 0) {
            slotshapes[i] = square;
        } else if (slots[i] == 1) {
            slotshapes[i] = circle;
        } else if (slots[i] == 2) {
            slotshapes[i] = triangle;
        } else if (slots[i] == 3){
            slotshapes[i] = hexagon;
        } else if (slots[i] == 4){
           slotshapes[i] = parallelogram;
        } else if (slots[i] == 5){
            slotshapes[i] = arrow;
        }
    }

    // Iterate over slots and construct the output
    for (int i = 0; i<7; i++){
        cout << slotshapes[0][i] << "     " << slotshapes[1][i] << "     " << slotshapes[2][i] << endl;
    }
    delete[] slotshapes;
}

void Slots(int& coins){
    //Input: int_by_reference(Player's coins)
    //Output: void
    //Initiates the game of slots, making use of its helper functions
    /*
    HOW TO PLAY
    1. Input how much money to bet
    2. Three slots
    3. If three same, return coins + 10*bet
    4. If two same, return coins - bet
    5. If no same, return coins - 2*bet
    */ 

    while (true){ 
        string temp;
        int bet;
        
        cout << "How much to bet: ";
        cin >> temp;

        while (!getValidNumber(temp, bet, 0, coins)){
            cout << "Invalid bet. Enter another bet: ";
            cin >> temp;
        }

        int slots[3];
        int matches;
        srand(static_cast<unsigned int>(time(0))); //seed for rand
        
        for (int i=0; i<3; i++){
            slots[i] = rand() % 6; //3 random numbers, each in range [1,6]
            
        }
        
        if (slots[0] == slots[1] && slots[1] == slots[2]){ //If three identical shapes
            coins += 10*bet;
            cout << "WIN" << endl;
        } else if (slots[0] == slots[1] && slots[0] != slots[2] || slots[0] == slots[2] && slots[0] != slots[1] || slots[1] == slots[2] && slots[1] != slots[0]){
            //if two identical shapes
            const int tempCoins = coins-bet;
            coins = max(tempCoins,0);
            cout << "LOSE" << endl;
        } else{
            //no identical shapes
            const int tempCoins = coins-2*bet;
            coins = max(tempCoins,0);
            cout << "LOSE" << endl;
        }
        PrintSlots(slots);
        cout << "Net Worth: " << coins << endl;
        if (coins == 0){
            return;
        }

        
        // Asking if they still want to play this game
        char again;
        cout << "Would you like to play Slots again? (Y/N): ";
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


