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
    void sendMessage(const QString &message);

signals:
    void sent(const QString &message);

public slots:
    void newMessage();

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QLocalSocket::LocalSocketError socketError);
    void onStateChanged(QLocalSocket::LocalSocketState socketState);
};

#endif // CLIENT_H
