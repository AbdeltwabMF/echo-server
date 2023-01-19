#include <QByteArray>
#include <QtWidgets>
#include <QDebug>

#include "../include/dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    server = new Server(this);
    client = new Client(this);

    connect(server, &Server::sent, this, &Dialog::newMessage);
    connect(client, &Client::sent, this, &Dialog::newMessage);

    chat = new QPlainTextEdit;
    chat->setReadOnly(true);

    chat->setMinimumWidth(649);
    chat->setMinimumHeight(350);

    message = new QLineEdit();
    message->setStyleSheet("QLineEdit {"
                           "background-color: #F8F8F8;"
                           "border: 1px solid #C3C3C3;"
                           "padding: 3 3;"
                           "border-radius: 4%;"
                           "}"
                           "QLineEdit:hover:!pressed {"
                           "border: 1px solid #60CDCF;"
                           "}"
                           "QLineEdit:focus, QLineEdit:hover {"
                           "background-color: #F9F9F9;"
                           "}");

    send = new QPushButton(tr("&Send"));
    connect(send, &QPushButton::clicked, this, &Dialog::onSendClicked);

    QVBoxLayout *chatLayout = new QVBoxLayout;
    chatLayout->addWidget(chat);
    chatLayout->addWidget(message);
    chatLayout->addWidget(send);

    QGroupBox *chatBox = new QGroupBox(tr("&CryptoChat"));
    chatBox->setLayout(chatLayout);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(chatBox, 0, 0);

    setLayout(mainLayout);
    setWindowTitle("Echo Server");
}

Dialog::~Dialog()
{
}

void Dialog::onSendClicked()
{
    QString clientMsg = message->text().trimmed();
    if(clientMsg.size() == 0) return;

    qInfo(Q_FUNC_INFO);
    client->sendMessage(clientMsg);
}

void Dialog::newMessage(const QString &message)
{
    qInfo(Q_FUNC_INFO);
    chat->appendPlainText(message);
    if(message.startsWith("Server") == true) {
        chat->appendPlainText("\n");
    }
}
