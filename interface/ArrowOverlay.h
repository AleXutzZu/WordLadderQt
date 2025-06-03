//
// Created by AleXutzZu on 03/06/2025.
//

#ifndef WORDLADDER_ARROWOVERLAY_H
#define WORDLADDER_ARROWOVERLAY_H

#include <QWidget>
#include <QVector>
#include <QPair>

class ArrowOverlay : public QWidget {
Q_OBJECT
public:
    struct Arrow {
        QPointF from;
        QPointF to;
    };

    explicit ArrowOverlay(QWidget *parent = nullptr);
    void setArrows(const QVector<Arrow> &arrows);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<Arrow> arrowList;
};



#endif //WORDLADDER_ARROWOVERLAY_H
