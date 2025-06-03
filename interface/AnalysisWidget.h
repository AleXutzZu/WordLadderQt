//
// Created by AleXutzZu on 03/06/2025.
//

#ifndef WORDLADDER_ANALYSISWIDGET_H
#define WORDLADDER_ANALYSISWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "../Dictionary.h"
#include "ArrowOverlay.h"

class AnalysisWidget : public QWidget {
Q_OBJECT
private:
    const Dictionary &dictionary;
    QLineEdit *sourceWord{};
    QLineEdit *targetWord{};
    QPushButton *computePath{};
    QGridLayout *path{};
    ArrowOverlay *overlay{};
    QWidget *gridContainer{};
    QLabel *totalLength{};
    const int GRID_COLUMNS = 3;
    QVector<ArrowOverlay::Arrow> arrows;

    void setUpUI();

    void setUpConnections();

    void clearPath();

protected:
    void generateArrows(int total);
    void resizeEvent(QResizeEvent *event) override;

public:
    explicit AnalysisWidget(const Dictionary &dictionary, QWidget *parent = nullptr);

private slots:

    void onComputePathButtonClick();

    void fillCells(int total, const std::vector<std::string> &labels);
};


#endif //WORDLADDER_ANALYSISWIDGET_H
