#ifndef GUI_OVERVIEW_H
#define GUI_OVERVIEW_H

#include <QGridLayout>
#include <QListWidget>
#include <QToolBar>
#include <QToolButton>
#include <QEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include "gui_displayinfo.h"
#include "gui_links.h"
#include "gui_search.h"
#include "../linqclient.h"

class Gui_Overview : public QGridLayout {
    Q_OBJECT

    QToolBar* toolbar;
    enum { NumToolButtons = 3 };
    QToolButton* toolButtons[NumToolButtons];
    Gui_DisplayInfo* dispInfo;
    Gui_Links* listLinks;
    Gui_Search* searchBar;
    QLabel* portrait;
    QListWidget* listview;
    QListWidget* rightSide;
    LinqClient* user;

    void createRightSideList(QGridLayout*);
    void logicInitialize();
    bool eventFilter(QObject*, QEvent*);

public:
    Gui_Overview(QWidget* parent = 0);
    void refresh();
signals:
public slots:
    void viewContact();
    void addConnection();
    void removeConnection();
};

#endif