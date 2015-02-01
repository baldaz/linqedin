#include "gui_overview.h"

Gui_Overview::Gui_Overview(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    dispInfo = new Gui_DisplayInfo(QString::fromStdString(_client->displayHtmlInfo()));

    portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    QLabel* links = new QLabel(tr("Connections (%1)").arg(_client->netSize()));
    links->setMaximumSize(120,20);

    toolbar = new QToolBar;
    toolButtons[0] = new QToolButton(toolbar);
    toolButtons[0]->setIcon(QPixmap("img/add70.png"));
    toolButtons[0]->setToolTip("Add connection");
    toolButtons[1] = new QToolButton(toolbar);
    toolButtons[1]->setIcon(QPixmap("img/cross108.png"));
    toolButtons[1]->setToolTip("Delete connection");
    toolButtons[2] = new QToolButton(toolbar);
    toolButtons[2]->setIcon(QPixmap("img/right244.png"));
    toolButtons[2]->setToolTip("Next result");

    toolbar->addWidget(toolButtons[0]);
    toolbar->addWidget(toolButtons[1]);
    toolbar->addWidget(toolButtons[2]);
    toolbar->hide();
    toolbar->installEventFilter(this); //prevent double click maximizing window

    listLinks = new Gui_Links(_client, dispInfo, toolbar, portrait);

    searchBar = new Gui_Search(_client, dispInfo, toolbar, listLinks, portrait);

    connect(toolButtons[0], SIGNAL(clicked()), this, SLOT(addConnection()));
    connect(toolButtons[1], SIGNAL(clicked()), this, SLOT(removeConnection()));


    this->addWidget(portrait, 0, 0, 1, 1, Qt::AlignTop);
    this->addWidget(dispInfo, 0, 1, 3, 1); /* 0 1 4 2*/
    this->addWidget(links, 1, 0, 1, 1);
    this->addWidget(listLinks, 2, 0, 1, 1);
    this->addWidget(searchBar, 3, 0, 1, 1);
    this->addWidget(toolbar, 3, 1, 1, 1, Qt::AlignCenter);

    createRightSideList(this);

    this->setColumnStretch(0, 1);
    this->setColumnStretch(1, 6);
    this->setColumnStretch(2, 2);
    this->setRowStretch(0, 0);
    this->setRowStretch(1, 10);
}

void Gui_Overview::createRightSideList(QGridLayout* lay) {
    vector<SmartPtr<User> > users = _client->similarity();
    rightSide = new QListWidget();
    QFont font;
    font.setBold(true);
    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::DisplayRole, "People you may know");
    item->setFont(font);
    item->setFlags(Qt::ItemIsEnabled);
    item->setWhatsThis("header");
    rightSide->addItem(item);

    vector<SmartPtr<User> >::iterator it = users.begin();
    QString fullname;
    UserInfo* uf;
    for(; it < users.end(); ++it) {
        QListWidgetItem* itemD = new QListWidgetItem();
        uf = dynamic_cast<UserInfo*> ((*it)->account()->info());
        fullname = QString(QString::fromStdString(uf->name()) + " " + QString::fromStdString(uf->surname()));
        itemD->setData(Qt::DisplayRole, fullname);
        itemD->setData(Qt::DecorationRole, QPixmap("img/link19.png"));
        itemD->setData(Qt::UserRole + 1, QString::fromStdString((*it)->account()->username().login()));
        QString desc = QString(QString::fromStdString((*it)->net()->printHtml()));
        itemD->setData(Qt::ToolTipRole, desc);
        rightSide->addItem(itemD);
    }
    lay->addWidget(rightSide, 0, 2, 2, 1, Qt::AlignTop);
    connect(rightSide, SIGNAL(clicked(QModelIndex)), this, SLOT(viewContact()));
}

void Gui_Overview::refresh() {
    listLinks->refresh();
    createRightSideList(this);
    dispInfo->setHtml(QString::fromStdString(_client->displayHtmlInfo()));
    toolbar->hide();
    portrait->setPath(QString::fromStdString(_client->avatar()));
}

bool Gui_Overview::eventFilter(QObject* obj, QEvent* event) {
    if(event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
        if(mouseEvent->button() == (Qt::LeftButton | Qt::RightButton))
            return true;
    }
    return false;
}

void Gui_Overview::viewContact() {
    if(rightSide->currentItem()->whatsThis() != "header") {
        QString sel = rightSide->currentItem()->data(Qt::DisplayRole).toString();
        map<string, string> _contacts = _client->find(sel.toStdString());
        map<string, string>::iterator it = _contacts.begin();
        QString output = QString(QString::fromStdString(it->second));
        dispInfo->setHtml(output);
        portrait->setPath(QString::fromStdString(_client->avatarFromUser(Username(it->first, ""))));
        QString title = QString(QString::fromStdString(it->first));
        dispInfo->setInfo1(title);
        _client->addVisitTo(Username(it->first, ""));
        toolbar->show();
    }
}

void Gui_Overview::addConnection() {
    if(!dispInfo->info1().isEmpty()) listLinks->addConn();
    else searchBar->addConn();
}

void Gui_Overview::removeConnection() {
    if(!dispInfo->info1().isEmpty()) listLinks->rmConn();
    else searchBar->rmConn();
}
