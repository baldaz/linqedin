#ifndef GUI_LINKS_H
#define GUI_LINKS_H

#include <QStringList>
#include <QString>
#include <QListWidget>
#include <QToolBar>
#include <QAction>
#include <QGridLayout>
#include "gui_viewcontact.h"
#include "../username.h"
#include "../user.h"
#include "../linqnet.h"
#include "../linqclient.h"

class Gui_Links : public QListWidget {
    Q_OBJECT
public:
    Gui_Links(LinqClient*, Gui_DisplayInfo*, QToolBar*, QWidget* parent = 0);
    void refresh();
    void removeWidget();
signals:

public slots:
    void viewContact();
private:
    LinqClient* _client;
    Gui_DisplayInfo* _display;
    QString _selected;
    QGridLayout* _layout;
    QToolBar* _tbar;
    void createList();
};
#endif