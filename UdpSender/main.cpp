#include "networkwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkWidget w;
    w.show();

    return a.exec();
}
