//
// Created by AleXutzZu on 03/06/2025.
//

#include "ArrowOverlay.h"
#include <QPainter>
#include <QtMath>

ArrowOverlay::ArrowOverlay(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_AlwaysStackOnTop);
}

void ArrowOverlay::setArrows(const QVector<Arrow> &arrows) {
    arrowList = arrows;
    update();
}

void ArrowOverlay::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen(Qt::white, 2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    for (const auto &arrow : arrowList) {
        painter.setPen(pen);

        painter.drawLine(arrow.from, arrow.to);

        // Arrowhead
        QLineF line(arrow.from, arrow.to);
        double angle = std::atan2(line.dy(), line.dx());

        static const double arrowSize = 10.0;

        QPointF arrowP1 = arrow.to - QPointF(std::cos(angle + M_PI / 6) * arrowSize,
                                             std::sin(angle + M_PI / 6) * arrowSize);
        QPointF arrowP2 = arrow.to - QPointF(std::cos(angle - M_PI / 6) * arrowSize,
                                             std::sin(angle - M_PI / 6) * arrowSize);

        QPolygonF arrowHead;
        arrowHead << arrow.to << arrowP1 << arrowP2;

        painter.setBrush(Qt::white); // Fill the arrowhead
        painter.drawPolygon(arrowHead);
    }
}
