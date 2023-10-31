#include "mainwindow.h"
#include <QDebug>
#include <QDBusArgument>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QDBusInterface interface("com.deepin.system.Power",
                             "/com/deepin/system/Power",
                             "org.freedesktop.DBus.Properties",
                             QDBusConnection::systemBus());

    QList<QVariant> outArgs = interface.call("Get", "com.deepin.system.Power", "Mode").arguments();
    if (outArgs.count() > 0) {
        QString value = outArgs.at(0).value<QDBusVariant>().variant().toString();
        qWarning() << "reply = " << value;
    }

    QDBusConnection connection = QDBusConnection::systemBus();
    connection.connect("com.deepin.system.Power",
                       "/com/deepin/system/Power",
                       "org.freedesktop.DBus.Properties",
                       "PropertiesChanged",
                       "sa{sv}as",
                       this,
                       SLOT(handlePropertiesChanged(QDBusMessage)));
}

void MainWindow::handlePropertiesChanged(QDBusMessage msg)
{
    QList<QVariant> arguments = msg.arguments();
    if (3 != arguments.count()) {
        return;
    }

    QString interfaceName = msg.arguments().at(0).toString();
    if (interfaceName == "com.deepin.system.Power") {
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        QStringList keys = changedProps.keys();
        for (int i = 0; i < keys.size(); i++) {
            // 监听窗口圆角值信号
            if (keys.at(i) == "Mode") {
                QString mode = static_cast<QString>(changedProps.value(keys.at(i)).toString());
                qInfo() << " ########### Current Mode : " << mode;
                return;
            }
        }
    }
}

MainWindow::~MainWindow()
{

}
