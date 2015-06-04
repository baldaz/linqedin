#ifndef GUI_BILL_H
#define GUI_BILL_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include "linqclient.h"

class Gui_Bill : public QDialog {
    Q_OBJECT
private:
    LinqClient* _client;
    QLineEdit* edt[2];
    privLevel _level;
public:
    Gui_Bill(LinqClient*, QWidget* parent = 0);
    void setLevel(privLevel);
public slots:
    void confirm();
};
#endif