#include "gui_overview.h"

Gui_Overview::Gui_Overview(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    dispInfo = new Gui_DisplayInfo(_client);

    portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    QLabel* links = new QLabel(tr("Connections (%1)").arg(_client->netSize()));
    links->setMaximumSize(120,20);
    // links->setPixmap(QPixmap("img/share12.png"));
    // dispInfo->setStyleSheet("background:#000 url('img/abstract.png') no-repeat; background-attachment:fixed; border-radius: 10px; background-position: bottom;");
    // searchBar->setStyleSheet("background: #f0f");
    // dispInfo->setStyleSheet("background: #fff");

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

    listLinks = new Gui_Links(_client, dispInfo, toolbar);

    searchBar = new Gui_Search(_client, dispInfo, toolbar, listLinks);

    connect(toolButtons[0], SIGNAL(clicked()), this, SLOT(addConnection()));
    connect(toolButtons[1], SIGNAL(clicked()), this, SLOT(removeConnection()));


    this->addWidget(portrait, 0, 0, 1, 1, Qt::AlignTop);
    this->addWidget(dispInfo, 0, 1, 3, 1); /* 0 1 4 2*/
    this->addWidget(links, 1, 0, 1, 1);
    // listLinks->setStyleSheet("background: #f0f");
    this->addWidget(listLinks, 2, 0, 1, 1);
    this->addWidget(searchBar, 3, 0, 1, 1);
    this->addWidget(toolbar, 3, 1, 1, 1, Qt::AlignCenter);

    createRightSideList(this);
    connect(rightSide, SIGNAL(clicked(QModelIndex)), this, SLOT(viewContact()));
    this->setColumnStretch(0, 1);
    this->setColumnStretch(1, 5);
    this->setColumnStretch(2, 2);
    // this->setColumnStretch(3, 2);
    this->setRowStretch(0, 0);
    this->setRowStretch(1, 10);
    // layout->setRowStretch(2, 20);
    // layout->setRowStretch(3, 1);
}

void Gui_Overview::createRightSideList(QGridLayout* lay) {
    vector<SmartPtr<User> > users = _client->similarity();
    rightSide = new QListWidget();
    QFont font;
    font.setBold(true);
    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::DisplayRole, "People you may know");
    item->setFont(font);
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
        itemD->setData(Qt::UserRole + 1, QString::fromStdString((*it)->account()->username()->login()));
        // itemD->setData(Qt::ToolTipRole, "Connected with Pablos, Sara, Atos");
        rightSide->addItem(itemD);
    }
    // rightSide->setStyleSheet("background:#ff0");
    lay->addWidget(rightSide, 0, 2, 2, 1, Qt::AlignTop);
}

void Gui_Overview::refresh() {
    listLinks->refresh();
    createRightSideList(this);
    dispInfo->setHtml(QString::fromStdString(_client->displayHtmlInfo()));
    toolbar->hide();
}

bool Gui_Overview::eventFilter(QObject* obj, QEvent* event) {
    if(event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
        if(mouseEvent->button() == Qt::LeftButton | Qt::RightButton)
            return true;
    }
    else return false;
}

void Gui_Overview::viewContact() {
    QString sel = rightSide->currentItem()->data(Qt::DisplayRole).toString();
    map<string, string> _contacts = _client->find(sel.toStdString());
    map<string, string>::iterator it = _contacts.begin();
    // for(; it != _contacts.end(); ++it) {
        QString output = QString(QString::fromStdString(it->second));
        dispInfo->setHtml(output);
        QString title = QString(QString::fromStdString(it->first));
        dispInfo->setDocumentTitle(title);
        _client->addVisitTo(Username(it->first, ""));
    // }
    toolbar->show();
}

void Gui_Overview::addConnection() {
    if(!dispInfo->documentTitle().isEmpty()) listLinks->addConn();
    else searchBar->addConn();
}

void Gui_Overview::removeConnection() {
    if(!dispInfo->documentTitle().isEmpty()) listLinks->rmConn();
    else searchBar->rmConn();
}