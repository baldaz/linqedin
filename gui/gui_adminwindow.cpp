#include "gui_adminwindow.h"
#include "gui_displayinfo.h"
#include "linqadmin.h"
#include <QLabel>
#include <QAction>
#include <QGroupBox>
#include <QToolBar>
#include <QToolButton>
#include <QCompleter>

Gui_AdminWindow::Gui_AdminWindow(QWidget* parent) : QWidget(parent) {
    _admin = new LinqAdmin;
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    setStyleSheet(QStringLiteral("QGroupBox{border:1px solid #000;border-radius:15px;} QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center;top:-6px;}"));
    QLabel* linkLabel = new QLabel("User list");
    QPushButton* add = new QPushButton("Insert");
    add->setIcon(QPixmap("img/add70.png"));
    linkLabel->setMaximumSize(120,20);
    _level = new QComboBox;
    _level->addItem("Basic", QVariant(0));
    _level->addItem("Business", QVariant(1));
    _level->addItem("Executive", QVariant(2));
    tbar = new QToolBar;
    QToolButton* rm = new QToolButton(tbar);
    QToolButton* ok = new QToolButton(tbar);
    rm->setIcon(QPixmap("img/cross108.png"));
    rm->setToolTip("Remove this user from Linqedin");
    ok->setIcon(QPixmap("img/check67.png"));
    ok->setToolTip("Upgrade this user");
    connect(rm, SIGNAL(clicked()), this, SLOT(removeUser()));
    connect(add, SIGNAL(clicked()), this, SLOT(addUser()));
    tbar->addWidget(rm);
    tbar->addWidget(ok);
    tbar->actions().at(1)->setVisible(false);
    tbar->hide();
    QGroupBox* _admbox = new QGroupBox;
    QGroupBox* _admins = new QGroupBox;
    for(int i = 0; i < 5; ++i)
        edt[i] = new QLineEdit;
    // search bar
    edt[4]->setPlaceholderText("Search user");
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

    QVBoxLayout* _mainLayout = new QVBoxLayout;
    _mainLayout->setSpacing(20);
    QGridLayout* _layout = new QGridLayout;
    QGridLayout* _inslay = new QGridLayout;
    QFormLayout* frmsx = new QFormLayout;
    QFormLayout* frmdx = new QFormLayout;
    _userList = new QListWidget;

    _userInfo = new Gui_DisplayInfo;
    _userInfo->setReadOnly(true);
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    createUserList();
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    _layout->addWidget(linkLabel, 0, 0, 1, 1);
    _layout->addWidget(_userInfo, 0, 1, 2, 1);
    _layout->addWidget(_userList, 1, 0, 1, 1);
    _layout->addWidget(edt[4], 2, 0, 1, 1);
    _layout->addWidget(tbar, 2, 1, 1, 1, Qt::AlignCenter);
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

void Gui_AdminWindow::createUserList() {
    list<SmartPtr<User> > l = _admin->listUsers();
    for(list<SmartPtr<User> >::iterator it = l.begin(); it != l.end(); ++it) {
        QListWidgetItem* item = new QListWidgetItem;
        item->setData(Qt::DisplayRole, QString::fromStdString((*it)->account()->username().login()));
        if(!(*it)->account()->lastPayment()->approvation()) {
            item->setData(Qt::DecorationRole, QPixmap("img/arrow106.png"));
            item->setData(Qt::UserRole + 3, 1);
        }
        else
            item->setData(Qt::DecorationRole, QPixmap("img/profile11.png"));
        item->setData(Qt::UserRole + 1, QString::fromStdString((*it)->account()->info()->printHtml()));
        item->setData(Qt::UserRole + 2, QString::fromStdString((*it)->account()->username().login()));
        _userList->addItem(item);
    }
    connect(_userList, SIGNAL(clicked(QModelIndex)), this, SLOT(showUser()));
}

//SLOT
void Gui_AdminWindow::showUser() {
    QString _sel = _userList->currentItem()->data(Qt::UserRole + 1).toString();
    _userInfo->setHtml(_sel);
    _userInfo->setInfo1(_userList->currentItem()->data(Qt::UserRole + 2).toString());
    if(tbar->isHidden()) tbar->show();
    if(_userList->currentItem()->data(Qt::UserRole + 3) == 1) tbar->actions().at(1)->setVisible(true);
    else tbar->actions().at(1)->setVisible(false);
}

//SLOT
void Gui_AdminWindow::addUser() {
    QString name = edt[0]->text();
    QString surn = edt[1]->text();
    QString uname = edt[2]->text();
    QString passw = edt[3]->text();
    int level = _level->itemData(_level->currentIndex()).toInt();

    std::cout<< level << std::endl;
    QMap<string, string> map;
    map.insert("name", name.toStdString());
    map.insert("surname", surn.toStdString());
    _admin->insertUser(uname.toStdString(), passw.toStdString(), map.toStdMap());
}

//SLOT
void Gui_AdminWindow::removeUser() {
    // int row = _userList->currentRow() - 1;
    _admin->removeUser(Username(_userInfo->info1().toStdString(), ""));
    // _userList->setCurrentItem(_userList->item(row));
    // showUser();
    emit modified();
}

//SLOT
void Gui_AdminWindow::refreshLists() {
    _userList->clear();
    createUserList();
}