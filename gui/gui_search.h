#ifndef GUI_SEARCH_H
#define GUI_SEARCH_H

#include <QLineEdit>
#include <QCompleter>
#include "gui_displayinfo.h"
#include "../linqclient.h"

class Gui_Search : public QLineEdit {
    Q_OBJECT
private:
    LinqClient* _client;
    Gui_DisplayInfo* _display;
public:
    Gui_Search(LinqClient*, Gui_DisplayInfo*, QWidget* parent = 0);

signals:

public slots:
    void search();
};
#endif