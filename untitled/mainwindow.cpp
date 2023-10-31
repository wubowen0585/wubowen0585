#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 480);
//    move(400, 300);
    QMap<int, QWidget *>mapss;
    for (int i = 0; i < 10; i++) {
        QWidget *w = new QWidget;
        mapss.insert(i, w);
    }
    qWarning() << " >>>>>>>>. " << mapss.keys().length();

    QMap<int, QWidget *>::iterator itTray = mapss.end();
    while (itTray != mapss.begin()) {
        --itTray;
       QWidget *ptr = itTray.value();
       delete ptr;
       itTray = mapss.erase(itTray);

       qWarning() << " ####### " << mapss.keys().length();
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    qInfo() << Q_FUNC_INFO << " release e->button() : " << e->button();
}

void MainWindow::moveEvent(QMoveEvent *e)
{
    qInfo() << Q_FUNC_INFO << " e->pos() : " << e->pos();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    qInfo() << Q_FUNC_INFO << " press e->button() : " << e->button();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    qInfo() << Q_FUNC_INFO << " move e->button() : " << e->button();
}
