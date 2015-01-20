#ifndef GUI_PAYMENTS_H
#define GUI_PAYMENTS_H

#include <QGridLayout>
#include <QTextBrowser>
#include <QListWidget>
#include "gui_avatar.h"
#include "linqclient.h"
// #include "gui_paymentsdelegate.h"

class Gui_Payments : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
    QTextBrowser* _list;
public:
    Gui_Payments(LinqClient*, QWidget* parent = 0);
};
#endif