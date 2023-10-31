#include "manage.h"

Manage::Manage(QObject *parent)
    : QObject(parent)
    , m_window(new Window)
{

}

Manage::~Manage()
{
    if (m_window) {
        m_window->deleteLater();
    }
}

void Manage::Quit()
{
    if (!m_window)
        return;
    m_window->Quit();
}

void Manage::SetVisible(bool visible)
{
    if (!m_window)
        return;
    m_window->SetVisible(visible);
}

void Manage::Show()
{
    if (!m_window)
        return;
    m_window->Show();
}
