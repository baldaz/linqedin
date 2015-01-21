#include "gui_links.h"

Gui_Links::Gui_Links(LinqClient* client, Gui_DisplayInfo* disp, QToolBar* tb, QWidget* parent) : _client(client), _display(disp), _tbar(tb), QListWidget(parent) {
    refresh();
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(viewContact()));
    // connect(this->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(reload()));
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
            item->setData(Qt::UserRole + 1, QString::fromStdString((*it)->account()->username().login()));
            item->setData(Qt::DecorationRole, QPixmap("img/link63.png"));
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
    // Gui_ViewContact* _view = new Gui_ViewContact(_display, _client->contactsInfo(), _selected);

    vector<SmartPtr<User> > _contacts = _client->contactsInfo();
    vector<SmartPtr<User> >::iterator it = _contacts.begin();
    for(; it < _contacts.end(); ++it)
        if(QString::fromStdString((*it)->account()->username().login()) == _selected) {
            QString output = QString(QString::fromStdString((*it)->account()->info()->printHtml()) + "<h5>Visit Count</h5><p> %1").arg((*it)->visitCount());
            _display->setHtml(output);
            QString title = QString(QString::fromStdString((*it)->account()->username().login()));
            _display->setDocumentTitle(title);
        }
    _client->addVisitTo(Username(_selected.toStdString(), ""));

    if(_tbar->isHidden()) _tbar->show();
    // _tbar->actions().at(0)->setIconVisibleInMenu(false);
    // if(_tbar->actions().at(0)->isVisible()) _tbar->actions().at(0)->setVisible(false);
    // if(!_tbar->actions().at(1)->isVisible()) _tbar->actions().at(1)->setVisible(true);
    // if(_tbar->actions().at(2)->isVisible()) _tbar->actions().at(2)->setVisible(true);
}

void Gui_Links::reload() {
    refresh();
}

void Gui_Links::addConn() {
    Username us((_display->documentTitle()).toStdString(), "");
    _client->addContact(us);
}
void Gui_Links::rmConn() {
    Username us((_display->documentTitle()).toStdString(), "");
    _client->removeContact(us);
}