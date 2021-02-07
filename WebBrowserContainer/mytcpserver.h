#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

/** server to listen to embedded window */
class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    /** constructor */
    explicit MyTcpServer(QObject *parent = nullptr);

    /** destructor */
    virtual ~MyTcpServer();

    /** sends data to embedded window */
    void sendData(const QString &data);
signals:
    /** data received from embedded window */
    void dataReceived(const QString &data);
private slots:
    /** ready to read the data from embedded window */
    void onReadyRead();
protected:
    /** connecting embedded window to this application */
    void incomingConnection(qintptr socketDescriptor) override;
private:
    QTcpSocket *m_socket; //!< socket to read and write data to embedded window
};

#endif // MYTCPSERVER_H
