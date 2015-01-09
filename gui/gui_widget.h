#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QGroupBox>
#include <QTextEdit>
#include <QTextBrowser>
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QGridLayout>
#include <QListWidget>
#include <QPainter>
#include <QBitmap>
#include "gui_displayinfo.h"
#include "gui_links.h"
#include "gui_search.h"
#include "../linqclient.h"

class Gui_Widget : public QWidget {
    Q_OBJECT
public:
    Gui_Widget();
public slots:
    void refreshLinks();
    void insertContatto();
    void removeContatto();
    void viewSettings();
    void viewPayments();
    void viewMessages();
    void userSearch();
    void logout();
private:
    // campo dati logico
    LinqClient* user;
    // inizializzazione logica
    void logicInitialize();

    // Componenti grafiche di Gui_Widget
    QGroupBox* horizontalGroupBox;
    QGroupBox* gridGroupBox;
    QToolBar* toolbar;
    enum { NumGridRows = 2, NumButtons = 6, NumToolButtons = 2 };
    QToolButton* toolButtons[NumToolButtons];
    // QTextEdit* smallEditor;
    // QTextEdit* bigEditor;
    Gui_DisplayInfo* dispInfo;
    Gui_Links* listLinks;
    Gui_Search* searchBar;
    QLabel* labels[NumGridRows];
    QLabel* portrait;
    QLineEdit* lineEdits[NumGridRows];
    QPushButton* buttons[NumButtons];
    QListWidget* listview;

    // metodi privati di set-up di Gui_Widget
    void createHorizontalGroupBox();
    void createGridGroupBox();
    void createRightSideList(QGridLayout*);
};

#endif