#ifndef PROFILE_H
#define PROFILE_H

#include <string>

bool usernameExists(const std::string& username, int& coins);
void saveUsername(const std::string& username, int coins);

#endif // PROFILE_H
