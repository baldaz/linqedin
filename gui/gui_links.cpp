#include "gui_links.h"

Gui_Links::Gui_Links(LinqClient* client, QWidget* parent) : _client(client), QListWidget(parent) {
    refresh();
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(viewContact()));
}
void Gui_Links::createList() {
    vector<string> vec = _client->displayHtmlNet();
    vector<string>::iterator it = vec.begin();
    for(; it < vec.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, QString::fromStdString(*it));
        item->setData(Qt::UserRole + 1, "Sara87");
        item->setData(Qt::DecorationRole, QPixmap("img/profile11.png"));
        this->addItem(item);
    }
}
void Gui_Links::refresh() {
    this->clear();
    createList();
}
//slot
void Gui_Links::viewContact() {
    _selected = this->currentItem()->data(Qt::UserRole + 1).toString();
}