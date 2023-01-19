#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "server.h"
#include "client.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QLineEdit;
class QPlainTextEdit;
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QPlainTextEdit *chat;
    QLineEdit *message;
    QPushButton *send;

private:
    Server *server;
    Client *client;

private slots:
    void onSendClicked();
    void newMessage(const QString &message);
};
#endif // DIALOG_H
