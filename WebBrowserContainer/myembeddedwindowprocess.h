#ifndef MYEMBEDDEDWINDOWPROCESS_H
#define MYEMBEDDEDWINDOWPROCESS_H

#include <QObject>
#include <QProcess>
#include "myembeddedwindow.h"

/** process to execute external windowed program */
class MyEmbeddedWindowProcess : public QObject
{
    Q_OBJECT
    /* friend class */
    friend class MyEmbeddedWidget;
private:
    /** constructor */
    explicit MyEmbeddedWindowProcess(QObject *parent = nullptr);

    /** destructor */
    virtual ~MyEmbeddedWindowProcess();

    void setArguments(const QStringList &args);

    /** starts the program */
    void startProgram();

    /** sets the widget parent */
    void setWidgetParent(QWidget *parent);

    /** sets the window title */
    void setWindowName(LPCWSTR windowName);

    /** sets the program file path */
    void setProgramFilePath(const QString &filepath);

    /** gets the embedded widget */
    QWidget *embeddedWidget() const;

    /** gets the program embedded window */
    MyEmbeddedWindow *programWindow() const;
signals:
    /** window has been embedded */
    void embedded();

    void readyRead(const QString &message);
private slots:
    /** on started the program */
    void onStarted();

    void readyReadStandardOutput();
private:
    QProcess *m_process; //!< process
    MyEmbeddedWindow *m_window; //!< embedded window
};

#endif // MYEMBEDDEDWINDOWPROCESS_H
