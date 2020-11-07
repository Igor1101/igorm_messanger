#include <QCoreApplication>
#include <QtNetwork>
#include <QString>
#include <QDebug>
#include "server.h"
#include "client.h"
using namespace std;
void server()
{
    static msgServer serv;
}

void client()
{
    static Client cl;
    cl.serv_connect();
}
int main(int argc, char *argv[])
{
    QString type;
    if(argc >=  2) {
        type = QString(argv[1]);
    }
    argc = 1;
    QCoreApplication a(argc, argv);
    // here select server or client
     if(type == "server") {
        server();
    } else if(type == "client") {
        client();
    } else {
        qWarning() << QString::fromUtf8("Некоректний командний рядок");
        server();
    }
    return a.exec();
}
