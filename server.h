#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QList>
#include <QDebug>
#include <QString>
#include <QDataStream>
#include <QTimer>
#include "client.h"

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = 0);
    QList<client *> cList;

    QList<client *> getCList() const;
    void setCList(const QList<client *> &value);
    QTcpSocket *conn;

private slots:
    void readData();
    void removeClient();
    void newClient();

private:
    QTcpServer s;
};

#endif // SERVER_H
