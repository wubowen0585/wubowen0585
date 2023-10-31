#include <QApplication>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDebug>

#include "adaptors/BlackScreenInterfaceAdaptor.h"
#include "manage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Manage m;
    BlackScreenInterface *recovery = new BlackScreenInterface(&m);
    if (QDBusConnection::sessionBus().registerService("com.deepin.dde.BlackScreen"))
        QDBusConnection::sessionBus().registerObject("/com/deepin/dde/BlackScreen", "com.deepin.dde.BlackScreen", recovery, QDBusConnection::ExportAllSlots);

    return app.exec();
}

