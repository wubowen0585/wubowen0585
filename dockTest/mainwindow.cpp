#include "mainwindow.h"
#include <QDBusInterface>
#include <QDBusPendingCallWatcher>
#include <QPixmap>
#include <QImage>
#include <QBuffer>
#include <QDBusPendingReply>
#include <QDebug>
#include <QDBusReply>
#include <QDBusMetaType>
#include <QDBusConnection>
#include <QTimer>
#include <QMutex>
#include <QPainter>


static const char* WATCHER_SERVICE = "org.kde.StatusNotifierWatcher";
static const char* WATCHER_PATH = "/StatusNotifierWatcher";
static const char* WATCHER_IFACE = "org.kde.StatusNotifierWatcher";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_sniInter(nullptr)
    , m_server("")
    , m_path("")
{
    qRegisterMetaType<DBusImage>("DBusImage");
    qRegisterMetaType<DBusImageList>("DBusImageList");
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *p)
{
    // 创建QPainter对象
    QPainter painter(this);

    for (int i = 0; i < m_imageList.count(); i++) {
        painter.drawImage(0, 0, m_imageList.at(i));
    }
}

void MainWindow::setMoniotrInterId(QString id)
{
    if (id == "") {
        id = "untitled";
    }
    qInfo() << " #### [setMoniotrInterId] monitor id : " << id;

    QDBusInterface watcherace(WATCHER_SERVICE, WATCHER_PATH, WATCHER_IFACE, QDBusConnection::sessionBus(), this);
    QStringList list = watcherace.property("RegisteredStatusNotifierItems").toStringList();
    qWarning() << " ####### list : " << list;

    for (auto server : list) {
        QStringList parts = server.split('/');
        if (parts.size() >= 2) {
            QString server = parts.at(0);
            QString path = QString("/%1").arg(parts.at(1));
            QDBusInterface sniInter(server, path, "org.kde.StatusNotifierItem", QDBusConnection::sessionBus(), this);
            QString monitorid = sniInter.property("Id").toString();
            qInfo() << " ######## server, path,id : " << server << path << monitorid;

            if (monitorid != id)
                continue;

            m_server = server;
            m_path = path;

            qInfo() << " ######### connect result : " <<
                       QDBusConnection::sessionBus().connect(m_server,
                                                             m_path,
                                                             "org.freedesktop.DBus.Properties",
                                                             "PropertiesChanged",
                                                             "sa{sv}as",
                                                             this, SLOT(onIconMapChanged(QDBusMessage)));
            m_sniInter = new QDBusInterface(m_server, m_path, "org.freedesktop.DBus.Properties", QDBusConnection::sessionBus(), this);
            m_sniInter->call("Get", "org.kde.StatusNotifierItem", "IconPixmap");

            m_timer = new QTimer;
            m_timer->start(100);
            connect(m_timer, &QTimer::timeout, this, &MainWindow::func_is_call);
        }
    }
}

// 异步
void MainWindow::func_is_asyn(/*QString server, QString path*/)
{
    qInfo() << " parts : " << m_server << m_path << m_sniInter;
    if (m_server == "" || m_path == "" || !m_sniInter)
        return;

    QDBusPendingCall reply = m_sniInter->asyncCall("Get", "org.kde.StatusNotifierItem", "IconPixmap");
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(reply);

    DBusImageList iconDataLists;
    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, [&] (QDBusPendingCallWatcher* call) {
        watcher->deleteLater();
        iconDataLists.clear();
        if (call->isError()) {
            qWarning() << " failed, error:" << call->error().message();
            return iconDataLists;
        }

        QList<QVariant> outArgs = reply.reply().arguments();

        if (outArgs.count() <= 0) {
            return iconDataLists;
        }
        QVariant first = outArgs.at(0).value<QDBusVariant>().variant();
        const QDBusArgument &dbusArgs = first.value<QDBusArgument>();

        dbusArgs.beginArray();
        while (!dbusArgs.atEnd()) {
            DBusImage icon;
            dbusArgs.beginStructure();
            dbusArgs >> icon.height >> icon.width >> icon.pixels;
            dbusArgs.endStructure();
            iconDataLists.append(icon);

            qWarning() << " $$$$$$$$$$ pixels : " << icon.width << icon.height << icon.pixels;
            //            m_trayIcon->setIcon(QIcon(icon.pixels));
        }
        dbusArgs.endArray();

        return iconDataLists;
    });
}

// 同步
void MainWindow::func_is_call()
{
    qInfo() << " parts : " << m_server << m_path << m_sniInter;

    QByteArray pixels;
    QDBusMessage reply = m_sniInter->call("Get", "org.kde.StatusNotifierItem", "IconPixmap");

    if (reply.type() == QDBusMessage::ReplyMessage) {
        QList<QVariant> outArgs = reply.arguments();
        if (outArgs.count() <= 0) {
            return;
        }
        QVariant first = outArgs.at(0).value<QDBusVariant>().variant();
        const QDBusArgument &dbusArgs = first.value<QDBusArgument>();

        m_list.clear();
        m_imageList.clear();
        dbusArgs.beginArray();
        while (!dbusArgs.atEnd()) {
            DBusImage icon;
            dbusArgs.beginStructure();
            dbusArgs >> icon.height >> icon.width >> icon.pixels;
            dbusArgs.endStructure();
            m_list.append(icon);
            pixels = icon.pixels;
        }
        dbusArgs.endArray();

        if (m_list.count() <= 0)
            return;

        for (int k = 0; k < m_list.count(); k++) {
            QByteArray converted;
            for (auto i = m_list.at(k).pixels.begin(); i !=  m_list.at(k).pixels.end() ; i += 4) {
                QByteArray seq;
                for (auto j = i; j != i+4; ++j) {
                    seq += *j;
                }
                QByteArray revSeq(seq.size(), 0);
                std::copy(seq.crbegin(), seq.crend(), revSeq.begin());
                converted += revSeq;
            }
            auto img = QImage((const uchar *)converted.constData(),
                              m_list.at(k).width,
                              m_list.at(k).height,
                              QImage::Format_ARGB32);

            m_imageList.append(img);
            update();
            qInfo() << " ###### k image : " << k << img.width() << img.height();
        }
    } else {
        qWarning() << "no iconpixmap.";
    }
}
