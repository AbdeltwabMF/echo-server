#include <QDebug>

#include "../include/client.h"

Client::Client(QObject *parent)
    : QObject{parent}
{
    client = new QLocalSocket(parent);
    client->connectToServer("echo-server.pipe");
    connect(client, &QLocalSocket::connected, this, &Client::onConnected);
    connect(client, &QLocalSocket::disconnected, this, &Client::onDisconnected);
    connect(client, &QLocalSocket::errorOccurred, this, &Client::onErrorOccurred);
    connect(client, &QLocalSocket::stateChanged, this, &Client::onStateChanged);
    connect(client, &QLocalSocket::readyRead, this, &Client::newMessage);
}

void Client::onConnected()
{
    qInfo(Q_FUNC_INFO);
}

void Client::onDisconnected()
{
    qInfo(Q_FUNC_INFO);
}

void Client::onErrorOccurred(QLocalSocket::LocalSocketError socketError)
{
    qInfo(Q_FUNC_INFO);
    switch (socketError)
    {
    case QLocalSocket::ConnectionRefusedError:
        qWarning("Timed out");
        break;
    case QLocalSocket::UnknownSocketError:
        qWarning("Undefined error");
        break;
    case QLocalSocket::PeerClosedError:
        qWarning("The server closed the connection");
        break;
    case QLocalSocket::ServerNotFoundError:
        qWarning("The named server was not found");
        break;
    case QLocalSocket::SocketAccessError:
        qWarning("Access error: required privileges");
        break;
    case QLocalSocket::SocketResourceError:
        qWarning("Too many sockets");
        break;
    case QLocalSocket::SocketTimeoutError:
        qWarning("The socket operation timed out");
        break;
    case QLocalSocket::DatagramTooLargeError:
        qWarning("The datagram was larger than the operating system's limit");
        break;
    case QLocalSocket::ConnectionError:
        qWarning("Network error");
        break;
    case QLocalSocket::UnsupportedSocketOperationError:
        qWarning("The requested socket operation is not supported");
        break;
    case QLocalSocket::OperationError:
        qWarning("An operation was attempted while the socket was in a state that did not permit it.");
        break;
    default:
        break;
    }
}

void Client::onStateChanged(QLocalSocket::LocalSocketState socketState)
{
    qInfo(Q_FUNC_INFO);
    switch (socketState)
    {
    case QLocalSocket::UnconnectedState:
        qInfo("Unconnected");
        break;
    case QLocalSocket::ConnectingState:
        qInfo("Connecting");
        break;
    case QLocalSocket::ConnectedState:
        qInfo("Connected");
        break;
    case QLocalSocket::ClosingState:
        qInfo("Closing");
        break;
    default:
        break;
    }
}

void Client::newMessage()
{
    qInfo(Q_FUNC_INFO);
    emit sent(QString("Server: ") + client->readAll());
}

void Client::sendMessage(const QString &message)
{
    qInfo(Q_FUNC_INFO);
    client->write(message.toStdString().c_str());
}
