#include "netreceiverdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetReceiverDialog w;
    w.show();

    return a.exec();
}
