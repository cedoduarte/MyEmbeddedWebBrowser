#ifndef MYEMBEDDEDWIDGET_H
#define MYEMBEDDEDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "myembeddedwindowprocess.h"

/** embedded widget for external programs */
class MyEmbeddedWidget : public QWidget
{
    Q_OBJECT
public:
    /** constructor */
    explicit MyEmbeddedWidget(const QString &programFilePath,
                              LPCWSTR windowName,
                              const QStringList &args,
                              bool autoRun = true,
                              QWidget *parent = nullptr);

    /** destructor */
    virtual ~MyEmbeddedWidget();

    /** runs the program */
    void run();
signals:
    void readyRead(const QString &message);
private slots:
    /** on embedded window */
    void onEmbedded();
private:
    QVBoxLayout *m_vbox; //!< layout
    MyEmbeddedWindowProcess *m_process; //!< process
};

#endif // MYEMBEDDEDWIDGET_H
