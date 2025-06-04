//
// Created by AleXutzZu on 04/06/2025.
//

#include "User.h"

#include <utility>
#include <fstream>

User::User(std::string username) : username(std::move(username)) {
    load();
}

int User::getWins() const {
    return std::accumulate(games.begin(), games.end(), 0, [](int value, const auto &gameData) {
        return value + gameData.hasWon();
    });
}

int User::getLosses() const {
    return std::accumulate(games.begin(), games.end(), 0, [](int value, const auto &gameData) {
        return value + !gameData.hasWon();
    });
}

float User::getWLR() const {
    float wins = getWins();
    float losses = getLosses();
    if (losses == 0) return INFINITY;
    return wins / getLosses();
}

void User::load(const std::string &username) {
    this->username = username;
    std::ifstream input("gameData/" + username + ".csv");
    if (!input) throw std::runtime_error("Could not open file");

    GameData gameData;
    while (input >> gameData) {
        games.push_back(std::move(gameData));
    }
}

void User::saveGame(const GameData &gameData) {
    if (username.empty()) throw std::runtime_error("Cannot save game of non-loaded user");
    std::ofstream gameFile("gameData/" + username + ".csv", std::ios::out | std::ios::ate);

    gameFile << gameData << '\n';
    games.push_back(gameData);
}
