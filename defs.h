#ifndef DEFS_H
#define DEFS_H
#include <QDebug>
#define PORT_NUM_DEF 19999
#define ADDR_DEFAULT "127.0.0.1"
#define UKR(STR)	QStringLiteral(STR)
#define QINFO 	qInfo().noquote()
#define QWARN 	qWarning().noquote()
#define QDEB	qDebug().noquote()
#define QERR	qError().noquote()
#define QCRI	qCritical().noquote()
#define NAME_SZ 64
enum info_type_t {
    CLIENT_INFO = 0,
    CLIENT_TRANSMISSION
};
struct client_info_t {
    char usrname[NAME_SZ];
};

// transmission
// username "broadcast" is reserved
struct client_transmission_t {
    char usrname_transfer[NAME_SZ];
};

#endif // DEFS_H
