//
// Created by AleXutzZu on 03/06/2025.
//

#ifndef WORDLADDER_MAINWINDOW_H
#define WORDLADDER_MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "../Dictionary.h"

class MainWindow : public QMainWindow {
Q_OBJECT

private:
    QAction *playAction{};
    QAction *analysisAction{};
    QAction *leaderboardAction{};
    QStackedWidget *stack{};

    const Dictionary &dictionary;

    void setUpUI();
    void setUpConnections();

public:

    MainWindow(const Dictionary &dictionary, QWidget *parent = nullptr);


};


#endif //WORDLADDER_MAINWINDOW_H
