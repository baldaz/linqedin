#ifndef GUI_PAYMENTS_H
#define GUI_PAYMENTS_H

#include <QGridLayout>
#include "gui_avatar.h"
#include "linqclient.h"

class Gui_Payments : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
public:
    Gui_Payments(LinqClient*, QWidget* parent = 0);
};
#endif