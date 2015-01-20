#ifndef GUI_MESSAGES_H
#define GUI_MESSAGES_H

#include "linqclient.h"
// #include "gui_listmessages.h"
#include "gui_listdelegate.h"
#include "gui_newmessage.h"
#include "gui_avatar.h"
#include <QGridLayout>
#include <QListWidget>
#include <QTextBrowser>
#include <QTabWidget>

class Gui_Messages : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
    QListWidget* _list;
    QTextBrowser* _output;
public:
    Gui_Messages(LinqClient*, QWidget* parent = 0);
signals:
public slots:
    void viewMessageBody();
};
#endif