#include "tcpserver.h"

TcpServer* TcpServer::mInstance = nullptr;

TcpServer::~TcpServer()
{
    for (auto socket : threadSockets) {
        delete socket;
    }
}

TcpServer *TcpServer::getInstance(QObject *parent)
{
    // 非线程安全, 如果是多线程并发则需要 双检查加锁并去 reorder
    if (mInstance == nullptr) {
        mInstance = new TcpServer(parent);
    }

    return mInstance;
}

bool TcpServer::listen(const QHostAddress &address, quint16 port)
{
    return this->QTcpServer::listen(address, port);
}

void TcpServer::setTcpSocketInterface(TcpSocketInterface * tcpSocketInterface)
{
    mITcpSocket = tcpSocketInterface;
}

TcpServer::TcpServer(QObject *parent)
{
    Q_UNUSED(parent)
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    TcpThreadSocket* socket = new TcpThreadSocket(socketDescriptor);
    if (socket != nullptr) {
        socket->setTcpSocketInterface(mITcpSocket);
        connect(socket, &TcpThreadSocket::connected, this, &TcpServer::connected);
        connect(socket, &TcpThreadSocket::disConnected, this, &TcpServer::disConnected);

        socket->start();
    }
}

void TcpServer::connected(TcpThreadSocket *socket)
{
    threadSockets.push_front(socket);
}

void TcpServer::disConnected(TcpThreadSocket *socket)
{
    threadSockets.removeOne(socket);
    delete socket;
}
