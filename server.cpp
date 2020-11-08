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
    int idusersocs=socket->socketDescriptor();
    clients[idusersocs]=socket;
    // append signal from this user
    connect(clients[idusersocs],SIGNAL(readyRead()),this, SLOT(readClient()));
}

void msgServer::readClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    int idusersocs=clientSocket->socketDescriptor();
    QByteArray arr = clientSocket->readAll();
    if(arr.at(0) == CLIENT_INFO) {
        // client added some data
        client_info_t* cinfo = (client_info_t*)(arr.data()+1);
        clients_names[idusersocs] = QString(cinfo->usrname);
        QINFO << UKR("прийшов користувач:") << cinfo->usrname;
        QString res = "Користувач " + clients_names[idusersocs] + " приєднався";
        foreach(int i,clients.keys()){
            clients[i]->write(res.toLocal8Bit());
        }
        return;
    }
    QString res = clients_names[idusersocs] + ": " + QString(arr);
    QINFO << res;
    QByteArray arr_form = res.toLocal8Bit();
    foreach(int i,clients.keys()){
        clients[i]->write(arr_form);
    }
}
