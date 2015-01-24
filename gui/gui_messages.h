#ifndef GUI_MESSAGES_H
#define GUI_MESSAGES_H

#include "linqclient.h"
#include "gui_listdelegate.h"
#include "gui_avatar.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QTextBrowser>
#include <QTabWidget>

class Gui_Messages : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
    QListWidget* _listIn;
    QListWidget* _listOut;
    QTextBrowser* _output;
    QLineEdit* edt1;
    QLineEdit* edt2;
    QTextEdit* te;
public:
    Gui_Messages(LinqClient*, QWidget* parent = 0);
signals:
    void messageSent();
public slots:
    void viewInMailBody();
    void viewOutMailBody();
    void sendMail();
    void refreshMessages();
};
#endif