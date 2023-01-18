#include <QLocalSocket>
#include <QByteArray>
#include <QDebug>

#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    server = new QLocalServer(parent);
    connect(server, &QLocalServer::newConnection, this, &Server::onNewConnection);
}

void Server::onNewConnection()
{
    qInfo(Q_FUNC_INFO);
    QLocalSocket *client = server->nextPendingConnection();
    QByteArray data = client->readAll();
    qInfo() << "Server: "<< data;
}
