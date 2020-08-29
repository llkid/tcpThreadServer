#include "tcpthreadsocket.h"

TcpThreadSocket::TcpThreadSocket(qintptr socketDescriptor)
    : mThread(new QThread)
    , mSocketDescriptor(socketDescriptor)
{
    this->moveToThread(mThread);
    connect(mThread, &QThread::started, this, &TcpThreadSocket::work);
}

TcpThreadSocket::~TcpThreadSocket()
{
    mThread->quit();
    mThread->wait();

    if (mSocket) {
        mSocket->close();
    }

    delete mThread, mSocket;
}

void TcpThreadSocket::setTcpSocketInterface(TcpSocketInterface * itcpSocket)
{
    mTcpSocketInterface = itcpSocket;
}

void TcpThreadSocket::start()
{
    mThread->start();
}

void TcpThreadSocket::quit()
{
    if (mSocket) {
        mSocket->close();
    }
}

void TcpThreadSocket::work()
{
    mSocket = new QTcpSocket;
    if (mSocket != nullptr) {
        qDebug() << "等待客户端连接...";
        connect(mSocket, &QTcpSocket::disconnected, this, &TcpThreadSocket::_disconnected);
        connect(mSocket, &QTcpSocket::readyRead, this, &TcpThreadSocket::_readyRead);

        if (mSocket->setSocketDescriptor(mSocketDescriptor)) {
            if (mTcpSocketInterface != nullptr) {
                mSocket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
                mTcpSocketInterface->connected(*mSocket);
            }

            emit connected(this);
            return;
        }
    }

    _disconnected();
}

void TcpThreadSocket::_disconnected()
{
    if (mTcpSocketInterface != nullptr) {
        mTcpSocketInterface->disconnected(*mSocket);
    }

    emit disConnected(this);
}

void TcpThreadSocket::_readyRead()
{
    if (mTcpSocketInterface != nullptr) {
        mTcpSocketInterface->readyRead(*mSocket);
    }
}
