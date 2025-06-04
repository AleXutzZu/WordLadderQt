//
// Created by AleXutzZu on 04/06/2025.
//

#include <QMessageBox>
#include <QFuture>
#include "GameDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

void GameDialog::setUpUI() {
    setWindowTitle("Reach " + QString::fromStdString(targetWord));

    enterWord = new QLineEdit(this);
    auto inputForm = new QFormLayout;
    inputForm->addRow("Enter a word", enterWord);

    auto mainLayout = new QVBoxLayout;

    mainLayout->addLayout(inputForm);

    auto buttonsLayout = new QHBoxLayout;

    submitWord = new QPushButton("Submit", this);
    getAHint = new QPushButton("Hint?", this);
    quitButton = new QPushButton("Quit game", this);

    buttonsLayout->addWidget(submitWord);
    buttonsLayout->addWidget(getAHint);
    buttonsLayout->addWidget(quitButton);

    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
}

void GameDialog::onQuitButtonClicked() {
    if (!won) {
        QMessageBox warningBox;
        warningBox.setWindowTitle("About to quit...");
        warningBox.setText(
                "You have not yet won the game - quitting now will result in a loss. Do you want to proceed?");

        QPushButton *confirmQuit = warningBox.addButton("Quit", QMessageBox::AcceptRole);
        QPushButton *keepGoing = warningBox.addButton("Keep playing", QMessageBox::RejectRole);

        warningBox.exec();

        if (warningBox.clickedButton() == confirmQuit) {
            this->accept();
        }
    } else {
        this->accept();
    }
}

void GameDialog::setUpConnections() {
    connect(quitButton, &QPushButton::clicked, this, &GameDialog::onQuitButtonClicked);
    connect(submitWord, &QPushButton::clicked, this, &GameDialog::onSubmitButtonClicked);
}

void GameDialog::onSubmitButtonClicked() {
    QString input = enterWord->text().trimmed();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Invalid input", "You must enter a valid word");
        return;
    }

    //get dictionary
//    auto validMoves = dictionary.getGraph().getAdjacencyList();
}

GameDialog::GameDialog(const Dictionary &dictionary, QWidget *parent) : QDialog(parent),
                                                                        dictionary(dictionary) {
    setUpUI();
    setUpConnections();
}
