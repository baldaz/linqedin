#ifndef GUI_OVERVIEW_H
#define GUI_OVERVIEW_H

#include <QGridLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QToolBar>
#include <QToolButton>
#include <QEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include "gui_displayinfo.h"
#include "gui_avatar.h"
#include "linqclient.h"

class Gui_Overview : public QGridLayout {
    Q_OBJECT
private:
    QToolBar* toolbar;
    enum { NumToolButtons = 3 };
    QToolButton* toolButtons[NumToolButtons];
    Gui_DisplayInfo* dispInfo;
    Gui_Avatar* portrait;
    QListWidget* rightSide;
    LinqClient* _client;
    QListWidget* _links;
    QLineEdit* _search;
    map<string, string> res;
    map<string, string>::iterator it;
    QString _cnt;

    void createLinks();
    void createSearchBar();
    void createRightSideList(QGridLayout*);
    bool eventFilter(QObject*, QEvent*);

public:
    Gui_Overview(LinqClient*, QWidget* parent = 0);
    void refresh();
signals:
    void modified();
public slots:
    void search();
    void viewLink();
    void viewContact();
    void showSearchResult();
    void addConnection();
    void removeConnection();
    void incrementIterator();
    void refreshLists();
};

#endif