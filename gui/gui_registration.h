#ifndef GUI_REGISTRATION_H
#define GUI_REGISTRATION_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QCalendarWidget>
#include "linqadmin.h"

class Gui_Registration : public QWidget {
    Q_OBJECT
private:
    enum {edit = 15};
    QLineEdit* edt[edit];
    QTextEdit* bio;
    QCalendarWidget* calendar;
    QVBoxLayout* _mainLayout;
    QGroupBox* _registration;
    QGroupBox* _mandatory;
    LinqAdmin* _admin;
    QString uname;

    void createForm();
public:
    Gui_Registration(QWidget* parent = 0);
signals:
    void userCreated(bool);
public slots:
    void submitData();
    void proceed(bool);
};
#endif