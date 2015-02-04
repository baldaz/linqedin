#ifndef GUI_ADMINWINDOW_H
#define GUI_ADMINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QListWidgetItem>

class LinqAdmin;

class Gui_AdminWindow : public QWidget {
    Q_OBJECT
private:
    LinqAdmin* _admin;
    QVBoxLayout* _mainLayout;
    QListWidget* _userList;
    QTextEdit* _userInfo;
public:
    Gui_AdminWindow(QWidget* parent = 0);
public slots:
    void showUser();
};
#endif