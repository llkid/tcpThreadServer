#ifndef TCPTHREADSOCKET_H
#define TCPTHREADSOCKET_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

#include "tcpSocketInterface.h"

class TcpThreadSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpThreadSocket(qintptr socketDescriptor);
    ~TcpThreadSocket();

    void setTcpSocketInterface(TcpSocketInterface*);
    void start();
    void quit();

protected:
    QThread* mThread;
    QTcpSocket* mSocket;
    qintptr mSocketDescriptor;
    TcpSocketInterface* mTcpSocketInterface;
signals:
    void connected(TcpThreadSocket* obj);
    void disConnected(TcpThreadSocket* obj);

protected slots:
    void work();
    void _disconnected();
    void _readyRead();
};

#endif // TCPTHREADSOCKET_H
