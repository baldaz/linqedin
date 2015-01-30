#include "gui_groups.h"

Gui_Groups::Gui_Groups(LinqClient* c, QWidget* parent) : _client(c), QGridLayout(parent) {
    Gui_Avatar* portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    QPushButton* create = new QPushButton("CREATE");
    QLabel* title = new QLabel("NEW GROUP");
    showgrp = new Gui_DisplayInfo;
    newpost = new QTextEdit;
    newgrp = new QLineEdit;
    search = new QLineEdit;
    newbox = new QGroupBox;

    grpname = new QLineEdit;
    newgrplayout = new QFormLayout;
    newgrplayout->setSpacing(15);
    newgrplayout->addRow(title);
    newgrplayout->addRow("Group name:", grpname);
    newgrplayout->addRow("Group description:", newgrp);
    newgrplayout->addRow(create);

    newbox->setLayout(newgrplayout);
    newbox->hide();

    search->setPlaceholderText("Search group..");
    search->hide();
    if(_client->level() >= business) {
        QStringList completions;
        list<Group*> grps = _client->listAllGroups();
        if(!grps.empty()) {
            list<Group*>::iterator it = grps.begin();
            for(; it != grps.end(); ++it)
                completions.push_back(QString::fromStdString((*it)->name()));
        }
        QCompleter* completer = new QCompleter(completions);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        search->setCompleter(completer);
        search->setClearButtonEnabled(true);
        search->show();
        connect(search,  SIGNAL(returnPressed()), this, SLOT(searchGroup()));
    }

    post = new QPushButton("POST");
    grplist = new QListWidget;
    QLabel* grplbl = new QLabel("Groups");
    grplbl->setMaximumSize(120,20);
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

    frm->addRow(mbuttons[0]);
    frm->addRow(mbuttons[3]);
    frm->addRow(mbuttons[1]);
    frm->addRow(mbuttons[2]);

    connect(mbuttons[0], SIGNAL(clicked()), this, SLOT(showNewGroup()));
    connect(create, SIGNAL(clicked()), this, SLOT(newGroup()));

    mbuttons[0]->hide();
    mbuttons[1]->hide();
    mbuttons[2]->hide();
    mbuttons[3]->hide();
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

    list<Group*> g = _client->listGroups();
    QString out;
    for(list<Group*>::iterator it = g.begin(); it != g.end(); ++it) {
       QListWidgetItem* item = new QListWidgetItem;
       item->setData(Qt::DisplayRole, QString::fromStdString((*it)->name()));
       item->setData(Qt::UserRole + 1, QString::fromStdString((*it)->admin().login()));
       item->setData(Qt::UserRole + 2, QString::fromStdString((*it)->description()));
       grplist->addItem(item);
    }

    // addWidget(tbar, 5, 1, 1, 1);
    addWidget(newbox, 0, 1, 1, 1);
    addWidget(portrait, 0, 0, 1, 1, Qt::AlignTop);
    addWidget(showgrp, 0, 1, 3, 1);
    addLayout(frm, 0, 2, 1, 1, Qt::AlignRight);
    addWidget(newpost, 3, 1, 2, 3);
    addWidget(post, 4, 4, 1, 1, Qt::AlignRight);
    addWidget(grplbl, 1, 0, 1, 1);
    addWidget(grplist, 2, 0, 1, 1);
    addWidget(search, 4, 0, 1, 1);
    setRowStretch(0, 0);
    setRowStretch(1, 10);
    setColumnStretch(0, 1);
    setColumnStretch(1, 5);
    // setColumnStretch(2, 3);
    connect(grplist, SIGNAL(clicked(QModelIndex)), this, SLOT(showGroup()));
    connect(post, SIGNAL(clicked()), this, SLOT(sendPost()));
}

//SLOT
void Gui_Groups::showGroup() {
    newbox->hide();
    showgrp->show();
    newpost->show();
    post->show();
    name = grplist->currentItem()->data(Qt::DisplayRole).toString();
    desc = grplist->currentItem()->data(Qt::UserRole + 2).toString();
    admin = grplist->currentItem()->data(Qt::UserRole + 1).toString();
    if(admin == QString::fromStdString(_client->username().login()) && mbuttons[1]->isHidden() && mbuttons[2]->isHidden()) {
        mbuttons[1]->show();
        mbuttons[2]->show();
        mbuttons[3]->hide();
    }
    else {
        mbuttons[1]->hide();
        mbuttons[2]->hide();
        mbuttons[3]->show();
    }
    Group g(Username(admin.toStdString(), ""), name.toStdString());
    list<Post*> p = _client->listPostFromGroup(g);
    int num = _client->postNumberFromGroup(g);
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
    newbox->show();
}

//SLOT
void Gui_Groups::newGroup() {
    QString name = grpname->text();
    QString desc = newgrp->text();
    Group* g = new Group(_client->username(), name.toStdString(), desc.toStdString());
    _client->createNewGroup(*g);
    _client->save();
}

//SLOT
void Gui_Groups::addGroup() {
    QString name = showgrp->info1();
    QString admin = showgrp->info2();
    _client->addGroup(name.toStdString(), admin.toStdString());
}

//SLOT
void Gui_Groups::searchGroup() {
    newbox->hide();
    showgrp->show();
    newpost->show();
    post->show();
    QString name = search->text();
    Group g = _client->findGroup(name.toStdString());
    admin = QString::fromStdString(g.admin().login());
    if(admin == QString::fromStdString(_client->username().login()) && mbuttons[1]->isHidden() && mbuttons[2]->isHidden()) {
        mbuttons[1]->show();
        mbuttons[2]->show();
        mbuttons[3]->hide();
    }
    else {
        mbuttons[1]->hide();
        mbuttons[2]->hide();
        mbuttons[3]->show();
    }
    list<Post*> p = _client->listPostFromGroup(g);
    int num = _client->postNumberFromGroup(g);
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