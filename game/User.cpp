//
// Created by AleXutzZu on 04/06/2025.
//

#include "User.h"

#include <utility>
#include <fstream>
#include <filesystem>

User::User(std::string username) : username(std::move(username)) {
    load(this->username);
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
    std::filesystem::create_directories("gameData");
    std::ifstream input("gameData/" + username + ".csv");

    if (!input) {
        //No previous data, creating new...
        std::ofstream out;
        out.open("gameData/" + username + ".csv");
        out.flush();
        return;
    }

    GameData gameData;
    while (input >> gameData) {
        games.push_back(gameData);
    }
}

void User::saveGame(const GameData &gameData) {
    if (username.empty()) throw std::runtime_error("Cannot save game of non-loaded user");
    std::ofstream gameFile("gameData/" + username + ".csv", std::ios::out | std::ios::app);

    gameFile << gameData << '\n';
    games.push_back(gameData);
}

bool User::isUsernameUnknown(const std::string &username) {
    std::filesystem::path path("gameData/" + username + ".csv");
    return !std::filesystem::exists(path);
}

const std::string &User::getUsername() const {
    return username;
}
