#include "gui_messages.h"

Gui_Messages::Gui_Messages(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    // _list = new Gui_ListMessages(parent);
    Gui_Avatar* portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    _list = new QListWidget;
    _list->setItemDelegate(new ListDelegate(_list));
    _output = new QTextBrowser;
    QListWidgetItem* item = new QListWidgetItem;
    QListWidgetItem* item2 = new QListWidgetItem;
    QListWidgetItem* item3 = new QListWidgetItem;
    QListWidgetItem* item4 = new QListWidgetItem;

    item->setData(Qt::DisplayRole, "A new dawn");
    // item->setData(Qt::DecorationRole, QPixmap("img/link19.png"));
    item->setData(Qt::UserRole + 1, "From: Pablito 12-12-2014");
    item->setData(Qt::UserRole + 2, "Lorem ipsum dolorem sit amet");
    item->setData(Qt::UserRole + 3, 1);
    item2->setData(Qt::DisplayRole, "2nd try!");
    item2->setData(Qt::UserRole + 1, "From: Atilio 12-09-2014");
    item2->setData(Qt::UserRole + 2, "Lorem ipsum dolorem sit amet");
    item2->setData(Qt::UserRole + 3, 1);
    item3->setData(Qt::DisplayRole, "Connection request");
    item3->setData(Qt::UserRole + 1, "From: Andrea 02-08-2014");
    item3->setData(Qt::UserRole + 2, "Lorem ipsum dolorem sit amet");
    item3->setData(Qt::UserRole + 3, 0);
    item4->setData(Qt::DisplayRole, "Ok! fine!");
    item4->setData(Qt::UserRole + 1, "From: ser 12-11-2014");
    item4->setData(Qt::UserRole + 2, "Lorem ipsum dolorem sit amet");
    item4->setData(Qt::UserRole + 3, 1);
    _list->addItem(item);
    _list->addItem(item2);
    _list->addItem(item3);
    _list->addItem(item4);

    // portrait->setStyleSheet("background:#fff");
    // _list->setStyleSheet("background:#ff0");
    this->addWidget(portrait, 0, 0, 1, 1, Qt::AlignTop);
    this->addWidget(_list, 0, 1, 1, 1);
    addWidget(_output, 0, 2, 1, -1);
    this->setColumnStretch(0, 1);
    this->setColumnStretch(1, 2);
    this->setColumnStretch(2, 4);
    // this->setColumnStretch(3, 2);
    this->setRowStretch(0, 0);
    this->setRowStretch(1, 0);
    this->setRowStretch(2, 10);

    QLabel* ne = new QLabel("<h2>New message</h2>");
    this->addWidget(ne, 1, 0, 1, -1, Qt::AlignCenter);
    Gui_NewMessage* newmex = new Gui_NewMessage(parent);
    this->addWidget(newmex, 2, 0, 3, -1);
    connect(_list, SIGNAL(clicked(QModelIndex)), this, SLOT(viewMessageBody()));
}

void Gui_Messages::viewMessageBody() {
    QString sel = _list->currentItem()->data(Qt::UserRole + 2).toString();
    _output->setHtml(sel);
}