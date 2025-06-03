//
// Created by AleXutzZu on 03/06/2025.
//

#include "AnalysisWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QLabel>
#include "ArrowOverlay.h"
#include <QApplication>

AnalysisWidget::AnalysisWidget(const Dictionary &dictionary, QWidget *parent) :
        QWidget(parent),
        dictionary(dictionary) {
    setUpUI();
    setUpConnections();
}

void AnalysisWidget::setUpUI() {
    sourceWord = new QLineEdit(this);
    targetWord = new QLineEdit(this);
    computePath = new QPushButton("See solution!", this);
    totalLength = new QLabel("Total moves: Unknown", this);
    auto fl = new QFormLayout;
    fl->addRow("Start word:", sourceWord);
    fl->addRow("Target word:", targetWord);
    fl->addRow(computePath);
    QFont labelFont;
    labelFont.setPointSize(18);
    totalLength->setFont(labelFont);

    auto hl2 = new QHBoxLayout;
    hl2->addStretch(1);
    hl2->addWidget(totalLength, 1);
    hl2->addStretch(1);
    fl->addRow(hl2);

    auto hl = new QHBoxLayout;
    hl->addStretch(1);
    hl->addLayout(fl, 1);
    hl->addStretch(1);

    auto hl1 = new QVBoxLayout;
    hl1->addLayout(hl, 1);

    gridContainer = new QWidget(this);
    path = new QGridLayout(gridContainer);
    path->setVerticalSpacing(30);
    gridContainer->setLayout(path);

    overlay = new ArrowOverlay(gridContainer);
    overlay->setAttribute(Qt::WA_TransparentForMouseEvents);
    overlay->resize(gridContainer->size());

    hl1->addWidget(gridContainer, 2);

    setLayout(hl1);

}

void AnalysisWidget::fillCells(int total, const std::vector<std::string> &labels) {

    auto findChangedPosition = [](const std::string &str1, const std::string &str2) -> int {
        for (int i = 0; i < str1.size(); ++i) {
            if (str1[i] != str2[i]) return i;
        }
        return -1;
    };

    for (int i = 0; i < total; ++i) {
        int row = i / GRID_COLUMNS;
        int col = (row % 2 == 0) ? (i % GRID_COLUMNS) : (GRID_COLUMNS - 1 - (i % GRID_COLUMNS));
        QLabel *label;
        if (i > 0 && i < total - 1) {
            int boldIndex = findChangedPosition(labels[i - 1], labels[i]);

            std::string formatted = labels[i].substr(0, boldIndex)
                                    + "<b>" + labels[i][boldIndex] + "</b>"
                                    + labels[i].substr(boldIndex + 1);
            label = new QLabel(QString::fromStdString(formatted), this);
            label->setTextFormat(Qt::RichText);
        } else {
            label = new QLabel(QString::fromStdString(labels[i]), this);
        }
        QFont labelFont;
        labelFont.setPointSize(16);
        label->setFixedSize(100, 40);
        label->setFont(labelFont);
        if (i == 0) {
            label->setStyleSheet(
                    "background: black; border: 1px solid black; color: green; font-weight: bold; text-align: center;");
        } else if (i == total - 1) {
            label->setStyleSheet(
                    "background: black; border: 1px solid black; color: red; text-align: center; font-weight: bold;");
        } else {
            label->setStyleSheet(
                    "background: black; border: 1px solid black; color: white; text-align: center;");
        }
        label->setAlignment(Qt::AlignCenter);

        path->addWidget(label, row, col);
    }
}

void AnalysisWidget::onComputePathButtonClick() {
    std::string source = sourceWord->text().trimmed().toStdString();
    std::string target = targetWord->text().trimmed().toStdString();
    if (source.empty() || target.empty()) {
        QMessageBox::warning(this, "Invalid input", "All fields are required");
        return;
    }
    std::map<std::string, unsigned int> distances;
    std::map<std::string, std::string> prev;
    try {
        auto pair = dictionary.getGraph().getDistances(source);
        distances = pair.first;
        prev = pair.second;
    } catch (std::invalid_argument &e) {
        QMessageBox::warning(this, "Invalid input", "Start word does not exist in the dictionary");
        return;
    }

    if (distances.count(target) == 0) {
        QMessageBox::warning(this, "Invalid input", "There is no way to reach the target from the current word");
        return;
    }

    int cellsToDraw = distances[target] + 1;

    std::vector<std::string> labels;

    totalLength->setText(QString("Total moves: %1").arg(cellsToDraw - 1));

    while (prev.count(target) != 0) {
        labels.push_back(target);
        target = prev[target];
    }
    labels.push_back(source);
    std::reverse(labels.begin(), labels.end());

    clearPath();
    fillCells(cellsToDraw, labels);
    gridContainer->updateGeometry();
    gridContainer->adjustSize();
    QApplication::processEvents();
    overlay->raise();
    generateArrows(cellsToDraw);
}

void AnalysisWidget::generateArrows(int total) {
    for (int i = 0; i < total - 1; ++i) {
        int row1 = i / GRID_COLUMNS;
        int col1 = (row1 % 2 == 0) ? (i % GRID_COLUMNS) : (GRID_COLUMNS - 1 - (i % GRID_COLUMNS));

        int row2 = (i + 1) / GRID_COLUMNS;
        int col2 = (row2 % 2 == 0) ? ((i + 1) % GRID_COLUMNS) : (GRID_COLUMNS - 1 - ((i + 1) % GRID_COLUMNS));

        QWidget *w1 = path->itemAtPosition(row1, col1)->widget();
        QWidget *w2 = path->itemAtPosition(row2, col2)->widget();

        QPointF fromCenter = w1->mapTo(gridContainer, w1->rect().center());
        QPointF toCenter = w2->mapTo(gridContainer, w2->rect().center());

        if (row2 == row1 + 1) {
            if (fromCenter.y() > toCenter.y()) {
                std::swap(fromCenter, toCenter);
            }
        }

        QLineF line(fromCenter, toCenter);

        const qreal margin = 35;
        line.setP1(line.pointAt(margin / line.length()));
        line.setP2(line.pointAt(1.0 - margin / line.length()));

        arrows.append({line.p1(), line.p2()});
    }
    overlay->setArrows(arrows);
}

void AnalysisWidget::setUpConnections() {
    connect(computePath, &QPushButton::clicked, this, &AnalysisWidget::onComputePathButtonClick);
}

void AnalysisWidget::clearPath() {
    while (QLayoutItem *item = path->takeAt(0)) {
        if (QWidget *w = item->widget()) {
            delete w;
        }
        delete item;
    }
    arrows.clear();
}

void AnalysisWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    if (overlay && gridContainer) {

        overlay->resize(gridContainer->size());
        overlay->update();
    }
}
