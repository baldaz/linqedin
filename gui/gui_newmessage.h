#ifndef GUI_NEWMESSAGE_H
#define GUI_NEWMESSAGE_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class Gui_NewMessage : public QWidget {
public:
    Gui_NewMessage(QWidget *parent = 0);
};

#endif