#include "window.h"

#include <QApplication>
#include <QDebug>

Window::Window(QWidget *parent)
    : QWidget(parent)
{

}

Window::~Window()
{

}

void Window::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setVisible(false);
    }
}

void Window::Quit()
{
    qInfo() << Q_FUNC_INFO;
    qApp->quit();
}

void Window::SetVisible(bool visible)
{
    qInfo() << Q_FUNC_INFO << visible;
    setVisible(visible);
}

void Window::Show()
{
    qInfo() << Q_FUNC_INFO;
    show();
}

