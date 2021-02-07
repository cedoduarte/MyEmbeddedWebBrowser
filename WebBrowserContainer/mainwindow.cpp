#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytcpserver.h"
#include "myembeddedwidget.h"

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_webBrowser = nullptr;
    m_server = new MyTcpServer(this);
    if (m_server->listen(QHostAddress::Any, getPort()))
        m_webBrowser = makeWebBrowser();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead(const QString &message)
{
    // reads data from tcp-client (web browser in C#)
    qDebug().noquote().nospace() << message;
}

int MainWindow::getPort() const
{
    // reads port from settings file
    QString filepath = "settings.txt";
    QFileInfo finfo(filepath);
    if (finfo.exists())
    {
        QFile F(filepath);
        if (F.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonDocument doc = QJsonDocument::fromJson(F.readAll());
            F.close();
            QJsonObject object = doc.object();
            return object["port"].toString().toInt();
        }
    }
    return -1;
}

MyEmbeddedWidget *MainWindow::makeWebBrowser()
{
    // makes web browser widget
    QStringList args { QString::number(getPort()) };
    MyEmbeddedWidget *webBrowser = new MyEmbeddedWidget("EmbeddedWebBrowser.exe", L"MyWebBrowser", args, true, this);
    connect(webBrowser, &MyEmbeddedWidget::readyRead, this, &MainWindow::onReadyRead);
    setCentralWidget(webBrowser);
    return webBrowser;
}

void MainWindow::on_actionSalir_triggered()
{
    // exits from application
    close();
}

void MainWindow::on_actionDuarteCorporation_Tutoriales_triggered()
{
    // request for web page to be showed
    m_server->sendData("https://www.youtube.com/c/duartecorporationtutoriales");
}

void MainWindow::on_actionGoogle_triggered()
{
    // request for web page to be showed
    m_server->sendData("https://www.google.com");
}

void MainWindow::on_actionFacebook_triggered()
{
    // request for web page to be showed
    m_server->sendData("https://facebook.com");
}

void MainWindow::on_actionInstagram_triggered()
{
    // request for web page to be showed
    m_server->sendData("https://www.instagram.com");
}

void MainWindow::on_actionYoutube_triggered()
{
    // request for web page to be showed
    m_server->sendData("https://www.youtube.com");
}

void MainWindow::on_actionTwitter_triggered()
{
    // request for web page to be showed
    m_server->sendData("https://www.twitter.com");
}

void MainWindow::on_actionindex_html_triggered()
{
    // request for web page to be showed
    m_server->sendData("index.html");
}
