#ifndef GUI_MODPOPUP_H
#define GUI_MODPOPUP_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QBitmap>
#include <QPainter>

class Gui_ModPopup : public QDialog {
    Q_OBJECT
private:
    QVBoxLayout* _mainLayout;
    QLineEdit* edt;
    void resizeEvent(QResizeEvent*);
public:
    Gui_ModPopup(QWidget* parent = 0);
};
#endif