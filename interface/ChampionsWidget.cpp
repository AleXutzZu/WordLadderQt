//
// Created by AleXutzZu on 05/06/2025.
//

#include "ChampionsWidget.h"
#include <QPainter>
#include <filesystem>
#include "../game/User.h"
#include <algorithm>

ChampionsWidget::ChampionsWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 250);
}

void ChampionsWidget::paintEvent(QPaintEvent *event) {
    auto names = getTopThree();
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Define sizes
    int pedestalWidth = 100;
    int spacing = 30;

    int bronzeHeight = 100;
    int silverHeight = 140;
    int goldHeight = 180;

    int totalWidth = pedestalWidth * 3 + spacing * 2;
    int startX = (width() - totalWidth) / 2;
    int bottom = height() - 20;

    // X positions relative to startX
    int bronzeX = startX;
    int goldX = startX + pedestalWidth + spacing;
    int silverX = startX + 2 * (pedestalWidth + spacing);

    // Draw Gold pedestal
    painter.setBrush(QColor(255, 215, 0)); // Gold
    painter.drawRect(goldX, bottom - goldHeight, pedestalWidth, goldHeight);

    // Draw Silver pedestal
    painter.setBrush(QColor(192, 192, 192)); // Silver
    painter.drawRect(silverX, bottom - silverHeight, pedestalWidth, silverHeight);

    // Draw Bronze pedestal
    painter.setBrush(QColor(205, 127, 50)); // Bronze
    painter.drawRect(bronzeX, bottom - bronzeHeight, pedestalWidth, bronzeHeight);

    // Draw labels
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    QFontMetrics fm(font);

    std::vector<QString> texts;
    for (const auto &name: names) {
        texts.push_back(QString::fromStdString(name));
    }

    while (texts.size() < 3) {
        texts.emplace_back("N/A");
    }

    painter.setPen(Qt::white);
    painter.drawText(bronzeX + (pedestalWidth - fm.horizontalAdvance(texts[2])) / 2,
                     bottom - bronzeHeight - 10, texts[2]);

    painter.drawText(goldX + (pedestalWidth - fm.horizontalAdvance(texts[0])) / 2,
                     bottom - goldHeight - 10, texts[0]);

    painter.drawText(silverX + (pedestalWidth - fm.horizontalAdvance(texts[1])) / 2,
                     bottom - silverHeight - 10, texts[1]);
}

std::vector<std::string> ChampionsWidget::getTopThree() {
    std::vector<User> users;
    try {
        for (const auto &entry: std::filesystem::directory_iterator("gameData")) {
            if (entry.is_regular_file()) {
                const auto &path = entry.path();
                User user(path.stem().string());
                users.push_back(user);
            }
        }
        std::sort(users.begin(), users.end(), [](const User &lhs, const User &rhs) {
            return lhs.getWins() > rhs.getWins();
        });
        std::vector<std::string> answer;

        for (int i = 0; i < std::min<int>(3, users.size()); ++i) {
            answer.push_back(users[i].getUsername());
        }
        return answer;

    } catch (const std::filesystem::filesystem_error &e) {
        return {};
    }
}
