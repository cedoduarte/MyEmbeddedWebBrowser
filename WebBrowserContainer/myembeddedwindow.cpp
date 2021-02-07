#include "myembeddedwindow.h"

MyEmbeddedWindow::MyEmbeddedWindow(QObject *parent)
    : QObject(parent)
{
    m_id = nullptr;
    m_name = nullptr;
    m_window = nullptr;
    m_widget = nullptr;
    m_widgetParent = nullptr;
}

MyEmbeddedWindow::~MyEmbeddedWindow()
{
    // nothing to do here
}

void MyEmbeddedWindow::setWidgetParent(QWidget *parent)
{
    m_widgetParent = parent;
}

void MyEmbeddedWindow::setName(LPCWSTR name)
{
    m_name = name;
}

LPCWSTR MyEmbeddedWindow::name() const
{
    return m_name;
}

QWidget *MyEmbeddedWindow::widget() const
{
    return m_widget;
}

bool MyEmbeddedWindow::grab()
{
    m_id = FindWindow(nullptr, m_name);
    if (m_id)
    {
        m_window = QWindow::fromWinId(WId(m_id));
        if (m_window)
        {
            m_window->setFlags(Qt::FramelessWindowHint);
            m_widget = QWidget::createWindowContainer(m_window, m_widgetParent);
            if (m_widget)
                return true;
        }
    }
    return false;
}
