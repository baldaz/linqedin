#ifndef GUI_SEARCH_H
#define GUI_SEARCH_H

#include <QLineEdit>
#include <QToolBar>
#include <QAction>
#include <QCompleter>
#include "gui_displayinfo.h"
#include "gui_links.h"
#include "linqclient.h"

class Gui_Search : public QLineEdit {
    Q_OBJECT
private:
    LinqClient* _client;
    Gui_DisplayInfo* _display;
    QToolBar* _tbar;
    Gui_Links* _links;
    QString _cnt;
    map<string, string> res;
    map<string, string>::iterator it;

public:
    Gui_Search(LinqClient*, Gui_DisplayInfo*, QToolBar*, Gui_Links*, QWidget* parent = 0);
    void addConn();
    void rmConn();

signals:

public slots:
    void search();
    void incrementIterator();
    void showResult();
};
#endif