#include "server.h"

server::server(QObject *parent) :
    QObject(parent)
{
    if(!s.listen(QHostAddress(address), port))
    {
        QTextStream(stdout) << "Server could not start" << endl;
    }
    else
    {
        QTextStream(stdout) << "Server started" << endl;
        QTextStream(stdout) << "Server address: " << s.serverAddress().toString() << endl;
        QTextStream(stdout) << "Server port: " << s.serverPort() << endl;
    }
    connect(&s, &QTcpServer::newConnection, this, &server::newClient);
}

QList<client *> server::getCList() const
{
    return cList;
}

void server::setCList(const QList<client *> &value)
{
    cList = value;
}

void server::newClient()
{
    QTcpSocket *newclient = s.nextPendingConnection();
    QTextStream(stdout) << "Nove spojeni" << endl;
    QTextStream(stdout) << "Remote address: " << newclient->peerAddress().toString() << endl;
    QTextStream(stdout) << "Remote port: " << newclient->peerPort() << endl;
    QTextStream(stdout) << "Local address: " << newclient->localAddress().toString() << endl;
    QTextStream(stdout) << "Local port: " << newclient->localPort() << endl;
    client *c = new client(newclient);
    connect(c, &client::disconnected, this, &server::removeClient);
    //QByteArray block;
    //QDataStream output(&block, QIODevice::WriteOnly);
    //output.setVersion(QDataStream::Qt_5_9);
    //output << QString("hello ") + newclient->peerAddress().toString() + ":" + QString::number(newclient->peerPort());
    //newclient->write(block);
    cList.append(c);
    QTextStream(stdout) << newclient << endl;
    qDebug() << cList;
    connect(newclient,&QTcpSocket::readyRead,this,&server::readData);
}

void server::removeClient()
{
    client *c = static_cast<client *>(QObject::sender());
    QTextStream(stdout) << QObject::sender() << " se odpojil" << endl;
    cList.removeOne(c);
    qDebug() << cList;
}

void server::readData()
{
    conn = cList.last()->conn;
    QByteArray block;
    QDataStream stream(&block, QIODevice::ReadOnly);
    stream.setDevice(conn);
    stream.setVersion(QDataStream::Qt_5_9);
    stream.startTransaction();
    QString data;
    stream >> data;
    qDebug() << data;
    QByteArray blockout;
    QDataStream output(&blockout, QIODevice::WriteOnly);
    output.setDevice(conn);
    output.setVersion(QDataStream::Qt_5_9);
    output << data;
    output << QString(data);
    conn->write(blockout);
    stream.abortTransaction();
}
