#ifndef GUI_LISTMESSAGES_H
#define GUI_LISTMESSAGES_H

#include <QTableView>
#include "messagemodel.h"

class Gui_ListMessages : public QTableView {
    Q_OBJECT
private:
public:
    Gui_ListMessages(QWidget* parent = 0);
signals:
public slots:
};
#endif