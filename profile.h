#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Game Class
class Game {
public:
    string username;
    int level;
    int coins;
    int coinsNeeded;

    Game();
    Game(const string& name);

    bool loadProfile(const string& filename);
    void saveProfile(const string& filename) const;
    void enterGame();
};

// Functions to manage profiles
bool profileExists(const string& filename);
void saveUsername(const string& username);
vector<string> getAllUsernames();
bool usernameExists(const string& username);
bool loadGameProfile(Game& game);

// Main Menu Function
void displayMainMenu();

#endif // GAME_H
