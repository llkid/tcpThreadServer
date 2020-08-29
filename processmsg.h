#ifndef PROCESSMSG_H
#define PROCESSMSG_H

#include <QObject>
#include "tcpSocketInterface.h"

class ProcessMsg : public TcpSocketInterface
{
public:
    ProcessMsg(QObject* parent = nullptr);

protected:
    void connected(QTcpSocket& socket) override;
    void disconnected(const QTcpSocket& socket) override;
    void readyRead(QTcpSocket& socket) override;

private:
    int socketNumber;
};

#endif // PROCESSMSG_H
