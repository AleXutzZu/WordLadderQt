//
// Created by AleXutzZu on 04/06/2025.
//

#include "GameData.h"

GameData::GameData(const QDate &timestamp, bool won, int moves, int hints) : timestamp(timestamp), won(won),
                                                                             moves(moves), hints(hints) {}

const QDate &GameData::getTimestamp() const {
    return timestamp;
}

bool GameData::hasWon() const {
    return won;
}

int GameData::getMoves() const {
    return moves;
}

int GameData::getHints() const {
    return hints;
}

std::istream &operator>>(std::istream &in, GameData &data) {
    std::string line;
    if (!std::getline(in, line))
        return in;

    std::istringstream ss(line);
    std::string token;

    if (!std::getline(ss, token, ','))
        return in;
    QString qdateStr = QString::fromStdString(token);
    QDate timestamp = QDate::fromString(qdateStr.trimmed(), Qt::ISODate);
    if (!timestamp.isValid()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (!std::getline(ss, token, ','))
        return in;
    std::string wonStr = token;
    for (char &c: wonStr) c = std::tolower(c);
    bool won = (wonStr == "1" || wonStr == "true");

    if (!std::getline(ss, token, ','))
        return in;
    int moves = std::stoi(token);

    if (!std::getline(ss, token, ','))
        return in;
    int hints = std::stoi(token);

    data = GameData(timestamp, won, moves, hints);
    return in;
}


std::ostream &operator<<(std::ostream &out, const GameData &data) {
    // QDate to string in ISO format (yyyy-MM-dd)
    out << data.getTimestamp().toString(Qt::ISODate).toStdString() << ',';
    out << (data.hasWon() ? "true" : "false") << ',';
    out << data.getMoves() << ',';
    out << data.getHints();
    return out;
}