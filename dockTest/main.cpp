#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qInfo() << " argc : " << argc;
    QString monitorId = "";
    for (int i = 0; i < argc; i++) {
        qInfo() << " i argv : " << i << argv[i];
    }
    if (argc >= 2) {
        monitorId = argv[1];
    }
    w.setMoniotrInterId(monitorId);
    w.show();

    return a.exec();
}
