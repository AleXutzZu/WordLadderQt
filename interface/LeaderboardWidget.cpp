//
// Created by AleXutzZu on 04/06/2025.
//

#include "LeaderboardWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "../game/User.h"
#include <QSpacerItem>

LeaderboardWidget::LeaderboardWidget(QWidget *parent) : QWidget(parent) {
    setUpUI();
    setUpConnections();
}

void LeaderboardWidget::setUpUI() {
    auto mainLayout = new QHBoxLayout;

    username = new QLineEdit(this);
    searchForStats = new QPushButton("Search!", this);

    auto firstHalf = new QVBoxLayout;

    auto form = new QFormLayout;
    form->addRow("Enter username:", username);
    form->addRow(searchForStats);

    firstHalf->addStretch(1);
    firstHalf->addLayout(form);

    //Setting up stat fields
    auto statsLayout = new QVBoxLayout;
    statsGroup = new QWidget(this);
    usernameLabel = new QLabel(statsGroup);
    winsLabel = new QLabel(statsGroup);
    lossesLabel = new QLabel(statsGroup);
    wlrLabel = new QLabel(statsGroup);
    lastGame = new QLabel(statsGroup);

    QFont font;
    font.setPointSize(16);

    usernameLabel->setFont(font);
    winsLabel->setFont(font);
    lossesLabel->setFont(font);
    wlrLabel->setFont(font);
    lastGame->setFont(font);
    statsLayout->addWidget(usernameLabel);
    statsLayout->addWidget(winsLabel);
    statsLayout->addWidget(lossesLabel);
    statsLayout->addWidget(wlrLabel);
    statsLayout->addWidget(lastGame);

    firstHalf->addLayout(statsLayout);
    firstHalf->addStretch(1);
    statsGroup->setVisible(false);

    mainLayout->addLayout(firstHalf, 1);

    auto leaderboardLayout = new QVBoxLayout;

    top = new ChampionsWidget(this);
    refreshLeaderboard = new QPushButton("Refresh", this);
    leaderboardLayout->addStretch(1);
    leaderboardLayout->addWidget(top, 1, Qt::AlignCenter);
    leaderboardLayout->addWidget(refreshLeaderboard, 1);
    leaderboardLayout->addStretch(1);
    mainLayout->addLayout(leaderboardLayout, 1);
    setLayout(mainLayout);
}

void LeaderboardWidget::setUpConnections() {
    connect(searchForStats, &QPushButton::clicked, this, &LeaderboardWidget::onSearchButtonClick);
}

void LeaderboardWidget::onSearchButtonClick() {
    std::string user = username->text().trimmed().toStdString();
    if (user.empty()) {
        QMessageBox::warning(this, "Invalid input", "The username field cannot be empty");
        return;
    }

    if (User::isUsernameUnknown(user)) {
        QMessageBox::warning(this, "Unknown user", "This user has not yet played anything!");
        return;
    }

    User userData(user);
    statsGroup->setVisible(true);

    usernameLabel->setText(QString("Displaying stats for user %1").arg(user));
    winsLabel->setText(QString("Total wins: %1").arg(userData.getWins()));
    lossesLabel->setText(QString("Total loses: %1").arg(userData.getLosses()));
    wlrLabel->setText(QString("Win/Lose ratio: %1").arg(userData.getWLR()));
    lastGame->setText(QString("Last game: Unknown"));
}
