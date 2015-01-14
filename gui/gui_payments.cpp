#include "gui_payments.h"

Gui_Payments::Gui_Payments(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    Gui_Avatar* avatar = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    addWidget(avatar, 0, 0, 1, 1, Qt::AlignCenter);
    setColumnStretch(0, 1);
    setColumnStretch(1, 5);
    setColumnStretch(2, 2);
    setRowStretch(0, 0);
    setRowStretch(1, 0);
    setRowStretch(2, 10);
}