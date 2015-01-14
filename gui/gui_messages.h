#ifndef GUI_MESSAGES_H
#define GUI_MESSAGES_H

#include "gui_listmessages.h"
#include "gui_newmessage.h"
#include <QGridLayout>
#include <QLabel>
#include <QBitmap>
#include <QPainter>

class Gui_Messages : public QGridLayout {
    Q_OBJECT
private:
    Gui_ListMessages* _list;
public:
    Gui_Messages(QWidget* parent = 0);
signals:
public slots:
};
#endif