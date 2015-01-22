#ifndef GUI_SETTINGS_H
#define GUI_SETTINGS_H

#include <QGridLayout>
#include <QFormLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include "gui_avatar.h"
#include "linqclient.h"

class Gui_Settings : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
    QListWidget* skills;
    QListWidget* inters;
public:
    Gui_Settings(LinqClient*, QWidget* = 0);
public slots:
    void skillsMenu(const QPoint&);
    void interestsMenu(const QPoint&);
};
#endif