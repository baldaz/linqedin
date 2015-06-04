#ifndef GUI_USERWINDOW_H
#define GUI_USERWINDOW_H

#include <QApplication>
#include <QWidget>
// #include <QMouseEvent>
// #include <QPushButton>
#include <QGroupBox>
// #include <QGridLayout>
#include <QStackedLayout>
#include "gui_overview.h"
#include "gui_messages.h"
#include "gui_settings.h"
#include "gui_statistics.h"
#include "gui_groups.h"

class Gui_UserWindow : public QWidget {
    Q_OBJECT
public:
    explicit Gui_UserWindow(LinqClient* cli = 0, QWidget* parent = 0);
    void setClient(LinqClient*);
protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    bool eventFilter(QObject*, QEvent*);
private:
    QStackedLayout* _layoutStack;
    QVBoxLayout* _mainLayout;
    QPoint mpos;
    QGroupBox* horizontalGroupBox;
    QGroupBox* overviewGroupBox;
    QGroupBox* messagesGroupBox;
    QGroupBox* paymentsGroupBox;
    QGroupBox* settingsGroupBox;
    QGroupBox* groupsGroupBox;
    enum {NumButtons = 6};
    QPushButton* buttons[NumButtons];
    Gui_Overview* _layout;
    Gui_Settings* _set;
    Gui_Messages* _mex;
    Gui_Statistics* _pay;
    Gui_Groups* _grp;
    LinqClient* user;
    void createHorizontalGroupBox();
    void createOverview();
    void createMessages();
    void createPayments();
    void createSettings();
    void createGroups();

    void mouseDoubleClickEvent(QMouseEvent*);
    void closeEvent(QCloseEvent*);
signals:
    void logOut();
    void ext();
public slots:
    void overview();
    void messages();
    void settings();
    void payments();
    void groups();
    void logout();
    void exit();
};

#endif