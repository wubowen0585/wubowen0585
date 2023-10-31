#ifndef MANAGE_H
#define MANAGE_H

#include "window.h"

#include <QtCore/QObject>

class Manage : public QObject
{
    Q_OBJECT
public:
    explicit Manage(QObject *parent = nullptr);
    ~Manage();

public Q_SLOTS:
    void Quit();
    void SetVisible(bool visible);
    void Show();

private:
    Window *m_window;
};

#endif // MANAGE_H
