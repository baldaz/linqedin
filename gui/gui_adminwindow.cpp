#include "gui_adminwindow.h"
#include "linqadmin.h"

Gui_AdminWindow::Gui_AdminWindow(QWidget* parent) : QWidget(parent) {
    _admin = new LinqAdmin;
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.95);
    _mainLayout = new QVBoxLayout;
    _userList = new QListWidget;
    _userInfo = new QTextEdit;
    QPushButton* quit = new QPushButton;
    quit->setIcon(QPixmap("img/prohibited1.png"));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    list<SmartPtr<User> > l = _admin->listUsers();
    for(list<SmartPtr<User> >::iterator it = l.begin(); it != l.end(); ++it) {
        UserInfo* b = dynamic_cast<UserInfo*> ((*it)->account()->info());
        QListWidgetItem* item = new QListWidgetItem;
        item->setData(Qt::DisplayRole, QString::fromStdString((*it)->account()->username().login()));
        item->setData(Qt::UserRole + 1, QString::fromStdString(b->printHtml()));
        _userList->addItem(item);
    }
    connect(_userList, SIGNAL(clicked(QModelIndex)), this, SLOT(showUser()));
    _mainLayout->addWidget(quit, 0, Qt::AlignTop | Qt::AlignRight);
    _mainLayout->addWidget(_userList, 0);
    _mainLayout->addWidget(_userInfo, 1);
    setLayout(_mainLayout);
    move(100, 30);
    resize(1150, 720);
}

//SLOT
void Gui_AdminWindow::showUser() {
    QString _sel = _userList->currentItem()->data(Qt::UserRole + 1).toString();
    _userInfo->setHtml(_sel);
}