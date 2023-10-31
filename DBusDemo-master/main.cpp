#include "mainwindow.h"
#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QProcess process;
    QString cmd = "dbus-daemon --session --print-address";
    process.start(cmd);
    process.waitForReadyRead();

    QString path = process.readAllStandardOutput().simplified();

    setenv("DBUS_SESSION_BUS_ADDRESS", path.toStdString().data(), 1);
    setenv("QT_QPA_PLATFORM", "offscreen", 1);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    process.close();

    return a.exec();
}
