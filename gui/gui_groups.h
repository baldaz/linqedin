#ifndef GUI_GROUPS_H
#define GUI_GROUPS_H

#include <QGridLayout>
#include <QTextBrowser>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QToolBar>
#include <QToolButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QFormLayout>
#include "linqclient.h"
#include "gui_avatar.h"

class Gui_Groups : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
    QTextBrowser* showgrp;
    QListWidget* grplist;
    QTextEdit* newpost;
    QLineEdit* newgrp;
    QLineEdit* grpname;
    QPushButton* post;
    QString name, desc, admin;
    QFormLayout* newgrplayout;
    QGroupBox* newbox;
    QToolBar* tbar;
    enum {numTbuttons = 5};
    QToolButton* tbuttons[numTbuttons];
    QPushButton* mbuttons[numTbuttons];
public:
    Gui_Groups(LinqClient*, QWidget* = 0);
public slots:
    void showGroup();
    void sendPost();
    void newGroup();
};
#endif