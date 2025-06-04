//
// Created by AleXutzZu on 04/06/2025.
//

#ifndef WORDLADDER_USER_H
#define WORDLADDER_USER_H

#include <vector>
#include "GameData.h"

class User {
private:
    std::vector<GameData> games;
    std::string username;
public:
    User() = default;

    explicit User(std::string username);

    void load(const std::string &username = "");

    [[nodiscard]] int getWins() const;

    [[nodiscard]] int getLosses() const;

    [[nodiscard]] float getWLR() const;

    std::string getLastGame() const;

    void saveGame(const GameData &gameData);

    static bool isUsernameUnknown(const std::string &username);

    const std::string &getUsername() const;
};


#endif //WORDLADDER_USER_H
