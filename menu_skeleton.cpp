#include <iostream>
#include <string>

void displayMainMenu() {
    std::cout << "\n------ Main Menu ------\n";
    std::cout << "1. Start Game\n";
    std::cout << "2. Exit\n";
    std::cout << "3. Profile???\n";
    std::cout << "4. Profiles???\n";
    std::cout << "Select an option: ";
}

// Function to start the game
void startGame(const std::string& username) {
    // Insert game logic here...
    std::cout << "Starting the game for user: " << username << std::endl;
}

// Function to display current stats
void displayCurrentStats() {
    // Logic for displaying current stats here
    std::cout << "Displaying current stats..." << std::endl;
}

// Function to manage or display profiles
void manageProfiles() {
    // Logic for managing profiles here
    std::cout << "Managing profiles..." << std::endl;
}

int main() {
    std::cout << "Enter your username: ";
    std::string username;
    std::getline(std::cin, username); // Read username
    
    while (true) {
        displayMainMenu();
        int option;
        std::cin >> option;

        switch (option) {
            case 1:
                startGame(username);  // Call function to start the game
                break;
            case 2:
                std::cout << "Game Exited. Good Bye!!!\n";
                return 0; // Exit the program
            case 3:
                displayCurrentStats(); // Display current stats
                break;
            case 4:
                manageProfiles(); // Manage or display profiles
                break;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
    }

    return 0;
}
