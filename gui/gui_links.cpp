#include "gui_links.h"

Gui_Links::Gui_Links(LinqClient* client, Gui_DisplayInfo* disp, QToolBar* tb, QWidget* parent) : _client(client), _display(disp), _tbar(tb), QListWidget(parent) {
    refresh();
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(viewContact()));
}
void Gui_Links::createList() {
    vector<SmartPtr<User> > vec = _client->contactsInfo();
    vector<SmartPtr<User> >::iterator it = vec.begin();
    UserInfo* uf;
    for(; it < vec.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem();
        uf = dynamic_cast<UserInfo*> ((*it)->account()->info());
        if(uf) {
            QString link = QString::fromStdString(uf->name()) + " " + QString::fromStdString(uf->surname());
            item->setData(Qt::DisplayRole, link);
            item->setData(Qt::UserRole + 1, QString::fromStdString((*it)->account()->username()->login()));
            item->setData(Qt::DecorationRole, QPixmap("img/link63.png"));
            this->addItem(item);
        }
    }
}
void Gui_Links::refresh() {
    this->clear();
    // _layout->removeWidget(rm);
    createList();
}
void Gui_Links::removeWidget() {
}
//slot
void Gui_Links::viewContact() {
    _selected = this->currentItem()->data(Qt::UserRole + 1).toString();
    Gui_ViewContact* _view = new Gui_ViewContact(_display, _client->contactsInfo(), _selected);
    _client->addVisitTo(Username(_selected.toStdString(), ""));
    _tbar->show();
    _tbar->actions().at(0)->setVisible(false);
    _tbar->actions().at(1)->setVisible(true);
    _tbar->actions().at(2)->setVisible(false);
    // _selected = this->currentItem()->data(Qt::DisplayRole).toString();
    // Gui_ViewContact* _view = new Gui_ViewContact(_client, _display, _selected);
    // rm = new QPushButton("REMOVE CONNECTION");
    // _layout->removeWidget(rm);
    // _layout->addWidget(rm, 3, 2, 1, -1);
}