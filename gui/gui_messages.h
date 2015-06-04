#ifndef GUI_MESSAGES_H
#define GUI_MESSAGES_H

#include "linqclient.h"
#include "gui_listdelegate.h"
#include "gui_avatar.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QTextBrowser>
#include <QTabWidget>

class Gui_Messages : public QGridLayout {
    Q_OBJECT
private:
    LinqClient* _client;
    list<SmartPtr<Message> > inm;
    QListWidget* _listIn;
    QListWidget* _listOut;
    QTextBrowser* _output;
    QPushButton* box;
    QLineEdit* edt1;
    QLineEdit* edt2;
    QTextEdit* te;
    int mexcount;
    QString rcv;
    Message* _m_sel;

    QString unreadMex(int);
    void createLists();
    bool eventFilter(QObject*, QEvent*);
public:
    explicit Gui_Messages(LinqClient*, QWidget* parent = 0);
signals:
    void modified();
public slots:
    void viewInMailBody();
    void viewOutMailBody();
    void sendMail();
    void refreshMessages();
    void delMenu(const QPoint&);
    void deleteMessage();
};
#endif