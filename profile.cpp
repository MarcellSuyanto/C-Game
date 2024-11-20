#include "profile.h"
#include <fstream>
#include <sstream>

using namespace std;
void displayMainMenu() {
    cout << "\n------ Main Menu ------\n";
    cout << "1. Create New User\n";
    cout << "2. Load Profile\n";
    cout << "3. Exit\n";
    cout << "Select an option: ";
}

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

void updateUserCoins(const string& username, int coins) {
    vector<string> lines;
    ifstream infile("users.txt");
    string line;
    bool userFound = false;

    // Read file content
    while (getline(infile, line)) {
        // If the user is found, update their coin value
        if (line.find(username + " ") == 0) {
            line = username + " " + to_string(coins); // Update coins
            userFound = true;
        }
        lines.push_back(line);
    }
    infile.close();

    // If the user was not found, you can choose to add them or handle the error
    if (!userFound) {
        lines.push_back(username + " " + to_string(coins)); // Add new user
    }

    // Write the updated content back to the file
    ofstream outfile("users.txt");
    for (const auto& l : lines) {
        outfile << l << "\n";
    }
    outfile.close();
}
