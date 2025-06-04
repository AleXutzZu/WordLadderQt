//
// Created by AleXutzZu on 04/06/2025.
//

#ifndef WORDLADDER_GAMEDATA_H
#define WORDLADDER_GAMEDATA_H

#include <QDate>

class GameData {
private:
    QDate timestamp{};
    bool won{};
    int moves{};
    int hints{};

public:
    GameData() = default;

    GameData(const QDate &timestamp, bool won, int moves, int hints);

    [[nodiscard]] const QDate &getTimestamp() const;

    [[nodiscard]] bool hasWon() const;

    [[nodiscard]] int getMoves() const;

    [[nodiscard]] int getHints() const;

    friend std::istream &operator>>(std::istream &is, GameData &data);

    friend std::ostream &operator<<(std::ostream &out, const GameData &data);
};


#endif //WORDLADDER_GAMEDATA_H
