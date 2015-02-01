#ifndef GUI_ADMINWINDOW_H
#define GUI_ADMINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class Gui_AdminWindow : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* _mainLayout;
public:
    Gui_AdminWindow(QWidget* =0);
};
#endif