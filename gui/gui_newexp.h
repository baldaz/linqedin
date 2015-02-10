#ifndef GUI_NEWEXP
#define GUI_NEWEXP

#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QCalendarWidget>
#include <QMessageBox>
#include "linqclient.h"

class Gui_NewExp : public QDialog {
    Q_OBJECT
private:
    LinqClient* _client;
    QLineEdit* edt[2];
    QCalendarWidget* from;
    QCalendarWidget* to;
    QRadioButton* rb[2];
public:
    Gui_NewExp(LinqClient*, QWidget* parent = 0);
signals:
    void modified();
public slots:
    void insert();
};
#endif