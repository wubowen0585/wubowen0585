#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QtDBus>
#include <QDBusVariant>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void handlePropertiesChanged(QDBusMessage msg);
};

#endif // MAINWINDOW_H
