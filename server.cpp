#include <QObject>
#include <QtDebug>
#include <QTcpServer>
#include "server.h"
#include "defs.h"

msgServer::msgServer(QObject *parent) : QObject(parent)
{
    qtcp_serv = new QTcpServer(this);
    // signal
    connect(qtcp_serv, SIGNAL(newConnection()), this, SLOT(newConnection()));
    status = qtcp_serv->listen(QHostAddress::Any, PORT_NUM);
    if(status) {
        qWarning() << QString::fromUtf8("Сервер чекає на клієнтів, порт:") <<  PORT_NUM;
    } else {
        qWarning() << QString::fromUtf8("Помилка запуска сервера, не може чекати клієнтів");
    }
    qWarning() << qtcp_serv->serverError() << qtcp_serv->errorString();
}

void msgServer::newConnection()
{
    qWarning() << QString::fromUtf8("нове з'єднання");
    QTcpSocket * socket = qtcp_serv->nextPendingConnection();
    socket->write("IGORS_CLIENT");
    socket->flush();
    socket->waitForBytesWritten(3000);

    socket->close();
}
