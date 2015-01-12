// #include <QApplication>
// #include <QFont>
// #include <QPushButton>
// #include <QWidget>
#include <iostream>
// #include "account.h"
// #include "linqnet.h"
// #include "linqdb.h"
#include "linqclient.h"
#include "linqadmin.h"
#include "gui/gui_widget.h"
#include "gui/gui_userwindow.h"
#include <QPalette>
#include <QStyleFactory>

using std::cout;
using std::endl;

int main(int argc, char**argv) {
    // LinqAdmin* admin = new LinqAdmin();
    // // Info* info = new UserInfo();
    // Username* ser = new Username("ser", "wword");
    // // admin->alterSubscription(ser, business);
    // // Account* a = new Account(info , ser, basic);
    // // LinqNet* inet = new LinqNet();
    // // User* prova = new BasicUser(a, inet);
    // admin->removeUser(Username("ser", "wword"));
    // // admin->insertUser(prova);
    // cout << endl << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    // Username* user = new Username("Baldaz", "qwerty");
    // LinqClient* client = new LinqClient(Username("Baldaz", "qwerty"));
    // cout << client->similarity(Username("Sara87", "sara"));
    // cout << client->find("Atos");
    // Username* sara = new Username("Sara87", "sara");
    // // Username* ser = new Username("ser", "wword");
    // client->addContact(sara);
    // // client->addContact(sara);
    // // client->addContact(ser);
    // client->removeContact(sara);
    // Experience* frm = new Instruction("ITIS F.Severi", "2002", "2007");
    // // client->addFormation(frm);
    // client->displayProfile();
    // client->find();
    // // client->save();
    // // delete ser, user, sara, client;
    // cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    QApplication app(argc, argv);
    // Gui_Widget window;
    Gui_UserWindow window;
    QFile File("style/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
    // window.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    window.setStyleSheet("border: none");
    window.setWindowTitle("");
    window.show();
    return app.exec();
    // return 0;
}