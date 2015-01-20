#ifndef GUI_LOGIN_H
#define GUI_LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QBitmap>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class Gui_Login : public QDialog {
    Q_OBJECT
public:
    Gui_Login(QWidget* = 0);
    void resizeEvent(QResizeEvent*);
};
#endif