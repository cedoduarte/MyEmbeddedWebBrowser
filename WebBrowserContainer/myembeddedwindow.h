#ifndef MYEMBEDDEDWINDOW_H
#define MYEMBEDDEDWINDOW_H

#include <windows.h>
#include <QObject>
#include <QWidget>
#include <QWindow>

/** embedded window for external programs */
class MyEmbeddedWindow : public QObject
{
    Q_OBJECT
    /* friend class */
    friend class MyEmbeddedWindowProcess;
private:
    /** constructor */
    explicit MyEmbeddedWindow(QObject *parent = nullptr);

    /** destructor */
    virtual ~MyEmbeddedWindow();

    /** grabs the external window */
    bool grab();

    /** sets the widget parent */
    void setWidgetParent(QWidget *parent);

    /** sets the external window title */
    void setName(LPCWSTR name);

    /** gets the external window title */
    LPCWSTR name() const;

    /** gets the created widget */
    QWidget *widget() const;
private:
    HWND m_id; //!< window id
    LPCWSTR m_name; //!< window title
    QWindow *m_window; //!< window
    QWidget *m_widget; //!< widget
    QWidget *m_widgetParent; //!< widget parent
};

#endif // MYEMBEDDEDWINDOW_H
