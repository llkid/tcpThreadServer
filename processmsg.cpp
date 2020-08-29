#include "processmsg.h"

#include <QThread>
#include <QHostAddress>
#include <QDebug>

ProcessMsg::ProcessMsg(QObject* parent)
{
    Q_UNUSED(parent)
    socketNumber = 0;
}

void ProcessMsg::connected(QTcpSocket &socket)
{
    qDebug() << "---------------------------------";
    qDebug() << "Connected: ";
    qDebug() << "Current thread id: " << QThread::currentThreadId();
    qDebug() << socket.peerAddress();
    qDebug() << socket.peerPort();
    qDebug() << "Current link numbers: " << ++socketNumber;
}

void ProcessMsg::disconnected(const QTcpSocket &socket)
{
    qDebug() << "---------------------------------";
    qDebug() << "Disconnected: ";
    qDebug() << "Current thread id: " << QThread::currentThreadId();
    qDebug() << socket.peerAddress();
    qDebug() << socket.peerPort();
    qDebug() << "Current link numbers: " << --socketNumber;
}

void ProcessMsg::readyRead(QTcpSocket &socket)
{
    qDebug() << socket.readAll().data();
}
