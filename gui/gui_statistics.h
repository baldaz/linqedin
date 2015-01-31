#ifndef GUI_STATISTICS_H
#define GUI_STATISTICS_H

#include <QGridLayout>
#include <QTextBrowser>
#include <QListWidget>
#include <QFormLayout>
#include "gui_avatar.h"
#include "linqclient.h"

class Gui_Statistics : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
    QTextBrowser* _list;
public:
    Gui_Statistics(LinqClient*, QWidget* parent = 0);
};
#endif