#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
//#include <QDBusAbstractAdaptor>
#include <QMouseEvent>
#include <QTimer>

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

public Q_SLOTS:
    void Quit();
    void SetVisible(bool visible);
    void Show();
};


#endif // WINDOW_H
