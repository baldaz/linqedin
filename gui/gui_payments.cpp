#include "gui_payments.h"

Gui_Payments::Gui_Payments(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    Gui_Avatar* avatar = new Gui_Avatar(QString::fromStdString(_client->avatar()));

    _list = new QListWidget;
    _list->setItemDelegate(new PaymentsDelegate(_list));
    QListWidgetItem* item = new QListWidgetItem;
    QListWidgetItem* item2 = new QListWidgetItem;
    QListWidgetItem* item3 = new QListWidgetItem;
    QListWidgetItem* item4 = new QListWidgetItem;

    item->setData(Qt::DisplayRole, "12-12-2014");
    item->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
    item->setData(Qt::UserRole + 4, "12-01-2015");
    item->setData(Qt::UserRole + 1, "expired");
    item->setData(Qt::UserRole + 2, "€ 29.90");
    item->setData(Qt::UserRole + 3, "Executive");

    item2->setData(Qt::DisplayRole, "12-09-2014");
    item2->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
    item2->setData(Qt::UserRole + 4, "12-01-2015");
    item2->setData(Qt::UserRole + 1, "expired");
    item2->setData(Qt::UserRole + 2, "€ 29.90");
    item2->setData(Qt::UserRole + 3, "Executive");

    item3->setData(Qt::DisplayRole, "02-08-2014");
    item3->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
    item3->setData(Qt::UserRole + 4, "12-01-2015");
    item3->setData(Qt::UserRole + 1, "expired");
    item3->setData(Qt::UserRole + 2, "€ 29.90");
    item3->setData(Qt::UserRole + 3, "Executive");

    item4->setData(Qt::DisplayRole, "12-11-2014");
    item4->setData(Qt::DecorationRole, QPixmap("img/envelope12.png"));
    item4->setData(Qt::UserRole + 4, "12-01-2015");
    item4->setData(Qt::UserRole + 1, "pending");
    item4->setData(Qt::UserRole + 2, "€ 29.90");
    item4->setData(Qt::UserRole + 3, "Executive");

    _list->addItem(item);
    _list->addItem(item2);
    _list->addItem(item3);
    _list->addItem(item4);

    addWidget(avatar, 0, 0, 1, 1, Qt::AlignTop);
    addWidget(_list, 0, 1, -1, -1);
    setColumnStretch(0, 1);
    setColumnStretch(1, 5);
    setColumnStretch(2, 2);
    setRowStretch(0, 0);
    setRowStretch(1, 0);
    setRowStretch(2, 10);
}