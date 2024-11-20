#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Function to check if a username exists in users.txt
bool usernameExists(const string& username, int& coins) {
    ifstream file("users.txt");
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string storedUsername;
        int storedCoins;
        ss >> storedUsername >> storedCoins;

        if (storedUsername == username) {
            coins = storedCoins;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Function to save a new username and coins to users.txt
void saveUsername(const string& username, int coins) {
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << coins << "\n";
        file.close();
    }
}

// Function to display the main menu
void displayMainMenu() {
    cout << "\n------ Main Menu ------\n";
    cout << "1. Create New User\n";
    cout << "2. Load Profile\n";
    cout << "3. Exit\n";
    cout << "Select an option: ";
}


