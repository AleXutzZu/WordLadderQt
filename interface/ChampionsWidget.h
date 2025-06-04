//
// Created by AleXutzZu on 05/06/2025.
//

#ifndef WORDLADDER_CHAMPIONSWIDGET_H
#define WORDLADDER_CHAMPIONSWIDGET_H

#include <QWidget>
#include "../game/User.h"

class ChampionsWidget : public QWidget {
Q_OBJECT
private:
    static std::vector<User> getTopThree();
public:
    explicit ChampionsWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //WORDLADDER_CHAMPIONSWIDGET_H
