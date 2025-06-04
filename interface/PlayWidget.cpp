//
// Created by AleXutzZu on 04/06/2025.
//

#include "PlayWidget.h"
#include "GameDialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "../game/User.h"

PlayWidget::PlayWidget(const Dictionary &dictionary, QWidget *parent) : QWidget(parent),
                                                                        dictionary(dictionary) {
    setUpUI();
    setUpConnections();
}

void PlayWidget::setUpUI() {
    auto horizLayout = new QHBoxLayout;
    horizLayout->addStretch(1);

    QLabel *label = new QLabel("Enter username: ", this);
    username = new QLineEdit(this);
    play = new QPushButton("Start game!", this);

    horizLayout->addWidget(label, 1);
    horizLayout->addWidget(username, 1);
    horizLayout->addWidget(play, 1);
    horizLayout->addStretch(1);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addLayout(horizLayout, 1);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void PlayWidget::setUpConnections() {
    connect(play, &QPushButton::clicked, this, &PlayWidget::onPlayButtonClicked);
}

void PlayWidget::onPlayButtonClicked() {
    QString user = username->text().trimmed();
    if (user.isEmpty()) {
        QMessageBox::warning(this, "Invalid input", "Username may not be empty");
    }

    GameDialog dialog(dictionary, this);
    dialog.exec();
    auto data = dialog.getGameResult();
    User userData(user.toStdString());
    userData.saveGame(data);
}
