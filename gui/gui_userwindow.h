#ifndef GUI_USERWINDOW_H
#define GUI_USERWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QStackedLayout>
#include "gui_overview.h"
#include "gui_messages.h"


class Gui_UserWindow : public QWidget {
    Q_OBJECT
public:
    explicit Gui_UserWindow(QWidget* parent = 0);

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
private:
    QStackedLayout* _layoutStack;
    QVBoxLayout* _mainLayout;
    QPoint mpos;
    QGroupBox* horizontalGroupBox;
    QGroupBox* overviewGroupBox;
    QGroupBox* messagesGroupBox;
    QGroupBox* paymentsGroupBox;
    enum {NumButtons = 5};
    QPushButton* buttons[NumButtons];
    Gui_Overview* _layout;
    Gui_Messages* _mex;

    void createHorizontalGroupBox();
    void createOverview();
    void createMessages();
    // bool eventFilter(QObject*, QEvent*);

signals:

public slots:
    void overview();
    void messages();
};

#endif