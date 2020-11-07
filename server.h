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
    bool status_working()
    {
        return status;
    }
signals:
public slots:
    void newConnection();
private:
    bool status;
    QTcpServer*qtcp_serv;

};

#endif // SERVER_H
