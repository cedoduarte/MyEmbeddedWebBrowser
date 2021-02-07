#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer(parent)
{
    m_socket = nullptr;
}

MyTcpServer::~MyTcpServer()
{
    // nothing to do here
}

void MyTcpServer::sendData(const QString &data)
{
    if (m_socket)
        m_socket->write(data.toLatin1());
}

void MyTcpServer::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    emit dataReceived(QString::fromLatin1(data));
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    if (m_socket == nullptr)
    {
        m_socket = new QTcpSocket(this);
        m_socket->setSocketDescriptor(socketDescriptor);
        connect(m_socket, &QTcpSocket::readyRead, this, &MyTcpServer::onReadyRead);
    }
}
