#include <QString>
#include <QTcpSocket>
#include <QDebug>
#include <termios.h>
#include <ncurses.h>
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
    socket->connectToHost(host, port);
    QINFO << UKR("порт:") << port << UKR(" ,адреса:") << host << UKR(" ,приєднуємось...");
}

void Client::connected()
{
    QINFO << UKR("приєднано до сервера");
    // setup this connection+write name
    info_type_t info = CLIENT_INFO;
    QByteArray arr;
    arr += (quint8)info;
    arr += username.toLocal8Bit();
    socket->write(arr);
}

void Client::disconnected()
{
    qWarning() << QString::fromUtf8("від'єднався від сервера");
}

void Client::readyRead()
{
    // force read
    //QDEB << "READ:";
    QINFO << socket->readAll();
}

void Client::bytesWritten(qint64 bytes)
{
    //QDEB << "Written " << bytes << " bytes";
}

void Client::init()
{
    ConsoleReader *consoleReader = new ConsoleReader();
    consoleReader->start();
    serv_connect();
    connect (consoleReader, SIGNAL (KeyPressed(char)), this, SLOT(OnConsoleKeyPressed(char)));
}

void Client::OnConsoleKeyPressed(char ch)
{
    int y, x;            // to store where you are
    switch (ch) {
    case '\r':
        socket->write(data_snd.toLocal8Bit());
        data_snd = "";
        //getyx(stdscr, y, x); // save current pos
        //move(LINES-1, 0);          // move to begining of line
        //wclrtoeol(window);          // clear line
        //move(y, x);          // move back to where you were
        //QINFO << UKR("відправлено");
        //refresh();
        break;
    default:
        data_snd += QChar(ch);
        attron(COLOR_PAIR(1));
        getyx(stdscr, y, x); // save current pos
        move(y, 0);          // move back to where you were
        wprintw( window,  "%s", data_snd.toStdString().c_str());
        refresh();
        break;
    }
}
