#include "gui_adminwindow.h"
#include "gui_displayinfo.h"
#include "linqadmin.h"
#include <QLabel>
#include <QAction>
#include <QGroupBox>
#include <QToolBar>
#include <QToolButton>
#include <QCompleter>
#include <QMessageBox>

Gui_AdminWindow::Gui_AdminWindow(QWidget* parent) : QWidget(parent) {
    _admin = new LinqAdmin;
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    setStyleSheet(QStringLiteral("QGroupBox{border:1px solid #000;border-radius:15px;} QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center;top:-6px;}"));
    QLabel* linkLabel = new QLabel("User list");
    QLabel* groupLabel = new QLabel("Group list");
    QPushButton* add = new QPushButton("Insert");
    add->setIcon(QPixmap("img/add70.png"));
    linkLabel->setMaximumSize(120,20);
    groupLabel->setMaximumSize(120,20);
    _level = new QComboBox;
    _level->addItem("Basic", QVariant(0));
    _level->addItem("Business", QVariant(1));
    _level->addItem("Executive", QVariant(2));
    tbar = new QToolBar;
    QToolButton* rm = new QToolButton(tbar);
    QToolButton* ok = new QToolButton(tbar);
    QToolButton* next = new QToolButton(tbar);
    QToolButton* delG = new QToolButton(tbar);
    rm->setIcon(QPixmap("img/cross108.png"));
    rm->setToolTip("Remove this user from Linqedin");
    ok->setIcon(QPixmap("img/check67.png"));
    ok->setToolTip("Upgrade this user");
    next->setIcon(QPixmap("img/right244.png"));
    next->setToolTip("Next result");
    delG->setIcon(QPixmap("img/cross108.png"));
    delG->setToolTip("Delete group");
    connect(rm, SIGNAL(clicked()), this, SLOT(removeUser()));
    connect(add, SIGNAL(clicked()), this, SLOT(addUser()));
    connect(ok, SIGNAL(clicked()), this, SLOT(upgradeUser()));
    connect(next, SIGNAL(clicked()), this, SLOT(nextResult()));
    connect(delG, SIGNAL(clicked()), this, SLOT(deleteGroup()));
    tbar->addWidget(rm);
    tbar->addWidget(ok);
    tbar->addWidget(next);
    tbar->addWidget(delG);
    tbar->actions().at(1)->setVisible(false);
    tbar->hide();
    QGroupBox* _admbox = new QGroupBox;
    QGroupBox* _admins = new QGroupBox;
    for(int i = 0; i < 5; ++i)
        edt[i] = new QLineEdit;
    // search bar
    edt[3]->setEchoMode(QLineEdit::Password);
    edt[4]->setPlaceholderText("Search user");
    createSearch();
    connect(edt[4], SIGNAL(returnPressed()), this, SLOT(startSearch()));
    QVBoxLayout* _mainLayout = new QVBoxLayout;
    _mainLayout->setSpacing(20);
    QGridLayout* _layout = new QGridLayout;
    QGridLayout* _inslay = new QGridLayout;
    QFormLayout* frmsx = new QFormLayout;
    QFormLayout* frmdx = new QFormLayout;

    _userList = new QListWidget;
    _groupList = new QListWidget;

    _userInfo = new Gui_DisplayInfo;
    _userInfo->setReadOnly(true);
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    createUserList();
    createGroupList();
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    _layout->addWidget(linkLabel, 0, 0, 1, 1);
    _layout->addWidget(_userInfo, 0, 1, 4, 1);
    _layout->addWidget(_userList, 1, 0, 1, 1);
    _layout->addWidget(groupLabel, 2, 0, 1, 1);
    _layout->addWidget(_groupList, 3, 0, 1, 1);
    _layout->addWidget(edt[4], 4, 0, 1, 1);
    _layout->addWidget(tbar, 4, 1, 1, 1, Qt::AlignCenter);
    _layout->setRowStretch(0,0);
    _layout->setRowStretch(1,1);
    _layout->setRowStretch(2,0);
    _layout->setColumnStretch(0,1);
    _layout->setColumnStretch(1,5);
    frmsx->addRow("Name:", edt[0]);
    frmdx->addRow("Surname:", edt[1]);
    frmsx->addRow("Username:", edt[2]);
    frmdx->addRow("Password:", edt[3]);
    frmsx->addRow("Privilege:", _level);

    _inslay->addLayout(frmsx, 0, 0, 1, 1);
    _inslay->addLayout(frmdx, 0, 1, 1, 1);
    _inslay->addWidget(add, 1, 1, 1, 1, Qt::AlignCenter);

    _admbox->setLayout(_layout);
    _admins->setLayout(_inslay);

    _mainLayout->addWidget(_admbox);
    _mainLayout->addWidget(_admins);
    setLayout(_mainLayout);
    connect(this, SIGNAL(modified()), this, SLOT(refreshLists()));
    move(100, 30);
    resize(1150, 720);
}

void Gui_AdminWindow::createSearch() {
    list<SmartPtr<User> > lst = _admin->listUsers();
    QStringList completions;
    if(!lst.empty()) {
        list<SmartPtr<User> >::iterator it = lst.begin();
        for(; it != lst.end(); ++it) {
            QString cmpname = "";
            if(UserInfo* uf = dynamic_cast<UserInfo*> ((*it)->account()->info()))
                cmpname = QString::fromStdString(uf->name()) + " " + QString::fromStdString(uf->surname());
            completions.push_back(QString::fromStdString((*it)->account()->username().login()));
            completions.push_back(cmpname);
        }
    }
    QCompleter* completer = new QCompleter(completions);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    edt[4]->setCompleter(completer);
    edt[4]->setClearButtonEnabled(true);
}

void Gui_AdminWindow::createUserList() {
    list<SmartPtr<User> > l = _admin->listUsers();
    for(list<SmartPtr<User> >::iterator it = l.begin(); it != l.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        item->setData(Qt::DisplayRole, QString::fromStdString((*it)->account()->username().login()));
        if(!(*it)->account()->lastPayment()->approvation()) {
            item->setData(Qt::DecorationRole, QPixmap("img/arrow106.png"));
            item->setData(Qt::UserRole + 3, 1);
            item->setData(Qt::UserRole + 4, QString::number((*it)->account()->lastPayment()->subscription()->level()));
        }
        else
            item->setData(Qt::DecorationRole, QPixmap("img/profile11.png"));
        item->setData(Qt::UserRole + 1, QString::fromStdString((*it)->showInfo()));
        item->setData(Qt::UserRole + 2, QString::fromStdString((*it)->account()->username().login()));
        _userList->addItem(item);
    }
    connect(_userList, SIGNAL(clicked(QModelIndex)), this, SLOT(showUser()));
}

void Gui_AdminWindow::createGroupList() {
    list<Group*> l = _admin->listGroups();
    for(list<Group*>::iterator it = l.begin(); it != l.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        item->setData(Qt::DisplayRole, QString::fromStdString((*it)->name()));
        item->setData(Qt::UserRole + 1, QString::fromStdString((*it)->admin().login()));
        _groupList->addItem(item);
    }
    connect(_groupList, SIGNAL(clicked(QModelIndex)), this, SLOT(showGroup()));
}

//SLOT
void Gui_AdminWindow::startSearch() {
    res = _admin->find(edt[4]->text().toStdString());
    if(res.empty()) {
        if(!tbar->isHidden()) tbar->hide();
        _userInfo->setHtml("<h2> No results</h2>");
    }
    else {
        if(tbar->isHidden()) tbar->show();
        if(!tbar->actions().at(0)->isVisible()) tbar->actions().at(0)->setVisible(true);
        if(res.size() > 1)
            if(!tbar->actions().at(2)->isVisible()) tbar->actions().at(2)->setVisible(true);
        it = res.begin();
        showSearchResult();
    }
}

//SLOT
void Gui_AdminWindow::showSearchResult() {
    if(it != res.end()) {
        _userInfo->setInfo1(QString::fromStdString(it->first));
        _cnt = _userInfo->info1();
        tbar->actions().at(0)->setVisible(true);
        tbar->actions().at(1)->setVisible(false);
        tbar->actions().at(3)->setVisible(false);
        if(res.size() > 1 && it != res.end()) tbar->actions().at(2)->setVisible(true);
        QString htmloutput = QString("<span style='color: #666'>( " + QString::fromStdString(it->first) + " )</span>" + QString::fromStdString(it->second));
        std::list<Group*> lsg = _admin->listUserGroups(Username(it->first, ""));
        if(lsg.size() > 0) {
            htmloutput.append("<h4>Groups</h4><ul style='font-weight:400'>");
            for(std::list<Group*>::iterator j = lsg.begin(); j != lsg.end(); ++j)
                htmloutput += "<li>" + QString::fromStdString((*j)->name()) + "</li>";
            htmloutput.append("</ul>");
        }
        _userInfo->setHtml(htmloutput);
    }
    else _userInfo->setHtml("<h2>End</h2>");
}

//SLOT
void Gui_AdminWindow::nextResult() {
    ++it;
    showSearchResult();
}

//SLOT
void Gui_AdminWindow::showUser() {
    QString _sel = _userList->currentItem()->data(Qt::UserRole + 1).toString();
    std::list<Group*> lsg = _admin->listUserGroups(Username(_userList->currentItem()->data(Qt::UserRole + 2).toString().toStdString(), ""));
    if(lsg.size() > 0) {
        _sel.append("<h4>Groups</h4><ul style='font-weight:400'>");
        for(std::list<Group*>::iterator j = lsg.begin(); j != lsg.end(); ++j)
            _sel += "<li>" + QString::fromStdString((*j)->name()) + "</li>";
        _sel.append("</ul>");
    }
    _userInfo->setHtml(_sel);
    _userInfo->setInfo1(_userList->currentItem()->data(Qt::UserRole + 2).toString());
    if(tbar->isHidden()) tbar->show();
    tbar->actions().at(3)->setVisible(false);
    tbar->actions().at(2)->setVisible(false);
    tbar->actions().at(0)->setVisible(true);
    if(_userList->currentItem()->data(Qt::UserRole + 3) == 1) {
        tbar->actions().at(1)->setVisible(true);
        _userInfo->setInfo2(_userList->currentItem()->data(Qt::UserRole + 4).toString());
    }
    else tbar->actions().at(1)->setVisible(false);
}

//SLOT
void Gui_AdminWindow::showGroup() {
    QString _sel = _groupList->currentItem()->data(Qt::DisplayRole).toString();
    QString _adm = _groupList->currentItem()->data(Qt::UserRole + 1).toString();
    Group g = _admin->findGroup(_sel.toStdString());
    QString _dsc = QString::fromStdString(g.description());
    list<Post*> p = _admin->listPostFromGroup(g);
    int num = p.size();
    QString output = "<h1>" + _sel + "</h1><h4>Admin: <span style='font-weight:400'>" + _adm + "</span></h4><h5>" + _dsc + "</h5>";
    if(!p.empty()) {
        output.append(QString("<h2>Posts (%1):</h2>").arg(num));
        for(list<Post*>::iterator it = p.begin(); it != p.end(); ++it)
            output.append(QString("<h5>Author: <span style='font-weight:400;font-size:10px'>" + QString::fromStdString((*it)->author().login()) + "</span></h5><p style='font-weight:400;font-size:11px;'>" + QString::fromStdString((*it)->content()) + "</p><hr>"));
    }
    _userInfo->setInfo1(_sel);
    _userInfo->setInfo2(_adm);
    _userInfo->setHtml(output);
    if(tbar->isHidden()) tbar->show();
    tbar->actions().at(0)->setVisible(false);
    tbar->actions().at(1)->setVisible(false);
    tbar->actions().at(2)->setVisible(false);
    tbar->actions().at(3)->setVisible(true);
}

//SLOT
void Gui_AdminWindow::deleteGroup() {
    QString name = _userInfo->info1();
    try {
        _admin->deleteGroup(name.toStdString());
        _admin->save();
        emit modified();
    }catch(Error e) {
        QMessageBox::critical(0, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}

//SLOT
void Gui_AdminWindow::addUser() {
    bool inserted = true;
    QString name = edt[0]->text();
    QString surn = edt[1]->text();
    QString uname = edt[2]->text();
    QString passw = edt[3]->text();
    int level = _level->itemData(_level->currentIndex()).toInt();
    QMap<string, string> map;
    map.insert("name", name.toStdString());
    map.insert("surname", surn.toStdString());
    map.insert("birthdate", QDate::currentDate().toString("dd.MM.yyyy").toStdString());
    try {
        _admin->insertUser(uname.toStdString(), passw.toStdString(), (privLevel) level, map.toStdMap(), 1);
    }catch(Error e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.errorMessage()));
        inserted = false;
    }
    if(inserted) {
        QMessageBox::information(this, "Operation complete", "User successfully created");
        emit modified();
    }
}

//SLOT
void Gui_AdminWindow::removeUser() {
    try {
        _admin->removeUser(Username(_userInfo->info1().toStdString(), ""));
    }catch(Error e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.errorMessage()));
    }
    emit modified();
}

//SLOT
void Gui_AdminWindow::upgradeUser() {
    _admin->upgradeSubscription(Username(_userInfo->info1().toStdString(), ""), (privLevel) ((_userInfo->info2().toInt())));
    QMessageBox::information(this, "Operation successful", "Upgrade request succesfully approved.");
    emit modified();
}

//SLOT
void Gui_AdminWindow::refreshLists() {
    _userList->clear();
    createUserList();
    _groupList->clear();
    createGroupList();
}