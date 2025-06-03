#include <QApplication>
#include "interface/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow main;
    main.setWindowTitle("Word Ladder");
    main.setMinimumSize({800, 640});
    main.show();
    return QApplication::exec();
}
