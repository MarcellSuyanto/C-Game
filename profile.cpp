#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Profile structure to hold user information
struct Profile {
    string username;
    double coins;

    Profile(const string& name, double c) : username(name), coins(c) {}
};

// Vector to store profiles
vector<Profile> profiles;

// Function to create a profile
void createProfile() {
    cout << "Enter a username for your profile: ";
    string username;
    cin >> username;

    // Check if the username already exists
    for (const auto& profile : profiles) {
        if (profile.username == username) {
            cout << "Username already exists. Please choose a different username." << endl;
            return;
        }
    }

    // Create a new profile with starting coins
    profiles.emplace_back(username, 100.0);
    cout << "Profile created successfully!" << endl;
}

// Function to view profiles
void viewProfiles() {
    if (profiles.empty()) {
        cout << "No profiles available." << endl;
        return;
    }

    cout << "\nAvailable Profiles:\n";
    for (const auto& profile : profiles) {
        cout << "Username: " << profile.username << ", Coins: " << profile.coins << endl;
    }
    cout << endl;
}

// Function to delete a profile
void deleteProfile() {
    cout << "Enter the username of the profile to delete: ";
    string username;
    cin >> username;

    // Find and erase the profile
    for (auto it = profiles.begin(); it != profiles.end(); ++it) {
        if (it->username == username) {
            profiles.erase(it);
            cout << "Profile deleted successfully!" << endl;
            return;
        }
    }

    cout << "Profile not found." << endl;
}

// Main profile function to display options
void profile() {
    while (true) {
        cout << "\n------ Profile Menu ------\n";
        cout << "1. Create Profile\n";
        cout << "2. View Profiles\n";
        cout << "3. Delete Profile\n";
        cout << "4. Back to Main Menu\n";
        cout << "Select an option: ";

        int profile_option;
        cin >> profile_option;

        switch (profile_option) {
            case 1:
                createProfile();
                break;
            case 2:
                viewProfiles();
                break;
            case 3:
                deleteProfile();
                break;
            case 4:
                return; // Exit profile menu
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}
