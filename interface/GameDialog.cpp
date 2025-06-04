//
// Created by AleXutzZu on 04/06/2025.
//

#include <QMessageBox>
#include <QFuture>
#include "GameDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QKeyEvent>

void GameDialog::setUpUI() {
    setWindowTitle("Reach " + QString::fromStdString(targetWord));

    enterWord = new QLineEdit(this);
    auto inputForm = new QFormLayout;
    inputForm->addRow("Enter a word", enterWord);

    auto mainLayout = new QVBoxLayout;

    mainLayout->addLayout(inputForm);

    auto buttonsLayout = new QHBoxLayout;

    submitWord = new QPushButton("Submit", this);
    submitWord->setDefault(true);
    getAHint = new QPushButton("Hint?", this);
    quitButton = new QPushButton("Quit game", this);

    buttonsLayout->addWidget(submitWord);
    buttonsLayout->addWidget(getAHint);
    buttonsLayout->addWidget(quitButton);

    mainLayout->addLayout(buttonsLayout);

    currentState = new QListWidget(this);

    QFont font;
    font.setPointSize(18);
    currentState->setFont(font);

    insertWord(QString::fromStdString(sourceWord));

    mainLayout->addWidget(currentState);
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
    connect(getAHint, &QPushButton::clicked, this, &GameDialog::onHintButtonClicked);
}

void GameDialog::onSubmitButtonClicked() {
    QString input = enterWord->text().trimmed();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Invalid input", "You must enter a valid word");
        return;
    }

    //get dictionary
    auto validMoves = dictionary.getGraph().getAdjacencyList(getCurrentWord().toStdString());
    if (!validMoves.count(input.toStdString())) {
        QMessageBox::warning(this, "Invalid input", "This is not a valid move");
        return;
    }
    moves++;
    insertWord(input);
    enterWord->clear();
    if (input == targetWord) {
        won = true;
        QMessageBox::information(this, "Congratulations!",
                                 QString("You won the game in %1 moves using %2 hints").arg(moves).arg(hints));
        disconnect(submitWord, &QPushButton::clicked, this, &GameDialog::onSubmitButtonClicked);
        disconnect(getAHint, &QPushButton::clicked, this, &GameDialog::onHintButtonClicked);
    }
}

GameDialog::GameDialog(const Dictionary &dictionary, QWidget *parent) : QDialog(parent),
                                                                        dictionary(dictionary) {

    //TODO pick 2 random words
    sourceWord = "accept";
    targetWord = "accuse";
    setUpUI();
    setUpConnections();
}

void GameDialog::onHintButtonClicked() {
    hints++;
    auto currentWord = getCurrentWord();
    auto [distances, prev] = dictionary.getGraph().getDistances(currentWord.toStdString());
    std::vector<std::string> bestPath;
    std::string word = targetWord;
    while (prev.count(word) != 0) {
        bestPath.push_back(word);
        word = prev[word];
    }

    enterWord->setText(QString::fromStdString(bestPath.back()));
}

void GameDialog::insertWord(const QString &label) {
    QListWidgetItem *item = new QListWidgetItem(label);
    item->setTextAlignment(Qt::AlignCenter);
    currentState->addItem(item);
}

QString GameDialog::getCurrentWord() {
    QListWidgetItem *lastItem = currentState->item(currentState->count() - 1);
    return lastItem->text();
}

void GameDialog::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (quitButton) {
            quitButton->click();
        }
    } else {
        QDialog::keyPressEvent(event);
    }
}

void GameDialog::closeEvent(QCloseEvent *event) {
    quitButton->click();
    event->ignore();
}
