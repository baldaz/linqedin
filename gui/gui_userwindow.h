#ifndef GUI_USERWINDOW_H
#define GUI_USERWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include "gui_overview.h"

class Gui_UserWindow : public QWidget {
    Q_OBJECT
public:
    Gui_UserWindow(QWidget* parent = 0);

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
private:
    QPoint mpos;
    QGroupBox* horizontalGroupBox;
    QGroupBox* gridGroupBox;
    enum {NumButtons = 5};
    QPushButton* buttons[NumButtons];
    Gui_Overview* layout;

    void createHorizontalGroupBox();
    void createGridGroupBox();

signals:

public slots:
    void overview();

};

#endif