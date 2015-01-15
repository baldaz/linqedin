#include "gui_settings.h"

Gui_Settings::Gui_Settings(LinqClient* cli, QWidget* parent) : _client(cli), QGridLayout(parent) {
    Gui_Avatar* avatar = new Gui_Avatar(QString::fromStdString(_client->avatar()));
    addWidget(avatar, 0, 0, 1, 1, Qt::AlignTop);
    setColumnStretch(0, 1);
    setColumnStretch(1, 5);
    setColumnStretch(2, 2);
    setRowStretch(0, 0);
    setRowStretch(1, 0);
    setRowStretch(2, 10);
}