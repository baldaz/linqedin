#ifndef GUI_LOGIN_H
#define GUI_LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QBitmap>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include "gui_userwindow.h"
#include "gui_adminwindow.h"
#include "gui_registration.h"

class Gui_Login : public QDialog {
    Q_OBJECT
private:
    Gui_UserWindow window;
    Gui_Registration reg;
    Gui_AdminWindow admwin;
    QDialogButtonBox* buttonBox;

    void resizeEvent(QResizeEvent*);
public:
    Gui_Login(QWidget* = 0);
public slots:
    void onClicked(QAbstractButton*);
};
#endif