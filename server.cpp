#include <QObject>
#include <QTcpServer>
#include "server.h"
#include "defs.h"

msgServer::msgServer(QObject *parent) : QObject(parent)
{
    qtcp_serv = new QTcpServer(this);
    // signal
    connect(qtcp_serv, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void msgServer::init()
{
    status = qtcp_serv->listen(QHostAddress::Any, port);
    if(status) {
        QINFO << UKR("Сервер чекає на клієнтів, порт:") <<  port;
    } else {
        QCRI << UKR("Помилка запуска сервера, не може чекати клієнтів");
        QCRI << qtcp_serv->serverError() << qtcp_serv->errorString();
        exit(-1);
    }
}

void msgServer::newConnection()
{
    QINFO << UKR("нове з'єднання");
    QTcpSocket * socket = qtcp_serv->nextPendingConnection();
    socket->write("IGORS_CLIENT");
    socket->flush();
    socket->waitForBytesWritten(3000);
    socket->close();
}
