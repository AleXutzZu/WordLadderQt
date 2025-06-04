//
// Created by AleXutzZu on 05/06/2025.
//

#include "ChampionsWidget.h"
#include <QPainter>
#include <filesystem>
#include <algorithm>

ChampionsWidget::ChampionsWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 300);
}

void ChampionsWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw "Champions" text at the top center in big font
    QFont titleFont("Arial", 24, QFont::Bold);
    painter.setFont(titleFont);
    QString title = "Champions";
    QFontMetrics fmTitle(titleFont);
    int titleWidth = fmTitle.horizontalAdvance(title);
    painter.drawText((width() - titleWidth) / 2, 40, title);

    std::vector<QString> labels;
    std::vector<QString> wins;

    auto users = getTopThree();
    for (const auto &user: users) {
        labels.push_back(QString::fromStdString(user.getUsername()));
        wins.push_back(QString::number(user.getWins()));
    }

    while (labels.size() != 3) {
        labels.emplace_back("N/A");
        wins.emplace_back("0");
    }
    std::swap(wins[0], wins[1]);
    std::swap(wins[0], wins[2]);
    std::swap(labels[0], labels[1]);
    std::swap(labels[0], labels[2]);

    QFont labelFont("Arial", 12, QFont::Bold);
    painter.setFont(labelFont);
    QFontMetrics fmLabel(labelFont);

    // Pedestal dimensions and spacing
    int pedestalWidth = 100;
    int pedestalHeights[3] = {100, 160, 120};
    QColor pedestalColors[3] = {QColor(205, 127, 50), QColor(255, 215, 0),
                                QColor(192, 192, 192),};
    int spacing = 40;

    // Total width of all pedestals + spacing
    int totalWidth = pedestalWidth * 3 + spacing * 2;
    int startX = (width() - totalWidth) / 2;
    int baseY = 280;  // baseline for pedestals

    // Draw each pedestal with labels
    for (int i = 0; i < 3; ++i) {
        int x = startX + i * (pedestalWidth + spacing);
        int height = pedestalHeights[i];
        int y = baseY - height;

        // Draw label above pedestal
        QString label = labels[i];
        int labelWidth = fmLabel.horizontalAdvance(label);
        int labelX = x + (pedestalWidth - labelWidth) / 2;
        int labelY = y - 15;  // 15 px above pedestal
        painter.setPen(Qt::white);
        painter.drawText(labelX, labelY, label);


        // Draw pedestal rectangle
        painter.setBrush(pedestalColors[i]);
        painter.setPen(Qt::black);
        painter.drawRect(x, y, pedestalWidth, height);

        QFont pedestalFont("Arial", 14, QFont::Bold);
        painter.setFont(pedestalFont);
        QFontMetrics fmPedestal(pedestalFont);

        int numberWidth = fmPedestal.horizontalAdvance(wins[i]);
        painter.setPen(Qt::black);
        painter.drawText(x + (pedestalWidth - numberWidth) / 2, y + 30, wins[i]);

        // Draw "Wins" below number, also centered
        QString winsStr = "Wins";
        int winsWidth = fmPedestal.horizontalAdvance(winsStr);
        painter.drawText(x + (pedestalWidth - winsWidth) / 2, y + 55, winsStr);
    }
}


std::vector<User> ChampionsWidget::getTopThree() {
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
            if (lhs.getWins() == rhs.getWins()) {
                return lhs.getWLR() > rhs.getWLR();
            }
            return lhs.getWins() > rhs.getWins();
        });
        std::vector<User> answer;

        for (int i = 0; i < std::min<int>(3, users.size()); ++i) {
            answer.push_back(users[i]);
        }
        return answer;

    } catch (const std::filesystem::filesystem_error &e) {
        return {};
    }
}
