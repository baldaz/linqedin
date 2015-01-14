#include "gui_messages.h"

Gui_Messages::Gui_Messages(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    _list = new Gui_ListMessages(parent);
    Gui_Avatar* portrait = new Gui_Avatar(QString::fromStdString(_client->avatar()));

    // portrait->setStyleSheet("background:#fff");
    // _list->setStyleSheet("background:#ff0");
    this->addWidget(portrait, 0, 0, 1, 1, Qt::AlignCenter);
    this->addWidget(_list, 0, 1, 3, 1);
    this->setColumnStretch(0, 1);
    this->setColumnStretch(1, 5);
    this->setColumnStretch(2, 2);
    // this->setColumnStretch(3, 2);
    this->setRowStretch(0, 0);
    this->setRowStretch(1, 0);
    this->setRowStretch(2, 10);

    QLabel* ne = new QLabel("<h2>New message</h2>");
    this->addWidget(ne, 1, 0, 1, -1, Qt::AlignCenter);
    Gui_NewMessage* newmex = new Gui_NewMessage(parent);
    this->addWidget(newmex, 2, 0, -1, -1);
}