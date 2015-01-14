#ifndef GUI_MESSAGES_H
#define GUI_MESSAGES_H

#include "linqclient.h"
#include "gui_listmessages.h"
#include "gui_newmessage.h"
#include "gui_avatar.h"
#include <QGridLayout>

class Gui_Messages : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
    Gui_ListMessages* _list;
public:
    Gui_Messages(LinqClient*, QWidget* parent = 0);
signals:
public slots:
};
#endif