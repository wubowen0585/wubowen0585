#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDBusMessage>
#include <QDBusInterface>

struct DBusImage
{
    int width;
    int height;
    QByteArray pixels;
};
Q_DECLARE_METATYPE(DBusImage)

typedef QList<DBusImage> DBusImageList;
Q_DECLARE_METATYPE(DBusImageList)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *p) override;
    void setMoniotrInterId(QString id);

public Q_SLOTS:
    void func_is_asyn(/*QString server, QString path*/);
    void func_is_call(/*QString server, QString path*/);

private:
    QTimer *m_timer;
    QDBusInterface *m_sniInter;
    QString m_server;
    QString m_path;

    DBusImageList m_list;
    QList<QImage> m_imageList;
};

#endif // MAINWINDOW_H
