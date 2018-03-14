#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QObject>
#include <QRegExp>
#include <QBuffer>

class client : public QObject
{
    Q_OBJECT
public:
    client(QTcpSocket *conn, QObject *parent = 0);
    QTcpSocket *conn;
private slots:
    void clientDisconnected();
    void gotMessage();
signals:
    void disconnected();
};

#endif // CLIENT_H
