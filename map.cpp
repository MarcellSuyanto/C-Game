// map and movement

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAP_WIDTH = 49; // Map width
const int MAP_HEIGHT = 20; // Map height

char playerSymbol = '@'; // @ represents the character. Can change

// Map representation, "1, 2, 3, 4" represents chairs to activate the mini-game.
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

// Function to initiate mini-game
void startMiniGame1() {
    cout << "You have reached a chair! The BLACKJACK is starting..." << endl;
}
void startMiniGame2() {
    cout << "You have reached a chair! The HIGHER OR LOWER is starting..." << endl;
}
void startMiniGame3() {
    cout << "You have reached a chair! The SLOTS is starting..." << endl;
}
void startMiniGame4() {
    cout << "You have reached a chair! The BACCARAT is starting..." << endl;
}


// Function to move player
void movePlayer(char direction) {
    // First find the player's current position
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
        if (playerX != -1) break; // Exit the loop once the player position is found
    }

    // Determine the new position based on the direction
    int newX = playerX;
    int newY = playerY;

    switch (direction) {
        case 'w': // Up
            newX--;
            break;
        case 's': // Down
            newX++;
            break;
        case 'a': // Left
            newY--;
            break;
        case 'd': // Right
            newY++;
            break;
        default:
            cout << "Invalid move. Use w/a/s/d." << endl;
            return;
    }

    // Check bounds of walls / map. If valid then update player position.
    if (newX >= 0 && newX < MAP_HEIGHT && newY >= 0 && newY < MAP_WIDTH) {
        // If the new position is a chair, start the mini-game
        if (gameMap[newX][newY] == '1') {
            startMiniGame1();
        }
        else if (gameMap[newX][newY] == '2') {
            startMiniGame2();
        }
        else if (gameMap[newX][newY] == '3') {
            startMiniGame3();
        }
        else if (gameMap[newX][newY] == '4') {
            startMiniGame4();
        }

        // Allow movement to empty spaces
        if (gameMap[newX][newY] == ' ' || gameMap[newX][newY] == '_') { 
            gameMap[playerX][playerY] = ' '; // Clear old position
            gameMap[newX][newY] = playerSymbol; // Set new position
        } 
        else if (gameMap[newX][newY] == '#') {
            cout << "Movement blocked by wall!" << endl;
        } // Do nothing for walls
    } 
    else {
        cout << "Movement blocked by wall or out of bounds!" << endl;
    }
}

int main() {
    char choice;

    // Display the initial map
    displayMap();

    while (true) {
        cout << "Move (w/a/s/d) or press 'q' to quit: ";
        cin >> choice;
        if (choice == 'q') break; // Exit game loop
        
        movePlayer(choice);
        displayMap(); // Display the map after each move
    }

    return 0;
}