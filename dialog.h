#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "server.h"
#include "client.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QPlainTextEdit;
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QPushButton *clientSend;
    QPlainTextEdit *serverChat;
    QPlainTextEdit *clientChat;
    QPlainTextEdit *serverChatText;
    QPlainTextEdit *clientChatText;

private:
    Server *server;
    Client *client;
};
#endif // DIALOG_H
