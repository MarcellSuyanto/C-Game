#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include <ncurses.h>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

const int MENU_WIDTH = 40;
const int CENTER_WIDTH = 60;
const int GRID_SIZE = 8;

// ----------------------------------- Class definition of game -----------------------------------
class Game {
public:
    std::string username;
    int level;
    int coins;
    int coinsNeeded; 
    int playerX, playerY; 
    int enemyX, enemyY;   
    std::vector<std::string> enemies;

    Game(const std::string& name)
        : username(name), level(1), coins(20), coinsNeeded(50), enemies{"Goblin", "Knight", "Alien", "Dark Wizard"} {
        std::srand(static_cast<unsigned int>(std::time(0))); 
        playerX = GRID_SIZE / 2; 
        playerY = GRID_SIZE / 2;
        placeEnemy(); 
    }

    void placeEnemy() {
        do {
            enemyX = std::rand() % GRID_SIZE;
            enemyY = std::rand() % GRID_SIZE;
        } while (enemyX == playerX && enemyY == playerY);
    }

    void displayGrid() {
        clear(); // Clear the screen for ncurses
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                if (i == playerX && j == playerY)
                    printw(GREEN " P " RESET); // Player position
                else if (i == enemyX && j == enemyY)
                    printw(RED " E " RESET); // Enemy position
                else
                    printw(" . "); // Empty cell
            }
            printw("\n");
        }
        refresh(); // Refresh the screen to show changes
    }
    
    void playMiniGame() {
        int enemyNumber = (std::rand() % 10) + 1; 
        int playerGuess;

        printw(CYAN "Mini-game with " BOLD "%s\n" RESET, enemies[level - 1].c_str());
        printw(CYAN "Enemy's number (for testing): %d\n", enemyNumber);

        while (true) {
            printw(MAGENTA "Guess the enemy's number between 1 and 10: " RESET);
            char guessInput[10];
            getnstr(guessInput, 9); // Read input

            try {
                playerGuess = std::stoi(guessInput); // Convert to integer
                if (playerGuess < 1 || playerGuess > 10) {
                    printw(RED "Invalid guess! Please enter a number between 1 and 10.\n" RESET);
                } else {
                    break;
                }
            } catch (std::invalid_argument&) {
                printw(RED "Invalid input! Please enter a number.\n" RESET);
            } catch (std::out_of_range&) {
                printw(RED "Input out of range! Please enter a number between 1 and 10.\n" RESET);
            }
        }

        if (playerGuess == enemyNumber) {
            printw(GREEN "You won! Coins retained.\n" RESET);
            coins += 10; 
        } else {
            printw(RED "You lost! Lost some coins.\n" RESET);
            coins -= 5; 
        }

        placeEnemy();
        printw("\n"); 
    }

    void displayStatus() {
        printw(WHITE BOLD "Player: %s | Level: %d | Coins: %d | Coins Needed: %d\n\n" RESET,
               username.c_str(), level, coins, coinsNeeded); 
    }

    void moveCharacter(char direction) {
        switch (direction) {
        case 'w': if (playerX > 0) playerX--; break;
        case 'a': if (playerY > 0) playerY--; break;
        case 's': if (playerX < GRID_SIZE - 1) playerX++; break;
        case 'd': if (playerY < GRID_SIZE - 1) playerY++; break;
        default:
            printw(RED "Invalid move.\n" RESET);
            return;
        }

        displayGrid(); 

        if (playerX == enemyX && playerY == enemyY) {
            playMiniGame();
        }
    }

    void gameLoop() {
        char choice;
        while (true) {
            displayStatus();
            displayGrid();
            printw(YELLOW "Move your character (w/a/s/d) or press 'q' to quit: " RESET);
            choice = getch(); // Use getch to get the input immediately

            if (choice == 'q') {
                printw("\n" RED "Exiting game...\n" RESET);
                break; // Exit the game loop
            }

            moveCharacter(choice);

            // Level-up condition check
            if (coins >= coinsNeeded) {
                levelUp();
                continue; // Skip the rest of the loop after leveling up
            }

            // Check for game-over condition
            if (coins <= 0) {
                printw(RED "\nYou ran out of coins! Game Over.\n" RESET);
                break;
            }
        }
    }

    void levelUp() {
        level += 1;
        coinsNeeded += 10;  
        printw(GREEN BOLD "Progressed to Level %d! Collect %d coins to continue.\n" RESET, level, coinsNeeded);

        if (level > 4) {
            printw(GREEN BOLD "Congratulations! You have completed all levels of the game!\n" RESET);
            endwin(); // End ncurses mode
            exit(0); 
        }
        printw("\n");
    }
};

// ----------------------------------- Game display menu options -----------------------------------
void displayMainMenu() {
    clear(); // Clear screen for ncurses
    printw("\n" YELLOW "------ Main Menu ------\n" RESET);
    printw(CYAN "1. Start Game\n" RESET);
    printw(CYAN "2. Exit\n" RESET);
    printw(CYAN "3. Current Stats???\n" RESET);
    printw(CYAN "4. Profiles???\n" RESET);
    printw(GREEN "\tSelect an option: " RESET);
    refresh(); // Refresh to show changes
}

int main() {
    // Initialize ncurses
    initscr();                // Start ncurses mode
    cbreak();                 // Disable line buffering
    noecho();                 // Don't echo user input
    keypad(stdscr, TRUE);    // Enable capturing function keys and arrows

    printw(MAGENTA "\tEnter your username: " RESET);

    char userInput[50];  // Declare a char array
    getnstr(userInput, 49); // Use getnstr to safely read string input
    std::string username(userInput); // Initialize std::string from char array

    while (true) {
        displayMainMenu();
        char optionInput[10]; // Temporary buffer for menu
        getnstr(optionInput, 9); // Read input for menu option

        int option;
        try {
            option = std::stoi(optionInput); // Convert to integer
            switch (option) {
            case 1: {
                Game game(username);
                game.gameLoop();
                break;
            }
            case 2:
                printw(RED "Game Exited. Good Bye!!!\n" RESET);
                goto end; // Exit loop to end program
            case 3:
                printw(YELLOW "Profiles???\n" RESET); 
                break;
            case 4:
                printw(YELLOW "Current Stats???\n" RESET);
                break;
            default:
                printw(RED "Invalid option, please try again.\n" RESET);
            }
        } catch (std::invalid_argument&) {
            printw(RED "Invalid input! Please enter a number.\n" RESET);
        } catch (std::out_of_range&) {
            printw(RED "Input out of range! Please enter a valid option.\n" RESET);
        }
    }

end:
    endwin(); // End ncurses mode before returning
    return 0;
}
