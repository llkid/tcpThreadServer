#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <iostream>
#include <mutex>

#include "tcpSocketInterface.h"
#include "tcpthreadsocket.h"

// 单例模式
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    ~TcpServer();
    static TcpServer* getInstance(QObject *parent = nullptr);
    bool listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
    void setTcpSocketInterface(TcpSocketInterface*);

private:
    // 私有构造
    explicit TcpServer(QObject *parent = nullptr);
    void incomingConnection(qintptr socketDescriptor);

private:
    static TcpServer* mInstance;
//    static std::atomic<TcpServer*> mInstance;
//    static std::mutex mMutex;
    QList<TcpThreadSocket*> threadSockets;
    TcpSocketInterface* mITcpSocket;

private slots:
    void connected(TcpThreadSocket* socket);
    void disConnected(TcpThreadSocket* socket);

};

#endif // TCPSERVER_H
