#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;

// Game Class
class Game {
public:
    string username;
    int level;
    int coins;
    int coinsNeeded;

    Game()
        : username(""), level(1), coins(20), coinsNeeded(50) {
    }

    Game(const string& name)
        : username(name), level(1), coins(20), coinsNeeded(50) {
    }

    bool loadProfile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            return false;  // If file doesn't exist, return false
        }

        string line;
        while (getline(file, line)) {
            if (line.find("Username: ") == 0) {
                username = line.substr(10);  // Extract the username
            }
            else if (line.find("Level: ") == 0) {
                level = stoi(line.substr(7));  // Extract the level
            }
            else if (line.find("Coins: ") == 0) {
                coins = stoi(line.substr(7));  // Extract the coins
            }
            else if (line.find("CoinsNeeded: ") == 0) {
                coinsNeeded = stoi(line.substr(13));  // Extract the coins needed for level up
            }
        }
        file.close();
        return true;
    }

    void saveProfile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << "Username: " << username << "\n";
            file << "Level: " << level << "\n";
            file << "Coins: " << coins << "\n";
            file << "CoinsNeeded: " << coinsNeeded << "\n";
            file.close();
        }
    }

    // Simulate entering the game
    void enterGame() {
        cout << "\n--- Game Started for " << username << " ---\n";
        cout << "Level: " << level << "\n";
        cout << "Coins: " << coins << "\n";
        cout << "Coins Needed for Next Level: " << coinsNeeded << "\n";
        // Here you can add the actual game loop or gameplay code
    }
};

// Function to check if a specific profile exists
bool profileExists(const string& filename) {
    ifstream file(filename);
    return file.is_open();
}

// Function to save username to profiles list
void saveUsername(const string& username) {
    ofstream file("profiles.txt", ios::app); // Append mode
    if (file.is_open()) {
        file << username << endl;
        file.close();
    }
}

// Function to get all usernames from profiles.txt
vector<string> getAllUsernames() {
    vector<string> usernames;
    ifstream file("profiles.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                usernames.push_back(line);
            }
        }
        file.close();
    }
    return usernames;
}

// Function to check if a username already exists in profiles.txt
bool usernameExists(const string& username) {
    vector<string> usernames = getAllUsernames();
    for (const string& name : usernames) {
        if (name == username) {
            return true;
        }
    }
    return false;
}

// Function to load a specific profile
bool loadGameProfile(Game& game) {
    vector<string> usernames = getAllUsernames();
    if (usernames.empty()) {
        cout << "No profiles found.\n";
        return false;
    }

    cout << "Available profiles:\n";
    for (size_t i = 0; i < usernames.size(); ++i) {
        cout << i + 1 << ". " << usernames[i] << "\n";
    }

    int choice;
    cout << "Enter the number of the profile to load: ";
    cin >> choice;

    if (choice < 1 || choice > usernames.size()) {
        cout << "Invalid option. Returning to the main menu.\n";
        return false;
    }

    string username = usernames[choice - 1];
    string filename = username + ".txt";

    if (game.loadProfile(filename)) {
        cout << "Profile loaded successfully! Entering the game...\n";
        game.enterGame();
        return true;
    }
    else {
        cout << "Failed to load the profile. Returning to the main menu.\n";
        return false;
    }
}

// Main Menu Function
void displayMainMenu() {
    cout << "\n------ Main Menu ------\n";
    cout << "1. Start New Game\n";
    cout << "2. Load Profile\n";
    cout << "3. Exit\n";
    cout << "Select an option: ";
}
