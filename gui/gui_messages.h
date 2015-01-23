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
#include <QFormLayout>

class Gui_Messages : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
    QListWidget* _listIn;
    QListWidget* _listOut;
    QTextBrowser* _output;
public:
    Gui_Messages(LinqClient*, QWidget* parent = 0);
signals:
public slots:
    void viewInMailBody();
    void viewOutMailBody();
    void sendMail();
};
#endif