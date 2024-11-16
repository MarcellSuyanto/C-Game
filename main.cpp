#include <iostream>
#include <vector>
#include <string>

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
    " I   @                                  |       #",
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
void displayMap(double &coins) {
    cout << endl << "Current coins: " << coins << endl; // Fixed formatting
    for (const auto& row : gameMap) {
        cout << row << endl;
    }
    cout << endl;
}

// Function to move player
void movePlayer(char direction, double &coins, bool &exit) {
    int playerX = -1;
    int playerY = -1;

    for (int i = 0; i < gameMap.size(); ++i) {
        for (int j = 0; j < gameMap[i].size(); ++j) {
            if (gameMap[i][j] == playerSymbol) {
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
        case 'W': newX--; break;
        case 'S': newX++; break;
        case 'A': newY--; break;
        case 'D': newY++; break;
        default:
            cout << "Invalid move. Use W/A/S/D." << endl;
            return;
    }

    if (newX >= 0 && newX < MAP_HEIGHT && newY >= 0 && newY < MAP_WIDTH) {
        if (gameMap[newX][newY] == '1') {
            cout << "Welcome to Blackjack!" << endl;
            Blackjack(coins); // Call Blackjack game
        } 
        else if (gameMap[newX][newY] == '2') {
            cout << "Welcome to Higher or Lower!" << endl;
            HighOrLow(coins); // Call HighOrLow game
        }
        else if (gameMap[newX][newY] == '3') {
            Slots(coins); // Call Slot Machine
        } 
        else if (gameMap[newX][newY] == '4') {
            Baccarat(coins); // Call Baccarat
        }
        else if (gameMap[newX][newY] == 'E' || gameMap[newX][newY] == 'X' || gameMap[newX][newY] == 'I' || gameMap[newX][newY] == 'T') {
            cout << "\n";
            cout << "Thank you for visiting the casino1 Come back again soon!" << endl;
            exit = true; // Terminate the game
            return;
        } else if (gameMap[newX][newY] == ' ') {
            gameMap[playerX][playerY] = ' '; // Clear the old position
            gameMap[newX][newY] = playerSymbol; // Set the new position
        } else if (gameMap[newX][newY] == '#') {
            cout << "Movement blocked by wall!" << endl;
        }
    } else {
        cout << "Movement blocked by wall or out of bounds!" << endl;
    }
}

void displayMainMenu() { // need to format menu nicer
    cout << "\n------ Main Menu ------\n";
    cout << "1. Start Game\n";
    cout << "2. Profiles\n"; // Load existing profile
    cout << "3. Exit Game\n";
    cout << "\n";
    cout << "Select an option: ";
}

void startGame(const string& username, double &coins) {
    displayMap(coins);
    bool exit = false;

    while (!exit) {
        cout << "Move (w/a/s/d): ";
        char choice;
        cin >> choice;

        movePlayer(choice, coins, exit); // Move the player based on input
        displayMap(coins); // Update the display of the map
    }
}

int main() {
    double coins = 100.0; // Initial amount of coins

    while (true) {
        displayMainMenu(); // Display the main menu
        int menu_option;
        cin >> menu_option; // Get user input

        switch (menu_option) {
            case 1: {
                cout << endl << "Enter your username: ";
                string username;
                cin >> username;
                startGame(username, coins); // Start the game with the given username
                break;
            }
            case 2:
                cout << endl << "Going to profiles..." << endl;
                profile(); // Load an existing profile
                break;
            case 3:
                cout << endl << "Game Exited. Good Bye!!!\n";
                return 0; // Exit the program
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }

    return 0; // Return statement for main
}
