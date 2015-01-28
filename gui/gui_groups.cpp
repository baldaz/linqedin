#include "gui_groups.h"

Gui_Groups::Gui_Groups(LinqClient* c, QWidget* parent) : _client(c), QGridLayout(parent) {
    Gui_Avatar* portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    QTextBrowser* showgrp = new QTextBrowser;
    QListWidget* grplist = new QListWidget;
    list<Group*> g = _client->listGroups();
    QString out;
    for(list<Group*>::iterator it = g.begin(); it != g.end(); ++it) {
       QListWidgetItem* item = new QListWidgetItem;
       item->setData(Qt::DisplayRole, QString::fromStdString((*it)->name()));
       grplist->addItem(item);
    }
    // showgrp->setHtml(out);
    addWidget(portrait, 0, 0, 1, 1, Qt::AlignTop);
    addWidget(grplist, 1, 0, 1, 1);
    // addWidget(showgrp, 0, 1, 1, 1);
}