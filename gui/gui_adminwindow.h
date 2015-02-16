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
#include <QComboBox>
#include <map>
#include <string>

using std::map;
using std::string;

class LinqAdmin;
class QToolBar;
class Gui_DisplayInfo;

class Gui_AdminWindow : public QWidget {
    Q_OBJECT
private:
    LinqAdmin* _admin;
    QListWidget* _userList;
    Gui_DisplayInfo* _userInfo;
    QLineEdit* edt[5];
    QToolBar* tbar;
    QComboBox* _level;
    map<string, string> res;
    map<string, string>::iterator it;
    QString _cnt;

    void createUserList();
    void createSearch();
public:
    Gui_AdminWindow(QWidget* parent = 0);
signals:
    void modified();
public slots:
    void startSearch();
    void showSearchResult();
    void nextResult();
    void showUser();
    void addUser();
    void removeUser();
    void upgradeUser();
    void refreshLists();
};
#endif