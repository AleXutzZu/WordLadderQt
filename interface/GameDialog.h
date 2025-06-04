//
// Created by AleXutzZu on 04/06/2025.
//

#ifndef WORDLADDER_GAMEDIALOG_H
#define WORDLADDER_GAMEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QListView>
#include <QListWidget>
#include "../Dictionary.h"
#include "../game/GameData.h"

class GameDialog : public QDialog {
Q_OBJECT
private:
    QLineEdit *enterWord;
    QPushButton *submitWord;
    QPushButton *getAHint;

    QPushButton *quitButton;
    QListWidget *currentState;

    std::string sourceWord;
    std::string targetWord;
    int hints = 0;
    int moves = 0;
    bool won = false;

    void setUpUI();
    void setUpConnections();

    const Dictionary &dictionary;

    void insertWord(const QString &label);
    QString getCurrentWord();
public:
    explicit GameDialog(const Dictionary &dictionary, QWidget *parent = nullptr);

    GameData getGameResult() const;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

private slots:
    void onQuitButtonClicked();

    void onSubmitButtonClicked();

    void onHintButtonClicked();
};


#endif //WORDLADDER_GAMEDIALOG_H
