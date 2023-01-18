#include <QByteArray>
#include <QtWidgets>
#include <QDebug>

#include "../include/dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    server = new Server(this);
    client = new Client(this);

    if (server->server->listen("server") == false)
    {
        qWarning("Unable to start server");
    }

    client->client->connectToServer("server", QIODevice::ReadWrite);

    client->client->write("hello, server");

    QByteArray data = client->client->readAll();
    qInfo() << "Client: " << data;

    client->client->disconnectFromServer();

    clientSend = new QPushButton(tr("&Send"));

    serverChatText = new QPlainTextEdit;
    serverChatText->setPlainText("No messages yet.");
    serverChatText->setReadOnly(true);

    clientChatText = new QPlainTextEdit;
    clientChatText->setPlainText("No messages yet.");
    clientChatText->setReadOnly(true);

    QVBoxLayout *serverSide = new QVBoxLayout();
    serverSide->addWidget(serverChatText);

    QGroupBox *serverBox = new QGroupBox(tr("&Server"));
    serverBox->setLayout(serverSide);

    QVBoxLayout *clientSide = new QVBoxLayout();
    clientSide->addWidget(clientChatText);
    clientSide->addWidget(clientSend);

    QGroupBox *clientBox = new QGroupBox(tr("&Client"));
    clientBox->setLayout(clientSide);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(clientBox, 0, 0);
    mainLayout->addWidget(serverBox, 0, 1);

    setLayout(mainLayout);
}

Dialog::~Dialog()
{
}
