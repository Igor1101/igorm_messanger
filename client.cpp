#include <QString>
#include <QTcpSocket>
#include <QDebug>
#include "client.h"
#include "defs.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

void Client::serv_connect()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    socket->connectToHost("127.0.0.1", PORT_NUM);
    qWarning() << QString::fromUtf8("приєднуємось...");
}

void Client::connected()
{
    qWarning() << QString::fromUtf8("приєднано до сервера");
}

void Client::disconnected()
{
    qWarning() << QString::fromUtf8("від'єднався від сервера");
}

void Client::readyRead()
{
    // force read
    qDebug() << "READ:";
    qDebug() << socket->readAll();
}

void Client::bytesWritten(qint64 bytes)
{
    qDebug() << "Written " << bytes << " bytes";
}
