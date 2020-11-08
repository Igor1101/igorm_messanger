#include <QCoreApplication>
#include <QtNetwork>
#include <QString>
#include <QDebug>
#include "server.h"
#include "client.h"
#include "defs.h"

void server(quint16 port)
{
    static msgServer serv;
    serv.set_port(port);
    serv.init();
}

void client(quint16 port, QString host, QString username)
{
    static Client cl;
    cl.set_port(port);
    cl.set_host(host);
    cl.set_username(username);
    cl.init();
}
int main(int argc, char *argv[])
{
    // arg1: "server" or "client"
    // arg2: username
    // arg3: port [optional]
    // arg4: host [optional]
    QString type;
    QString username;
    QString port_s;
    quint16 port = PORT_NUM_DEF;
    QString host = ADDR_DEFAULT;
    QDEB << "argc:"<< argc;
    if(argc >=  2) {
        type = QString(argv[1]);
    }
    if(argc >=  3) {
        username = QString(argv[2]);
    }
    if(argc >=  4) {
        port_s = QString(argv[3]);
	QTextStream ts(&port_s);
	ts >> port;
	QDEB << port;
    }

    if(argc >=  5) {
        host = QString(argv[4]);
    }
    // force to ignore QT command line params
    argc = 1;
    QCoreApplication a(argc, argv);
    // here select server or client
     if(type == "server") {
        server(port);
    } else if(type == "client") {
        client(port, host, username);
    } else {
        QWARN << UKR("Некоректний командний рядок");
        QWARN << UKR("коректний: ");
        QWARN << UKR("1: \"server\", \"client\"");
        QWARN << UKR("2: username");
        QWARN << UKR("3: port [optional]");
        QWARN << UKR("4: host [optional]");
        exit(-1);
    }
    return a.exec();
}
