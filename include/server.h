#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QLocalServer>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    QLocalServer *server;

private slots:
    void onNewConnection();
};

#endif // SERVER_H
