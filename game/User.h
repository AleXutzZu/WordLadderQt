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

    void saveGame(const GameData &gameData);

};


#endif //WORDLADDER_USER_H
