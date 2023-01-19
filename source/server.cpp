#include <QLocalSocket>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>

#include "../include/server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    server = new QLocalServer(parent);
    server->listen("server");
    connect(server, &QLocalServer::newConnection, this, &Server::onNewConnection);
}

void Server::onNewConnection()
{
    qInfo(Q_FUNC_INFO);
    QLocalSocket *ls = server->nextPendingConnection();
    if(ls == nullptr) return;
    if(ls->waitForReadyRead(0) == false) {
        qWarning() << ls->errorString();
        return;
    }
    QByteArray message = ls->readAll();
    qInfo() << "Client said: " << message;
    emit sent(QString("Client: ") + message);

    QCryptographicHash hash = QCryptographicHash(QCryptographicHash::Keccak_256);
    QString hashed = hash.hash(message, QCryptographicHash::Keccak_256).toBase64();
    message.append(", Hash: " + hashed.toStdString());

    ls->write(message);
    if(ls->waitForBytesWritten(0) == false) {
        qWarning() << ls->errorString();
        return;
    }
}
