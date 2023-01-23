#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QLocalServer>

class Server : public QObject
{
    Q_OBJECT
    QLocalSocket *ls;

public:
    explicit Server(QObject *parent = nullptr);
    QLocalServer *server;

signals:
    void sent(const QString &message);

public slots:
    void newMessage();

private slots:
    void onNewConnection();
};

#endif // SERVER_H
