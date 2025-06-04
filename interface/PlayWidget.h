//
// Created by AleXutzZu on 04/06/2025.
//

#ifndef WORDLADDER_PLAYWIDGET_H
#define WORDLADDER_PLAYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "../Dictionary.h"

class PlayWidget : public QWidget {
Q_OBJECT

private:
    QLineEdit *username;
    QPushButton *play;
    const Dictionary &dictionary;

    void setUpUI();
    void setUpConnections();

public:
    explicit PlayWidget(const Dictionary &dictionary, QWidget *parent = nullptr);

private slots:
    void onPlayButtonClicked();
};


#endif //WORDLADDER_PLAYWIDGET_H
