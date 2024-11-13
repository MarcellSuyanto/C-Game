#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>   /* printf, NULL */
#include <stdlib.h>  /* srand, rand */
#include <ctime>
#include <vector>

#include "playingcards.h"

void PrintSlots(int slots[3]){
    // 1 = Square, 2 = Circle, 3 = Triangle, 4 = Hexagon, 5 = Parallelogram, 6 = Arrow
    vector<string> *shape = nullptr;

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

    vector<string> slotshapes[3];

    for (int i = 0; i < 3; i++) {
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

}

void Slots(double& coins){
    /*
    HOW TO PLAY
    1. Input how much money to bet
    2. Three slots
    3. If three same, return coins + 3*bet
    4. If two same, return coins - bet
    5. If no same, return coins - 2*bet
    */ 
    while (true){ 
        string temp;
        double bet;
        
        cout << "How much to bet: ";
        cin >> temp;

        while (!getValidNumber(temp, bet, 0, coins)){
            cout << "Invalid bet. Enter another bet: ";
            cin >> temp;
        }

        int slots[3];
        int matches;
        srand(static_cast<unsigned int>(time(0)));
        
        for (int i=0; i<3; i++){
            slots[i] = rand() % 6;
            
        }
        
        if (slots[0] == slots[1] && slots[1] == slots[0]){
            coins += 3*bet;
            cout << "WIN 3" << endl;
        } else if (slots[0] == slots[1] && slots[0] != slots[2] || slots[0] == slots[2] && slots[0] != slots[1] || slots[1] == slots[2] && slots[1] != slots[0]){
            coins -= bet;
            cout << "LOSE 2" << endl;
        } else{
            coins -= 2*bet;
            cout << "LOSE 0" << endl;
        }
        PrintSlots(slots);
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


