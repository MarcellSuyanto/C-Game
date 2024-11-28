#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "playingcards.h"
#include "blackjack.h"
#include "HighOrLow.h"
#include "slotmachine.h"
#include "Baccarat.h"
#include "profile.h"

using namespace std;

const int MAP_WIDTH = 49;  // Map width
const int MAP_HEIGHT = 20; // Map height

char playerSymbol = '@'; // '@' represents the character.

vector<string> gameMap = {
    "#################################################",
    "#                                               #",
    "#       BLACKJACK           HIGHER OR LOWER     #",
    "#                                               #",
    "#      $$$$$$$$$$$                              #",
    "#      $$$     $$$             <<<<^>>>>        #",
    "#      $$$$$$$$$$$             <<<<v>>>>        #",
    "#          |1|                    |2|           #",
    "#----------| |--------------------| |----       #",
    " E                                      |       #",
    " X                                      |       #",
    " I       @                              |       #",
    " T                                      |       #",
    "#----------| |--------------------| |----       #",
    "#          |3|                    |4|           #",
    "#      !!! !!! !!!               &&&&&          #",
    "#      !!! !!! !!!              &&&&&&&         #",
    "#      !!! !!! !!!               &&&&&          #",
    "#                                               #",
    "#         SLOTS                BACCARAT         #",
    "#                                               #",
    "#################################################"
};

void displayMap(int& coins) {
    //Input: int_by_reference(Player's coins)
    //Output: void
    // Function to display the map
    cout << endl << "Current coins: " << coins << endl;
    for (const auto& row : gameMap) {

        cout << row << endl;
    }
    cout << endl;
}



void movePlayer(char direction, const string& username, int& coins, bool& exit) {
    //Input: char(direction, wasd), string_by_reference(Player usernam), int_by_reference(Player's coins), bool_by_reference(exit status)
    //Output: void
    //Function to move the player
    int playerX = -1;
    int playerY = -1;


    for (int i = 0; i < gameMap.size(); ++i) { //Searches for the current position of the player
        for (int j = 0; j < gameMap[i].size(); ++j) {
            if (gameMap[i][j] == playerSymbol) { // Set new position of player
                playerX = i;
                playerY = j;
                break;
            }
        }
        if (playerX != -1) break;
    }

    int newX = playerX;
    int newY = playerY;

    switch (direction) {
        case 'W': newX--; break; // Move up
        case 'w': newX--; break;
        
        case 'S': newX++; break; // Move down
        case 's': newX++; break;
        
        case 'A': newY--; break; // Move left
        case 'a': newY--; break;
        
        case 'D': newY++; break; // Move right
        case 'd': newY++; break;
        
        default:
            cout << "Invalid move. Use W/A/S/D." << endl;
            return;
    }

    if (newX >= 0 && newX < MAP_HEIGHT && newY >= 0 && newY < MAP_WIDTH) { // If valid positon on map
        if (gameMap[newX][newY] == '1') { // If character lands on 1 on the map
            for(int i=0; i<5; i++){
                cout << " " << endl;
            }
            cout << "Welcome to Blackjack!" << endl; 
            Blackjack(coins); // Call Blackjack game
        }
        else if (gameMap[newX][newY] == '2') {  
            for(int i=0; i<5; i++){
                cout << " " << endl;
            }
            cout << "Welcome to Higher or Lower!" << endl;
            HighOrLow(coins); // Call HighOrLow game
        }
        else if (gameMap[newX][newY] == '3') {
            for(int i=0; i<5; i++){
                cout << " " << endl;
            }
            cout << "Welcome to the Slot Machine!" << endl;
            Slots(coins); // Call Slot Machine
        }
        else if (gameMap[newX][newY] == '4') {
            for(int i=0; i<5; i++){
                cout << " " << endl;
            }
            cout << "Welcome to Baccarat!" << endl;
            Baccarat(coins); // Call Baccarat
        }

        // If character goes to 'EXIT' on map
        else if (gameMap[newX][newY] == 'E' || gameMap[newX][newY] == 'X' || gameMap[newX][newY] == 'I' || gameMap[newX][newY] == 'T') {
            exit = true; // Toggle off, exit from startGame()
            cout << "Exiting the game. Goodbye!\n";
            if (coins == 0){
                coins = 50;
            }
            updateUserCoins(username, coins); // Update the user's coins
            return;
        }
        else if (gameMap[newX][newY] == ' ') {
            gameMap[playerX][playerY] = ' '; // Clear the old position
            gameMap[newX][newY] = playerSymbol; // Set the new position
        }
        else if (gameMap[newX][newY] == '#') {
            cout << "Out of Bounds!" << endl;
        }
    }
    else {
        cout << "Out of Bounds!" << endl;
    }
}

void startGame(const string& username, int& coins) {
    //Input: string_by_reference(Player username), int_by_reference(Player's coins)
    //Output: void
    //Starts the game and exits when necessary
    displayMap(coins); // Display the initial map
    bool exit = false; // Toggle mechanism, to force kick out only if coins < 0

    while (!exit) {
        cout << "Move (W/A/S/D): ";
        char choice;
        cin >> choice; // Get the player's move choice

        // Move the player based on the choice
        movePlayer(choice, username, coins, exit);
        // and check if the player's coins are below zero
        if (coins == 0) {
            cout << "You have run out of coins! Exiting the game.\n";
            exit = true; // Set exit to true to break the loop
            coins = 50;
            updateUserCoins(username, coins); // Update the user's coins
            continue; // Proceed to the next iteration (which exits)
        }

        // Display the updated game map
        displayMap(coins);
    }
}

int main() {
    //main function of program
    string username;
    int coins = 1000; // Default coins for new users
    bool gameRunning = true;

    while (gameRunning) {
        displayMainMenu();  // Display the main menu
        int choice;
        string temp;
        cin >> temp;
        while (!getValidNumber(temp, choice, 0, 4)){
            cout << "Invalid choice. Try again: ";
            cin >> temp;
        }
        if (choice == 1){ // Create New User
            cout << "Enter a new username: ";
            cin >> username;
            

            // Check if the username already exists
            int tempCoins;
            if (usernameExists(username, tempCoins)) {
                cout << "Username already exists! Please choose a different username.\n";
            }
            else {
                saveUsername(username, coins);
                cout << "Profile created for " << username << " with " << coins << " coins.\n";
                startGame(username, coins);
            }
            
        }
        else if (choice == 2){ // Load Profile
            cout << "Enter your username to load the profile: ";
            cin >> username;

            // Check if the username exists
            if (usernameExists(username, coins)) {
                cout << "Profile loaded for " << username << ". You have " << coins << " coins.\n";
                cout << "Game starts now! Enjoy!\n";
                startGame(username, coins);
            }
            else {
                cout << "Profile not found. Returning to main menu.\n";
            }
        }
        else if (choice == 3){ // Exit
            cout << "Exiting the game. Goodbye!\n";
            gameRunning = false;
            updateUserCoins(username, coins);  // Update the user profile before exit
        }
    }

    return 0;
}
