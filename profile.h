#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// Function to display the main menu
void displayMainMenu();

// Function to check if a username exists in users.txt and get the user's coins
bool usernameExists(const std::string& username, int& coins);

// Function to save a new username and coins to users.txt
void saveUsername(const std::string& username, int coins);

// Function to update the user's coins in users.txt
void updateUserCoins(const std::string& username, int coins);

#endif // PROFILE_H
