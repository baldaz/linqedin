#include "gui_overview.h"
#include <QAction>
#include <QCompleter>

Gui_Overview::Gui_Overview(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    dispInfo = new Gui_DisplayInfo(QString::fromStdString(_client->displayHtmlInfo()));

    portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    QLabel* links = new QLabel(tr("Connections (%1)").arg(_client->netSize()));
    links->setMaximumSize(120,20);
    // QLabel* mayk = new QLabel(tr("People you could know"));
    // mayk->setMaximumSize(130, 20);

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

    _links = new QListWidget;
    connect(_links, SIGNAL(clicked(QModelIndex)), this, SLOT(viewLink()));
    createLinks();
    createSearchBar();

    connect(toolButtons[0], SIGNAL(clicked()), this, SLOT(addConnection()));
    connect(toolButtons[1], SIGNAL(clicked()), this, SLOT(removeConnection()));
    connect(toolButtons[2], SIGNAL(clicked()), this, SLOT(incrementIterator()));

    toolButtons[0]->installEventFilter(this);
    toolButtons[1]->installEventFilter(this);
    toolButtons[2]->installEventFilter(this);

    this->addWidget(portrait, 0, 0, 1, 1, Qt::AlignTop);
    this->addWidget(dispInfo, 0, 1, 3, 1); /* 0 1 4 2*/
    this->addWidget(links, 1, 0, 1, 1);
    // addWidget(mayk, 0, 2, 1, 3);
    this->addWidget(_links, 2, 0, 1, 1);
    this->addWidget(_search, 3, 0, 1, 1);
    this->addWidget(toolbar, 3, 1, 1, 1, Qt::AlignCenter);

    createRightSideList(this);

    this->setColumnStretch(0, 1);
    this->setColumnStretch(1, 6);
    this->setColumnStretch(2, 2);
    this->setRowStretch(0, 0);
    this->setRowStretch(1, 10);

    connect(this, SIGNAL(modified()), this, SLOT(refreshLists()));
}

void Gui_Overview::viewLink() {
    QString sel = _links->currentItem()->data(Qt::UserRole + 1).toString();
    QString lnk = _links->currentItem()->data(Qt::UserRole + 2).toString();
    QString pth = _links->currentItem()->data(Qt::UserRole + 3).toString();
    _client->addVisitTo(Username(lnk.toStdString(), ""));
    portrait->setPath(pth);
    dispInfo->setInfo1(lnk);
    dispInfo->setHtml(sel);
    if(toolbar->isHidden()) toolbar->show();
    if(toolbar->actions().at(0)->isVisible()) toolbar->actions().at(0)->setVisible(false);
    if(toolbar->actions().at(2)->isVisible()) toolbar->actions().at(2)->setVisible(false);
    if(!toolbar->actions().at(1)->isVisible()) toolbar->actions().at(1)->setVisible(true);
}

void Gui_Overview::createLinks() {
    vector<SmartPtr<User> > vec = _client->contactsInfo();
    vector<SmartPtr<User> >::iterator it = vec.begin();
    for(; it < vec.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        QString link;
        if(UserInfo* uf = dynamic_cast<UserInfo*> ((*it)->account()->info()))
            link = QString::fromStdString(uf->name()) + " " + QString::fromStdString(uf->surname());
        item->setData(Qt::DisplayRole, link);
        item->setData(Qt::UserRole + 1, QString::fromStdString((*it)->showInfo()));
        item->setData(Qt::UserRole + 2, QString::fromStdString((*it)->account()->username().login()));
        item->setData(Qt::UserRole + 3, QString::fromStdString((*it)->account()->avatar().path()));
        item->setData(Qt::DecorationRole, QPixmap("img/link63.png"));
        _links->addItem(item);
    }
}

void Gui_Overview::createSearchBar() {
    _search = new QLineEdit;
    _search->setPlaceholderText("Search..");
    _search->setToolTip("<p>You can activate unified search by typing ':'. E.G: ':c++,perl,snowboard' will list all users that have c++ perl and snowboard into their skills / interests fields.</p>");
    vector<string> vec = _client->displayHtmlNet();
    QStringList completions;
    if(!vec.empty()) {
        vector<string>::iterator it = vec.begin();
        for(; it < vec.end(); ++it)
            completions.push_back(QString::fromStdString(*it));
    }
    QCompleter* completer = new QCompleter(completions);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    _search->setCompleter(completer);
    _search->setClearButtonEnabled(true);
    connect(_search, SIGNAL(returnPressed()), this, SLOT(search()));
}

void Gui_Overview::search() {
    res = _client->find(_search->text().toStdString());
    if(res.empty()) {
        if(!toolbar->isHidden()) toolbar->hide();
        dispInfo->setHtml("<h2> No results</h2>");
    }
    else {
        if(toolbar->isHidden()) toolbar->show();
        if(!toolbar->actions().at(0)->isVisible()) toolbar->actions().at(0)->setVisible(true);
        if(toolbar->actions().at(2)->isVisible()) toolbar->actions().at(2)->setVisible(false);
        if(!toolbar->actions().at(1)->isVisible()) toolbar->actions().at(1)->setVisible(true);
        it = res.begin();
        if(res.size() > 1)
            if(!toolbar->actions().at(2)->isVisible()) toolbar->actions().at(2)->setVisible(true);
        showSearchResult();
    }
}

void Gui_Overview::showSearchResult() {
    if(it != res.end()) {
        bool list = _client->linked(Username(it->first, ""));
        dispInfo->setInfo1(QString::fromStdString(it->first));
        _cnt = dispInfo->info1();
        if(!list) {
            toolbar->actions().at(0)->setVisible(true);
            toolbar->actions().at(1)->setVisible(false);
            toolbar->actions().at(2)->setVisible(false);
        }
        else {
            toolbar->actions().at(0)->setVisible(false);
            toolbar->actions().at(1)->setVisible(true);
            toolbar->actions().at(2)->setVisible(false);
        }
        if(res.size() > 1 && it != res.end()) toolbar->actions().at(2)->setVisible(true);
        else toolbar->actions().at(2)->setVisible(false);
        QString htmloutput = QString("<span style='color: #666'>( " + QString::fromStdString(it->first) + " )</span>" + QString::fromStdString(it->second));
        dispInfo->setHtml(htmloutput);
        portrait->setPath(QString::fromStdString(_client->avatarFromUser(Username(it->first, ""))));
    }
    else {
        dispInfo->setHtml("<h2>Fine</h2>");
        toolbar->actions().at(2)->setVisible(false);
    }
}

void Gui_Overview::incrementIterator() {
    std::cout << "forward" << std::endl;
    ++it;
    showSearchResult();
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
    _links->clear();
    createLinks();
    createRightSideList(this);
    dispInfo->setHtml(QString::fromStdString(_client->displayHtmlInfo()));
    toolbar->hide();
    portrait->setPath(QString::fromStdString(_client->avatar()));
}

bool Gui_Overview::eventFilter(QObject* obj, QEvent* event) {
    if(event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
        if(mouseEvent->button() == Qt::LeftButton)
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
        if(toolbar->isHidden()) toolbar->show();
        if(!toolbar->actions().at(0)->isVisible()) toolbar->actions().at(0)->setVisible(true);
        if(toolbar->actions().at(2)->isVisible()) toolbar->actions().at(2)->setVisible(false);
        if(toolbar->actions().at(1)->isVisible()) toolbar->actions().at(1)->setVisible(false);
    }
}

void Gui_Overview::refreshLists() {
    _links->clear();
    rightSide->clear();
    createLinks();
    createRightSideList(this);
}

void Gui_Overview::addConnection() {
    Username us((dispInfo->info1()).toStdString(), "");
    _client->addContact(us);
    emit modified();
}

void Gui_Overview::removeConnection() {
    Username us((dispInfo->info1()).toStdString(), "");
    _client->removeContact(us);
    emit modified();
}
