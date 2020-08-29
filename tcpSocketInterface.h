#ifndef TCPSOCKETINTERFACE_H
#define TCPSOCKETINTERFACE_H

#include <QTcpSocket>

class TcpSocketInterface : public QTcpSocket
{
public:
    virtual void connected(QTcpSocket& socket) = 0;
    virtual void disconnected(const QTcpSocket& socket) = 0;
    virtual void readyRead(QTcpSocket& socket) = 0;
    virtual ~TcpSocketInterface() = default;
};

#endif // TCPSOCKETINTERFACE_H
