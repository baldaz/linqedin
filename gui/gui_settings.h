#ifndef GUI_SETTINGS_H
#define GUI_SETTINGS_H

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include "gui_avatar.h"
#include "linqclient.h"

class Gui_Settings : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
public:
    Gui_Settings(LinqClient*, QWidget* = 0);
};
#endif