//
// Created by AleXutzZu on 03/06/2025.
//

#include "MainWindow.h"
#include "AnalysisWidget.h"
#include <QToolBar>

MainWindow::MainWindow(const Dictionary &dictionary, QWidget *parent) : QMainWindow(parent), dictionary(dictionary) {
    setUpUI();
}

void MainWindow::setUpUI() {
    playAction = new QAction("Play!", this);
    analysisAction = new QAction("Analyze answers", this);
    leaderboardAction = new QAction("Top players", this);

    auto toolbar = addToolBar("Word Ladder");

    QFont toolbarFont;
    toolbarFont.setPointSize(20);
    toolbar->setFont(toolbarFont);

    toolbar->setMovable(false);
    toolbar->setFloatable(false);
    addToolBar(Qt::TopToolBarArea, toolbar);

    QWidget *spacer1 = new QWidget();
    spacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QWidget *spacer2 = new QWidget();
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    toolbar->addWidget(spacer1);
    toolbar->addAction(analysisAction);
    toolbar->addSeparator();
    toolbar->addAction(playAction);
    toolbar->addSeparator();
    toolbar->addAction(leaderboardAction);
    toolbar->addWidget(spacer2);

    stack = new QStackedWidget(this);
    stack->addWidget(new AnalysisWidget(dictionary));

    setCentralWidget(stack);
}
