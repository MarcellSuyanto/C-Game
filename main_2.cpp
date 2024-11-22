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

// Function to display the map
void displayMap(double& coins) {
    cout << endl << "Current coins: :" << coins << endl;
    for (const auto &row : gameMap) { // print out each object of vector gamemap, which is each row (separated by commas)
        cout << row << endl;
    }
    cout << endl; // skip a line for aesthetics
}

// Function to move player
void movePlayer(char direction, const string& username, double& coins, bool& exit) {
    int playerX = -1; // initially starting at (left-most - 1) position
    int playerY = -1; // initially starting at (top-most - 1) position

    // finding the character position
    for (int i = 0; i < gameMap.size(); ++i) { // for each element (each row) of vector (gamemap) ... 
        for (int j = 0; j < gameMap[i].size(); ++j) {  // ... for each character or space from that row
            if (gameMap[i][j] == playerSymbol) { // playerSymbol = gameMap[newX][newY], which is setting the new position of player
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
    case 'W': case 'w':
        newX--; // move up
        break;
    case 'S': case 's':
        newX++; // move down
        break;
    case 'A': case 'a':
        newY--; // move left
        break;
    case 'D': case 'd':
        newY++; // move right
        break;
    default:
        cout << "Invalid move. Use W/A/S/D." << endl;
        return;
    }

    if (newX >= 0 && newX < MAP_HEIGHT && newY >= 0 && newY < MAP_WIDTH) { // if valid positon on map
        if (gameMap[newX][newY] == '1') { // if character lands on 1 on the map
            cout << "Welcome to Blackjack!" << endl;
            Blackjack(coins); // Call Blackjack game
        }
        else if (gameMap[newX][newY] == '2') {
            cout << "Welcome to Higher or Lower!" << endl;
            HighOrLow(coins); 
        }
        else if (gameMap[newX][newY] == '3') {
            Slots(coins); 
        }
        else if (gameMap[newX][newY] == '4') {
            Baccarat(coins); 
        }

        else if (gameMap[newX][newY] == 'E' || gameMap[newX][newY] == 'X' || gameMap[newX][newY] == 'I' || gameMap[newX][newY] == 'T') { // if character goes to "EXIT" on the map
            exit = true; // toggle off, exit from startGame()
            cout << "Exiting the game. Goodbye!\n";
            updateUserCoins(username, coins); // Update the user's coins
            return;
        }
        else if (gameMap[newX][newY] == ' ') {
            gameMap[playerX][playerY] = ' '; // Clear the old position
            gameMap[newX][newY] = playerSymbol; // Set the new position
        }
        else if (gameMap[newX][newY] == '#') {
            cout << "Movement blocked by wall!" << endl;
        }
    }
    else {
        cout << "Movement blocked by wall or out of bounds!" << endl;
    }
}

void startGame(const string& username, double& coins) {
    displayMap(coins); // Display the initial map
    bool exit = false; // Toggle mechanism, to force kick out only if coins < 0

    while (!exit) {
        cout << "Move (W/A/S/D): ";
        char choice;
        cin >> choice; // Get the player's move choice

        // Move the player based on the choice
        movePlayer(choice, username, coins, exit);
        // and check if the player's coins are below zero
        if (coins < 0) {
            cout << "You have run out of coins! Exiting the game.\n";
            exit = true; // Set exit to true to break the loop
            continue; // Proceed to the next iteration (which exits)
        }

        // Display the updated game map
        displayMap(coins);
    }
}

int main() {
    string username;
    double coins = 20.0; // Default coins for new users
    bool gameRunning = true;

    while (gameRunning) {
        displayMainMenu();  // Display the main menu
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: // Create New User
            cout << "Enter a new username: ";
            cin >> username;

            // Check if the username already exists
            double tempCoins;
            if (usernameExists(username, tempCoins)) {
                cout << "Username already exists! Please choose a different username.\n";
            }
            else {
                saveUsername(username, coins);
                cout << "Profile created for " << username << " with " << coins << " coins.\n";
                startGame(username, coins);
            }
            break;

        case 2: // Load Profile
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
            break;

        case 3: // Exit
            cout << "Exiting the game. Goodbye!\n";
            gameRunning = false;
            updateUserCoins(username, coins);  // Update the user profile before exit
            break;

        default:
            cout << "Invalid choice. Please select a valid option.\n";
            break;
        }
    }

    return 0;
}
