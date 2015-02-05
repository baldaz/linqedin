#ifndef GUI_ADMINWINDOW_H
#define GUI_ADMINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>

class LinqAdmin;
class QToolBar;
class Gui_DisplayInfo;

class Gui_AdminWindow : public QWidget {
    Q_OBJECT
private:
    LinqAdmin* _admin;
    QListWidget* _userList;
    Gui_DisplayInfo* _userInfo;
    QLineEdit* edt[4];
    QToolBar* tbar;

    void createUserList();
public:
    Gui_AdminWindow(QWidget* parent = 0);
signals:
    void modified();
public slots:
    void showUser();
    void removeUser();
    void refreshLists();
};
#endif