#ifndef GUI_GROUPS_H
#define GUI_GROUPS_H

#include <QGridLayout>
#include <QTextBrowser>
#include <QListWidget>
#include <QListWidgetItem>
#include "linqclient.h"
#include "gui_avatar.h"

class Gui_Groups : public QGridLayout {
private:
    LinqClient* _client;
public:
    Gui_Groups(LinqClient*, QWidget* = 0);
};
#endif