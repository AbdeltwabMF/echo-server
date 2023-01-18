#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QLocalSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    QLocalSocket *client;

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QLocalSocket::LocalSocketError socketError);
    void onStateChanged(QLocalSocket::LocalSocketState socketState);
};

#endif // CLIENT_H
