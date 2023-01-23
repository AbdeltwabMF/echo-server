#include <QLocalSocket>
#include <QByteArray>
#include <QDebug>

#include "../include/server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    server = new QLocalServer(parent);
    server->listen("echo-server.pipe");
    connect(server, &QLocalServer::newConnection, this, &Server::onNewConnection);
}

void Server::onNewConnection()
{
    qInfo(Q_FUNC_INFO);
    ls = server->nextPendingConnection();
    connect(ls, &QLocalSocket::readyRead, this, &Server::newMessage);
}

void Server::newMessage()
{
    qInfo(Q_FUNC_INFO);
    QByteArray message = ls->readAll();
    emit sent(QString("Client: ") + message);
    ls->write(message);
}