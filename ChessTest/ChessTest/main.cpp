#include "ChessTest.h"
#include <QtWidgets/QApplication>
//inspire du guide de la librairie QT sur PackTub
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessTest w;
    w.show();
    return a.exec();
}
