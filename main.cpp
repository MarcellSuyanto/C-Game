#include <iostream>
#include <vector>
#include <string>

#include "playingcards.h"
#include "blackjack.h"
#include "HighOrLow.h"
#include "slotmachine.h"
#include "Baccarat.h"

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
void displayMap() {
    for (const auto& row : gameMap) {
        cout << row << endl;
    }
    cout << endl;
}

// Function to move player
void movePlayer(char direction, double &coins) {
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
        case 'w': newX--; break;
        case 's': newX++; break;
        case 'a': newY--; break;
        case 'd': newY++; break;
        default:
            cout << "Invalid move. Use w/a/s/d." << endl;
            return;
    }

    if (newX >= 0 && newX < MAP_HEIGHT && newY >= 0 && newY < MAP_WIDTH) {
        if (gameMap[newX][newY] == '1') {
            Blackjack(coins); // Call Blackjack game
        } 
        else if (gameMap[newX][newY] == '2') {
            HighOrLow(coins); // Call HighOrLow game
        }else if (gameMap[newX][newY] == '3') {
            Slots(coins); // Call Slot Machine
        } 
        else if (gameMap[newX][newY] == '4') {
            Baccarat(coins); // Call Baccarat
        }

        else if (gameMap[newX][newY] == ' ') {
            gameMap[playerX][playerY] = ' '; // Clear the old position
            gameMap[newX][newY] = playerSymbol; // Set the new position
        } else if (gameMap[newX][newY] == '#') {
            cout << "Movement blocked by wall!" << endl;
        }
    } else {
        cout << "Movement blocked by wall or out of bounds!" << endl;
    }
}

void displayMainMenu() {
    cout << "\n------ Main Menu ------\n";
    cout << "1. Start Game\n";
    cout << "2. Exit Game\n";
    cout << "3. Profile\n";
    cout << "4. Manage Profiles\n";
    cout << "Select an option: ";
}

void startGame(const string& username, double &coins) {
    displayMap();

    while (true) {
        cout << "Move (w/a/s/d) or press 'q' to quit: ";
        char choice;
        cin >> choice;

        if (choice == 'q') break;

        movePlayer(choice, coins);
        displayMap();
    }
}

int main() {
    cout << "Enter your username: ";
    string username;
    getline(cin, username);

    double coins = 100.0; // Initial amount of coins

    while (true) {
        displayMainMenu();
        int option;
        cin >> option;

        switch (option) {
            case 1:
                startGame(username, coins); // Start the game
                break;
            case 2:
                cout << "Game Exited. Good Bye!!!\n";
                return 0; // Exit the program
            case 3:
                cout << "Displaying Profiles...\n"; // Implement stats display if needed
                break;
            case 4:
                cout << "Managing profiles...\n"; // Implement profile management if needed
                break;
            default:
                cout << "Invalid option, please try again.\n";
        }
    }

    return 0;
}
