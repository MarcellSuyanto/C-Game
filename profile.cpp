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

// Main Function
int main() {
    string username;
    int coins = 20; // Default coins for new users
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
            int tempCoins;
            if (usernameExists(username, tempCoins)) {
                cout << "Username already exists! Please choose a different username.\n";
            }
            else {
                saveUsername(username, coins);
                cout << "Profile created for " << username << " with " << coins << " coins.\n";
            }
            break;

        case 2: // Load Profile
            cout << "Enter your username to load the profile: ";
            cin >> username;

            // Check if the username exists
            if (usernameExists(username, coins)) {
                cout << "Profile loaded for " << username << ". You have " << coins << " coins.\n";
                cout << "Game starts now! Enjoy!\n";
            }
            else {
                cout << "Profile not found. Returning to main menu.\n";
            }
            break;

        case 3: // Exit
            cout << "Exiting the game. Goodbye!\n";
            gameRunning = false;
            break;

        default:
            cout << "Invalid choice. Please select a valid option.\n";
            break;
        }
    }

    return 0;
}
