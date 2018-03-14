#include "client.h"

client::client(QTcpSocket *conn, QObject *parent):
    QObject::QObject(parent)
{
    qDebug() << this;
    this->conn = conn;

}

void client::gotMessage()
{

    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::ReadOnly);
    stream.setDevice(conn);
    stream.setVersion(QDataStream::Qt_5_9);
    stream.startTransaction();
    QString data;
    stream >> data;
    QTextStream(stdout) << this << " poslal: " << data << endl;
    QByteArray block;
    QDataStream output(&block, QIODevice::WriteOnly);
    output.setVersion(QDataStream::Qt_5_9);
    output << data;
    output << QString(data);
    conn->write(block);
    stream.abortTransaction();
}

void client::clientDisconnected()
{
    emit(disconnected());
}
