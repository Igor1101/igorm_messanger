#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class msgServer : public QObject
{
    Q_OBJECT
public:
    explicit msgServer(QObject *parent = nullptr);
    void init();
    bool status_working()
    {
        return status;
    }
signals:
public slots:
    void newConnection();
    void set_port(quint16 port)
    {
        this->port = port;
    }
private:
    quint16 port ;
    bool status;
    QTcpServer*qtcp_serv;

};

#endif // SERVER_H
