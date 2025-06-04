//
// Created by AleXutzZu on 04/06/2025.
//

#ifndef WORDLADDER_LEADERBOARDWIDGET_H
#define WORDLADDER_LEADERBOARDWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>

class LeaderboardWidget : public QWidget {
Q_OBJECT
private:
    QLineEdit *username;
    QPushButton *searchForStats;
    QPushButton *refreshLeaderboard;

    //Stats fields
    QLabel *usernameLabel;
    QLabel *winsLabel;
    QLabel *lossesLabel;
    QLabel *wlrLabel;
    QLabel *lastGame;
//    QLabel *longestStreak;
    QWidget *statsGroup;

    void setUpUI();

    void setUpConnections();

private slots:
    void onSearchButtonClick();

public:

    explicit LeaderboardWidget(QWidget *parent = nullptr);


};


#endif //WORDLADDER_LEADERBOARDWIDGET_H
