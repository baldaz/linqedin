#include "gui_groups.h"
#include <QMessageBox>
#include <QMenu>

Gui_Groups::Gui_Groups(LinqClient* c, QWidget* parent) : QGridLayout(parent), _client(c) {
    Gui_Avatar* portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    QPushButton* create = new QPushButton("CREATE");
    QLabel* title = new QLabel("NEW GROUP");
    showgrp = new Gui_DisplayInfo;
    newpost = new QTextEdit;
    newgrp = new QLineEdit;
    search = new QLineEdit;
    newbox = new QGroupBox;
    memlbl = new QLabel("Members");
    memlbl->setMaximumSize(80,20);

    grpname = new QLineEdit;
    newgrplayout = new QFormLayout;
    newgrplayout->setSpacing(15);
    newgrplayout->addRow(title);
    newgrplayout->addRow("Group name:", grpname);
    newgrplayout->addRow("Group description:", newgrp);
    newgrplayout->addRow(create);

    newbox->setLayout(newgrplayout);
    if(_client->level() < executive) newbox->hide();

    search->setPlaceholderText("Search group..");
    search->hide();
    connect(search,  SIGNAL(returnPressed()), this, SLOT(searchGroup()));

    post = new QPushButton("POST");
    grplist = new QListWidget;
    memlist = new QListWidget;
    QLabel* grplbl = new QLabel("Groups");
    grplbl->setMaximumSize(120,20);
    createGroups();
    QFormLayout* frm = new QFormLayout;
    mbuttons[0] = new QPushButton;
    mbuttons[0]->setIcon(QPixmap("img/document185.png"));
    mbuttons[0]->setToolTip("New group");
    mbuttons[1] = new QPushButton;
    mbuttons[1]->setIcon(QPixmap("img/cross108.png"));
    mbuttons[1]->setToolTip("Delete group");
    mbuttons[2] = new QPushButton;
    mbuttons[2]->setIcon(QPixmap("img/mop2.png"));
    mbuttons[2]->setToolTip("Delete all posts");
    mbuttons[3] = new QPushButton;
    mbuttons[3]->setIcon(QPixmap("img/exit6.png"));
    mbuttons[3]->setToolTip("Leave this group");
    mbuttons[4] = new QPushButton;
    mbuttons[4]->setIcon(QPixmap("img/enter3.png"));
    mbuttons[4]->setToolTip("Join this group");

    frm->addRow(mbuttons[0]);
    frm->addRow(mbuttons[3]);
    frm->addRow(mbuttons[4]);
    frm->addRow(mbuttons[1]);
    frm->addRow(mbuttons[2]);

    connect(mbuttons[0], SIGNAL(clicked()), this, SLOT(showNewGroup()));
    connect(create, SIGNAL(clicked()), this, SLOT(newGroup()));
    connect(mbuttons[1], SIGNAL(clicked()), this, SLOT(deleteGroup()));
    connect(mbuttons[2], SIGNAL(clicked()), this, SLOT(clearPosts()));
    connect(mbuttons[3], SIGNAL(clicked()), this, SLOT(leaveGroup()));
    connect(mbuttons[4], SIGNAL(clicked()), this, SLOT(addGroup()));

    mbuttons[0]->hide();
    mbuttons[1]->hide();
    mbuttons[2]->hide();
    mbuttons[3]->hide();
    mbuttons[4]->hide();
    if(_client->level() >= executive)
        mbuttons[0]->show();
    tbar = new QToolBar;
    tbuttons[0] = new QToolButton(tbar);
    tbuttons[0]->setIcon(QPixmap("img/cross108.png"));
    tbar->addWidget(tbuttons[0]);

    newpost->setStyleSheet("background: #1a1a1a; font-weight:400");
    newpost->setPlaceholderText("Insert new post into this group.");
    newpost->hide();
    post->hide();
    showgrp->hide();
    memlbl->hide();
    memlist->hide();
    memlist->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(memlist, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(memListMenu(const QPoint&)));

    addWidget(newbox, 0, 1, 1, 1);
    addWidget(portrait, 0, 0, 1, 1, Qt::AlignTop);
    addWidget(showgrp, 0, 1, 3, 1);
    addLayout(frm, 0, 2, 1, 1, Qt::AlignRight);
    addWidget(newpost, 3, 1, 2, 3);
    addWidget(post, 5, 4, 1, 1, Qt::AlignRight);
    addWidget(grplbl, 1, 0, 1, 1);
    addWidget(grplist, 2, 0, 1, 1);
    addWidget(memlbl, 3, 0, 1, 1);
    addWidget(memlist, 4, 0, 1, 1);
    addWidget(search, 5, 0, 1, 1);
    setRowStretch(0, 0);
    setRowStretch(1, 10);
    setColumnStretch(0, 1);
    setColumnStretch(1, 5);
    connect(grplist, SIGNAL(clicked(QModelIndex)), this, SLOT(showGroup()));
    connect(post, SIGNAL(clicked()), this, SLOT(sendPost()));
    connect(this, SIGNAL(created(int)), this, SLOT(refresh(int)));
}

void Gui_Groups::createGroups() {
    if(_client->level() >= business) {
        QStringList completions;
        list<Group*> grps = _client->listAllGroups();
        if(!grps.empty()) {
            list<Group*>::iterator it = grps.begin();
            for(; it != grps.end(); ++it)
                completions.push_back(QString::fromStdString((*it)->name()));
        }
        QCompleter* completer = new QCompleter(completions, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        search->setCompleter(completer);
        search->setClearButtonEnabled(true);
        search->show();
        for(list<Group*>::iterator it = grps.begin(); it != grps.end(); ++it) {
            if((*it)->isMember(_client->username())) {
               QListWidgetItem* item = new QListWidgetItem;
               item->setData(Qt::DisplayRole, QString::fromStdString((*it)->name()));
               item->setData(Qt::UserRole + 1, QString::fromStdString((*it)->admin().login()));
               item->setData(Qt::UserRole + 2, QString::fromStdString((*it)->description()));
               grplist->addItem(item);
           }
        }
    }
}

void Gui_Groups::createMemList(const string& gname) {
    memlist->clear();
    Group g = _client->findGroup(gname);
    list<SmartPtr<User> > mb = g.members();
    for(list<SmartPtr<User> >::iterator it = mb.begin(); it != mb.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        QString link;
        if((*it)->account()->username().login() != _client->username().login()) {
            if(UserInfo* uf = dynamic_cast<UserInfo*> ((*it)->account()->info())) {
                link = QString::fromStdString(uf->name()) + " " + QString::fromStdString(uf->surname());
                if((*it)->account()->username().login() == g.admin().login()) link += " - A";
            }
            item->setData(Qt::DisplayRole, link);
            item->setData(Qt::UserRole + 2, QString::fromStdString((*it)->account()->username().login()));
            if(_client->linked((*it)->account()->username()))
                item->setData(Qt::DecorationRole, QPixmap("img/link63.png"));
            else item->setData(Qt::DecorationRole, QPixmap("img/link19.png"));
            memlist->addItem(item);
        }
    }
}

//SLOT
void Gui_Groups::refresh(int t) {
    switch(t) {
        case 0:
        {
            grplist->clear();
            createGroups();
            memlist->clear();
            createMemList(showgrp->info1().toStdString());
        }
        break;
        case 1:
        {
            grplist->clear();
            createGroups();
            memlist->clear();
        }
    }
}

//SLOT
void Gui_Groups::showGroup() {
    newbox->hide();
    showgrp->show();
    newpost->show();
    post->show();
    memlbl->show();
    name = grplist->currentItem()->data(Qt::DisplayRole).toString();
    createMemList(name.toStdString());
    memlist->show();
    memlist->setEnabled(false);
    desc = grplist->currentItem()->data(Qt::UserRole + 2).toString();
    admin = grplist->currentItem()->data(Qt::UserRole + 1).toString();
    Group g = _client->findGroup(name.toStdString());
    if(admin == QString::fromStdString(_client->username().login())) {
        mbuttons[1]->show();
        mbuttons[2]->show();
        mbuttons[3]->hide();
        mbuttons[4]->hide();
        memlist->setEnabled(true);
    }
    else {
        mbuttons[1]->hide();
        mbuttons[2]->hide();
        if(g.isMember(_client->username()))
            mbuttons[3]->show();
        else mbuttons[4]->show();
    }
    list<Post*> p = _client->listPostFromGroup(g);
    int num = p.size();
    QString output = "<h1>" + name + "</h1><h4>Admin: <span style='font-weight:400'>" + admin + "</span></h4><h5>" + desc + "</h5>";
    if(!p.empty()) {
        output.append(QString("<h2>Posts (%1):</h2>").arg(num));
        for(list<Post*>::iterator it = p.begin(); it != p.end(); ++it)
            output.append(QString("<h5>Author: <span style='font-weight:400;font-size:10px'>" + QString::fromStdString((*it)->author().login()) + "</span></h5><p style='font-weight:400;font-size:11px;'>" + QString::fromStdString((*it)->content()) + "</p><hr>"));
    }
    showgrp->setInfo1(name);
    showgrp->setInfo2(admin);
    showgrp->setHtml(output);
}

//SLOT
void Gui_Groups::sendPost() {
    QString pst = newpost->toPlainText();
    Group g(Username(admin.toStdString(), ""), name.toStdString());
    if(!pst.isEmpty()) {
        Post* p = new Post(_client->username(), pst.toStdString());
        _client->addPostToGroup(g, *p);
        QString dump = showgrp->toHtml();
        QString me = QString::fromStdString(_client->username().login());
        dump.append(QString("<h5>Author: <span style='font-weight:400;font-size:10px'>" + me + "</span></h5><p style='font-weight:400;font-size:11px;'>" + pst + "</p><hr>"));
        showgrp->setHtml(dump);
        _client->save();
    }
}

//SLOT
void Gui_Groups::showNewGroup() {
    showgrp->hide();
    newpost->hide();
    post->hide();
    memlbl->hide();
    memlist->hide();
    newbox->show();
    mbuttons[1]->hide();
    mbuttons[2]->hide();
    mbuttons[3]->hide();
    mbuttons[4]->hide();
}

//SLOT
void Gui_Groups::newGroup() {
    QString name = grpname->text();
    QString desc = newgrp->text();
    Group* g = new Group(_client->username(), name.toStdString(), desc.toStdString()); // freed in db destructor
    try {
        _client->createNewGroup(*g);
        _client->save();
        QMessageBox::information(0, "Operation succesful", "Group \"" + name + " \" successfully created");
        emit created(1);
    }catch(Error e) {
        QMessageBox::critical(0, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}

//SLOT
void Gui_Groups::addGroup() {
    QString name = showgrp->info1();
    QString admin = showgrp->info2();
    try {
        _client->addGroup(name.toStdString(), admin.toStdString());
        _client->save();
        emit created(0);
    }catch(Error e) {
        QMessageBox::critical(0, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}

//SLOT
void Gui_Groups::searchGroup() {
    newbox->hide();
    showgrp->show();
    newpost->show();
    post->show();
    memlbl->show();
    QString name = search->text();
    try {
        Group g = _client->findGroup(name.toStdString());
        admin = QString::fromStdString(g.admin().login());
        createMemList(name.toStdString());
        memlist->show();
        memlist->setEnabled(false);
        if(admin == QString::fromStdString(_client->username().login()) && mbuttons[1]->isHidden() && mbuttons[2]->isHidden()) {
            mbuttons[1]->show();
            mbuttons[2]->show();
            mbuttons[3]->hide();
            mbuttons[4]->hide();
            memlist->setEnabled(true);
        }
        else {
            mbuttons[1]->hide();
            mbuttons[2]->hide();
            if(g.isMember(_client->username())) {
                mbuttons[3]->show();
                mbuttons[4]->hide();
            }
            else {
                mbuttons[3]->hide();
                mbuttons[4]->show();
            }
        }
        list<Post*> p = _client->listPostFromGroup(g);
        int num = p.size();
        QString output = "<h1>" + name + "</h1><h4>Admin: <span style='font-weight:400'>" + admin + "</span></h4><h5>" + desc + "</h5>";
        if(!p.empty()) {
            output.append(QString("<h2>Posts (%1):</h2>").arg(num));
            for(list<Post*>::iterator it = p.begin(); it != p.end(); ++it)
                output.append(QString("<h5>Author: <span style='font-weight:400;font-size:10px'>" + QString::fromStdString((*it)->author().login()) + "</span></h5><p style='font-weight:400;font-size:11px;'>" + QString::fromStdString((*it)->content()) + "</p><hr>"));
        }
        showgrp->setInfo1(name);
        showgrp->setInfo2(admin);
        showgrp->setHtml(output);
    }catch(Error e) {
        QMessageBox::critical(0, "An error occoured", QString::fromStdString(e.errorMessage()));
        return;
    }
}

//SLOT
void Gui_Groups::deleteGroup() {
    QString name = showgrp->info1();
    try {
        _client->deleteGroup(name.toStdString());
        _client->save();
        emit created(1);
    }catch(Error e) {
        QMessageBox::critical(0, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}

//SLOT
void Gui_Groups::clearPosts() {
    QString name = showgrp->info1();
    try {
        _client->clearPosts(name.toStdString());
        _client->save();
        emit created(0);
    }catch(Error e) {
        QMessageBox::critical(0, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}

//SLOT
void Gui_Groups::leaveGroup() {
    QString name = showgrp->info1();
    try {
        _client->leaveGroup(name.toStdString());
        emit created(0);
    }catch(Error e) {
        QMessageBox::critical(0, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}

//SLOT
void Gui_Groups::kickMember() {
    name = showgrp->info1();
    try {
        _client->kickMember(name.toStdString(), _selected.toStdString());
        emit created(0);
    }catch(Error e) {
        QMessageBox::critical(0, "Error occoured", QString::fromStdString(e.errorMessage()));
    }
}

//SLOT
void Gui_Groups::memListMenu(const QPoint& pos) {
    if(memlist->item(memlist->indexAt(pos).row())) {
        QPoint globalPos = memlist->mapToGlobal(pos);    // Map the global position to the userlist
        QModelIndex t = memlist->indexAt(pos);
        memlist->item(t.row())->setSelected(true);           // even a right click will select the item
        _selected = memlist->item(t.row())->data(Qt::UserRole + 2).toString();
        QMenu myMenu;
        myMenu.addAction("Kick member", this, SLOT(kickMember()));
        myMenu.exec(globalPos);
    }
}