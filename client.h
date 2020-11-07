#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include "ConsoleReader.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void serv_connect();

signals:
    // signals
public slots:
    void set_port(quint16 port)
    {
        this->port = port;
    }
    void init();
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void OnConsoleKeyPressed(char ch);
private:
    QString data_snd;
    quint16 port;
    QTcpSocket *socket;
};

#endif // CLIENT_H
