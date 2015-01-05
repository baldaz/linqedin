#include "gui_links.h"

Gui_Links::Gui_Links(LinqClient* client, Gui_DisplayInfo* disp, QWidget* parent) : _client(client), _display(disp), QListWidget(parent) {
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
            item->setData(Qt::DecorationRole, QPixmap("img/profile11.png"));
            this->addItem(item);
        }
    }
}
void Gui_Links::refresh() {
    this->clear();
    createList();
}
//slot
void Gui_Links::viewContact() {
    _selected = this->currentItem()->data(Qt::UserRole + 1).toString();
    Gui_ViewContact* _view = new Gui_ViewContact(_display, _client->contactsInfo(), _selected);
}