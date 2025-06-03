#include <QApplication>
#include "interface/MainWindow.h"
#include "Dictionary.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Dictionary dictionary;

    dictionary.load(":/dictionary.txt");

    MainWindow main(dictionary);
    main.setWindowTitle("Word Ladder");
    main.setMinimumSize({800, 800});
    main.show();
    return QApplication::exec();
}
