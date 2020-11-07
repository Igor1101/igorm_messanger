#include <QString>
#include <QTcpSocket>
#include <QDebug>
#include <termios.h>
#include "ConsoleReader.h"
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
    socket->connectToHost("127.0.0.1", port);
    qWarning() << QString::fromUtf8("приєднуємось...");
}

void Client::connected()
{
    qWarning() << QString::fromUtf8("приєднано до сервера");
    // setup this connection
    info_type_t info = CLIENT_INFO;
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

void Client::init()
{
    serv_connect();
    ConsoleReader *consoleReader = new ConsoleReader();
    connect (consoleReader, SIGNAL (KeyPressed(char)), this, SLOT(OnConsoleKeyPressed(char)));
    consoleReader->start();
}

void Client::OnConsoleKeyPressed(char ch)
{

}
