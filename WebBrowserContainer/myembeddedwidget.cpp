#include "myembeddedwidget.h"

MyEmbeddedWidget::MyEmbeddedWidget(const QString &programFilePath, LPCWSTR windowName, const QStringList &args, bool autoRun, QWidget *parent)
    : QWidget(parent)
{
    m_vbox = nullptr;
    m_process = new MyEmbeddedWindowProcess(this);
    m_process->setProgramFilePath(programFilePath);
    m_process->setWindowName(windowName);
    m_process->setWidgetParent(this);
    m_process->setArguments(args);
    connect(m_process, &MyEmbeddedWindowProcess::embedded, this, &MyEmbeddedWidget::onEmbedded);
    connect(m_process, &MyEmbeddedWindowProcess::readyRead, this, &MyEmbeddedWidget::readyRead);
    if (autoRun)
        m_process->startProgram();
}

MyEmbeddedWidget::~MyEmbeddedWidget()
{
    // nothing to do here
}

void MyEmbeddedWidget::run()
{
    m_process->startProgram();
}

void MyEmbeddedWidget::onEmbedded()
{
    m_vbox = new QVBoxLayout;
    m_vbox->addWidget(m_process->embeddedWidget());
    m_vbox->setContentsMargins(0, 0, 0, 0);
    setLayout(m_vbox);
}
